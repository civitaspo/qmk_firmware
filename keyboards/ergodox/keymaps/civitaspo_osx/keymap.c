#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"

#define L_BASE   0 // default layer
#define L_MISC   1 // misc layer
#define L_MDIA   2 // media keys

// Fillers to make layering clearer
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Custom Aliases
#define G(kc) LGUI(kc)
#define A(kc) LALT(kc)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   |   {  |   }  |   (  |  )   |   [  |  ]   |           |  $   |   %  |   *  |   +  |   !  |   ~  |   \    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  TAB   |   '  |   ,  |   .  |   p  |   y  |  =   |           |  @   |   f  |   g  |   c  |   r  |   l  |   /    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCtrl  |   a  |   o  |   e  |   u  |   i  |------|           |------|   d  |   h  |   t  |   n  |   s  |   -    |
 * |--------+------+------+------+------+------|  #   |           |  `   |------+------+------+------+------+--------|
 * | LShift |   ;  |   q  |   j  |   k  |   x  |      |           |      |   b  |   m  |   w  |   v  |   z  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Alt  | LGui |                                       |L_MISC|      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |LGui+C|LGui+V|       |   ^  |  &   |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |L_MDIA|      |      |
 *                                 | Space|Back  |------|       |------|Back  |Enter |
 *                                 |      |space |AltSPC|       |LG+SPC|space |      |
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[L_BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_ESC,  KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC,
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_EQL,
        KC_LCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,
        KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_HASH,
        _______, _______, _______, KC_LALT, KC_LGUI,
                                                     G(KC_C), G(KC_V),
                                                              _______,
                                            KC_SPC,  KC_BSPC, A(KC_SPC),
        // right hand
        KC_DLR,  KC_PERC, KC_ASTR,    KC_PLUS, KC_EXLM, KC_TILD, KC_BSLS,
        KC_AT,   KC_F,    KC_G,       KC_C,    KC_R,    KC_L,    KC_SLSH,
                 KC_D,    KC_H,       KC_T,    KC_N,    KC_S,    KC_MINS,
        KC_GRV,  KC_B,    KC_M,       KC_W,    KC_V,    KC_Z,    KC_RSFT,
                          MO(L_MISC), _______, _______, _______, _______,
        KC_CIRC,    KC_AMPR,
        TG(L_MDIA),
        G(KC_SPC),  KC_BSPC, KC_ENT
    ),
/* Keymap 1: Misc Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  | F10  |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   1  |   2  |   3  |   4  |   5  |      |           |      |      |      |  Up  |      |      |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   6  |   7  |   8  |   9  |   0  |------|           |------|      | Left | Down |Right |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[L_MISC] = KEYMAP(
       // left hand
       _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,
       _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,
       _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______,
                                                    _______, _______,
                                                             _______,
                                           _______, _______, _______,
       // right hand
       _______, KC_F6,    KC_F7,  KC_F8,   KC_F9,    KC_F10,  KC_F11,
       _______, _______, _______, KC_UP,   _______,  _______, KC_F12,
                _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,
       _______, _______, _______, _______, _______,  _______, _______,
                         _______, _______, _______,  _______, _______,
       _______, _______,
       _______,
       _______, _______, _______
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  RESET |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      | Rclk | MsUp | Lclk |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |MsLeft|MsDown|MsRght|      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |VolUp |VolDn | Mute |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[L_MDIA] = KEYMAP(
       // left hand
       RESET,   _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______,
                                           _______, _______,
                                                    _______,
                                  _______, _______, _______,
       // right hand
       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, KC_BTN2, KC_MS_U, KC_BTN1, _______, _______,
                _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, KC_MPLY,
       _______, _______, _______, KC_MPRV, KC_MNXT, _______, _______,
                         _______, KC_VOLU, KC_VOLD, KC_MUTE, _______,
       _______, _______,
       _______,
       _______, _______, KC_WBAK
),
};

const uint16_t PROGMEM fn_actions[] = {
    // [1] = ACTION_LAYER_TAP_TOGGLE(L_MISC)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // MACRODOWN only works in this function
    // switch(id) {
    //   case 0:
    //   if (record->event.pressed) {
    //     register_code(KC_RSFT);
    //   } else {
    //     unregister_code(KC_RSFT);
    //   }
    //   break;
    // }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    /*
     * NOTE: My ErgoDox does not have LED,
     *       so does not need the below actions.
     *
    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }
    */
};
