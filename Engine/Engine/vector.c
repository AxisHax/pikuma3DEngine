#include <math.h>
#include "vector.h"

vec3_t vec3_rotate_x(vec3_t originalVector, float angle)
{
    vec3_t rotatedVector = {
        .x = originalVector.x,
        .y = originalVector.y * cos(angle) - originalVector.z * sin(angle),
        .z = originalVector.y * sin(angle) + originalVector.z * cos(angle)
    };

    return rotatedVector;
}

vec3_t vec3_rotate_y(vec3_t originalVector, float angle)
{
    vec3_t rotatedVector = {
        .x = originalVector.x * cos(angle) - originalVector.z * sin(angle),
        .y = originalVector.y,
        .z = originalVector.x * sin(angle) + originalVector.z * cos(angle)
    };

    return rotatedVector;
}

vec3_t vec3_rotate_z(vec3_t originalVector, float angle)
{
    vec3_t rotatedVector = {
        .x = originalVector.x * cos(angle) - originalVector.y * sin(angle),
        .y = originalVector.x * sin(angle) + originalVector.y * cos(angle),
        .z = originalVector.z
    };

    return rotatedVector;
}
