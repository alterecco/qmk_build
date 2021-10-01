#include QMK_KEYBOARD_H
#include <stdint.h>
#include <stdbool.h>
#include "quantum.h"

#include "alterecco.h"

#ifdef CUSTOM_ONESHOT_ENABLE
bool is_oneshot_cancel_key(uint16_t keycode)
{
  switch (keycode)
  {
  case o_NAV_o:
  // case __NAV__:
  // case __NUM__:
    return true;
  default:
    return false;
  }
}

bool is_oneshot_ignored_key(uint16_t keycode)
{
  switch (keycode)
  {
  case o_NAV_o:
  // case __NAV__:
  // case __NUM__:
  case _LSHFT_:
  case o_SFT_o:
  case o_CTL_o:
  case o_OPT_o:
  case o_CMD_o:
    return true;
  default:
    return false;
  }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_opt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;
#endif

#ifdef CUSTOM_MODTAP_ENABLE
bool mt_tab_active  = false;
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
#ifdef CONSOLE_ENABLE
  if (record->event.pressed)
  {
    uprintf(
        "0x%04X,%u,%u,%u\n",
        keycode,
        record->event.key.row,
        record->event.key.col,
        get_highest_layer(layer_state));
  }
#endif

#ifdef CUSTOM_NUM_WORD_ENABLE
  if (!process_num_word(keycode, record))
  {
    return false;
  }
#endif

#ifdef CUSTOM_NAV_WORD_ENABLE
  if (!process_nav_word(keycode, record))
  {
    return false;
  }
#endif

#ifdef CUSTOM_SYS_WORD_ENABLE
  if (!process_sys_word(keycode, record))
  {
    return false;
  }
#endif

  // #ifdef CUSTOM_MODTAP_ENABLE
  //   // clang-format off
  //   process_mod_hold_n_tap(
  //     &mt_tab_active, KC_LCMD, KC_TAB, o_LTB_o,
  //     keycode, record
  //   );
  //   process_mod_hold_n_tap(
  //     &mt_tab_active, KC_LCMD, KC_TAB, o_RTB_o,
  //     keycode, record
  //   );
  // #endif

#ifdef CUSTOM_ONESHOT_ENABLE
  process_oneshot(
    &os_shft_state, _LSHFT_, o_SFT_o,
    keycode, record
  );
  process_oneshot(
    &os_ctrl_state, _LCTRL_, o_CTL_o,
    keycode, record
  );
  process_oneshot(
    &os_opt_state, _LOPT__, o_OPT_o,
    keycode, record
  );
  process_oneshot(
    &os_cmd_state, _LCMD__, o_CMD_o,
    keycode, record
  );
#endif

#ifdef CUSTOM_REPEAT_KEY_ENABLE
  if (!process_repeat_last_key(keycode, record, o_RPT_o, o_NAV_o)) {
    return false;
  }
#endif


  switch (keycode)
  {
#ifdef CUSTOM_NUM_WORD_ENABLE
  case o_NUM_o:
    process_num_word_activation(record);
    return false;
#endif

#ifdef CUSTOM_NAV_WORD_ENABLE
  case o_NAV_o:
    process_nav_word_activation(record);
    return false;
#endif

#ifdef CUSTOM_SYS_WORD_ENABLE
  case o_SYS_o:
    process_sys_word_activation(record);
    return false;
#endif
  }

  return true;
}
