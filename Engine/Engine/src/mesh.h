#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

#pragma region Preprocessor directives
/**
 * @brief The total number of vertices for our mesh. In this case the mesh is a cube so there are 8 vertices.
 */

#define N_CUBE_VERTICES 8
/**
 * @brief The total number of triangle faces on our mesh. Cube has 6 faces, each face has 2 triangles each, total
 * of 12 faces.
 */
#define N_CUBE_FACES (6 * 2)
#pragma endregion

/**
 * @brief Array of vertices that represents our cube.
 */
extern vec3_t cube_vertices[N_CUBE_VERTICES];

/**
 * @brief Array of faces which contain the indices for each vertex that compose a single face.
 */
extern face_t cube_faces[N_CUBE_FACES];

/**
 * @brief Structure that describes a 3D mesh.
 */
typedef struct
{
    /**
     * @brief A dynamic array of vertices that compose the mesh. This is a dynamically sized array.
     */
    vec3_t* vertices;

    /**
     * @brief A dynamic array containing the faces of the mesh. This is a dynamically sized array.
     */
    face_t* faces;

    /**
     * @brief The mesh's rotation in 3D space.
     */
    vec3_t rotation;
} mesh_t;

extern mesh_t mesh;

void load_cube_mesh_data(void);
#endif