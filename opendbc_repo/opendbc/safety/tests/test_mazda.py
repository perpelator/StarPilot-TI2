#!/usr/bin/env python3
import unittest

from opendbc.car.structs import CarParams
from opendbc.safety.tests.libsafety import libsafety_py
import opendbc.safety.tests.common as common
from opendbc.safety.tests.common import CANPackerSafety, make_msg

# safetyParam flags, see MazdaSafetyFlags in car/mazda/values.py
GEN1 = 1
GEN2 = 2
GEN3 = 4
TORQUE_INTERCEPTOR = 8
RADAR_INTERCEPTOR = 16
NO_FSC = 32
NO_MRCC = 64

RADAR_ADDRS = [0x21c, 0x21b, 0x361, 0x362, 0x363, 0x364, 0x365, 0x366, 0x499]


def _raw_msg(bus, addr, data):
  """Build a CAN packet from a {byte index: value} dict, for messages the DBCs don't describe the way panda parses them."""
  dat = bytearray(8)
  for i, v in data.items():
    dat[i] = v
  return libsafety_py.make_CANPacket(addr, bus, bytes(dat))


class TestMazdaSafety(common.CarSafetyTest, common.DriverTorqueSteeringSafetyTest):
  SAFETY_PARAM = GEN1

  TX_MSGS = [[0x243, 0], [0x09d, 0], [0x440, 0]]
  STANDSTILL_THRESHOLD = .1
  RELAY_MALFUNCTION_ADDRS = {0: (0x243, 0x440)}
  FWD_BLACKLISTED_ADDRS = {2: [0x243, 0x440]}

  MAX_RATE_UP = 10
  MAX_RATE_DOWN = 25
  MAX_TORQUE_LOOKUP = [0], [800]

  MAX_RT_DELTA = 300

  DRIVER_TORQUE_ALLOWANCE = 15
  DRIVER_TORQUE_FACTOR = 1

  # Mazda actually does not set any bit when requesting torque
  NO_STEER_REQ_BIT = True

  def setUp(self):
    self.packer = CANPackerSafety("mazda_2017")
    self.safety = libsafety_py.libsafety
    self.safety.set_safety_hooks(CarParams.SafetyModel.mazda, self.SAFETY_PARAM)
    self.safety.init_tests()

  def _torque_meas_msg(self, torque):
    values = {"STEER_TORQUE_MOTOR": torque}
    return self.packer.make_can_msg_safety("STEER_TORQUE", 0, values)

  def _torque_driver_msg(self, torque):
    values = {"STEER_TORQUE_SENSOR": torque}
    return self.packer.make_can_msg_safety("STEER_TORQUE", 0, values)

  def _torque_cmd_msg(self, torque, steer_req=1):
    values = {"LKAS_REQUEST": torque}
    return self.packer.make_can_msg_safety("CAM_LKAS", 0, values)

  def _speed_msg(self, speed):
    values = {"SPEED": speed}
    return self.packer.make_can_msg_safety("ENGINE_DATA", 0, values)

  def _user_brake_msg(self, brake):
    values = {"BRAKE_ON": brake}
    return self.packer.make_can_msg_safety("PEDALS", 0, values)

  def _user_gas_msg(self, gas):
    values = {"PEDAL_GAS": gas}
    return self.packer.make_can_msg_safety("ENGINE_DATA", 0, values)

  def _pcm_status_msg(self, enable):
    values = {"CRZ_ACTIVE": enable}
    return self.packer.make_can_msg_safety("CRZ_CTRL", 0, values)

  def _button_msg(self, resume=False, cancel=False):
    values = {
      "CAN_OFF": cancel,
      "CAN_OFF_INV": (cancel + 1) % 2,
      "RES": resume,
      "RES_INV": (resume + 1) % 2,
    }
    return self.packer.make_can_msg_safety("CRZ_BTNS", 0, values)

  def test_buttons(self):
    # only cancel allows while controls not allowed
    self.safety.set_controls_allowed(0)
    self.assertTrue(self._tx(self._button_msg(cancel=True)))
    self.assertFalse(self._tx(self._button_msg(resume=True)))

    # do not block resume if we are engaged already
    self.safety.set_controls_allowed(1)
    self.assertTrue(self._tx(self._button_msg(cancel=True)))
    self.assertTrue(self._tx(self._button_msg(resume=True)))

  def _toggle_aol(self, toggle_on):
    # CRZ_CTRL, CRZ_AVAILABLE is the main on button
    values = {"CRZ_AVAILABLE": 1 if toggle_on else 0}
    return self.packer.make_can_msg_safety("CRZ_CTRL", 0, values)


class TestMazdaTorqueInterceptorSafety(TestMazdaSafety):
  """GEN1 with the torque interceptor: driver torque comes from the interceptor on the aux bus, steering is also sent to it."""
  SAFETY_PARAM = GEN1 | TORQUE_INTERCEPTOR

  TX_MSGS = [[0x243, 0], [0x249, 1], [0x09d, 0], [0x440, 0]]

  def _torque_driver_msg(self, torque):
    values = {"TI_TORQUE_SENSOR": torque}
    return self.packer.make_can_msg_safety("TI_FEEDBACK", 1, values)

  def test_stock_torque_sensor_ignored(self):
    # the stock sensor on the main bus must not feed the driver torque measurement
    self._reset_torque_driver_measurement(0)
    values = {"STEER_TORQUE_SENSOR": 50}
    self._rx(self.packer.make_can_msg_safety("STEER_TORQUE", 0, values))
    self.assertEqual(0, self.safety.get_torque_driver_max())
    self.assertEqual(0, self.safety.get_torque_driver_min())

    self._rx(self._torque_driver_msg(50))
    self.assertEqual(50, self.safety.get_torque_driver_max())


class TestMazdaNoMrccSafety(TestMazdaSafety):
  """GEN1 without stock MRCC: cruise state is read from PEDALS instead of CRZ_CTRL."""
  SAFETY_PARAM = GEN1 | NO_MRCC

  def _user_brake_msg(self, brake):
    # brake and cruise state share PEDALS, keep cruise active so only the brake changes
    values = {"BRAKE_ON": brake, "ACC_ACTIVE": 1}
    return self.packer.make_can_msg_safety("PEDALS", 0, values)

  def _pcm_status_msg(self, enable):
    values = {"ACC_ACTIVE": enable}
    return self.packer.make_can_msg_safety("PEDALS", 0, values)

  def _toggle_aol(self, toggle_on):
    # acc_main_on is not tracked without CRZ_CTRL
    return None

  def test_crz_ctrl_ignored(self):
    # CRZ_CTRL must not engage controls when the cruise state comes from PEDALS
    values = {"CRZ_ACTIVE": 1}
    self._rx(self.packer.make_can_msg_safety("CRZ_CTRL", 0, values))
    self.assertFalse(self.safety.get_controls_allowed())


class TestMazdaRadarInterceptorSafety(TestMazdaNoMrccSafety):
  """GEN1 with the radar interceptor: openpilot sends the radar/cruise messages, so they are relay-checked and not forwarded."""
  SAFETY_PARAM = GEN1 | RADAR_INTERCEPTOR

  TX_MSGS = [[0x243, 0], [0x09d, 0], [0x440, 0], *[[addr, 0] for addr in RADAR_ADDRS]]
  RELAY_MALFUNCTION_ADDRS = {0: (0x243, 0x440, *RADAR_ADDRS)}
  FWD_BLACKLISTED_ADDRS = {2: [0x243, 0x440, *RADAR_ADDRS]}


class TestMazdaTorqueAndRadarInterceptorSafety(TestMazdaRadarInterceptorSafety, TestMazdaTorqueInterceptorSafety):
  SAFETY_PARAM = GEN1 | TORQUE_INTERCEPTOR | RADAR_INTERCEPTOR

  TX_MSGS = [[0x243, 0], [0x249, 1], [0x09d, 0], [0x440, 0], *[[addr, 0] for addr in RADAR_ADDRS]]


class TestMazdaGen2Safety(common.CarSafetyTest, common.DriverTorqueSteeringSafetyTest):
  """GEN2 (2019+): torque is sent to the interceptor on the aux bus, ACC command is sent on the camera bus."""
  SAFETY_PARAM = GEN2

  TX_MSGS = [[0x249, 1], [0x220, 2]]
  RELAY_MALFUNCTION_ADDRS = {2: (0x220,)}
  FWD_BLACKLISTED_ADDRS = {0: [0x220]}

  # raw 16 bit speed, moving when > 10
  STANDSTILL_THRESHOLD = 10

  MAX_RATE_UP = 45
  MAX_RATE_DOWN = 80
  MAX_TORQUE_LOOKUP = [0], [8000]
  MAX_RT_DELTA = 1688

  DRIVER_TORQUE_ALLOWANCE = 1400
  DRIVER_TORQUE_FACTOR = 1

  NO_STEER_REQ_BIT = True

  def setUp(self):
    self.safety = libsafety_py.libsafety
    self.safety.set_safety_hooks(CarParams.SafetyModel.mazda, self.SAFETY_PARAM)
    self.safety.init_tests()

  def _torque_meas_msg(self, torque):
    return make_msg(0, 0x7FF)  # no motor torque measurement is used

  def _torque_driver_msg(self, torque):
    torque = int(torque)
    return _raw_msg(1, 0x24B, {0: (torque >> 8) & 0xFF, 1: torque & 0xFF})

  def _torque_cmd_msg(self, torque, steer_req=1):
    torque = int(torque)
    return _raw_msg(1, 0x249, {0: (torque >> 8) & 0xFF, 1: torque & 0xFF})

  def _speed_msg(self, speed):
    return _raw_msg(2, 0x217, {4: (speed >> 8) & 0xFF, 5: speed & 0xFF})

  def _user_gas_msg(self, gas):
    return _raw_msg(2, 0x202, {4: gas})

  def _user_brake_msg(self, brake):
    return _raw_msg(0, 0x43F, {5: 0x4 if brake else 0})

  def _pcm_status_msg(self, enable):
    return _raw_msg(0, 0x44A, {0: 0x20 if enable else 0})

  def test_pre_enable_engages(self):
    self._rx(_raw_msg(0, 0x44A, {0: 0x40}))
    self.assertTrue(self.safety.get_controls_allowed())

  def test_acc_command_not_allowed_on_main_bus(self):
    self.assertFalse(self._tx(make_msg(0, 0x220)))


class TestMazdaGen3Safety(TestMazdaGen2Safety):
  """GEN3 (2023+): speed and brake come from different messages than GEN2, and cruise state is on the aux bus."""
  SAFETY_PARAM = GEN3

  # wheel speed is offset by 10000, moving when != 10000
  STANDSTILL_THRESHOLD = 0

  def _speed_msg(self, speed):
    raw = 10000 + int(speed)
    return _raw_msg(2, 0x215, {0: (raw >> 8) & 0xFF, 1: raw & 0xFF})

  def _user_brake_msg(self, brake):
    return _raw_msg(0, 0x9F, {7: 0x8 if brake else 0})

  def _pcm_status_msg(self, enable):
    return _raw_msg(1, 0x44A, {0: 0x30 if enable else 0x10})

  def test_pre_enable_engages(self):
    # GEN3 has no pre-enable state, but cruise override keeps controls allowed
    self._rx(_raw_msg(1, 0x44A, {0: 0x40}))
    self.assertTrue(self.safety.get_controls_allowed())


if __name__ == "__main__":
  unittest.main()
