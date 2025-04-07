#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

#pragma region Preprocessor directives
/**
 * @brief The total number of vertices for our mesh. In this case the mesh is a cube so there are 8 vertices.
 */

#define N_MESH_VERTICES 8
/**
 * @brief The total number of triangle faces on our mesh. Cube has 6 faces, each face has 2 triangles each, total
 * of 12 faces.
 */
#define N_MESH_FACES (6 * 2)
#pragma endregion

/**
 * @brief Array of vertices that represents our cube.
 */
extern vec3_t mesh_vertices[N_MESH_VERTICES];

/**
 * @brief Array of faces which contain the indices for each vertex that compose a single face.
 */
extern face_t mesh_faces[N_MESH_FACES];
#endif