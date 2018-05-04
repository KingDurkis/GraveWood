//Hello darkness my old friend
//Currently in an SDL learning phase

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <string>


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Key press surfaces constants
enum KeyPressSurfaces //Enumerations are a shorthand way to do symbolic constants (first item = 0)
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL, 
};

//Starts up SDL and creates window
bool init();

//Loads Media... duh
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The window we'll be rendering to.
SDL_Window* gWindow = NULL;

//The surface contained by the window.
SDL_Surface* gScreenSurface = NULL;

/*An SDL surface is just a 2D image. A 2D image
can be loaded from a file or it can be the image inside of a window. In this case it
will be the image we see inside of the window on the screen.*/

//The images that corespond to a keypress
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

bool init()
{
	//Init success flag
	bool success = true;

	//Initializtion Notes:
	/*You can't call any SDL functions without initializing SDL first. Since all we care about
	is using SDL's video subsystem, we will only be passing it the SDL_INIT_VIDEO flag.*/

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) //SDL_Init returns -1 on error.
	{
		printf("SDL could not initialize!SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window.
		/*The last argument are the creation flags. SDL_WINDOW_SHOWN makes sure the window is shown when it is created.
		*/
		gWindow = SDL_CreateWindow("BAMF Window #1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) //If there is an error, SDL_CreateWindow returns NULL.
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

bool loadMedia()
{
	//LoadMedia success flag
	bool success = true;

	//Load default surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("bmp folder/press.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		printf("Failed to load default image!\n");
		success = false;
	}

	//Load up surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("bmp folder/up.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}

	//Load down surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("bmp folder/down.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		printf("Failed to load down image!\n");
		success = false;
	}

	//Load left surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("bmp folder/left.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		printf("Failed to load left image!\n");
		success = false;
	}

	//Load right surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("bmp folder/right.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
	{
		printf("Failed to load right image!\n");
		success = false;
	}

	return success;
}

void close()
{
	//Deallocate Surface
	SDL_FreeSurface(gCurrentSurface);
	gCurrentSurface = NULL;

	//Destroy Window
	SDL_DestroyWindow(gWindow); //This will also take care of the SDL_Surface we got from it.
	
	//Quit SDL subsystems
	SDL_Quit(); //Cleans up all initializes subsystems
}

SDL_Surface* loadSurface(std::string path)
{
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	return loadedSurface;
}

/*It's important that we have the arguments of the "main" function be an integer followed by a char* array 
and the return type be an integer. Any other type of main function will cause an undefined reference 
to main. SDL requires this type of main so it is compatible with multiple platforms.*/
int main(int argc, char* args[])
{
	//Start up SDL and create a window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else 
	{
		//Load Media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Set default current Surface
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				/*SDL_PollEvent takes events from the event queue and puts the event data into the 
				SDL_Event we passed into the function (in the order the events happened). The while 
				loop forces SDL_PollEvent to continue until it has gone through all events in the queue*/
				while (SDL_PollEvent(&e) != 0) //SDL_PollEvent will return 0 when empty.
				{
					//User requests quit (the event in this loop is "SDL_Quit")
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					//User presses a key
					else if (e.type == SDL_KEYDOWN)
					{
						//Select surface base on key press
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
							break;

						case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
							break;

						case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
							break;

						case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
							break;

						default:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
							break;
						}
					}
				}

				//Apply the image
				SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

				//Update the Surface
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}