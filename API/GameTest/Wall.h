#pragma once

class Wall
{
public:
	int wallDirection = {};
	int* numWalls = 0;

	void CreateWall(float x1, float y1, float x2, float y2, int dir);
private:
};

