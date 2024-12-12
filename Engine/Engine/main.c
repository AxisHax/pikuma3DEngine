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
/// Boolean that keeps track of the running state of the applicaion.
/// </summary>
bool is_running = false;

/// <summary>
/// Pointer to the color buffer.
/// </summary>
uint32_t* color_buffer = NULL;

/// <summary>
/// The window width in pixels.
/// </summary>
int window_width = 800;

/// <summary>
/// The window height in pixels.
/// </summary>
int window_height = 600;
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

	// We were able to initialize things properly.
	return true;
}

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

	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

/// <summary>
/// Clear the color buffer with the given color.
/// </summary>
/// <param name="color">An ARGB color value.</param>
void clear_color_buffer(uint32_t color)
{
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
/// Render visuals to the screen.
/// </summary>
/// <param name="">Void.</param>
void render(void)
{
	// Set the color for drawing to the screen.
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	// Clear the color buffer with the above color.
	SDL_RenderClear(renderer);

	render_color_buffer();

	clear_color_buffer(0xFFFFFF00);

	// Update the screen with the color we chose.
	SDL_RenderPresent(renderer);
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