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

#endif
