#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <stdbool.h>
#include "display.h"


#pragma region Global variables
/// <summary>
/// Boolean that keeps track of the running state of the applicaion.
/// </summary>
bool is_running = false;
#pragma endregion

/// <summary>
/// Setup the color buffer.
/// </summary>
/// <param name="">Void.</param>
void setup(void)
{
	// Allocate memory for the color buffer.
	color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);

	if (!color_buffer)
	{
		fprintf(stderr, "Error allocating color buffer.\n");
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
		fprintf(stderr, "Error creating the color buffer texture.\n");
		return;
	}
}

/// <summary>
/// Process the user's input.
/// </summary>
/// <param name="">Void.</param>
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

void update(void)
{

}

/// <summary>
/// Render visuals to the screen.
/// </summary>
/// <param name="">Void.</param>
void render(void)
{
	// Set the color for drawing to the screen.
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	// Clear the color buffer with the above color.
	SDL_RenderClear(renderer);

	draw_grid(0xFF333333);
	draw_pixel(20, 20, 0xFFFFFF00);
	draw_rect(0xFF00FFFF, 200, 200, 300, 100);

	render_color_buffer();
	clear_color_buffer(0xFF000000);
	
	// Update the screen with the color we chose.
	SDL_RenderPresent(renderer);
}

/// <summary>
/// Entry point of the program.
/// </summary>
/// <param name="argc">Number of command-line arguments.</param>
/// <param name="argv">Command-line arguments.</param>
/// <returns>0 on successful execution of the program, other values if program execution was not successful.</returns>
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