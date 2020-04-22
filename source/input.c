#include <gumo/input.h>

static input_system_t input_system;

static key_state_t update_keyboard_state(key_code_t code, key_state_t previous_state)
{
    int current_state = glfwGetKey(input_system.window, (int) code);
    if (current_state == GLFW_PRESS)
    {
        if(previous_state == STATE_OFF)
            return STATE_PRESSED;

        if(previous_state == STATE_PRESSED || previous_state == STATE_PRESSING)
            return STATE_PRESSING;

        if (previous_state == STATE_RELEASED)
            return STATE_OFF;
    }
    else
    {
        if(previous_state == STATE_PRESSED || previous_state == STATE_PRESSING)
            return STATE_RELEASED;
        else
            return STATE_OFF;
    }
}

static key_state_t get_key_state(key_code_t code)
{
    switch (code)
    {
        case KEYCODE_A: return input_system.keyboard.a;
        case KEYCODE_D: return input_system.keyboard.d;
        case KEYCODE_S: return input_system.keyboard.s;
        case KEYCODE_W: return input_system.keyboard.w;
        case KEYCODE_Q: return input_system.keyboard.q;
        case KEYCODE_E: return input_system.keyboard.e;
        default: return STATE_OFF;
    }
}

void initialize_input(window_t* window)
{
    input_system.keyboard.a = STATE_OFF;
    input_system.keyboard.b = STATE_OFF;
    input_system.keyboard.c = STATE_OFF;
    input_system.keyboard.d = STATE_OFF;
    input_system.keyboard.e = STATE_OFF;
    input_system.keyboard.f = STATE_OFF;
    input_system.keyboard.g = STATE_OFF;
    input_system.keyboard.h = STATE_OFF;
    input_system.keyboard.i = STATE_OFF;
    input_system.keyboard.j = STATE_OFF;
    input_system.keyboard.k = STATE_OFF;
    input_system.keyboard.l = STATE_OFF;
    input_system.keyboard.m = STATE_OFF;
    input_system.keyboard.n = STATE_OFF;
    input_system.keyboard.o = STATE_OFF;
    input_system.keyboard.p = STATE_OFF;
    input_system.keyboard.q = STATE_OFF;
    input_system.keyboard.r = STATE_OFF;
    input_system.keyboard.s = STATE_OFF;
    input_system.keyboard.t = STATE_OFF;
    input_system.keyboard.u = STATE_OFF;
    input_system.keyboard.v = STATE_OFF;
    input_system.keyboard.w = STATE_OFF;
    input_system.keyboard.x = STATE_OFF;
    input_system.keyboard.y = STATE_OFF;
    input_system.keyboard.z = STATE_OFF;

    input_system.window = window->window;
}

void update_keyboard()
{
    keyboard_state_t* keyboard = &input_system.keyboard;

    keyboard->a = update_keyboard_state(KEYCODE_A, keyboard->a);
    keyboard->b = update_keyboard_state(KEYCODE_B, keyboard->b);
    keyboard->c = update_keyboard_state(KEYCODE_C, keyboard->c);
    keyboard->d = update_keyboard_state(KEYCODE_D, keyboard->d);
    keyboard->e = update_keyboard_state(KEYCODE_E, keyboard->e);
    keyboard->f = update_keyboard_state(KEYCODE_F, keyboard->f);
    keyboard->g = update_keyboard_state(KEYCODE_G, keyboard->g);
    keyboard->h = update_keyboard_state(KEYCODE_H, keyboard->h);
    keyboard->i = update_keyboard_state(KEYCODE_I, keyboard->i);
    keyboard->j = update_keyboard_state(KEYCODE_J, keyboard->j);
    keyboard->k = update_keyboard_state(KEYCODE_K, keyboard->k);
    keyboard->l = update_keyboard_state(KEYCODE_L, keyboard->l);
    keyboard->m = update_keyboard_state(KEYCODE_M, keyboard->m);
    keyboard->n = update_keyboard_state(KEYCODE_N, keyboard->n);
    keyboard->o = update_keyboard_state(KEYCODE_O, keyboard->o);
    keyboard->p = update_keyboard_state(KEYCODE_P, keyboard->p);
    keyboard->q = update_keyboard_state(KEYCODE_Q, keyboard->q);
    keyboard->r = update_keyboard_state(KEYCODE_R, keyboard->r);
    keyboard->s = update_keyboard_state(KEYCODE_S, keyboard->s);
    keyboard->t = update_keyboard_state(KEYCODE_T, keyboard->t);
    keyboard->u = update_keyboard_state(KEYCODE_U, keyboard->u);
    keyboard->v = update_keyboard_state(KEYCODE_V, keyboard->v);
    keyboard->w = update_keyboard_state(KEYCODE_W, keyboard->w);
    keyboard->x = update_keyboard_state(KEYCODE_X, keyboard->x);
    keyboard->y = update_keyboard_state(KEYCODE_Y, keyboard->y);
    keyboard->z = update_keyboard_state(KEYCODE_Z, keyboard->z);

    glfwGetCursorPos(input_system.window, &input_system.x_pos, &input_system.y_pos);
}

inline bool key_pressed(key_code_t code)
{
    key_state_t state = get_key_state(code);
    return state == STATE_PRESSED;
}

inline bool key_release(key_code_t code)
{
    key_state_t state = get_key_state(code);
    return state == STATE_RELEASED;
}

inline bool key_pressing(key_code_t code)
{
    key_state_t state = get_key_state(code);
    return state == STATE_PRESSED || state == STATE_PRESSING;
}