#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>

#pragma region MyRegion
/// <summary>
/// Pointer to the SDL window data that will be used throughout the application.
/// </summary>
SDL_Window* window = NULL;

/// <summary>
/// Pointer to the SDL renderer data that will be used throughout the application.
/// </summary>
SDL_Renderer* renderer = NULL;

/// <summary>
/// Boolean that keeps track of the running state of the applicaion.
/// </summary>
bool is_running = false;
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
	
	// Create the SDL window.
	window = SDL_CreateWindow(
		NULL, // The title of the window.
		SDL_WINDOWPOS_CENTERED, // X position of the window.
		SDL_WINDOWPOS_CENTERED, // Y position of the window.
		800, // Width.
		600, // Height.
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

	// We were able to initialize things properly.
	return true;
}

int main(int argc, char* argv[])
{
	is_running = initialize_window();

	// Render loop. Also called a game loop.
	while (is_running)
	{

	}
	
	return 0;
}