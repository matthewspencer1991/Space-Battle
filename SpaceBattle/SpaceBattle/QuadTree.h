#pragma once
class GameObject;
#include <vector>
#include "SFML\Graphics\Rect.hpp"
class QuadTree
{
public:
	QuadTree();
	~QuadTree();
	void clear();
	void split();
private:
	const int NODE_MAX_OBJECTS = 10;
	const int MAX_DEPTH = 5;
	int level;
	std::vector<GameObject*> gameobjects;
	std::vector<QuadTree*> nodes;
	sf::IntRect bounds;
};

