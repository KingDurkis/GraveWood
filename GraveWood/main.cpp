//Hello darkness my old friend

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

#include "player.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/*It's important that we have the arguments of the "main" function be an integer followed by a char* array 
and the return type be an integer. Any other type of main function will cause an undefined reference 
to main. SDL requires this type of main so it is compatible with multiple platforms.*/
int main(int argc, char* args[])
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//This is the surface contained by the window.
	/*An SDL surface is just a 2D image. A 2D image 
	can be loaded from a file or it can be the image inside of a window. In this case it 
	will be the image we see inside of the window on the screen.*/
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	/*You can't call any SDL functions without initializing SDL first. Since all we care about 
	is using SDL's video subsystem, we will only be passing it the SDL_INIT_VIDEO flag.*/
	if (SDL_Init(SDL_INIT_VIDEO) < 0)	//When there's an error, SDL_Init returns -1.
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		/*
		If there is an error, SDL_CreateWindow returns NULL. If there's no window,we want to print out the error to the console.
		The last argument are the creation flags. SDL_WINDOW_SHOWN makes sure the window is shown when it is created.
		*/
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get window surface 
			/*
			If the window was created successfully, we want to get the window's surface so we can draw to it.
			*/
			screenSurface = SDL_GetWindowSurface(window);

			//Fill the surface white
			/*
			this is just a place holder function incase we want to use it later
			*/
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			//Update the surface
			/* 
			After you've done all your drawing you need to update the window so it shows everything you drew. 
			A call to SDL_UpdateWindowSurface will do this.
			*/
			SDL_UpdateWindowSurface(window);

			//Wait two seconds
			/*
			input is the number of ms to delay, so we can actually see the windowd before the script ends
			*/
			SDL_Delay(2000);
		}
	}

	//Destroy window
	/*
	destroy the window to free its memory. This will also take care of the SDL_Surface we got from it.
	*/
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	/*
	Cleans up all initializes subsystems
	*/
	SDL_Quit();
	
	return 0;
}