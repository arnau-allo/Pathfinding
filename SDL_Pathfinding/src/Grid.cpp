#include "Grid.h"

using namespace std;

struct MyNode
{
	Vector2D position;
	MyNode *parent;
	float cost;
	float heuristic;
	float costSoFar;

	MyNode(Vector2D _pos, MyNode* _parent, float _cost, float _heuristic) {
		position = _pos;
		parent = _parent;
		cost = _cost;
		heuristic = _heuristic;
		costSoFar = 0;
	}
	 bool operator== (const MyNode &n) const{
		return (cost == n.cost);
	}
	 bool operator > (const MyNode &n) const {
		return (cost > n.cost);
	}
	 bool operator < (const MyNode &n) const {
		return (cost < n.cost);
	}
	 bool operator >= (const MyNode &n) const {
		return (cost >= n.cost);
	}
	 bool operator <= (const MyNode &n) const {
		return (cost <= n.cost);
	}

};

Grid::Grid(char* filename)
{
	num_cell_x = SRC_WIDTH / CELL_SIZE;
	num_cell_y = SRC_HEIGHT / CELL_SIZE;

	// Initialize the terrain matrix from file (for each cell a zero value indicates it's a wall, positive values indicate terrain cell cost)
	std::ifstream infile(filename);
	std::string line;
	while (std::getline(infile, line))
	{
		vector<int> terrain_row;
		std::stringstream lineStream(line);
		std::string cell;
		while (std::getline(lineStream, cell, ','))
			terrain_row.push_back(atoi(cell.c_str()));
		SDL_assert(terrain_row.size() == num_cell_x);
		terrain.push_back(terrain_row);
	}
	SDL_assert(terrain.size() == num_cell_y);
	infile.close();
}

Grid::~Grid()
{
}

int Grid::getNumCellX()
{
	return num_cell_x;
}

int Grid::getNumCellY()
{
	return num_cell_y;
}

Vector2D Grid::cell2pix(Vector2D cell)
{
	int offset = CELL_SIZE / 2;
	return Vector2D(cell.x*CELL_SIZE + offset, cell.y*CELL_SIZE + offset);
}

Vector2D Grid::pix2cell(Vector2D pix)
{
	return Vector2D((float)((int)pix.x / CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
}

bool Grid::isValidCell(Vector2D cell)
{
	if ((cell.x < 0) || (cell.y < 0) || (cell.y >= terrain.size()) || (cell.x >= terrain[0].size()))
		return false;
	return !(terrain[(unsigned int)cell.y][(unsigned int)cell.x] == 0);
}

int Grid::getCostCell(Vector2D cell) 
{
	return terrain[(unsigned int)cell.y][(unsigned int)cell.x];
}

Path Grid::getPathBFS(Vector2D start, Vector2D end) 
{
	frontier.clear();
	frontier.push_back(std::make_pair(start, start));
	Vector2D endPix = end;
	bool isEnd = false;
	bool isInFrontier = false;
	int it = 0;
	while(!frontier.empty()) {
		
		Vector2D point1 = (0, 0);
		point1.x = frontier[it].first.x - 1.0f;
		point1.y = frontier[it].first.y - 1.0f;
		if (isValidCell(point1)) {
			for (int i = 0; i < frontier.size() - 1; i++) {
				if (frontier[i].first == point1)
					isInFrontier = true;
			}
			if (!isInFrontier)
				frontier.push_back(std::make_pair(point1, frontier[it].first));
			isInFrontier = false;
		}
		if (point1 == endPix)
		{
			isEnd = true;
			break;
		}

		Vector2D point2 = (0, 0);
		point2.x = frontier[it].first.x;
		point2.y = frontier[it].first.y - 1.0f;
		if (isValidCell(point2)) {
			for (int i = 0; i < frontier.size() - 1; i++) {
				if (frontier[i].first == point2)
					isInFrontier = true;
			}
			if (!isInFrontier)
				frontier.push_back(std::make_pair(point2, frontier[it].first));
			isInFrontier = false;
		}
		if (point2 == endPix)
		{
			isEnd = true;
			break;
		}

		Vector2D point3 = (0, 0);
		point3.x = frontier[it].first.x + 1.0f;
		point3.y = frontier[it].first.y - 1.0f;

		if (isValidCell(point3)) {
			for (int i = 0; i < frontier.size() - 1; i++) {
				if (frontier[i].first == point3)
					isInFrontier = true;
			}
			if (!isInFrontier)
				frontier.push_back(std::make_pair(point3, frontier[it].first));
			isInFrontier = false;
		}
		if (point3 == endPix)
		{
			isEnd = true;
			break;
		}

		Vector2D point4 = (0, 0);
		point4.x = frontier[it].first.x - 1.0f;
		point4.y = frontier[it].first.y;
		if (isValidCell(point4)) {
			for (int i = 0; i < frontier.size() - 1; i++) {
				if (frontier[i].first == point4)
					isInFrontier = true;
			}
			if (!isInFrontier)
				frontier.push_back(std::make_pair(point4, frontier[it].first));
			isInFrontier = false;
		}
		if (point4 == endPix)
		{
			isEnd = true;
			break;
		}

		Vector2D point6 = (0, 0);
		point6.x = frontier[it].first.x + 1.0f;
		point6.y = frontier[it].first.y;

		if (isValidCell(point6)) {
			for (int i = 0; i < frontier.size() - 1; i++) {
				if (frontier[i].first == point6)
					isInFrontier = true;
			}
			if (!isInFrontier)
				frontier.push_back(std::make_pair(point6, frontier[it].first));
			isInFrontier = false;
		}
		if (point6 == endPix)
		{
			isEnd = true;
			break;
		}

		Vector2D point7 = (frontier[it].first.x - 1, frontier[it].first.y + 1);
		point7.x = frontier[it].first.x - 1.0f;
		point7.y = frontier[it].first.y + 1.0f;
		if (isValidCell(point7)) {
			for (int i = 0; i < frontier.size() - 1; i++) {
				if (frontier[i].first == point7)
					isInFrontier = true;
			}
			if (!isInFrontier)
				frontier.push_back(std::make_pair(point7, frontier[it].first));
			isInFrontier = false;
		}
		if (point7 == endPix)
		{
			isEnd = true;
			break;
		}

		Vector2D point8 = (frontier[it].first.x, frontier[it].first.y + 1);
		point8.x = frontier[it].first.x;
		point8.y = frontier[it].first.y + 1.0f;
		if (isValidCell(point8)) {
			for (int i = 0; i < frontier.size() - 1; i++) {
				if (frontier[i].first == point8)
					isInFrontier = true;
			}
			if (!isInFrontier)
				frontier.push_back(std::make_pair(point8, frontier[it].first));
			isInFrontier = false;
		}
		if (point8 == endPix)
		{
			isEnd = true;
			break;
		}

		Vector2D point9 = (frontier[it].first.x + 1, frontier[it].first.y + 1);
		point9.x = frontier[it].first.x + 1.0f;
		point9.y = frontier[it].first.y + 1.0f;
		if (isValidCell(point9)) {
			for(int i = 0; i < frontier.size() - 1; i++) {
				if (frontier[i].first == point9)
					isInFrontier = true;
			}
			if (!isInFrontier)
				frontier.push_back(std::make_pair(point9, frontier[it].first));
			isInFrontier = false;
		}
		if (point9 == endPix)
		{
			isEnd = true;
			break;
		}
		it++;
	}

	std::vector<Vector2D> points;
	bool isStart = false;
	bool pointFound = false;


	it = frontier.size() - 1;

	
	while (!isStart) {
		Vector2D tempPoint = frontier[it].first;
		points.push_back(tempPoint);
		Vector2D comesFrom = frontier[it].second;
		if (comesFrom == start) {
			isStart = true;
		}
		for (int i = 0; i < frontier.size(); i++) {
			if (frontier[i].first == comesFrom) {
				it = i;
			}
		}
		
	}

	Path myPath;
	for (int i = points.size() - 1; i >= 0; i--) {
		myPath.points.push_back(points[i]);
	}

	return myPath;
}

Path Grid::getPathDjikstra(Vector2D start, Vector2D end) {
	std::deque<MyNode> visitedCells;
	MyNode n = MyNode(start, nullptr, 0, 0);
	visitedCells.push_back(n);


	int it = 0;
	MyNode itNode = n;

	while (!visitedCells.empty()) {

		std::deque<MyNode> frontierPriority;

		Vector2D point2 = (0, 0);
		point2.x = itNode.position.x;
		point2.y = itNode.position.y - 1.0f;
		if (isValidCell(point2)) {
			MyNode n2 = MyNode(point2, &itNode, getCostCell(point2), 0);
			if (point2 == end) {
				frontierPriority.push_back(n2);
				break;
			}
			frontierPriority.push_back(n2);
		}
		
	
		Vector2D point4 = (0, 0);
		point4.x = itNode.position.x - 1.0f;
		point4.y = itNode.position.y;
		if (isValidCell(point4)) {
			MyNode n4 = MyNode(point4, &itNode, getCostCell(point4), 0);
			if (point4 == end) {
				frontierPriority.push_back(n4);
				break;
			}
			frontierPriority.push_back(n4);
		}
		
		
		Vector2D point6 = (0, 0);
		point6.x = itNode.position.x + 1.0f;
		point6.y = itNode.position.y;
		if (isValidCell(point6)) {
			MyNode n6 = MyNode(point6, &itNode, getCostCell(point6), 0);
			if (point6 == end) {
				frontierPriority.push_back(n6);
				break;
			}
			frontierPriority.push_back(n6);
		}
		
				
		Vector2D point8 = (0, 0);
		point8.x = itNode.position.x;
		point8.y = itNode.position.y + 1.0f;
		if (isValidCell(point8)) {
			MyNode n8 = MyNode(point8, &itNode, getCostCell(point8), 0);
			if (point8 == end) {
				frontierPriority.push_back(n8);
				break;
			}
			frontierPriority.push_back(n8);
		}
		
		MyNode cheapestNode = frontierPriority[0];
		int cheapI = 0;

		for (int i = 0; i < frontierPriority.size() - 1; i++) {
			if (frontierPriority[i].cost < cheapestNode.cost) {
				cheapestNode = frontierPriority[i];
				cheapI = i;
			}
		}
		frontierPriority.erase(frontierPriority.begin() + cheapI);

		bool alreadyVisited = false;
		for (int i = 0; i < visitedCells.size(); i++) {
			if (visitedCells[i].position == cheapestNode.position) {
				alreadyVisited = true;
				if (visitedCells[i].costSoFar >= cheapestNode.parent->costSoFar + cheapestNode.cost) {
					visitedCells.push_back(cheapestNode);
					visitedCells[visitedCells.size() - 1].costSoFar = itNode.costSoFar + visitedCells[visitedCells.size() - 1].cost;
					itNode = visitedCells[visitedCells.size() - 1];
				}
				else {
					itNode = visitedCells[i];
				}
			}
		}
		if (!alreadyVisited) {
			visitedCells.push_back(cheapestNode);
			visitedCells[visitedCells.size() - 1].costSoFar = itNode.costSoFar + visitedCells[visitedCells.size() - 1].cost;
			itNode = visitedCells[visitedCells.size() - 1];
		}
		alreadyVisited = false;
		
	}

	std::vector<Vector2D> points;
	bool isStart = false;
	bool pointFound = false;


	itNode = visitedCells[visitedCells.size() - 1];

	while (!isStart) {
		Vector2D tempPoint = itNode.position;
		points.push_back(tempPoint);
		Vector2D comesFrom = itNode.parent->position;
		if (comesFrom == start) {
			isStart = true;
		}
		itNode = *itNode.parent;

	}

	Path myPath;
	for (int i = points.size() - 1; i >= 0; i--) {
		myPath.points.push_back(points[i]);
	}

	return myPath;

}