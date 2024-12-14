#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>

#pragma region Global variables
/// <summary>
/// Pointer to the SDL window data that will be used throughout the application.
/// </summary>
extern SDL_Window* window;

/// <summary>
/// Pointer to the SDL renderer data that will be used throughout the application.
/// </summary>
extern SDL_Renderer* renderer;

/// <summary>
/// The texture that will hold the data we have in our color_buffer to render to the screen.
/// </summary>
extern SDL_Texture* color_buffer_texture;

/// <summary>
/// Boolean that keeps track of the running state of the applicaion.
/// </summary>
extern bool is_running;

/// <summary>
/// Pointer to the color buffer.
/// </summary>
extern uint32_t* color_buffer;

/// <summary>
/// The window width in pixels.
/// </summary>
extern int window_width;

/// <summary>
/// The window height in pixels.
/// </summary>
extern int window_height;
#pragma endregion

#pragma region Function definitions
/// <summary>
/// Initialize an SDL window and initialize the renderer.
/// </summary>
/// <param name="">Void.</param>
/// <returns>True if everything was able to be initialized, false otherwise.</returns>
bool initialize_window(void);

/// <summary>
/// Render the color buffer to the screen.
/// </summary>
/// <param name="">Void.</param>
void render_color_buffer(void);

/// <summary>
/// Clear the color buffer with the given color.
/// </summary>
/// <param name="color">An ARGB color value.</param>
void clear_color_buffer(uint32_t color);

/// <summary>
/// Draw a grid to the screen.
/// </summary>
/// <param name="color">An ARGB color value to draw.</param>
void draw_grid(uint32_t color);

/// <summary>
/// Draw a rectangle to the screen.
/// </summary>
/// <param name="color">An ARGB color value to draw.</param>
/// <param name="x_start">Begin x position to draw.</param>
/// <param name="y_start">Begin y position to draw.</param>
/// <param name="width">Witdh of rectangle.</param>
/// <param name="height">Height of rectangle.</param>
void draw_rect(uint32_t color, int loc_x, int loc_y, int width, int height);

/// <summary>
/// Release allocated resources.
/// </summary>
/// <param name="">Void.</param>
void destroy_window(void);
#pragma endregion

#endif