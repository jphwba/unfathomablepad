#include QMK_KEYBOARD_H

// 1. Defining the Keymap Layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_F13, KC_F14, KC_F15,
        KC_F16, KC_F17, KC_F18
    )
};

// 2. Handling Rotary Encoder Rotation (Volume Control)
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { 
        if (clockwise) {
            tap_code(KC_VOLU); // Volume Up
        } else {
            tap_code(KC_VOLD); // Volume Down
        }
    }
    return true;
}

// 3. Handling the Direct-Pin Encoder Click (Mute Toggle via Pin GP1)
void keyboard_pre_init_user(void) {
    gpio_set_pin_input_high(GP1); // Sets GP1 as input with pull-up resistor
}

void house_keeping_task_user(void) {
    static bool s1_pressed = false;
    
    // Check state of the switch (Low means pressed because of the GND connection)
    if (!gpio_read_pin(GP1)) { 
        if (!s1_pressed) {
            register_code(KC_MUTE); // Mutes audio
            s1_pressed = true;
        }
    } else {
        if (s1_pressed) {
            unregister_code(KC_MUTE); // Unmutes / Releases key
            s1_pressed = false;
        }
    }
}

// 4. Custom OLED Display Output
#ifdef OLED_ENABLE
bool oled_task_user(void) {
    oled_write_P(PSTR("UNFATHOMABLEPAD\n"), false);
    return false;
}
#endif