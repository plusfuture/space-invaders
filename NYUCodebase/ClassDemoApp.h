#ifndef CLASSDEMOAPP_H
#define CLASSDEMOAPP_H
#ifdef _WINDOWS
#include <GL/glew.h>
#endif
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <vector>
#include "ShaderProgram.h"
#include "Matrix.h"
#include "Entity.h"
#include <algorithm>
#include <ctime>
#include <ratio>
#include <chrono>
#include <time.h>
#include <stdlib.h>
#using <System.dll>
using namespace std::chrono;
using namespace System;
using namespace System::Diagnostics;
#define DEBUG
#define RESOURCE_FOLDER ""

class ClassDemoApp{
public:
	ClassDemoApp();
	~ClassDemoApp();

	void Setup();
	void ProcessEvents();
	bool UpdateAndRender();

	void menuUpdate(float elapsed);
	void gameUpdate(float elapsed);
	void overUpdate(float elapsed);

	void menuRender();
	void gameRender();
	void overRender();

	void Render();
	void Update(float elapsed);
	//void DrawSpriteSheetSprite(int index, int spriteCountX, int spriteCountY);
	void ProcessInput();

	void spawnSpinner();

	bool shouldRemoveSpinner(Entity spinner);

private:
	
	std::vector<Entity> enemies;
	std::vector<Entity> bullets;
	std::vector<Entity> enemyBullets;
	std::vector<Entity> blocks;
	GLuint playerTex;
	GLuint blockTex;
	GLuint enemyTex;
	GLuint bulletTex;
	GLuint fontTex;

	enum GameState{ STATE_MENU, STATE_GAME, STATE_OVER };
	GameState state = STATE_MENU;
	int spawnTimer = 0;
	bool spawned = false;
	int lives = 3;

	Entity player;

	std::vector<Entity> entities; //make a vector of Entities

	bool done;
	SDL_Event event;
	float lastFrameTicks;
	SDL_Window *displayWindow;
	
	Matrix projectionMatrix;
	Matrix modelMatrix;
	Matrix viewMatrix;

	ShaderProgram *program;
};

#endif