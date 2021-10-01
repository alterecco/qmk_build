#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "tmk_core/common/action.h"

// Implements cmd-tab like behaviour on a single key. On first tap of trigger
// cmdish is held and tabish is tapped -- cmdish then remains held until some
// other key is hit or released. For example:
//
//     trigger, trigger, a -> cmd down, tab, tab, cmd up, a
//     nav down, trigger, nav up -> nav down, cmd down, tab, cmd up, nav up
//
// This behaviour is useful for more than just cmd-tab, hence: cmdish, tabish.
void process_mod_hold_n_tap(
    bool* active,
    uint16_t mod_hold,
    uint16_t tap_key,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t* record);
