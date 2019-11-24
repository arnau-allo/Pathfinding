#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Scene.h"
#include "Agent.h"
#include "Seek.h"
#include "PathFollowing.h"
#include "Grid.h"

class ScenePathFindingMouse :
	public Scene
{
public:
	ScenePathFindingMouse();
	~ScenePathFindingMouse();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
	void setMode(int _mode);
	int getMode();
	std::vector<Vector2D> enemies;

	float minBFS;
	float maxBFS;
	float totalBFS;
	float iterationsBFS;

	float minDji;
	float maxDji;
	float totalDji;
	float iterationsDji;

	float minGreedy;
	float maxGreedy;
	float totalGreedy;
	float iterationsGreedy;

	float minAStar;
	float maxAStar;
	float totalAStar;
	float iterationsAStar;

private:
	std::vector<Agent*> agents;
	Vector2D coinPosition;

	Grid *maze;
	bool draw_grid;
	int mode;

	void drawMaze();
	void drawCoin();
	SDL_Texture *background_texture;
	SDL_Texture *coin_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);

};
