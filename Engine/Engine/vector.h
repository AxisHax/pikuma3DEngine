#ifndef VECTOR_H
#define VECTOR_H

/**
 * @file vector.h
 * @brief This file contains the definition of the vector types.
 */

/**
 * @brief A 2D vector.
 */
typedef struct
{
    /**
     * @brief The x component of the vector.
     */
    float x;
    /**
     * @brief The y component of the vector.
     */
    float y;
} vec2_t;

/**
 * @brief A 3D vector.
 */
typedef struct
{
    /**
     * @brief The x component of the vector.
     */
    float x;
    /**
     * @brief The y component of the vector.
     */
    float y;
    /**
     * @brief The z component of the vector.
     */
    float z;
} vec3_t;

/**
 * @brief Rotate a 3D vector around the x-axis.
 * @param original_vector The original vector to rotate.
 * @param angle The angle to rotate the vector by in radians.
 * @return A new rotated vector.
 */
vec3_t vec3_rotate_x(const vec3_t original_vector, const float angle);

/**
 * @brief Rotate a 3D vector around the y-axis.
 * @param original_vector The original vector to rotate.
 * @param angle The angle to rotate the vector by in radians.
 * @return A new rotated vector.
 */
vec3_t vec3_rotate_y(const vec3_t original_vector, const float angle);

/**
 * @brief Rotate a 3D vector around the z-axis.
 * @param original_vector The original vector to rotate.
 * @param angle The angle to rotate the vector by in radians.
 * @return A new rotated vector.
 */
vec3_t vec3_rotate_z(const vec3_t original_vector, const float angle);

#endif
