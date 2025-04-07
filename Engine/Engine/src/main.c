#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <stdbool.h>
#include "../include/array.h"
#include "display.h"
#include "vector.h"
#include "mesh.h"

#pragma region Preprocessor directives
/**
 * @brief The factor used to calculate the field of view.
 */
#define FOV_FACTOR (float)650

/**
 * @brief The default color used when drawing things on the screen.
 */
#define DEFAULT_RENDER_COLOR 0xFFFFFF00

/**
 * @brief The default grid color.
 */
#define DEFAULT_GRID_COLOR 0xFF333333

/**
 * @brief The color to use when clearing the color buffer.
 */
#define CLEAR_BUFFER_COLOR 0xFF000000

/**
 * @brief Error message for when the color buffer cannot be allocated.
 */
#define CBUFFER_ALLOCATION_ERR "Error allocating color buffer.\n"

/**
 * @brief Error message for when the color buffer texture cannot be created.
 */
#define CBUFFER_TEXTURE_CREATE_ERR "Error creating the color buffer texture.\n"
#pragma endregion

#pragma region Global variables
/**
 * @brief The rotation amount for the cube points in each direction.
 */
float uniform_axis_rotation = 0.01f;

/**
 * @brief The triangles to render to the screen each frame.
 */
triangle_t* triangles_to_render = NULL;

/**
 * @brief The position of the camera in 3D space.
 */
vec3_t camera_position = { 0, 0, -5 };

/**
 * @brief Cube rotation vector in 3D space.
 */
vec3_t cube_rotation = { 0, 0, 0 };

/**
 * @brief Time elapsed since the previous frame.
 */
unsigned int previous_frame_time = 0;

/**
 * @brief Check if the application is running.
 */
bool is_running = false;
#pragma endregion

/**
 * @brief Initialize an SDL window and initialize the renderer.
 * @return True if the window was initialized successfully, false otherwise.
 */
void setup(void)
{
	// Allocate memory for the color buffer.
	color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);

	if (!color_buffer)
	{
		int _ = fprintf(stderr, CBUFFER_ALLOCATION_ERR);
		return;
	}

	// Create the SDL texture used to display the color buffer.
	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		window_width,
		window_height
	);

	if (!color_buffer_texture)
	{
		int _ = fprintf(stderr, CBUFFER_TEXTURE_CREATE_ERR);
	}
}

/**
 * @brief Process input from the user.
 */
void process_input(void)
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
		// The event triggered when you click the close button on the window.
		case SDL_QUIT:
			// Stop running the application.
			is_running = false;
			break;
		
		// Triggers on key press.
		case SDL_KEYDOWN:
			// If we press the escape key, quit the application.
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				is_running = false;
			}
			break;
	}
}

/**
 * @brief Project a 3D point to a 2D point.
 * @param point The 3D point to project.
 * @return The projected 2D point.
 */
vec2_t project(const vec3_t point)
{
	const vec2_t projected_point =
	{
		.x = (FOV_FACTOR * point.x) / point.z,
		.y = (FOV_FACTOR * point.y) / point.z
	};

	return projected_point;
}

/**
 * @brief Update the game world.
 */
void update(void)
{
	// Wait some time until the target frame time in ms is reached.
	const int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

	// Only delay execution if we are running too fast.
	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
	{
		SDL_Delay(time_to_wait);
	}

	// Initialize dynamic array of triangles to render.
	triangles_to_render = NULL;
	
	// How many ms passed since the last frame? SDL has a function for this.
	previous_frame_time = SDL_GetTicks();
	
	// Set the rotation amount for the cube points in each direction.
	cube_rotation.x += uniform_axis_rotation;
	cube_rotation.y += uniform_axis_rotation;
	cube_rotation.z += uniform_axis_rotation;

	// Loop through all the triangle faces that compose our cube mesh.
	for (int i = 0; i < N_MESH_FACES; i++)
	{
		face_t mesh_face = mesh_faces[i];
		
		vec3_t face_vertices[3];
		face_vertices[0] = mesh_vertices[mesh_face.a - 1];
		face_vertices[1] = mesh_vertices[mesh_face.b - 1];
		face_vertices[2] = mesh_vertices[mesh_face.c - 1];

		triangle_t projected_triangle;
		
		// Loop all three vertices of the current face and apply transformations.
		for (int j = 0; j < 3; j++)
		{
			vec3_t transformed_vertex = face_vertices[j];

			transformed_vertex = vec3_rotate_x(transformed_vertex, cube_rotation.x);
			transformed_vertex = vec3_rotate_y(transformed_vertex, cube_rotation.y);
			transformed_vertex = vec3_rotate_z(transformed_vertex, cube_rotation.z);

			// Translate vertex away from camera.
			transformed_vertex.z -= camera_position.z;

			// Project the current vertex.
			vec2_t projected_point = project(transformed_vertex);
			
			// Scale and translate the projected point to the middle of the screen.
			projected_point.x += (window_width / 2);
			projected_point.y += (window_height / 2);
			
			projected_triangle.points[j] = projected_point;
		}

		// Save the projected triangle to the dynamic array of triangles to render.
		array_push(triangles_to_render, projected_triangle);
	}
}

/**
 * @brief Render the color buffer to the screen.
 */
void render(void)
{
	draw_grid(DEFAULT_GRID_COLOR);
	
	// Loop all projected triangles and render them.
	const int num_triangles = array_length(triangles_to_render);
	
	for (int i = 0; i < num_triangles; i++)
	{
		const triangle_t triangle = triangles_to_render[i];
		const int desired_width = 10;
		const int desired_height = 10;

		// Draw vertex points.
		draw_rect(
			DEFAULT_RENDER_COLOR,
			triangle.points[0].x,
			triangle.points[0].y,
			desired_width,
			desired_height
			);
		draw_rect(
			DEFAULT_RENDER_COLOR,
			triangle.points[1].x,
			triangle.points[1].y,
			desired_width,
			desired_height
			);
		draw_rect(
			DEFAULT_RENDER_COLOR,
			triangle.points[2].x,
			triangle.points[2].y,
			desired_width,
			desired_height
			);

		// Draw the lines of the triangle.
		draw_line_DDA(
			0xFF00FF00,
			triangle.points[0],
			triangle.points[1]
			);
		draw_line_DDA(
			0xFF00FF00,
			triangle.points[1],
			triangle.points[2]
			);
		draw_line_DDA(
			0xFF00FF00,
			triangle.points[2],
			triangle.points[0]
			);
	}

	// Clear the array of triangles to render every frame loop.
	array_free(triangles_to_render);
	
	render_color_buffer();
	clear_color_buffer(CLEAR_BUFFER_COLOR);
	
	// Update the screen with the color we chose.
	SDL_RenderPresent(renderer);
}

/**
 * @brief Main entry point of the application.
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 * @return 0 if the application ran successfully, 1 otherwise.
 */
int main(int argc, char* argv[])
{
	is_running = initialize_window();

	setup();

	// Render loop. Also called a game loop.
	while (is_running)
	{
		process_input();
		update();
		render();
	}

	destroy_window();
	
	return 0;
}