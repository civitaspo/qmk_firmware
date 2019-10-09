#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

extern uint8_t is_master;

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

// common
#define KC_ KC_TRNS
#define KC_XXXX KC_NO
#define KC_RST RESET
#define KC_VD KC__VOLDOWN
#define KC_VU KC__VOLUP
#define KC_XLNG LGUI(KC_SPC)
#define KC_RESC LT(_RAISE, KC_ESC)

// layer
#define KC_LY_L MO(_LOWER)  // lower layer
#define KC_LY_R MO(_RAISE)  // raise layer


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc( \
  //,----+----+----+----+----+----.     ,----+----+----+----+----+----.
     TAB ,QUOT,COMM, DOT, P  , Y  ,       F  , G  , C  , R  , L  ,SLSH,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
     LCTL, A  , O  , E  , U  , I  ,       D  , H  , T  , N  , S  ,MINS,
  //|----+----+----+----+----+----+     |----+----+----+----+----+----|
     LSFT,SCLN, Q  , J  , K  , X  ,       B  , M  , W  , V  , Z  ,BSLS,
  //`----+----+----+----+----+----/     \----+----+----+----+----+----'
               LALT,LGUI,SPC ,RESC,      XLNG,BSPC,ENT ,LY_R
  //          `----+----+----+----'     `----+----+----+----'
  ),


  //     1  2  3  4  5          (  )
  //     6  7  8  9  0       =  {  }
  //     `  [  ]  {  }      `  \  [  ]
  //                

  [_RAISE] = LAYOUT_kc( \
  //,----+----+----+----+----+----.     ,----+----+----+----+----+----.
         , 1  , 2  , 3  , 4  , 5  ,      XXXX,XXXX, UP ,XXXX,XXXX,XXXX,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
         , 6  , 7  , 8  , 9  , 0  ,      PGUP,LEFT,DOWN,RGHT,XXXX,XXXX,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
         ,GRV ,LCBR,RCBR,LBRC,RBRC,      PGDN,EQL ,XXXX,XXXX,XXXX,    ,
  //`----+----+----+----+----+----/     \----+----+----+----+----+----'
                   ,    ,    ,    ,          ,    ,    ,
  //          `----+----+----+----'     `----+----+----+----'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,----+----+----+----+----+----.     ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,          ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,          ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,          ,    ,    ,    ,    ,RST ,
  //`----+----+----+--+-+----+----/     \----+----+----+----+----+----'
                   ,    ,    ,    ,          ,    ,    ,
  //          `----+----+----+----'     `----+----+----+----'
  ),
};

void matrix_init_user(void) {
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
    iota_gfx_init(!has_usb());   // turns on the display
  #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
  iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
  }
  return true;
}
