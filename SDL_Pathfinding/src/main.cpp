#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "SDL_SimpleApp.h"
#include "ScenePathFindingMouse.h"

using namespace std;

int main(int argc, char ** argv)
{
	bool quit = false;
	SDL_Event event;
	
	SDL_SimpleApp *app = SDL_SimpleApp::Instance();

	Scene *curr_scene = new ScenePathFindingMouse;
	app->setWindowTitle(curr_scene->getTitle());
	curr_scene->setMode(0);

	
	if (argc > 1) {
		cout << argv[1] << endl; 
		exit(0);
	}

	while (!quit)
	{
		// run app frame by frame
		event = app->run(curr_scene);

		/* Keyboard events */
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_1) //BFS
			{
				delete(curr_scene);
				curr_scene = new ScenePathFindingMouse;
				app->setWindowTitle(curr_scene->getTitle());
				curr_scene->setMode(0);

			}
			if (event.key.keysym.scancode == SDL_SCANCODE_2) //DJIKSTRA
			{
				delete(curr_scene);
				curr_scene = new ScenePathFindingMouse;
				app->setWindowTitle(curr_scene->getTitle());
				curr_scene->setMode(1);

			}
			if (event.key.keysym.scancode == SDL_SCANCODE_3) //GREEDY
			{
				delete(curr_scene);
				curr_scene = new ScenePathFindingMouse;
				app->setWindowTitle(curr_scene->getTitle());
				curr_scene->setMode(2);


			}
			if (event.key.keysym.scancode == SDL_SCANCODE_4) //A STAR
			{
				delete(curr_scene);
				curr_scene = new ScenePathFindingMouse;
				app->setWindowTitle(curr_scene->getTitle());
				curr_scene->setMode(3);
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_5) //EXERCICI 3
			{
				delete(curr_scene);
				curr_scene = new ScenePathFindingMouse;
				app->setWindowTitle(curr_scene->getTitle());
				curr_scene->setMode(4);
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_6) //EVALUAR EFICIENCIA ALGORISMES
			{
				delete(curr_scene);
				curr_scene = new ScenePathFindingMouse;
				app->setWindowTitle(curr_scene->getTitle());
				curr_scene->setMode(5);
			}
			if ((event.key.keysym.scancode == SDL_SCANCODE_Q) || (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			{
				quit = true;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_F)
			{
				app->setFullScreen();
			}
			break;
		case SDL_QUIT:
			quit = true;
			break;
		}

	}

	return 0;
}