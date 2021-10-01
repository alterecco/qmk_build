#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "tmk_core/common/action.h"

bool sys_word_enabled(void);
void enable_sys_word(void);
void disable_sys_word(void);
void process_sys_word_activation(const keyrecord_t *record);
bool process_sys_word(uint16_t keycode, const keyrecord_t *record);
