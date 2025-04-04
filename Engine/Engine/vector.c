#include <math.h>
#include "vector.h"

vec3_t vec3_rotate_x(const vec3_t original_vector, const float angle)
{
    const vec3_t rotated_vector = {
        .x = original_vector.x,
        .y = original_vector.y * cosf(angle) - original_vector.z * sinf(angle),
        .z = original_vector.y * sinf(angle) + original_vector.z * cosf(angle)
    };

    return rotated_vector;
}

vec3_t vec3_rotate_y(const vec3_t original_vector, const float angle)
{
    const vec3_t rotated_vector = {
        .x = original_vector.x * cosf(angle) - original_vector.z * sinf(angle),
        .y = original_vector.y,
        .z = original_vector.x * sinf(angle) + original_vector.z * cosf(angle)
    };

    return rotated_vector;
}

vec3_t vec3_rotate_z(const vec3_t original_vector, const float angle)
{
    const vec3_t rotated_vector = {
        .x = original_vector.x * cosf(angle) - original_vector.y * sinf(angle),
        .y = original_vector.x * sinf(angle) + original_vector.y * cosf(angle),
        .z = original_vector.z
    };

    return rotated_vector;
}
