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


/**
 * @brief Initialize an SDL window and initialize the renderer.
 * @return True if the window was initialized successfully, false otherwise.
 */
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

/**
 * @brief Setup the color buffer.
 */
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

/**
 * @brief Clear the color buffer with a specified color.
 * @param color An ARGB color value.
 */
void clear_color_buffer(const uint32_t color)
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

/**
 * @brief Draw a pixel to the screen.
 * @param x X position to draw.
 * @param y Y position to draw.
 * @param color An ARGB color value.
 */
void draw_pixel(const int x, const int y, const uint32_t color)
{
	if (x >= 0 && x < window_width && y >= 0 && y < window_height)
	{
		color_buffer[(window_width * y) + x] = color;
	}
}

/**
 * @brief Draw a grid to the screen.
 * @param color An ARGB color value to draw.
 */
void draw_grid(const uint32_t color)
{
	for (int y = 0; y < window_height; y += 10)
	{
		for (int x = 0; x < window_width; x += 10)
		{
			color_buffer[(window_width * y) + x] = color;
		}
	}
}

/**
 * @brief Draw a rectangle to the screen.
 * @param color An ARGB color value.
 * @param loc_x X position to draw.
 * @param loc_y Y position to draw.
 * @param width Witdh of rectangle.
 * @param height Height of rectangle.
 */
void draw_rect(const uint32_t color, const float loc_x, const float loc_y, const int width, const int height)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			// Calculate the current x and y.
			const int current_x = (int)(loc_x + (float)i);
			const int current_y = (int)(loc_y + (float)j);
			
			// Draw the pixel.
			draw_pixel(current_x, current_y, color);
		}
	}
}

/**
 * @brief Initialize the color buffer.
 */
void destroy_window(void)
{
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}