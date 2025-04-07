#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>
#include "vector.h"

#pragma region Preprocessor directives
/**
 * @brief Target frames per second.
 */
#define FPS 30

/**
 * @brief The time between frames.
 */
#define FRAME_TARGET_TIME (1000 / FPS)
#pragma endregion

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
/**
 * @brief Initialize an SDL window and initialize the renderer.
 * @return True if the window was initialized successfully, false otherwise.
 */
bool initialize_window(void);

/**
 * @brief Setup the color buffer.
 */
void render_color_buffer(void);

/**
 * @brief Clear the color buffer with a specified color.
 * @param color An ARGB color value.
 */
void clear_color_buffer(const uint32_t color);

/**
 * @brief Draw a pixel to the screen.
 * @param x X position to draw.
 * @param y Y position to draw.
 * @param color An ARGB color value.
 */
void draw_pixel(const uint32_t color, const int x, const int y);

/**
 * @brief Draw a grid to the screen.
 * @param color An ARGB color value to draw.
 */
void draw_grid(const uint32_t color);

/**
 * @brief Draw a rectangle to the screen.
 * @param color An ARGB color value.
 * @param loc_x X position to draw.
 * @param loc_y Y position to draw.
 * @param width Witdh of rectangle.
 * @param height Height of rectangle.
 */
void draw_rect(const uint32_t color, const float loc_x, const float loc_y, const int width, const int height);

/**
 * @brief Draw a line from an initial point to a target point using the DDA line drawing algorithm.
 * @param color An ARGB color value.
 * @param initial_point The starting point from which to begin drawing the line.
 * @param target_point The target point to draw the line to.
 */
void draw_line_DDA(const uint32_t color, const vec2_t initial_point, const vec2_t target_point);

/**
 * @brief Release allocated resources.
 */
void destroy_window(void);
#pragma endregion

#endif