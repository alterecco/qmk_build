#include "mod_hold_n_tap.h"

void process_mod_hold_n_tap(
    bool* active,
    uint16_t hold_mod,
    uint16_t tap_key,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t* record) {
  if (keycode == trigger) {
    if (record->event.pressed) {
      if (!*active) {
        *active = true;
        register_code(hold_mod);
      }
      register_code(tap_key);
    } else {
      unregister_code(tap_key);
      // Don't unregister cmdish until some other key is hit or released.
    }
  } else if (*active) {
    unregister_code(hold_mod);
    *active = false;
  }
}
