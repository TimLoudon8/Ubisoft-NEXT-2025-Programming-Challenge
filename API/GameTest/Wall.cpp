#include "stdafx.h"
#include "Wall.h"
#include "App/app.h"

void Wall::CreateWall(float x1, float y1, float x2, float y2, int dir)
{
	App::DrawLine(x1, y1, x2, y2, 0, 1, 0);
	wallDirection[numWalls] = dir;
	numWalls++;
}
