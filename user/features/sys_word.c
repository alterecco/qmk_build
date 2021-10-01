#include "../keycodes.h"
#include "sys_word.h"

static uint16_t sys_word_timer;
static bool _sys_word_enabled = false;

bool sys_word_enabled(void)
{
  return _sys_word_enabled;
}

void enable_sys_word(void)
{
  _sys_word_enabled = true;
  layer_on(SYS);
}

void disable_sys_word(void)
{
  _sys_word_enabled = false;
  layer_off(SYS);
}

void process_sys_word_activation(const keyrecord_t *record)
{
  if (record->event.pressed)
  {
    layer_on(SYS);
    sys_word_timer = timer_read();
  }
  else
  {
    if (timer_elapsed(sys_word_timer) < TAPPING_TERM)
    {
      // Tapping enables NUMWORD
      _sys_word_enabled = true;
    }
    else
    {
      // Holding turns off NUM when released
      layer_off(SYS);
    }
  }
}

bool process_sys_word(uint16_t keycode, const keyrecord_t *record)
{
  if (!_sys_word_enabled)
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
  case _BRIMN_:
  case _BRIMX_:
  case _DSKT1_:
  case _DSKT2_:
  case _DSKT3_:
  case _DSKT4_:
  case _DSKT5_:
  case _DSKT6_:
  case _SCRSH_:
    // Don't disable for above keycodes
    break;
  default:
    if (record->event.pressed)
    {
      disable_sys_word();
      if (keycode == o_STP_o) {
        return false;
      }
    }
  }
  return true;
}
