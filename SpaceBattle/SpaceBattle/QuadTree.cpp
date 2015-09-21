#include "QuadTree.h"
#include <cassert>

QuadTree::QuadTree()
{
}


QuadTree::~QuadTree()
{
}

void QuadTree::clear()
{

	gameobjects.clear();
	assert(gameobjects.size() == 0);

	for (QuadTree* node : nodes)
	{
		if (node != NULL)
		{
			node->clear();
			node = NULL;
		}
	}

}

void QuadTree::split()
{
	int sub_width = bounds.width / 2;
	int sub_height = bounds.height / 2;
	int x = bounds.left;
	int y = bounds.top;

}