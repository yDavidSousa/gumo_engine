#include <gumo/math.h>

const vector2_t VECTOR2_ZERO = {0, 0};
const vector2_t VECTOR2_ONE = {1, 1};
const vector2_t VECTOR2_UP = {0, 1};
const vector2_t VECTOR2_DOWN = {0, -1};
const vector2_t VECTOR2_LEFT = {-1, 0};
const vector2_t VECTOR2_RIGHT = {1, 0};

const vector3_t VECTOR3_ZERO = {0, 0, 0};
const vector3_t VECTOR3_ONE = {1, 1, 1};
const vector3_t VECTOR3_UP = {0, 1, 0};
const vector3_t VECTOR3_DOWN = {0, -1, 0};
const vector3_t VECTOR3_LEFT = {-1, 0, 0};
const vector3_t VECTOR3_RIGHT = {1, 0, 0};
const vector3_t VECTOR3_FORWARD = {0, 0, 1};

const matrix2_t MATRIX2_ZERO =
{
        0, 0,
        0, 0,
};

const matrix2_t MATRIX2_IDENTITY =
{
        1, 0,
        0, 1,
};

const matrix3_t MATRIX3_ZERO =
{
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
};

const matrix3_t MATRIX3_IDENTITY =
{
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
};

const matrix4_t MATRIX4_ZERO =
{
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
};

const matrix4_t MATRIX4_IDENTITY =
{
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
};

float to_radians(float degrees)
{
    return (degrees * PI / 180.0f);
}

float to_degrees(float radians)
{
    return (radians * 180.0f / PI);
}

// ##############################
// VECTOR
// #############################

vector3_t vector3_add(vector3_t v0, vector3_t v1)
{
    vector3_t result;
    result.x = v0.x + v1.x;
    result.y = v0.y + v1.y;
    result.z = v0.z + v1.z;
    return result;
}

vector3_t vector3_add_f(vector3_t v0, float f)
{
    vector3_t result;
    result.x = v0.x + f;
    result.y = v0.y + f;
    result.z = v0.z + f;
    return result;
}

vector3_t vector3_subtract(vector3_t v0, vector3_t v1)
{
    vector3_t result;
    result.x = v0.x - v1.x;
    result.y = v0.y - v1.y;
    result.z = v0.z - v1.z;
    return result;
}

vector3_t vector3_subtract_f(vector3_t v0, float f)
{
    vector3_t result;
    result.x = v0.x - f;
    result.y = v0.y - f;
    result.z = v0.z - f;
    return result;
}

vector3_t vector3_multiply(vector3_t v0, vector3_t v1)
{
    vector3_t result;
    result.x = v0.x * v1.x;
    result.y = v0.y * v1.y;
    result.z = v0.z * v1.z;
    return result;
}

vector3_t vector3_multiply_f(vector3_t v0, float f)
{
    vector3_t result;
    result.x = v0.x * f;
    result.y = v0.y * f;
    result.z = v0.z * f;
    return result;
}

// ##############################
// MATRIX
// #############################

matrix4_t matrix4_ortho(float left, float right, float bottom, float top, float near, float far)
{
    matrix4_t result;

    result.m11 = 2.0f / (right - left);
    result.m12 = 0.0f;
    result.m13 = 0.0f;
    result.m14 = -((right + left) / (right - left));

    result.m21 = 0.0f;
    result.m22 = 2.0f / (top - bottom);
    result.m23 = 0.0f;
    result.m24 = -((top + bottom) / (top - bottom));

    result.m31 = 0.0f;
    result.m32 = 0.0f;
    result.m33 = -2.0f / (far - near);
    result.m34 = -((far + near) / (far - near));

    result.m41 = 0.0f;
    result.m42 = 0.0f;
    result.m43 = 0.0f;
    result.m44 = 1.0f;

    return result;
}

matrix4_t matrix4_scale(matrix4_t m0, vector3_t v0)
{
    matrix4_t result = m0;
    result.m11 = m0.m11 * v0.x;
    result.m22 = m0.m22 * v0.y;
    result.m33 = m0.m33 * v0.z;
    return result;
}

matrix4_t matrix4_translate(matrix4_t m0, vector3_t v0)
{
    matrix4_t result = m0;

    result.m14 = m0.m14 + v0.x;
    result.m24 = m0.m24 + v0.y;
    result.m34 = m0.m34 + v0.z;

    return result;
}

matrix4_t matrix4_translation(matrix4_t m0, vector3_t v0)
{
    matrix4_t result = m0;

    result.m14 = v0.x;
    result.m24 = v0.y;
    result.m34 = v0.z;

    return result;
}

matrix4_t matrix4_rotate(matrix4_t m, float angle, vector3_t axis)
{
    matrix4_t result;

    float cos = COS(angle);
    float sin = SIN(angle);
    float one_cos = 1.0f - cos;

    float xx = axis.x * axis.x;
    float xy = axis.x * axis.y;
    float xz = axis.x * axis.z;
    float yy = axis.y * axis.y;
    float yz = axis.y * axis.z;
    float zz = axis.z * axis.z;
    float l = xx + yy + zz;
    float sqrt_l = sqrtf(l);

    result.m11 = (xx + (yy + zz) * cos) / l;
    result.m12 = (xy * one_cos - axis.z * sqrt_l * sin) / l;
    result.m13 = (xz * one_cos + axis.y * sqrt_l * sin) / l;
    result.m14 = 0.0f;

    result.m21 = (xy * one_cos + axis.z * sqrt_l * sin) / l;
    result.m22 = (yy + (xx + zz) * cos) / l;
    result.m23 = (yz * one_cos - axis.x * sqrt_l * sin) / l;
    result.m24 = 0.0f;

    result.m31 = (xz * one_cos - axis.y * sqrt_l * sin) / l;
    result.m32 = (yz * one_cos + axis.x * sqrt_l * sin) / l;
    result.m33 = (zz + (xx + yy) * cos) / l;
    result.m34 = 0.0f;

    result.m41 = 0.0f;
    result.m42 = 0.0f;
    result.m43 = 0.0f;
    result.m44 = 1.0f;

    return result;
}

matrix4_t matrix4_multiply(matrix4_t m0, matrix4_t m1)
{
    matrix4_t result;

    result.m11 = (m0.m11 * m1.m11) + (m0.m12 * m1.m21) + (m0.m13 * m1.m31) + (m0.m14 * m1.m41);
    result.m12 = (m0.m11 * m1.m12) + (m0.m12 * m1.m22) + (m0.m13 * m1.m32) + (m0.m14 * m1.m42);
    result.m13 = (m0.m11 * m1.m13) + (m0.m12 * m1.m23) + (m0.m13 * m1.m33) + (m0.m14 * m1.m43);
    result.m14 = (m0.m11 * m1.m14) + (m0.m12 * m1.m24) + (m0.m13 * m1.m34) + (m0.m14 * m1.m44);

    result.m21 = (m0.m21 * m1.m11) + (m0.m22 * m1.m21) + (m0.m23 * m1.m31) + (m0.m24 * m1.m41);
    result.m22 = (m0.m21 * m1.m12) + (m0.m22 * m1.m22) + (m0.m23 * m1.m32) + (m0.m24 * m1.m42);
    result.m23 = (m0.m21 * m1.m13) + (m0.m22 * m1.m23) + (m0.m23 * m1.m33) + (m0.m24 * m1.m43);
    result.m24 = (m0.m21 * m1.m14) + (m0.m22 * m1.m24) + (m0.m23 * m1.m34) + (m0.m24 * m1.m44);

    result.m31 = (m0.m31 * m1.m11) + (m0.m32 * m1.m21) + (m0.m33 * m1.m31) + (m0.m34 * m1.m41);
    result.m32 = (m0.m31 * m1.m12) + (m0.m32 * m1.m22) + (m0.m33 * m1.m32) + (m0.m34 * m1.m42);
    result.m33 = (m0.m31 * m1.m13) + (m0.m32 * m1.m23) + (m0.m33 * m1.m33) + (m0.m34 * m1.m43);
    result.m34 = (m0.m31 * m1.m14) + (m0.m32 * m1.m24) + (m0.m33 * m1.m34) + (m0.m34 * m1.m44);

    result.m41 = (m0.m41 * m1.m11) + (m0.m42 * m1.m21) + (m0.m43 * m1.m31) + (m0.m44 * m1.m41);
    result.m42 = (m0.m41 * m1.m12) + (m0.m42 * m1.m22) + (m0.m43 * m1.m32) + (m0.m44 * m1.m42);
    result.m43 = (m0.m41 * m1.m13) + (m0.m42 * m1.m23) + (m0.m43 * m1.m33) + (m0.m44 * m1.m43);
    result.m44 = (m0.m41 * m1.m14) + (m0.m42 * m1.m24) + (m0.m43 * m1.m34) + (m0.m44 * m1.m44);

    return result;
}

matrix4_t matrix4_inverse(matrix4_t m0)
{
    matrix4_t result;

    result.m11 =   m0.m22 * m0.m33 * m0.m44
                 - m0.m22 * m0.m34 * m0.m43
                 - m0.m32 * m0.m23 * m0.m44
                 + m0.m32 * m0.m24 * m0.m43
                 + m0.m42 * m0.m23 * m0.m34
                 - m0.m42 * m0.m24 * m0.m33;
    result.m12 = - m0.m21 * m0.m33 * m0.m44
                 + m0.m21 * m0.m34 * m0.m43
                 + m0.m31 * m0.m23 * m0.m44
                 - m0.m31 * m0.m24 * m0.m43
                 - m0.m41 * m0.m23 * m0.m34
                 + m0.m41 * m0.m24 * m0.m33;
    result.m13 =   m0.m21 * m0.m32 * m0.m44
                 - m0.m21 * m0.m34 * m0.m42
                 - m0.m31 * m0.m22 * m0.m44
                 + m0.m31 * m0.m24 * m0.m42
                 + m0.m41 * m0.m22 * m0.m34
                 - m0.m41 * m0.m24 * m0.m32;
    result.m14 = - m0.m21 * m0.m32 * m0.m43
                 + m0.m21 * m0.m33 * m0.m42
                 + m0.m31 * m0.m22 * m0.m43
                 - m0.m31 * m0.m23 * m0.m42
                 - m0.m41 * m0.m22 * m0.m33
                 + m0.m41 * m0.m23 * m0.m32;
    result.m21 = - m0.m12 * m0.m33 * m0.m44
                 + m0.m12 * m0.m34 * m0.m43
                 + m0.m32 * m0.m13 * m0.m44
                 - m0.m32 * m0.m14 * m0.m43
                 - m0.m42 * m0.m13 * m0.m34
                 + m0.m42 * m0.m14 * m0.m33;
    result.m22 =   m0.m11 * m0.m33 * m0.m44
                 - m0.m11 * m0.m34 * m0.m43
                 - m0.m31 * m0.m13 * m0.m44
                 + m0.m31 * m0.m14 * m0.m43
                 + m0.m41 * m0.m13 * m0.m34
                 - m0.m41 * m0.m14 * m0.m33;
    result.m23 = - m0.m11 * m0.m32 * m0.m44
                 + m0.m11 * m0.m34 * m0.m42
                 + m0.m31 * m0.m12 * m0.m44
                 - m0.m31 * m0.m14 * m0.m42
                 - m0.m41 * m0.m12 * m0.m34
                 + m0.m41 * m0.m14 * m0.m32;
    result.m24 =   m0.m11 * m0.m32 * m0.m43
                 - m0.m11 * m0.m33 * m0.m42
                 - m0.m31 * m0.m12 * m0.m43
                 + m0.m31 * m0.m13 * m0.m42
                 + m0.m41 * m0.m12 * m0.m33
                 - m0.m41 * m0.m13 * m0.m32;
    result.m31 =   m0.m12 * m0.m23 * m0.m44
                 - m0.m12 * m0.m24 * m0.m43
                 - m0.m22 * m0.m13 * m0.m44
                 + m0.m22 * m0.m14 * m0.m43
                 + m0.m42 * m0.m13 * m0.m24
                 - m0.m42 * m0.m14 * m0.m23;
    result.m32 = - m0.m11 * m0.m23 * m0.m44
                 + m0.m11 * m0.m24 * m0.m43
                 + m0.m21 * m0.m13 * m0.m44
                 - m0.m21 * m0.m14 * m0.m43
                 - m0.m41 * m0.m13 * m0.m24
                 + m0.m41 * m0.m14 * m0.m23;
    result.m33 =  m0.m11 * m0.m22 * m0.m44
                 - m0.m11 * m0.m24 * m0.m42
                 - m0.m21 * m0.m12 * m0.m44
                 + m0.m21 * m0.m14 * m0.m42
                 + m0.m41 * m0.m12 * m0.m24
                 - m0.m41 * m0.m14 * m0.m22;
    result.m34 = -m0.m11 * m0.m22 * m0.m43
                 + m0.m11 * m0.m23 * m0.m42
                 + m0.m21 * m0.m12 * m0.m43
                 - m0.m21 * m0.m13 * m0.m42
                 - m0.m41 * m0.m12 * m0.m23
                 + m0.m41 * m0.m13 * m0.m22;
    result.m41 = -m0.m12 * m0.m23 * m0.m34
                 + m0.m12 * m0.m24 * m0.m33
                 + m0.m22 * m0.m13 * m0.m34
                 - m0.m22 * m0.m14 * m0.m33
                 - m0.m32 * m0.m13 * m0.m24
                 + m0.m32 * m0.m14 * m0.m23;
    result.m42 =  m0.m11 * m0.m23 * m0.m34
                 - m0.m11 * m0.m24 * m0.m33
                 - m0.m21 * m0.m13 * m0.m34
                 + m0.m21 * m0.m14 * m0.m33
                 + m0.m31 * m0.m13 * m0.m24
                 - m0.m31 * m0.m14 * m0.m23;
    result.m43 = -m0.m11 * m0.m22 * m0.m34
                 + m0.m11 * m0.m24 * m0.m32
                 + m0.m21 * m0.m12 * m0.m34
                 - m0.m21 * m0.m14 * m0.m32
                 - m0.m31 * m0.m12 * m0.m24
                 + m0.m31 * m0.m14 * m0.m22;
    result.m44 =   m0.m11 * m0.m22 * m0.m33
                 - m0.m11 * m0.m23 * m0.m32
                 - m0.m21 * m0.m12 * m0.m33
                 + m0.m21 * m0.m13 * m0.m32
                 + m0.m31 * m0.m12 * m0.m23
                 - m0.m31 * m0.m13 * m0.m22;

    float inverted_determinant = 1.0f / (m0.m11 * result.m11 + m0.m21 * result.m12 + m0.m31 * result.m13 + m0.m41 * result.m14);

    result.m11 *= inverted_determinant;
    result.m12 *= inverted_determinant;
    result.m13 *= inverted_determinant;
    result.m14 *= inverted_determinant;
    result.m21 *= inverted_determinant;
    result.m22 *= inverted_determinant;
    result.m23 *= inverted_determinant;
    result.m24 *= inverted_determinant;
    result.m31 *= inverted_determinant;
    result.m32 *= inverted_determinant;
    result.m33 *= inverted_determinant;
    result.m34 *= inverted_determinant;
    result.m41 *= inverted_determinant;
    result.m42 *= inverted_determinant;
    result.m43 *= inverted_determinant;
    result.m44 *= inverted_determinant;

    return result;
}