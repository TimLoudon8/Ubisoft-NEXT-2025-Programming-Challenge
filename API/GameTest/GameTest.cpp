///////////////////////////////////////////////////////////////////////////////
// Filename: GameTest.cpp
// Provides a demo of how to use the API
///////////////////////////////////////////////////////////////////////////////
// Ubisoft NEXT 2025 submission by Timothy Loudon
// Email: loudtim1014@gmail.com
//------------------------------------------------------------------------
#define NOMINMAX
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>
//------------------------------------------------------------------------
#include "app\app.h"
#include "string.h"
#include <cmath>
#include <vector>
#include <algorithm>
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Example data....
//------------------------------------------------------------------------
CSimpleSprite* golfBall;
CSimpleSprite* flag;
/*enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
};
//------------------------------------------------------------------------*/

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	
	golfBall = App::CreateSprite(".\\TestData\\golftest.bmp", 1, 1);
	const float speed = 1.f;
	golfBall->SetScale(0.5f);

	flag = App::CreateSprite(".\\TestData\\flag.bmp", 1, 1);
	flag->SetScale(0.1f);
}

//Wall wall;

//const char* speedChar;
//char speedString[2];

// Debug and Player stats
std::string stringSpeed, stringX, stringY, stringmx, stringmy, stringStrokes, 
	stringTotalStrokes, stringTotalDeaths, stringLevel;
const char* numTotalStrokes = stringTotalStrokes.c_str();
const char* numTotalDeaths = stringTotalDeaths.c_str();

// Ball physics
double speedMod = 1;
int speedStat = 1;
float friction = 0.01;
bool toggleSpeed = true;

// Collision and Aiming
bool isAiming = true;
float targetX, targetY, newX, newY, oldX, oldY;
float mPosX;
float mPosY;
float xPos, yPos;
bool hitVert = false;
bool hitHori = false;
float holeX, holeY;
const float holeRadius = 10.f;

// Game state detection
bool win = false;
bool gameStart = true;
int levelID = 1;
int strokes = 0;
int totalStrokes = 0;
int deaths = 0;


struct Wall {
	float x, y, height, width;
};

// Various types of walls

std::vector<Wall> vertWalls =
{
};

std::vector<Wall> horiWalls =
{
};

std::vector<Wall> deathWalls =
{
};

void HitVert()
{
	if (targetX > xPos)
	{
		targetX = oldX - 1000;
	}
	else
	{
		targetX = oldX + 1000;
	}

	if (targetY > yPos)
	{
		targetY = oldY + 1000;

	}
	else
	{
		targetY = oldY - 1000;
	}
}

void HitHori()
{
	if (targetX > xPos)
	{
		targetX = oldX + 1000;
	}
	else
	{
		targetX = oldX - 1000;
	}

	if (targetY > yPos)
	{
		targetY = oldY - 1000;

	}
	else
	{
		targetY = oldY + 1000;
	}
}

void HitDeath()
{
	golfBall->SetPosition(oldX, oldY);
	speedMod = 0;
	deaths++;
}

void LevelOne()
{
	// Level Initialization
	if (gameStart)
	{
		win = false;
		strokes = 0;
		golfBall->SetPosition(480.f, 200.f);
		flag->SetPosition(480.f, 610.f);
		holeX = 475.f;
		holeY = 590.f;
		gameStart = false;
	}

	// Walls
	App::DrawLine(430.f, 100.f, 530.f, 100.f, 0, 1, 0); // Hori
	App::DrawLine(430.f, 100.f, 430.f, 300.f, 0, 1, 0); // Vert
	App::DrawLine(530.f, 100.f, 530.f, 200.f, 0, 1, 0); // Vert

	App::DrawLine(430.f, 300.f, 630.f, 300.f, 0, 1, 0); // Hori
	App::DrawLine(530.f, 200.f, 730.f, 200.f, 0, 1, 0); // Hori

	App::DrawLine(630.f, 300.f, 630.f, 550.f, 0, 1, 0); // Vert
	App::DrawLine(730.f, 200.f, 730.f, 650.f, 0, 1, 0); // Vert

	App::DrawLine(630.f, 550.f, 430.f, 550.f, 0, 1, 0); // Hori
	App::DrawLine(730.f, 650.f, 430.f, 650.f, 0, 1, 0); // Hori
	App::DrawLine(430.f, 550.f, 430.f, 650.f, 0, 1, 0); // Vert

	// Wall Colliders
	vertWalls =
	{
		{430.f, 100.f, 200.f, 1},
		{530.f, 100.f, 100.f, 1},
		{630.f, 300.f, 250.f, 1},
		{730.f, 200.f, 450.f, 1},
		{430.f, 550.f, 100.f, 1}
	};

	horiWalls =
	{
		{430, 100, 1, 100},
		{430, 300, 1, 200},
		{530, 200, 1, 200},
		{430, 550, 1, 200},
		{430, 650, 1, 300}
	};
}

void LevelTwo()
{
	// Level Initialization
	if (gameStart)
	{
		strokes = 0;
		golfBall->SetPosition(300.f, 600.f);
		flag->SetPosition(750.f, 150.f);
		holeX = 745.f;
		holeY = 130.f;
		gameStart = false;
	}

	// Walls
	App::DrawLine(250.f, 650.f, 350.f, 650.f, 0, 1, 0); // Hori
	App::DrawLine(250.f, 650.f, 250.f, 450.f, 0, 1, 0); // Vert
	App::DrawLine(350.f, 650.f, 350.f, 550.f, 0, 1, 0); // Vert

	App::DrawLine(250.f, 450.f, 350.f, 450.f, 1, 0, 0); // Death
	App::DrawLine(350.f, 450.f, 450.f, 450.f, 0, 1, 0); // Hori
	App::DrawLine(450.f, 450.f, 450.f, 500.f, 1, 0, 0); // Death
	App::DrawLine(350.f, 550.f, 550.f, 550.f, 0, 1, 0); // Hori

	App::DrawLine(450.f, 450.f, 450.f, 100.f, 0, 1, 0); // Vert
	App::DrawLine(550.f, 550.f, 550.f, 450.f, 1, 0, 0); // Death
	App::DrawLine(550.f, 450.f, 550.f, 200.f, 0, 1, 0); // Vert

	App::DrawLine(450.f, 100.f, 550.f, 100.f, 1, 0, 0); // Death
	App::DrawLine(550.f, 100.f, 800.f, 100.f, 0, 1, 0); // Hori
	App::DrawLine(550.f, 200.f, 800.f, 200.f, 0, 1, 0); // Hori
	App::DrawLine(800.f, 100.f, 800.f, 200.f, 1, 0, 0); // Death

	// Wall Colliders
	vertWalls =
	{
		{250.f, 450.f, 200.f, 1},
		{350.f, 550.f, 100.f, 1},
		{450.f, 100.f, 350.f, 1},
		{550.f, 200.f, 250.f, 1}
	};

	horiWalls =
	{
		{250.f, 650.f, 1, 100.f},
		{350.f, 450.f, 1, 100.f},
		{350.f, 550.f, 1, 200.f},
		{550.f, 100.f, 1, 250.f},
		{550.f, 200.f, 1, 250.f}
	};

	deathWalls =
	{
		{250.f, 450.f, 1, 100.f},
		{450.f, 450.f, 50.f, 1},
		{550.f, 450.f, 100.f, 1},
		{450.f, 100.f, 1, 100.f},
		{800.f, 100.f, 100.f, 1}
	};
}

void LevelThree()
{
	// Level Initialization
	if (gameStart)
	{
		strokes = 0;
		golfBall->SetPosition(200.f, 400.f);
		flag->SetPosition(805.f, 420.f);
		holeX = 800.f;
		holeY = 400.f;
		gameStart = false;
	}

	// Walls
	App::DrawLine(150.f, 350.f, 150.f, 450.f, 0, 1, 0); // Vert
	App::DrawLine(150.f, 350.f, 400.f, 350.f, 0, 1, 0); // Hori
	App::DrawLine(150.f, 450.f, 250.f, 450.f, 0, 1, 0); // Hori

	App::DrawLine(400.f, 350.f, 400.f, 450.f, 0, 1, 0); // Vert
	App::DrawLine(250.f, 450.f, 350.f, 450.f, 1, 0, 0); // Death
	App::DrawLine(350.f, 450.f, 350.f, 550.f, 1, 0, 0); // Death
	App::DrawLine(350.f, 550.f, 400.f, 550.f, 1, 0, 0); // Death

	App::DrawLine(400.f, 450.f, 600.f, 450.f, 0, 1, 0); // Hori
	App::DrawLine(400.f, 550.f, 700.f, 550.f, 0, 1, 0); // Hori

	App::DrawLine(600.f, 450.f, 600.f, 350.f, 0, 1, 0); // Vert
	App::DrawLine(700.f, 550.f, 700.f, 475.f, 0, 1, 0); // Vert
	App::DrawLine(600.f, 350.f, 700.f, 350.f, 1, 0, 0); // Death
	App::DrawLine(700.f, 450.f, 700.f, 475.f, 1, 0, 0); // Death
	App::DrawLine(700.f, 350.f, 700.f, 375.f, 1, 0, 0); // Death

	App::DrawLine(700.f, 475.f, 900.f, 475.f, 0, 1, 0); // Hori
	App::DrawLine(700.f, 350.f, 900.f, 350.f, 0, 1, 0); // Hori
	App::DrawLine(900.f, 350.f, 900.f, 475.f, 0, 1, 0); // Vert

	// Wall Colliders
	vertWalls =
	{
		{150.f, 350.f, 100.f, 1},
		{400.f, 350.f, 100.f, 1},
		{700.f, 475.f, 100.f, 1},
		{600.f, 350.f, 100.f, 1},
		{900.f, 350.f, 125.f, 1}
	};

	horiWalls =
	{
		{150.f, 350.f, 1, 250.f},
		{150.f, 450.f, 1, 100.f},
		{400.f, 450.f, 1, 200.f},
		{400.f, 550.f, 1, 300.f},
		{700.f, 475.f, 1, 200.f},
		{700.f, 350.f, 1, 200.f}
	};

	deathWalls =
	{
		{250.f, 450.f, 1, 100.f},
		{350.f, 450.f, 100.f, 1},
		{350.f, 550.f, 1, 50.f},
		{600.f, 350.f, 1, 100.f},
		{700.f, 475.f, 25.f, 1},
		{700.f, 350.f, 25.f, 1}
	};

	// Wall Colliders


}

void Finish()
{
	win = true;

	if (gameStart)
	{
		strokes = 0;
		golfBall->SetPosition(300.f, 600.f);
		flag->SetPosition(750.f, 150.f);
		holeX = 745.f;
		holeY = 130.f;
		gameStart = false;
	}

	App::Print(345.f, 484.f, "Congratulations!  You Win!");

	App::Print(320.f, 434.f, "Total Number of Strokes:");
	App::Print(570.f, 434.f, numTotalStrokes);

	App::Print(320.f, 384.f, "Total Number of Deaths:");
	App::Print(570.f, 384.f, numTotalDeaths);
}

bool checkHole(float x, float y)
{
	return std::sqrt((x - holeX) * (x - holeX) + (y - holeY) * (y - holeY)) < holeRadius;
}

// Clamps the value to determine a wall hit
#undef max
#undef min
float clampValue(float value, float minVal, float maxVal)
{
	return std::max(minVal, std::min(value, maxVal));
}

// Returns true if the ball hits a wall
bool checkWall(float x, float y, float radius, Wall wall)
{
	float closestX = clampValue(x, wall.x, wall.x + wall.width);
	float closestY = clampValue(y, wall.y, wall.y + wall.height);

	float dx = x - closestX;
	float dy = y - closestY;

	return (dx * dx + dy * dy) <= (radius * radius);
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(const float deltaTime)
{
	golfBall->Update(deltaTime);

	// Mouse and ball positions, debugging only
	float temp1, temp2, temp3, temp4;
	golfBall->GetPosition(temp1, temp2);
	App::GetMousePos(temp3, temp4);

	// Keyboard/mouse movement strictly for debugging purposes
	/*if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		float x, y;
		golfBall->GetPosition(x, y);
		x += speedMod * 2;
		golfBall->SetPosition(x, y);
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		float x, y;
		golfBall->GetPosition(x, y);
		x -= speedMod * 2;
		golfBall->SetPosition(x, y);
	}

    if (App::GetController().GetLeftThumbStickY() > 0.5f)
    {
        float x, y;
        golfBall->GetPosition(x, y);
        y += speedMod * 2;
        golfBall->SetPosition(x, y);
    }

	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		float x, y;
		golfBall->GetPosition(x, y);
		y -= speedMod * 2;
		golfBall->SetPosition(x, y);
	}*/

	// Adjusts power of the shot
	if (App::IsKeyPressed('F') && toggleSpeed && isAiming)
	{
		if (speedMod <= 2)
		{
			speedMod += 0.2f;
			speedStat++;
		}
		else
		{
			speedMod = 1;
			speedStat = 1;
		}

		toggleSpeed = false;
	}

	if (!App::IsKeyPressed('F'))
	{
		toggleSpeed = true;
	}

	// Get shot input, also gets the ball position before the shot in case it hits a wall or hazard
	if (App::IsKeyPressed(VK_SPACE) && isAiming && !win)
	{
		float x, y;
		App::GetMousePos(targetX, targetY);
		golfBall->GetPosition(x, y);
		oldX = x;
		oldY = y;
		isAiming = false;

		strokes++;
		App::PlaySound(".\\TestData\\putt.wav");
	}

	// Move ball according to player's aim
	if (!isAiming)
	{
		if (targetX > xPos)
		{
			golfBall->GetPosition(xPos, yPos);
			xPos += speedMod;
			golfBall->SetPosition(xPos, yPos);
		}

		if (targetX < xPos)
		{
			golfBall->GetPosition(xPos, yPos);
			xPos -= speedMod;
			golfBall->SetPosition(xPos, yPos);
		}

		if (targetY > yPos)
		{
			golfBall->GetPosition(xPos, yPos);
			yPos += speedMod;
			golfBall->SetPosition(xPos, yPos);
		}

		if (targetY < yPos)
		{
			golfBall->GetPosition(xPos, yPos);
			yPos -= speedMod;
			golfBall->SetPosition(xPos, yPos);
		}

		speedMod -= friction;

		// Go back into aim mode for another shot after ball has stopped moving
		if (speedMod <= 0)
		{
			isAiming = true;
			//hitHori = false;
			//hitVert = false;
			speedMod = 1;
			speedStat = 1;
		}

		// Check if the player hits a wall, one for loop for every type of wall
		for (size_t i = 0; i < vertWalls.size(); i++)
		{
			if (checkWall(xPos, yPos, 10.f, vertWalls[i]))
			{
				//hitVert = true;
				HitVert();
			}
		}

		for (size_t i = 0; i < horiWalls.size(); i++)
		{
			if (checkWall(xPos, yPos, 10.f, horiWalls[i]))
			{
				//hitHori = true;
				HitHori();
			}
		}

		for (size_t i = 0; i < deathWalls.size(); i++)
		{
			if (checkWall(xPos, yPos, 10.f, deathWalls[i]))
			{
				//hitHori = true;
				HitDeath();
			}
		}

		// This code is now deprecated and has been replaced by the HitVert() and HitHori() functions, left in to show process
		/*
		if (hitVert)
		{
			if (targetX > xPos)
			{
				//newX = targetX * -1;
				newX = oldX - 1000;
			}
			else
			{
				//newX = 384 + (384 - targetX);
				//newX = targetX * -1;
				newX = oldX + 1000;
			}

			//newX = oldX;

			if (newX > xPos)
			{
				golfBall->GetPosition(xPos, yPos);
				xPos += speedMod;
				golfBall->SetPosition(xPos, yPos);
			}

			if (newX < xPos)
			{
				golfBall->GetPosition(xPos, yPos);
				xPos -= speedMod;
				golfBall->SetPosition(xPos, yPos);
			}
		}

		if (hitHori)
		{
			if (targetY > yPos)
			{
				//newY = targetY * -1;
				newY = oldY - 100;

			}
			else
			{
				//newY = 512 + (512 - targetY);
				newY = oldY + 100;
			}

			//newY = oldY;

			if (newY > yPos)
			{
				golfBall->GetPosition(xPos, yPos);
				yPos += speedMod;
				golfBall->SetPosition(xPos, yPos);
			}

			if (newY < yPos)
			{
				golfBall->GetPosition(xPos, yPos);
				yPos -= speedMod;
				golfBall->SetPosition(xPos, yPos);
			}
		}*/

		// Check if player lands ball in hole
		if (checkHole(xPos, yPos))
		{
			speedMod = 0;
			App::PlaySound(".\\TestData\\clapping.wav");
			gameStart = true;
			totalStrokes += strokes;
			levelID++;

			if (levelID == 4)
			{
				win = true;
			}
		}
	}

	// Converts ints to string to be outputted using App::Print()
	//sprintf(speedString, "%s_%d_%d", speedChar, (int)speedMod, 0); Doesn't work, now deprecated
	stringSpeed = std::to_string(speedMod);
	stringStrokes = std::to_string(strokes);
	stringTotalStrokes = std::to_string(totalStrokes);
	stringTotalDeaths = std::to_string(deaths);
	stringLevel = std::to_string(levelID);
	stringX = std::to_string(temp1);
	stringY = std::to_string(temp2);
	stringmx = std::to_string(temp3);
	stringmy = std::to_string(temp4);
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	// Mostly debug variables + num of strokes the player took
	const char* speed = stringSpeed.c_str();
	const char* xPos = stringX.c_str();
	const char* yPos = stringY.c_str();
	const char* mxPos = stringmx.c_str();
	const char* myPos = stringmy.c_str();
	const char* numStrokes = stringStrokes.c_str();
	const char* numLevel = stringLevel.c_str();

	if (!win)
	{
		golfBall->Draw();
		flag->Draw();

		float x, y, mposX, mposY;

		// Draws a line between the ball position and mouse position so the player can aim
		golfBall->GetPosition(x, y);
		App::GetMousePos(mposX, mposY);
		App::DrawLine(x, y, mposX, mposY, 0, 0, 1);

		App::Print(100, 700, "Level");
		App::Print(180, 700, numLevel);
		App::Print(100, 600, "Strokes:");
		App::Print(180, 600, numStrokes);
		App::Print(100, 100, "Current Power:");
		//App::Print(230, 100, speed);

		// Shot power indicator
		for (int i = 1; i <= speedStat; i++)
		{
			App::DrawLine(230.f + (i * 10), 95.f, 230.f + (i * 10), 115.f, 1, 0, 1);
		}

		if (levelID == 1)
		{
			App::Print(100, 400, "Press Space to shoot");
			App::Print(100, 300, "Press F to increase power");
		}
		/*App::Print(100, 600, mxPos);
		App::Print(100, 500, myPos);*/
	}
	
	// Changes the level, similar in concept to Unity's scene manager
	switch (levelID)
	{
	case 1:
		LevelOne();
		break;

	case 2:
		LevelTwo();
		break;

	case 3:
		LevelThree();
		break;

	case 4:
		Finish();
		break;

	// Just in case the player ends up somewhere they're not supposed to.  Should be impossible to reach
	default:
		App::Print(100, 700, "Error: Invalid Level ID");
	}
	
	/*static float a = 0.f;
	const float r = 1.f;
	float g = 1.f;
	float b = 1.f;
	a += 0.1f;
	for (int i = 0; i < 20; i++)
	{

		const float sx = 200 + sinf(a + i * 0.1f) * 60.f;
		const float sy = 200 + cosf(a + i * 0.1f) * 60.f;
		const float ex = 700 - sinf(a + i * 0.1f) * 60.f;
		const float ey = 700 - cosf(a + i * 0.1f) * 60.f;
		g = (float)i / 20.f;
		b = (float)i / 20.f;
		App::DrawLine(sx, sy, ex, ey, r, g, b);
	}*/
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	//------------------------------------------------------------------------
	// Example Sprite Code....
	delete golfBall;
	delete flag;
	//------------------------------------------------------------------------
}
