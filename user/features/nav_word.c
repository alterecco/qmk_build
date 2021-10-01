#include "../keycodes.h"
#include "nav_word.h"

static uint16_t nav_word_timer;
static bool _nav_word_enabled = false;

bool nav_word_enabled(void)
{
  return _nav_word_enabled;
}

void enable_nav_word(void)
{
  _nav_word_enabled = true;
  layer_on(NAV);
}

void disable_nav_word(void)
{
  _nav_word_enabled = false;
  layer_off(NAV);
}

void process_nav_word_activation(const keyrecord_t *record)
{
  if (record->event.pressed)
  {
    layer_on(NAV);
    nav_word_timer = timer_read();
  }
  else
  {
    if (timer_elapsed(nav_word_timer) < TAPPING_TERM)
    {
      // Tapping enables NUMWORD
      _nav_word_enabled = true;
    }
    else
    {
      // Holding turns off NUM when released
      layer_off(NAV);
    }
  }
}

bool process_nav_word(uint16_t keycode, const keyrecord_t *record)
{
  if (!_nav_word_enabled)
    return true;

  switch (keycode)
  {
  case QK_MOD_TAP ... QK_MOD_TAP_MAX:
  case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
  case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
    if (record->tap.count == 0)
      return true;
    keycode = keycode & 0xFF;
  }

  switch (keycode)
  {
  case _LEFT__:
  case __UP___:
  case _DOWN__:
  case _RIGHT_:
  case __TAB__:
  case _ENTER_:
  case _BKSPC_:
  case o_SFT_o:
  case o_CTL_o:
  case o_OPT_o:
  case o_CMD_o:
  // case oMOUSEo:
    // Don't disable for above keycodes
    break;
  default:
    if (record->event.pressed)
    {
      disable_nav_word();
      if (keycode == o_STP_o) {
        return false;
      }
    }
  }
  return true;
}
