#include "keycodes.h"
#include "quantum/process_keycode/process_key_override.h"

const key_override_t** key_overrides = (const key_override_t*[]){
  // &ko_make_basic(MOD_MASK_SHIFT,      __DOT__,        _SQUOT_),
  // &ko_make_basic(MOD_MASK_SHIFT,      _COMMA_,        _GRAVE_),
  NULL
};
