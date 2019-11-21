#pragma once
#include <vector>
#include <utility>      
#include <deque>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Agent.h"

class Grid
{
public:
	Grid(char* filename);
	~Grid();

private:
	int num_cell_x;
	int num_cell_y;

	std::vector< std::vector<int> > terrain;
	std::deque<std::pair<Vector2D,Vector2D>> frontier;

public:
	Vector2D cell2pix(Vector2D cell);
	Vector2D pix2cell(Vector2D pix);
	bool isValidCell(Vector2D cell);
	int getNumCellX();
	int getNumCellY();
	Path getPathBetween(Vector2D start, Vector2D end);
};
