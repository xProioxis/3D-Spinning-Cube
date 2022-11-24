#pragma once
#include <SDL.h>
#undef main
#include <vector>


class Screen
{
	SDL_Event e;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<SDL_FPoint> points;
	
public:
	Screen()
	{
		SDL_Init(SDL_INIT_VIDEO);
		SDL_CreateWindowAndRenderer(
			640*2, 480*2, 0, &window, &renderer
		);
		SDL_RenderSetScale(renderer, 2, 2);
	}

	void pixel(float x, float y)
	{
		SDL_FPoint new_point;
		new_point.x = x;
		new_point.y = y;
		points.push_back(new_point);
	}

	void show()
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
		for (auto& point : points) // draw every pixel to the screen
		{
			SDL_RenderDrawPointF(renderer, point.x, point.y);
		}
		SDL_RenderPresent(renderer);

	}

	void clear()
	{
		points.clear();
	}

	void input()
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				SDL_Quit();
				exit(0);
			}
		}
	}

};