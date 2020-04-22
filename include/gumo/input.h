#ifndef GUMO_ENGINE_INPUT_H
#define GUMO_ENGINE_INPUT_H

#include "core.h"
#include "window.h"

typedef enum
{
    KEYCODE_0 = 48,
    KEYCODE_1 = 49,
    KEYCODE_2 = 50,
    KEYCODE_3 = 51,
    KEYCODE_4 = 52,
    KEYCODE_5 = 53,
    KEYCODE_6 = 54,
    KEYCODE_7 = 55,
    KEYCODE_8 = 56,
    KEYCODE_9 = 57,
    KEYCODE_A = 65,
    KEYCODE_B = 66,
    KEYCODE_C = 67,
    KEYCODE_D = 68,
    KEYCODE_E = 69,
    KEYCODE_F = 70,
    KEYCODE_G = 71,
    KEYCODE_H = 72,
    KEYCODE_I = 73,
    KEYCODE_J = 74,
    KEYCODE_K = 75,
    KEYCODE_L = 76,
    KEYCODE_M = 77,
    KEYCODE_N = 78,
    KEYCODE_O = 79,
    KEYCODE_P = 80,
    KEYCODE_Q = 81,
    KEYCODE_R = 82,
    KEYCODE_S = 83,
    KEYCODE_T = 84,
    KEYCODE_U = 85,
    KEYCODE_V = 86,
    KEYCODE_W = 87,
    KEYCODE_X = 88,
    KEYCODE_Y = 89,
    KEYCODE_Z = 90
} key_code_t;

typedef enum
{
    STATE_OFF = 0,
    STATE_PRESSED = 1,
    STATE_PRESSING = 2,
    STATE_RELEASED = 3
} key_state_t;

typedef struct keyboard_state
{
    key_state_t a;
    key_state_t b;
    key_state_t c;
    key_state_t d;
    key_state_t e;
    key_state_t f;
    key_state_t g;
    key_state_t h;
    key_state_t i;
    key_state_t j;
    key_state_t k;
    key_state_t l;
    key_state_t m;
    key_state_t n;
    key_state_t o;
    key_state_t p;
    key_state_t q;
    key_state_t r;
    key_state_t s;
    key_state_t t;
    key_state_t u;
    key_state_t v;
    key_state_t w;
    key_state_t x;
    key_state_t y;
    key_state_t z;
} keyboard_state_t;

typedef struct gamepad_state
{
    key_state_t dpad_up;
    key_state_t dpad_down;
    key_state_t dpad_left;
    key_state_t dpad_right;
    key_state_t down_button;
    key_state_t left_button;
    key_state_t right_button;
    key_state_t up_button;
    key_state_t pause;
    key_state_t select;
    key_state_t left_bumper;
    key_state_t right_bumper;
} gamepad_state_t;

typedef struct input_system
{
    GLFWwindow* window;
    keyboard_state_t keyboard;
    gamepad_state_t gamepad;
    double x_pos, y_pos;
    double x_scroll, y_scroll;
} input_system_t;

GUMO_API void initialize_input(window_t* window);
GUMO_API void update_keyboard();

GUMO_API bool key_pressed(key_code_t code);
GUMO_API bool key_release(key_code_t code);
GUMO_API bool key_pressing(key_code_t code);

#endif //GUMO_ENGINE_INPUT_H
