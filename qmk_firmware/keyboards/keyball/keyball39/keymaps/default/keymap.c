/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// combos
enum combos {
  CMB_BSPC,
  CMB_ALT_BSPC,
  CMB_LNG1,
  CMB_LNG2,
  CMB_TAB,
  CMB_L3L,
  CMB_L3R,
  CMB_GRV,
};

const uint16_t PROGMEM hj_combo[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM yu_combo[] = {KC_Y, KC_U, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM nm_combo[] = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM vb_combo[] = {KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM brc_combo[] = {KC_RBRC, KC_LBRC, COMBO_END};

combo_t key_combos[] = {
  [CMB_BSPC] = COMBO(hj_combo, KC_BSPC),
  [CMB_ALT_BSPC] = COMBO(yu_combo, LALT(KC_BSPC)),
  [CMB_LNG1] = COMBO(jk_combo, KC_LNG1),
  [CMB_LNG2] = COMBO(kl_combo, KC_LNG2),
  [CMB_TAB] = COMBO(qw_combo, KC_TAB),
  [CMB_L3L] = COMBO(vb_combo, MO(3)),
  [CMB_L3R] = COMBO(nm_combo, MO(3)),
  [CMB_GRV] = COMBO(brc_combo, KC_GRV),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_MINS  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,
    KC_LCTL  , KC_LGUI  , KC_LALT  ,KC_LGUI   ,MO(1)     ,KC_SPC,             KC_ENT, MO(2)    ,LSFT_T(KC_LNG2),KC_RALT,KC_RGUI , KC_ESC
  ),

  [1] = LAYOUT_universal(
    S(KC_0)  , S(KC_1)  , S(KC_2)  , S(KC_3)  , S(KC_4)  ,                            S(KC_5)  , S(KC_6)  , S(KC_7)  , S(KC_8)  , S(KC_9)  ,
    KC_F5    , KC_EXLM  , S(KC_6)  ,S(KC_INT3), S(KC_8)  ,                           S(KC_INT1), KC_BTN1  , KC_PGUP  , KC_BTN2  , KC_SCLN  ,
    S(KC_EQL),S(KC_LBRC),S(KC_7)   , S(KC_2)  ,S(KC_RBRC),                            KC_LBRC  , KC_DLR   , KC_PGDN  , KC_BTN3  , KC_F11   ,
    KC_INT1  , KC_EQL   , S(KC_3)  , _______  , _______  , _______  ,      MO(1)    , MO(2)    , _______  , KC_RALT  , KC_RGUI  , KC_F12
  ),

  [2] = LAYOUT_universal(
    KC_0     , KC_1     , KC_2     , KC_3     , KC_4     ,                            KC_5     , KC_6     , KC_7     , KC_8     , KC_9     ,
   S(KC_QUOT), KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                            S(KC_9)  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_QUOT  ,
    KC_SLSH  , KC_1     , KC_2     , KC_3     ,S(KC_MINS),                           S(KC_NUHS), KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  ,
    KC_ESC   , KC_0     , KC_DOT   , KC_DEL   , KC_ENT   , KC_BSPC  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    S(KC_0)  , S(KC_1)  , S(KC_2)  , S(KC_3)  , S(KC_4)  ,                            S(KC_5)  , S(KC_6)  , S(KC_7)  , S(KC_8)  , S(KC_9)  ,
    KC_F5    , KC_EXLM  , S(KC_6)  ,S(KC_INT3), S(KC_8)  ,                            KC_RALT  , KC_MINS  , KC_EQL   , KC_LBRC  , KC_RBRC  ,
    S(KC_EQL),S(KC_LBRC),S(KC_7)   , S(KC_2)  ,S(KC_RBRC),                            S(KC_MINS), S(KC_EQL), S(KC_LBRC), S(KC_RBRC), S(KC_BSLS),
    KC_INT1  , _______ , _______  , _______  , _______  , _______  ,      TO(2)    , TO(0)    , _______  , KC_RALT  , KC_RGUI  , KC_F12
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
