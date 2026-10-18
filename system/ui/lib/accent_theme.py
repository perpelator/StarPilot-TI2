"""Runtime accent theme for the raylib UI.

StarPilot's accent purple is shared across many widgets. Colors created through
`themed()` are registered here and recolored in place when the theme changes, so
every widget holding a reference picks up the new color on its next frame.

The Mazda theme replaces each purple with a neutral gray at the same peak
brightness (max channel), so bright accents become white and darker purple
shades become matching grays.
"""

import pyray as rl

MAZDA_THEME_PARAM = "MazdaTheme"

_mazda_theme = False
_registry: list[tuple[rl.Color, tuple[int, int, int], tuple[int, int, int] | None]] = []


def _neutral(rgb: tuple[int, int, int]) -> tuple[int, int, int]:
  m = max(rgb)
  return (m, m, m)


def _resolve(stock: tuple[int, int, int], mazda: tuple[int, int, int] | None) -> tuple[int, int, int]:
  if not _mazda_theme:
    return stock
  return mazda if mazda is not None else _neutral(stock)


def themed(r: int, g: int, b: int, a: int = 255, *, mazda: tuple[int, int, int] | None = None) -> rl.Color:
  """Create a color that follows the active theme. `mazda` overrides the default neutral mapping."""
  stock = (r, g, b)
  color = rl.Color(*_resolve(stock, mazda), a)
  _registry.append((color, stock, mazda))
  return color


def themed_alpha(base: rl.Color, alpha: int) -> rl.Color:
  """Like with_alpha(), but the result keeps following the theme if `base` is a themed color."""
  for color, stock, mazda in _registry:
    if color is base:
      return themed(*stock, max(0, min(base.a, int(alpha))), mazda=mazda)
  return rl.Color(base.r, base.g, base.b, max(0, min(base.a, int(alpha))))


def tint(r: int, g: int, b: int) -> tuple[int, int, int]:
  """Theme an RGB tuple computed per frame (e.g. gradient samples)."""
  return _resolve((r, g, b), None)


def mazda_theme_enabled() -> bool:
  return _mazda_theme


def set_mazda_theme(enabled: bool) -> None:
  global _mazda_theme
  _mazda_theme = bool(enabled)
  for color, stock, mazda in _registry:
    color.r, color.g, color.b = _resolve(stock, mazda)


def load_theme_from_params(params=None) -> None:
  # Also used by processes that can start before params are built (e.g. the spinner), so never raise.
  try:
    if params is None:
      from openpilot.common.params import Params
      params = Params()
    set_mazda_theme(params.get_bool(MAZDA_THEME_PARAM))
  except Exception:
    set_mazda_theme(False)
