/*
   This layout assumes that the OS will be translating keycodes into
   Colemak for the first two layers, as well as an alternate pair of
   layouts for machines that aren't configured for Colemak in the OS.

   The first layer has most of your keys in the expected positions,
   while the second layer (activated by the fn key) contains the
   digits in a numpad orientation as well as most of the punctuatiion.

   The third layer (activated by fn+ctrl) is just mostly function keys
   (on the right) and arrow/navcluster keys (on the left). Tapping the
   fn key by itself will go back to the first layer, and hitting the
   ctrl key will activate the "hardware colemak" layers. Hitting alt on
   this layer will reset the microcontroller in order to allow new
   firmware to be uploaded.
 */

#define ALEN(X) (sizeof(X) / sizeof(X[0]))

int base_qwerty[44] = {
    KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_0,     KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P,
    KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_0,     KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON,
    KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_ENTER, KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_SLASH,

    KEYBOARD_LEFT_CTRL, KEY_TAB, KEYBOARD_LEFT_GUI, KEYBOARD_LEFT_SHIFT, KEY_BACKSPACE,
    KEY_ESC,
    KEY_SPACE, PRE_FUNCTION(1), PRE_FUNCTION(2), KEY_QUOTE, KEYBOARD_LEFT_ALT };

int symbols_qwerty[44] = {
    SHIFT(KEY_1), SHIFT(KEY_2), SHIFT(KEY_LEFT_BRACE), SHIFT(KEY_RIGHT_BRACE), SHIFT(KEY_BACKSLASH), KEY_0, KEY_PAGE_UP, KEY_7, KEY_8, KEY_9, SHIFT(KEY_8),
    SHIFT(KEY_3), SHIFT(KEY_4), SHIFT(KEY_9), SHIFT(KEY_0), KEY_TILDE, KEY_0, KEY_PAGE_DOWN, KEY_4, KEY_5, KEY_6, SHIFT(KEY_EQUAL),
    SHIFT(KEY_5), SHIFT(KEY_6), KEY_LEFT_BRACE, KEY_RIGHT_BRACE, SHIFT(KEY_TILDE), KEYBOARD_LEFT_ALT, SHIFT(KEY_7), KEY_1, KEY_2, KEY_3, KEY_BACKSLASH,

    FUNCTION(5), SHIFT(KEY_INSERT), KEYBOARD_LEFT_GUI, KEYBOARD_LEFT_SHIFT, KEY_BACKSPACE,
    KEYBOARD_LEFT_CTRL,
    KEY_SPACE, PRE_FUNCTION(1), KEY_MINUS, KEY_0, KEY_EQUAL };

int motion_qwerty[44] = {
    KEY_INSERT, KEY_HOME, KEY_UP, KEY_END, KEY_PAGE_UP, KEY_0, KEY_UP, KEY_F7, KEY_F8, KEY_F9, KEY_F10,
    KEY_DELETE, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_PAGE_DOWN, KEY_0, KEY_DOWN, KEY_F4, KEY_F5, KEY_F6, KEY_F11,

    0, KEYBOARD_VOLUME_UP, 0, 0, FUNCTION(0),
    KEYBOARD_LEFT_ALT,
    0, KEY_F1, KEY_F2, KEY_F3, KEY_F12,

    FUNCTION(4), KEYBOARD_VOLUME_DOWN, KEYBOARD_LEFT_GUI, KEYBOARD_LEFT_SHIFT, KEY_BACKSPACE,
    KEYBOARD_LEFT_CTRL,
    KEY_SPACE, PRE_FUNCTION(1), PRE_FUNCTION(2), 0, 0 };

int base_colemak[44] = {
    KEY_Q, KEY_W, KEY_F, KEY_P, KEY_G, KEY_0,     KEY_J, KEY_L, KEY_U, KEY_Y, KEY_SEMICOLON,
    KEY_A, KEY_R, KEY_S, KEY_T, KEY_D, KEY_0,     KEY_H, KEY_N, KEY_E, KEY_I, KEY_O,
    KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_ENTER, KEY_K, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_SLASH,

    KEYBOARD_LEFT_CTRL, KEY_TAB, KEYBOARD_LEFT_GUI, KEYBOARD_LEFT_SHIFT, KEY_BACKSPACE,
    KEY_ESC,
    KEY_SPACE, PRE_FUNCTION(1), PRE_FUNCTION(2), KEY_QUOTE, KEYBOARD_LEFT_ALT };

int symbols_colemak[44] = {
    SHIFT(KEY_1), SHIFT(KEY_2), SHIFT(KEY_LEFT_BRACE), SHIFT(KEY_RIGHT_BRACE), SHIFT(KEY_BACKSLASH), KEY_0, KEY_PAGE_UP, KEY_7, KEY_8, KEY_9, SHIFT(KEY_8),
    SHIFT(KEY_3), SHIFT(KEY_4), SHIFT(KEY_9), SHIFT(KEY_0), KEY_TILDE, KEY_0, KEY_PAGE_DOWN, KEY_4, KEY_5, KEY_6, SHIFT(KEY_EQUAL),
    SHIFT(KEY_5), SHIFT(KEY_6), KEY_LEFT_BRACE, KEY_RIGHT_BRACE, SHIFT(KEY_TILDE), KEYBOARD_LEFT_ALT, SHIFT(KEY_7), KEY_1, KEY_2, KEY_3, KEY_BACKSLASH,

    FUNCTION(6), SHIFT(KEY_INSERT), KEYBOARD_LEFT_GUI, KEYBOARD_LEFT_SHIFT, KEY_BACKSPACE,
    KEYBOARD_LEFT_CTRL,
    KEY_SPACE, PRE_FUNCTION(1), KEY_MINUS, KEY_0, KEY_EQUAL };

int motion_colemak[44] = {
    KEY_INSERT, KEY_HOME, KEY_UP, KEY_END, KEY_PAGE_UP, KEY_0, KEY_UP, KEY_F7, KEY_F8, KEY_F9, KEY_F10,
    KEY_DELETE, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_PAGE_DOWN, KEY_0, KEY_DOWN, KEY_F4, KEY_F5, KEY_F6, KEY_F11,

    0, KEYBOARD_VOLUME_UP, 0, 0, FUNCTION(0),
    KEYBOARD_LEFT_ALT,
    0, KEY_F1, KEY_F2, KEY_F3, KEY_F12,

    FUNCTION(3), KEYBOARD_VOLUME_DOWN, KEYBOARD_LEFT_GUI, KEYBOARD_LEFT_SHIFT, KEY_BACKSPACE,
    KEYBOARD_LEFT_CTRL,
    KEY_SPACE, PRE_FUNCTION(1), PRE_FUNCTION(2), 0, 0 };

int *layers[] = {base_qwerty, symbols_qwerty, motion_qwerty, base_colemak, symbols_colemak, motion_colemak};

// stuff below is taken from layout_common.h but adapted to allow fn
// to function from more than one layer.

int momentary_key_decay[] = {0, 0};

void activate_symbols() {
  momentary_key_decay[0] = 20;
};

void activate_motion() {
  momentary_key_decay[1] = 20;
};

int base_layer = 0;
int layer_to_jump = 0;

void to_motion_qwerty() {
  layer_to_jump = 2;
};

void to_motion_colemak() {
  layer_to_jump = 5;
};

void to_base_colemak() {
  current_layer = layers[3];
  current_layer_number = 3;
  base_layer = 3;
};

void to_base_qwerty() {
  current_layer = layers[0];
  current_layer_number = 0;
  base_layer = 0;
};

void (*layer_functions[])(void) = {reset, activate_symbols, activate_motion, to_base_qwerty, to_base_colemak, to_motion_qwerty, to_motion_colemak};

void per_cycle() {
  for (int i = 0; i < ALEN(momentary_key_decay); i++) {
    if (momentary_key_decay[i] > 1) {
      current_layer = layers[current_layer_number + 1 + i];
      momentary_key_decay[i]--;
    } else if (momentary_key_decay[i] == 1) {
      current_layer_number = layer_to_jump;
      momentary_key_decay[i]--;
    } else {
      layer_to_jump = base_layer;
      momentary_key_decay[i] = 0;
    }
  }
};
