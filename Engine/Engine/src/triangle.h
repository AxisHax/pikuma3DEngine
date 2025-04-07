#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"

/**
 * @brief Number of points on a triangle.
 */
#define N_POINTS_TRIANGLE 3

/**
 * @brief Contains indices referencing vertices in a vertex array that describe a single triangle face.
 */
typedef struct
{
    /**
     * @brief The array index of first vertex of the triangle.
     */
    unsigned int a;
    /**
     * @brief The array index of the second vertex of the triangle.
     */
    unsigned int b;
    /**
     * @brief The array index of the third vertex of the triangle.
     */
    unsigned int c;
} face_t;

/**
 * @brief Stores 2-dimensional points in our triangle.
 */
typedef struct
{
    vec2_t points[N_POINTS_TRIANGLE];
} triangle_t;

#endif