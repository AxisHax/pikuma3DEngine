#include "display.h"
#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <stdbool.h>


#pragma region Global variables
/// <summary>
/// Pointer to the SDL window data that will be used throughout the application.
/// </summary>
SDL_Window* window = NULL;

/// <summary>
/// Pointer to the SDL renderer data that will be used throughout the application.
/// </summary>
SDL_Renderer* renderer = NULL;

/// <summary>
/// The texture that will hold the data we have in our color_buffer to render to the screen.
/// </summary>
SDL_Texture* color_buffer_texture = NULL;

/// <summary>
/// Pointer to the color buffer.
/// </summary>
uint32_t* color_buffer = NULL;

/// <summary>
/// The window width in pixels.
/// </summary>
int window_width;

/// <summary>
/// The window height in pixels.
/// </summary>
int window_height;
#pragma endregion


/// <summary>
/// Initialize an SDL window and initialize the renderer.
/// </summary>
/// <param name="">Void.</param>
/// <returns>True if everything was able to be initialized, false otherwise.</returns>
bool initialize_window(void)
{
	/* NOTES:
	*	Function can be made static, but I'm intentionally leaving it as is for the true
	*	C experience.
	*/

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		// If everything wasn't initialized correctly, return false.
		fprintf(stderr, "Error initializing SDL.\n");
		return false;
	}

	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);

	window_width = display_mode.w;
	window_height = display_mode.h;

	// Create the SDL window.
	window = SDL_CreateWindow(
		NULL, // The title of the window.
		SDL_WINDOWPOS_CENTERED, // X position of the window.
		SDL_WINDOWPOS_CENTERED, // Y position of the window.
		window_width, // Width.
		window_height, // Height.
		SDL_WINDOW_BORDERLESS // Flags.
	);

	if (!window)
	{
		// There was an error.
		fprintf(stderr, "Error creating the SDL window.\n");
		return false;
	}

	// Create the SDL renderer that accompanies the window.
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer)
	{
		// There was an issue creating the SDL renderer.
		fprintf(stderr, "Error creating SDL renderer.\n");
		return false;
	}

	// Set window to fullscreen.
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	// We were able to initialize things properly.
	return true;
}

/// <summary>
/// Render the color buffer to the screen.
/// </summary>
/// <param name="">Void.</param>
void render_color_buffer(void)
{
	int res = SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		color_buffer,
		(int)window_width * sizeof(uint32_t)
	);

	if (res < 0)
	{
		fprintf(stderr, "Error occured while updating texture: %d.\n", SDL_Error(res));
	}

	res = SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);

	if (res < 0)
	{
		fprintf(stderr, "Error occured while updating texture: %d.\n", SDL_Error(res));
	}
}

/// <summary>
/// Clear the color buffer with the given color.
/// </summary>
/// <param name="color">An ARGB color value.</param>
void clear_color_buffer(uint32_t color)
{
	// int y = 0;
	// int x = 0;

	// // Optimized loop... but its slower.
	// for (int i = 0; i < window_width * window_height; i++, y = (i / window_width), x = (i % window_width))
	// {
	// 	// Set the pixel color.
	// 	color_buffer[(y * window_width) + x] = color;
	// }

	// Slow solution... but it's faster???
	for (int y = 0; y < window_height; y++)
	{
		for (int x = 0; x < window_width; x++)
		{
			// We traverse to each row (the row is incremented by the value of y)
			// and across it (position within the row determined by the value of x)
			// and set the color of that pixel.
			color_buffer[(window_width * y) + x] = color;
		}
	}
}

/// <summary>
/// Draw a grid to the screen.
/// </summary>
/// <param name="color">An ARGB color value to draw.</param>
void draw_grid(uint32_t color)
{
	for (int y = 0; y < window_height; y += 10)
	{
		for (int x = 0; x < window_width; x += 10)
		{
			color_buffer[(window_width * y) + x] = color;
		}
	}
}

/// <summary>
/// Draw a rectangle to the screen.
/// </summary>
/// <param name="color">An ARGB color value to draw.</param>
/// <param name="x_start">Begin x position to draw.</param>
/// <param name="y_start">Begin y position to draw.</param>
/// <param name="width">Witdh of rectangle.</param>
/// <param name="height">Height of rectangle.</param>
void draw_rect(uint32_t color, int loc_x, int loc_y, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			int current_x = loc_x + i;
			int current_y = loc_y + j;
			color_buffer[(window_width * current_y) + current_x] = color;
		}
	}
}

/// <summary>
/// Release allocated resources.
/// </summary>
/// <param name="">Void.</param>
void destroy_window(void)
{
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}