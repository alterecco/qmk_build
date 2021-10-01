#include <stdint.h>
#include "config.h"
#include "process_combo.h"
#include "keycodes.h"


const uint16_t PROGMEM undo_combo[] = {KC_F, KC_M, COMBO_END};
const uint16_t PROGMEM redo_combo[] = {KC_F, KC_S, COMBO_END};
const uint16_t PROGMEM copy_combo[] = {KC_M, KC_V, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_V, KC_C, COMBO_END};
const uint16_t PROGMEM cut_combo[] = {KC_F, KC_V, COMBO_END};
const uint16_t PROGMEM select_all_combo[] = {KC_F, KC_C, COMBO_END};
const uint16_t PROGMEM paste_match_combo[] = {KC_M, KC_C, COMBO_END};

const uint16_t PROGMEM kc_q_combo[] = {KC_L, KC_R, COMBO_END};
const uint16_t PROGMEM kc_b_combo[] = {KC_R, KC_W, COMBO_END};
const uint16_t PROGMEM kc_j_combo[] = {KC_G, KC_U, COMBO_END};
const uint16_t PROGMEM kc_z_combo[] = {KC_U, KC_D, COMBO_END};

const uint16_t PROGMEM kc_0_combo[] = {o_SPC_o, _LSHFT_, COMBO_END};
const uint16_t PROGMEM kc_1_combo[] = {o_SPC_o, ___M___, COMBO_END};
const uint16_t PROGMEM kc_2_combo[] = {o_SPC_o, ___V___, COMBO_END};
const uint16_t PROGMEM kc_3_combo[] = {o_SPC_o, ___C___, COMBO_END};
const uint16_t PROGMEM kc_4_combo[] = {o_SPC_o, ___H___, COMBO_END};
const uint16_t PROGMEM kc_5_combo[] = {o_SPC_o, ___N___, COMBO_END};
const uint16_t PROGMEM kc_6_combo[] = {o_SPC_o, ___T___, COMBO_END};
const uint16_t PROGMEM kc_7_combo[] = {o_SPC_o, ___L___, COMBO_END};
const uint16_t PROGMEM kc_8_combo[] = {o_SPC_o, ___R___, COMBO_END};
const uint16_t PROGMEM kc_9_combo[] = {o_SPC_o, ___W___, COMBO_END};

const uint16_t PROGMEM aelig_combo[] = {KC_P, KC_X, COMBO_END};
const uint16_t PROGMEM oslsh_combo[] = {KC_X, KC_K, COMBO_END};
const uint16_t PROGMEM aring_combo[] = {KC_K, KC_Y, COMBO_END};

combo_t key_combos[] = {
  COMBO(undo_combo, MAC_UNDO),
  COMBO(redo_combo, MAC_REDO),
  COMBO(copy_combo, MAC_COPY),
  COMBO(paste_combo, MAC_PASTE),
  COMBO(cut_combo, MAC_CUT),
  COMBO(select_all_combo, MAC_SELECT_ALL),
  COMBO(paste_match_combo, MAC_PASTE_MATCH),

  COMBO(kc_q_combo, ___Q___),
  COMBO(kc_b_combo, ___B___),
  COMBO(kc_j_combo, ___J___),
  COMBO(kc_z_combo, ___Z___),

  COMBO(kc_0_combo, ___0___),
  COMBO(kc_1_combo, ___1___),
  COMBO(kc_2_combo, ___2___),
  COMBO(kc_3_combo, ___3___),
  COMBO(kc_4_combo, ___4___),
  COMBO(kc_5_combo, ___5___),
  COMBO(kc_6_combo, ___6___),
  COMBO(kc_7_combo, ___7___),
  COMBO(kc_8_combo, ___8___),
  COMBO(kc_9_combo, ___9___),

  COMBO(aelig_combo, _AELIG_),
  COMBO(oslsh_combo, _OSLSH_),
  COMBO(aring_combo, _ARING_),
};

uint16_t COMBO_LEN = sizeof(key_combos) / sizeof(key_combos[0]);
