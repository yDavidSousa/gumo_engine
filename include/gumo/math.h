#ifndef GUMO_ENGINE_MATH_H
#define GUMO_ENGINE_MATH_H

#include <math.h>
#include "core.h"

#define PI 3.1415926536f
#define DEG_TO_RAD ((PI * 2) / 360.0f)
#define RAD_TO_DEG (360.0f / (PI * 2))
#define COS(value) cosf(value)
#define SIN(value) sinf(value)

typedef struct vector2
{
    float x, y;
} vector2_t;

GUMO_API const vector2_t VECTOR2_ZERO;
GUMO_API const vector2_t VECTOR2_ONE;
GUMO_API const vector2_t VECTOR2_UP;
GUMO_API const vector2_t VECTOR2_DOWN;
GUMO_API const vector2_t VECTOR2_LEFT;
GUMO_API const vector2_t VECTOR2_RIGHT;

typedef struct vector3
{
    float x, y, z;
} vector3_t;

GUMO_API const vector3_t VECTOR3_ZERO;
GUMO_API const vector3_t VECTOR3_ONE;
GUMO_API const vector3_t VECTOR3_UP;
GUMO_API const vector3_t VECTOR3_DOWN;
GUMO_API const vector3_t VECTOR3_LEFT;
GUMO_API const vector3_t VECTOR3_RIGHT;
GUMO_API const vector3_t VECTOR3_FORWARD;

typedef struct vector4
{
    float x, y, z, w;
} vector4_t;

typedef struct matrix2
{
    float m11, m21;
    float m12, m22;
} matrix2_t;

GUMO_API const matrix2_t MATRIX2_ZERO;
GUMO_API const matrix2_t MATRIX2_IDENTITY;

typedef struct matrix3
{
    float m11, m21, m31;
    float m12, m22, m32;
    float m13, m23, m33;
} matrix3_t;

GUMO_API const matrix3_t MATRIX3_ZERO;
GUMO_API const matrix3_t MATRIX3_IDENTITY;

typedef struct matrix4
{
    float m11, m12, m13, m14;
    float m21, m22, m23, m24;
    float m31, m32, m33, m34;
    float m41, m42, m43, m44;
} matrix4_t;

GUMO_API const matrix4_t MATRIX4_ZERO;
GUMO_API const matrix4_t MATRIX4_IDENTITY;

GUMO_API float to_radians(float degrees);
GUMO_API float to_degrees(float radians);

GUMO_API vector3_t vector3_add(vector3_t v0, vector3_t v1);
GUMO_API vector3_t vector3_add_f(vector3_t v0, float f);
GUMO_API vector3_t vector3_subtract(vector3_t v0, vector3_t v1);
GUMO_API vector3_t vector3_subtract_f(vector3_t v0, float f);
GUMO_API vector3_t vector3_multiply(vector3_t v0, vector3_t v1);
GUMO_API vector3_t vector3_multiply_f(vector3_t v0, float f);

GUMO_API matrix4_t matrix4_ortho(float left, float right, float bottom, float top, float near, float far);
GUMO_API matrix4_t matrix4_translate(matrix4_t m0, vector3_t v0);
GUMO_API matrix4_t matrix4_translation(matrix4_t m0, vector3_t v0);
GUMO_API matrix4_t matrix4_rotate(float angle, vector3_t axis);
GUMO_API matrix4_t matrix4_scale(matrix4_t m0, vector3_t v0);
GUMO_API matrix4_t matrix4_multiply(matrix4_t m0, matrix4_t m1);
GUMO_API matrix4_t matrix4_inverse(matrix4_t m0);

#endif //GUMO_ENGINE_MATH_H