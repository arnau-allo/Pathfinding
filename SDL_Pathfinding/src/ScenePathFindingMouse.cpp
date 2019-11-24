#include "ScenePathFindingMouse.h"

using namespace std;

ScenePathFindingMouse::ScenePathFindingMouse()
{
	draw_grid = false;
	maze = new Grid("../res/maze.csv");

	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));

	Agent *agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setBehavior(new PathFollowing);
	agent->setTarget(Vector2D(-20,-20));
	agents.push_back(agent);

	minBFS = 100000.0f;
	maxBFS = 0.0f;
	totalBFS = 0.0f;
	iterationsBFS = 0.0f;

	minDji = 100000.0f;
	maxDji = 0.0f;
	totalDji = 0.0f;
	iterationsDji = 0.0f;

	minGreedy = 100000.0f;
	maxGreedy = 0.0f;
	totalGreedy = 0.0f;
	iterationsGreedy = 0.0f;

	minAStar = 100000.0f;
	maxAStar = 0.0f;
	totalAStar = 0.0f;
	iterationsAStar = 0.0f;

	enemies.clear();
	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1,-1);
	while (!maze->isValidCell(rand_cell))
		rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	agents[0]->setPosition(maze->cell2pix(rand_cell));

	// set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = Vector2D(-1,-1);
	while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell) < 3)) {
		coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
		while (maze->getCostCell(coinPosition) == 50) {
			coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
		}
	}
		

	for (int j = 0; j < maze->getNumCellY(); j++)
	{
		for (int i = 0; i < maze->getNumCellX(); i++)
		{
				if (maze->getCostCell(Vector2D((float)i, (float)j)) == 50) { //IS ENEMY
					Vector2D temp = (0, 0);
					temp.x = (float)i;
					temp.y = (float)j;
					enemies.push_back(temp);
				}
		}
	}


	if (mode == 0) {
		agent->clearPath();
		agents[0]->clearPath();
		Path myPath = maze->getPathBFS(maze->pix2cell(agents[0]->getPosition()), coinPosition);
		for (int i = 0; i < myPath.points.size(); i++) {
			agents[0]->addPathPoint(maze->cell2pix(myPath.points[i]));
		}
	}
	else if (mode == 1) {
		agent->clearPath();
		agents[0]->clearPath();
		Path myPath = maze->getPathDjikstra(maze->pix2cell(agents[0]->getPosition()), coinPosition);
		for (int i = 0; i < myPath.points.size(); i++) {
			agents[0]->addPathPoint(maze->cell2pix(myPath.points[i]));
		}
	}
	else if (mode == 2) {
		agent->clearPath();
		agents[0]->clearPath();
		Path myPath = maze->getPathGreedy(maze->pix2cell(agents[0]->getPosition()), coinPosition);
		for (int i = 0; i < myPath.points.size(); i++) {
			agents[0]->addPathPoint(maze->cell2pix(myPath.points[i]));
		}
	}
	else if (mode == 3) {
		agent->clearPath();
		agents[0]->clearPath();
		Path myPath = maze->getPathAStar(maze->pix2cell(agents[0]->getPosition()), coinPosition);
		for (int i = 0; i < myPath.points.size(); i++) {
			agents[0]->addPathPoint(maze->cell2pix(myPath.points[i]));
		}
	}
	else if (mode == 4) {
		agent->clearPath();
		agents[0]->clearPath();
		Path myPath = maze->getPathEnemies(maze->pix2cell(agents[0]->getPosition()), coinPosition, enemies);
		for (int i = 0; i < myPath.points.size(); i++) {
			agents[0]->addPathPoint(maze->cell2pix(myPath.points[i]));
		}
	}
	else if (mode == 5) {
		agents[0]->clearPath();
		Path myPath = maze->getPathEnemies(maze->pix2cell(agents[0]->getPosition()), coinPosition, enemies);
		for (int i = 0; i < myPath.points.size(); i++) {
			agents[0]->addPathPoint(maze->cell2pix(myPath.points[i]));
		}
	}
	
}

ScenePathFindingMouse::~ScenePathFindingMouse()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void ScenePathFindingMouse::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	//std::cout << getMode();
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;
		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			Vector2D cell = maze->pix2cell(Vector2D((float)(event->button.x), (float)(event->button.y)));
			if (maze->isValidCell(cell)) {
				/*agents[0]->clearPath();
				Path myPath = maze->getPathBetween(maze->pix2cell(agents[0]->getPosition()), cell);
				for (int i = 0; i < myPath.points.size(); i++) {
					agents[0]->addPathPoint(maze->cell2pix(myPath.points[i]));
				}
				*/
				//agents[0]->addPathPoint(maze->cell2pix(cell));
			}
		}
		break;
	default:
		break;
	}

	agents[0]->update(dtime, event);

	// if we have arrived to the coin, replace it in a random cell!
	if ((agents[0]->getCurrentTargetIndex() == -1) && (maze->pix2cell(agents[0]->getPosition()) == coinPosition))
	{
		//std::cout << getMode();
		coinPosition = Vector2D(-1, -1);
		while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, maze->pix2cell(agents[0]->getPosition())) < 3))
		{
			coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
			while (maze->getCostCell(coinPosition) == 50) {
				coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
			}
		}
			

		if(mode == 0){
			agents[0]->clearPath();
			Path myPath = maze->getPathBFS(maze->pix2cell(agents[0]->getPosition()), coinPosition);
			for (int i = 0; i < myPath.points.size(); i++) {
				agents[0]->addPathPoint(maze->cell2pix(myPath.points[i]));
			}
		}
		else if (mode == 1) {
			agents[0]->clearPath();
			Path myPath = maze->getPathDjikstra(maze->pix2cell(agents[0]->getPosition()), coinPosition);
			for (int i = 0; i < myPath.points.size(); i++) {
				agents[0]->addPathPoint(maze->cell2pix(myPath.points[i]));
			}
		}
		else if (mode == 2) {
			agents[0]->clearPath();
			Path myPath = maze->getPathGreedy(maze->pix2cell(agents[0]->getPosition()), coinPosition);
			for (int i = 0; i < myPath.points.size(); i++) {
				agents[0]->addPathPoint(maze->cell2pix(myPath.points[i]));
			}
		}
		else if (mode == 3) {
			agents[0]->clearPath();
			Path myPath = maze->getPathAStar(maze->pix2cell(agents[0]->getPosition()), coinPosition);
			for (int i = 0; i < myPath.points.size(); i++) {
				agents[0]->addPathPoint(maze->cell2pix(myPath.points[i]));
			}
		}
		else if (mode == 4) {
			agents[0]->clearPath();
			Path myPath = maze->getPathEnemies(maze->pix2cell(agents[0]->getPosition()), coinPosition, enemies);
			for (int i = 0; i < myPath.points.size(); i++) {
				agents[0]->addPathPoint(maze->cell2pix(myPath.points[i]));
			}
		}
		else if (mode == 5) {
			agents[0]->clearPath();
			Path myPath = maze->getPathBFS(maze->pix2cell(agents[0]->getPosition()), coinPosition);
			Path myPath2 = maze->getPathDjikstra(maze->pix2cell(agents[0]->getPosition()), coinPosition);
			Path myPath3 = maze->getPathGreedy(maze->pix2cell(agents[0]->getPosition()), coinPosition);
			Path myPath4 = maze->getPathAStar(maze->pix2cell(agents[0]->getPosition()), coinPosition);
			if (myPath.visitedCells < minBFS) {
				minBFS = myPath.visitedCells;
			}
			if (myPath.visitedCells > maxBFS) {
				maxBFS = myPath.visitedCells;
			}
			totalBFS += myPath.visitedCells;
			iterationsBFS++;

			if (myPath2.visitedCells < minDji) {
				minDji = myPath2.visitedCells;
			}
			if (myPath2.visitedCells > maxDji) {
				maxDji = myPath2.visitedCells;
			}
			totalDji += myPath2.visitedCells;
			iterationsDji++;

			if (myPath3.visitedCells < minGreedy) {
				minGreedy = myPath3.visitedCells;
			}
			if (myPath3.visitedCells > maxGreedy) {
				maxGreedy = myPath3.visitedCells;
			}
			totalGreedy += myPath3.visitedCells;
			iterationsGreedy++;

			if (myPath4.visitedCells < minAStar) {
				minAStar = myPath4.visitedCells;
			}
			if (myPath4.visitedCells > maxAStar) {
				maxAStar = myPath4.visitedCells;
			}
			totalAStar += myPath4.visitedCells;
			iterationsAStar++;

			std::cout << "Min BFS: " << minBFS << " Max BFS: " << maxBFS << " Average: " << (totalBFS / iterationsBFS) << " Iteration: " << iterationsBFS << std::endl;
			std::cout << "Min Djikstra: " << minDji << " Max Djikstra: " << maxDji << " Average: " << (totalDji / iterationsDji) << " Iteration: " << iterationsDji << std::endl;
			std::cout << "Min Greedy: " << minGreedy << " Max Greedy: " << maxGreedy << " Average: " << (totalGreedy / iterationsGreedy) << " Iteration: " << iterationsGreedy << std::endl;
			std::cout << "Min A Star: " << minAStar << " Max A Star: " << maxAStar << " Average: " << (totalAStar / iterationsAStar) << " Iteration: " << iterationsAStar << std::endl;
			std::cout << std::endl;
			for (int i = 0; i < myPath.points.size(); i++) {
				agents[0]->addPathPoint(maze->cell2pix(myPath.points[i]));
			}
		}
		
	}
	
}

void ScenePathFindingMouse::draw()
{
	drawMaze();
	drawCoin();

	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i+=CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}

	agents[0]->draw();
}

const char* ScenePathFindingMouse::getTitle()
{
	return "SDL Path Finding :: PathFinding Mouse Demo";
}

void ScenePathFindingMouse::drawMaze()
{
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
	SDL_Rect rect;
	Vector2D coords;
	for (int j = 0; j < maze->getNumCellY(); j++)
	{
		for (int i = 0; i < maze->getNumCellX(); i++)
		{		
			if (!maze->isValidCell(Vector2D((float)i, (float)j)))
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
				coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			} else {
				if (getMode() == 4 && maze->getCostCell(Vector2D((float)i, (float)j)) == 50) { //IS ENEMY
					SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 0, 0, 255);
					coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
					rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
					SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
				}
				// Do not draw if it is not necessary (bg is already black)
			}
					
			
		}
	}
	//Alternative: render a backgroud texture:
	//SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );
}

void ScenePathFindingMouse::drawCoin()
{
	Vector2D coin_coords = maze->cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = {(int)coin_coords.x-offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE};
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}


bool ScenePathFindingMouse::loadTextures(char* filename_bg, char* filename_coin)
{
	SDL_Surface *image = IMG_Load(filename_bg);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}

void ScenePathFindingMouse::setMode(int _mode) {
	mode = _mode;
}

int ScenePathFindingMouse::getMode() {
	return mode;
}