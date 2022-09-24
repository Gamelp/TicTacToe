//#include <iostream>
//
//#include <SDL.h>
//
//#include "Constants.h"
//
//SDL_Window* window = NULL;
//SDL_Renderer* renderer = NULL;
//
//bool running = false;
//
////Initializse SDL system
//bool init()
//{
//	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
//	{
//		printf("SDL_Init failed!");
//		return false;
//	}
//
//	window = SDL_CreateWindow(
//		WINDOW_TITLE,
//		SDL_WINDOWPOS_CENTERED,
//		SDL_WINDOWPOS_CENTERED,
//		WINDOW_WIDTH,
//		WINDOW_HEIGHT,
//		0
//	);
//	if (!window)
//	{
//		printf("SDL_CreateWindow failed!");
//		return false;
//	}
//
//	renderer = SDL_CreateRenderer(
//		window,
//		-1,
//		SDL_RENDERER_ACCELERATED
//	);
//	if (!renderer)
//	{
//		printf("SDL_CreateRenderer failed!");
//		return false;
//	}
//
//	return true;
//}
//
////Initialize game
//void setup()
//{
//
//}
//
////Cleanup before exiting
//void cleanup()
//{
//	SDL_DestroyRenderer(renderer);
//	SDL_DestroyWindow(window);
//}
//
////Check for player input
//void input(void)
//{
//	SDL_Event event;
//
//	while (SDL_PollEvent(&event))
//	{
//		switch (event.type)
//		{
//		case SDL_QUIT:
//			running = SDL_FALSE;
//			break;
//		}
//	}
//}
//
////Update game
//void update()
//{
//
//}
//
////Render game
//void render()
//{
//	//Clear
//	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
//	SDL_RenderClear(renderer);
//
//	//Preset
//	SDL_RenderPresent(renderer);
//}
//
//
//int main(int argc, char* args[])
//{
//	running = init();
//	if (running)
//	{
//		setup();
//	}
//
//	while (running)
//	{
//		input();
//		update();
//		render();
//	}
//
//	cleanup();
//
//	return 0;
//}