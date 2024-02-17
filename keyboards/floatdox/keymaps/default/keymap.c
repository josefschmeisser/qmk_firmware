#include QMK_KEYBOARD_H

enum Layers {
    _BASE = 0,
    _FN   = 1,
    _NAV  = 2
};

enum Encoder {
    _ENCODER_LEFT  = 0,
    _ENCODER_RIGHT = 1,
};

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT( \
    KC_ESC         , KC_1          , KC_2          , KC_3          , KC_4          , KC_5          , KC_6          ,                                 KC_7          , KC_8          , KC_9          , KC_0          , KC_MINS       , KC_EQL        , KC_BSPC        , \
    RALT_T(KC_TAB) , KC_Q          , KC_W          , KC_E          , KC_R          , KC_T          , KC_LBRC       ,                                 KC_RBRC       , KC_Y          , KC_U          , KC_I          , KC_O          , KC_P          , RALT_T(KC_BSLS), \
    KC_CAPS        , KC_A          , KC_S          , KC_D          , KC_F          , KC_G          , LT(1, KC_GRV) , KC_MUTE       , KC_MPLY       , LT(1, KC_QUOT), KC_H          , KC_J          , KC_K          , KC_L          , KC_SCLN       , KC_ENT         , \
    KC_LSFT        , KC_Z          , KC_X          , KC_C          , KC_V          , KC_B          , KC_HOME       , KC_END        , KC_PGDN       , KC_PGUP       , KC_N          , KC_M          , KC_COMM       , KC_DOT        ,RALT_T(KC_SLSH), KC_RSFT        , \
    KC_LCTL        , KC_LGUI       , KC_LALT       , TT(1)         , TT(2)                         , KC_SPC        , LT(2, KC_ESC) , LT(2, KC_DEL) , KC_SPC                        , KC_LEFT       , KC_DOWN       , KC_UP         , KC_RGHT       , KC_RCTL          \
  ),
  [_FN] = LAYOUT( \
    _______        , KC_F1         , KC_F2         , KC_F3         , KC_F4         , KC_F5         , KC_F6         ,                                 KC_F7         , KC_F8         , KC_F9         , KC_F10        , KC_F11        , KC_F12        , _______        , \
    KC_NO          , CL_SWAP       , CL_NORM       , KC_NO         , KC_NO         , KC_NO         , KC_NO         ,                                 KC_NO         , KC_NUMLOCK    , KC_KP_7       , KC_KP_8       , KC_KP_9       , KC_PSLS       , KC_DEL         , \
    _______        , KC_CAPS       , KC_SCROLLLOCK , KC_NO         , KC_NO         , KC_NO         , KC_NO         , RESET         , DEBUG         , KC_NO         , KC_PEQL       , KC_KP_4       , KC_KP_5       , KC_KP_6       , KC_PAST       , _______        , \
    _______        , KC_NO         , KC_NO         , KC_APP        , KC_NO         , KC_NO         , KC_INS        , KC_DEL        , KC_PSCR       , KC_PAUS       , KC_NO         , KC_KP_1       , KC_KP_2       , KC_KP_3       , KC_PMNS       , _______        , \
    _______        , _______       , _______       , _______       , _______                       , _______       , KC_NO         , KC_NO         , _______                       , _______       , _______       , _______       , _______       , _______          \
  ),
  [_NAV] = LAYOUT( \
    _______        , KC_NO         , KC_NO         , KC_NO         , KC_NO         , KC_NO         , KC_NO         ,                                 KC_NO         , KC_NO         , KC_NO         , KC_NO         , KC_NO         , KC_NO         , KC_NO          , \
    KC_NO          , KC_NO         , KC_UP         , KC_NO         , KC_NO         , KC_NO         , KC_NO         ,                                 KC_NO         , KC_HOME       , KC_PGDN       , KC_PGUP       , KC_END        , KC_NO         , KC_NO          , \
    _______        , KC_LEFT       , KC_DOWN       , KC_RGHT       , KC_NO         , KC_NO         , KC_NO         , KC_NO         , KC_NO         , KC_NO         , KC_LEFT       , KC_DOWN       , KC_UP         , KC_RGHT       , KC_NO         , KC_NO          , \
    _______        , KC_NO         , KC_NO         , KC_NO         , KC_NO         , KC_NO         , KC_NO         , KC_NO         , KC_NO         , KC_NO         , KC_NO         , KC_NO         , KC_NO         , KC_NO         , KC_NO         , _______        , \
    _______        , _______       , _______       , _______       , _______                       , KC_NO         , KC_NO         , KC_NO         , KC_NO                         , KC_NO         , KC_NO         , KC_NO         , KC_NO         , _______          \
  )
};


// clang-format on

#if defined(IGNORE_MOD_TAP_INTERRUPT_PER_KEY)
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_SPC):
            return false;
        case RSFT_T(KC_SPC):
            return false;
        default:
            return true;
    }
}
#endif

#if defined(HOLD_ON_OTHER_KEY_PRESS_PER_KEY)
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_SPC):
            return true;
        case RSFT_T(KC_SPC):
            return true;
        default:
            return false;
    }
}
#endif

#if defined(ENCODER_ENABLE)
bool encoder_update_user(uint8_t index, bool clockwise) {
    layer_state_t current_state = get_highest_layer(layer_state);

    if (index == _ENCODER_LEFT) {
        if (clockwise) {
            switch (current_state) {
                case _BASE:
                default:
                    tap_code(KC_MS_WH_DOWN);
                    break;
                case _NAV:
                    tap_code(KC_MS_WH_RIGHT);
                    break;
                case _FN:
                    tap_code_delay(KC_AUDIO_VOL_UP, 10);
                    break;
            }
        } else {
            switch (current_state) {
                case _BASE:
                default:
                    tap_code(KC_MS_WH_UP);
                    break;
                case _NAV:
                    tap_code(KC_MS_WH_LEFT);
                    break;
                case _FN:
                    tap_code_delay(KC_AUDIO_VOL_DOWN, 10);
                    break;
            }
        }
    } else if (index == _ENCODER_RIGHT) {
        if (clockwise) {
            switch (current_state) {
                case _BASE:
                default:
                    tap_code(KC_MS_WH_DOWN);
                    break;
                case _NAV:
                    tap_code(KC_MS_WH_RIGHT);
                    break;
                case _FN:
                    tap_code_delay(KC_MEDIA_NEXT_TRACK, 10);
                    break;
            }
        } else {
            switch (current_state) {
                case _BASE:
                default:
                    tap_code(KC_MS_WH_UP);
                    break;
                case _NAV:
                    tap_code(KC_MS_WH_LEFT);
                    break;
                case _FN:
                    tap_code_delay(KC_MEDIA_PREV_TRACK, 10);
                    break;
            }
        }
    }

    return false;
}
#endif

#if defined(OLED_ENABLE)

#    define w_val(str, val)                         \
        snprintf(buffer, sizeof(buffer), str, val); \
        oled_write_ln(buffer, false)

/*
void render_display(void) {
    static layer_state_t last_state    = ~0;
    layer_state_t        current_state = get_highest_layer(layer_state);

    if (last_state <= _SYM && current_state <= _SYM) {
        // Don't do anything if we are on the default layers
        return;
    } else if (last_state != current_state) {
        oled_clear();
        last_state = current_state;
    } else if (current_state != _FN) {
        return;
    }

    char buffer[25];
    switch (current_state) {
        case _FN:
            oled_write_ln("Function\n", false);
#    if defined(DEBUG_MATRIX_SCAN_RATE)
            oled_write_ln("Scan Freq:", false);
            w_val("%05ld", get_matrix_scan_rate());
#    endif
            break;
        default:
            if (is_keyboard_master()) {
                oled_write_ln("\x7QWERTY\x7", false);
            } else {
                oled_write_ln("QWERTY", false);
            }
            break;
    }
}*/

static void render_base_layer_indicator(void) {
    static const char PROGMEM base_indicator[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x1e,
        0x06, 0xe2, 0xf2, 0xf2, 0xe2, 0x06, 0x1e, 0xfe, 0xc2, 0x02, 0x3e, 0xfe, 0x1e, 0x1e, 0xfe, 0x3e,
        0x02, 0xc2, 0xfe, 0x02, 0x02, 0x72, 0x72, 0x72, 0x72, 0x06, 0x86, 0xfe, 0xfe, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x78,
        0x60, 0x47, 0x4f, 0x4f, 0x07, 0x20, 0x70, 0x7f, 0x7f, 0x40, 0x40, 0x43, 0x7c, 0x7c, 0x43, 0x40,
        0x40, 0x7f, 0x7f, 0x40, 0x40, 0x7e, 0x7e, 0x7c, 0x78, 0x40, 0x43, 0x5f, 0x7f, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(base_indicator, sizeof(base_indicator));
}

static void render_fn_layer_indicator(void) {
    static const char PROGMEM fn_indicator[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0xfe, 0x02, 0x02, 0x72, 0x72, 0x72, 0x72, 0x72, 0xf2, 0xfe, 0xfe, 0x02, 0x02,
        0xc2, 0x1e, 0x7e, 0xfe, 0x02, 0x02, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x7f, 0x40, 0x40, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7f, 0x7f, 0x7f, 0x40, 0x40,
        0x7f, 0x7e, 0x78, 0x43, 0x40, 0x40, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(fn_indicator, sizeof(fn_indicator));
}

static void render_nav_layer_indicator(void) {
    static const char PROGMEM nav_indicator[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x02,
        0x02, 0xc2, 0x1e, 0x7e, 0xfe, 0x02, 0x02, 0xfe, 0xfe, 0xfe, 0x7e, 0x06, 0x82, 0x82, 0x06, 0x7e,
        0xfe, 0xfe, 0xfe, 0xf2, 0x02, 0x06, 0xfe, 0xfe, 0x06, 0x02, 0xf2, 0xfe, 0xfe, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x40,
        0x40, 0x7f, 0x7e, 0x78, 0x43, 0x40, 0x40, 0x7f, 0x7f, 0x4f, 0x40, 0x60, 0x79, 0x79, 0x60, 0x40,
        0x4f, 0x7f, 0x7f, 0x7f, 0x7e, 0x40, 0x41, 0x41, 0x40, 0x7e, 0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(nav_indicator, sizeof(nav_indicator));
}

void render_display(void) {
    static layer_state_t last_layer_state    = ~0;
    static led_t         last_led_state      = { .raw = ~0 };
    layer_state_t        current_layer_state = get_highest_layer(layer_state);
    led_t                current_led_state   = host_keyboard_led_state();

/*
    if (last_layer_state <= _SYM && current_layer_state <= _SYM) {
        // Don't perform display inversion if we are on the default layers
        return;
    } else if (last_layer_state != current_layer_state || last_led_state.raw != current_led_state.raw) {
        oled_clear();
        last_layer_state = current_layer_state;
        last_led_state   = current_led_state;
    }
*/
    if (last_layer_state != current_layer_state || last_led_state.raw != current_led_state.raw) {
        oled_clear();
        last_layer_state = current_layer_state;
        last_led_state   = current_led_state;
    } else {
        return;
    }

    if (is_keyboard_master()) {
        oled_write("\x10 Layer  \x11", false);
    } else {
        oled_write("> Layer  <", false);
    }
    oled_set_cursor(0, 1);
    switch (current_layer_state) {
        case _BASE:
            render_base_layer_indicator();
            break;
        case _FN:
            //oled_write_ln("  FN", false);
            render_fn_layer_indicator();
            break;
        case _NAV:
            //oled_write_ln("  NAV", false);
            render_nav_layer_indicator();
            break;
    }
    oled_set_cursor(0, 3);

    oled_write("----------", false);

    /*
    if (current_led_state.num_lock) {
        oled_write_ln("  Num:", false);
        w_val("%01ld", get_matrix_scan_rate());
    }
    if (current_led_state.caps_lock) {
        oled_write_ln("  Cap:", false);
    }
    if (current_led_state.scroll_lock) {
        oled_write_ln("  Scr:", false);
    }*/
    char buffer[25];
    oled_write("> State  <", false);
    w_val("  Num: %01ld", current_led_state.num_lock);
    w_val("  Cap: %01ld", current_led_state.caps_lock);
    w_val("  Scr: %01ld", current_led_state.scroll_lock);

    /* debugging output */
    if (current_layer_state < _FN) {
        return;
    }
    oled_write("----------", false);
    oled_write("> Status <", false);
#    if defined(DEBUG_MATRIX_SCAN_RATE)
            oled_write("Scan Freq:", false);
            w_val("%05ld", get_matrix_scan_rate());
#    endif
}
#endif
