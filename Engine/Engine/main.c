#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <stdbool.h>
#include "display.h"
#include "vector.h"

#pragma region Preprocessor directives
/**
 * @brief The number of points in the cube.
 */
#define N_POINTS (int)(9 * 9 * 9)

/**
 * @brief The factor used to calculate the field of view.
 */
#define FOV_FACTOR (float)650

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
float uniform_axis_rotation = 0.005f;
/**
 * @brief Array of 2D vectors that will hold the projected points.
 */
vec2_t projected_points[N_POINTS];

/**
 * @brief Array of 3D vectors that will hold the points of a cube.
 */
vec3_t cube_points[N_POINTS];

/**
 * @brief The position of the camera in 3D space.
 */
vec3_t camera_position = { 0, 0, -5 };

/**
 * @brief Cube rotation vector in 3D space.
 */
vec3_t cube_rotation = { 0, 0, 0};

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

	
	int point_count = 0;
	float uniform_point_offset = 0.25f;

	// Loop through all points in the cube.
	for (float x = -1; x <= 1; x += uniform_point_offset)
	{
		for (float y = -1; y <= 1; y += uniform_point_offset)
		{
			for (float z = -1; z <= 1; z += uniform_point_offset)
			{
				vec3_t new_point = { .x = x, .y = y, .z = z };
				cube_points[point_count++] = new_point;
			}
		}
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
	// Set the rotation amount for the cube points in each direction.
	cube_rotation.x += uniform_axis_rotation;
	cube_rotation.y += uniform_axis_rotation;
	cube_rotation.z += uniform_axis_rotation;
	
	for (int i = 0; i < N_POINTS; i++)
	{
		// Current point in the cube.
		vec3_t point = cube_points[i];

		// Get the transformed points to update projections.
		vec3_t transformed_point = vec3_rotate_x(point, cube_rotation.x);
		transformed_point = vec3_rotate_y(transformed_point, cube_rotation.y);
		transformed_point = vec3_rotate_z(transformed_point, cube_rotation.z);

		// Translate point away from the camera.
		transformed_point.z -= camera_position.z;

		// Project the current point.
		vec2_t projected_point = project(transformed_point);

		// Save project 2D vector in the array of projected points.
		projected_points[i] = projected_point;
	}
}

/**
 * @brief Render the color buffer to the screen.
 */
void render(void)
{

	draw_grid(DEFAULT_GRID_COLOR);

	// Loop all projected points and render them.
	for (int i = 0; i < N_POINTS; i++)
	{
		vec2_t projected_point = projected_points[i];
		draw_rect(
			0x0FFFFFF00,
			projected_point.x + (window_width / 2),
			projected_point.y + (window_height / 2),
			4,
			4
			);
	}

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