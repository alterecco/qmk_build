#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "tmk_core/common/action.h"

bool nav_word_enabled(void);
void enable_nav_word(void);
void disable_nav_word(void);
void process_nav_word_activation(const keyrecord_t *record);
bool process_nav_word(uint16_t keycode, const keyrecord_t *record);
