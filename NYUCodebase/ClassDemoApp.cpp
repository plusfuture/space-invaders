#include "ClassDemoApp.h"

enum GameState{ STATE_MENU, STATE_GAME, STATE_OVER };
int state = STATE_MENU;
std::vector<Entity> enemies;
std::vector<Entity> bullets;
std::vector<Entity> blocks;
int lives = 3;

ClassDemoApp::ClassDemoApp(){
	Setup();
}

GLuint LoadTexture(const char *image_path){
	SDL_Surface *surface = IMG_Load(image_path);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surface);

	return textureID;
}

void spawnSpinner(){
	Entity spinner;
	spinner.x = -3.0f;
	spinner.y = 1.7f;

	spinner.width = 63.0f;
	spinner.height = 62.0f;

	enemies.push_back(spinner); 
}

bool shouldRemoveSpinner(Entity spinner){
	if (spinner.x > 3 && spinner.y < -1.2f){
		return true;
		lives--;
	} else
		return false;
}

void ClassDemoApp::menuUpdate(float elapsed){

}

void ClassDemoApp::gameUpdate(float elapsed){
	//player.Update(elapsed);

	if (((int)elapsed % 1000) == 0){
		spawnSpinner();
	}
	for (int i = 0; i < enemies.size(); i++){
		if (((int)elapsed % 1000) == 0){
			if (enemies[i].x <= 3)
				enemies[i].x += 1;
		}
		if (shouldRemoveSpinner(enemies[i]))
			enemies.erase(enemies.begin() + i);

		if (bullets.size() > 0){
			bullets[0].y += player.velocity_y * elapsed;
			if (enemies[i].collidesWith(&(bullets[0]))){
				enemies.erase(enemies.begin() + i);
				bullets.erase(bullets.begin()); 
			}
		}
	}
	if (bullets.size() > 0){
		if (bullets[0].y >= 1.9)
			bullets.erase(bullets.begin());
	}
/*	for (int i = 0; i < entities.size(); i++){
		if (!entities[i].isStatic){
			entities[i].y += entities[i].velocity_y*elapsed;
	for (int j = 0; j < entities.size(); j++){
		if (entities[j].isStatic && i != j){
			if (entities[i].collidesWith(&(entities[j]))){ //collision detection
				float penetration = fabs(fabs(player.y - block.y)) - player.height / 2.0f - block.height / 2.0f;

		if (player.y > block.y){
			player.y += penetration + 0.0001;
		}
		else {
			player.y += penetration + 0.0001;
		}

	player.velocity_y = 0.0f;
	}
	}
	else if (entities[j].entityType == ENTITY_ENEMY){ //check rules for entity types

	}
	}
	}
	}*/
}

void ClassDemoApp::overUpdate(float elapsed){

}

void ClassDemoApp::menuRender(){

}

void ClassDemoApp::gameRender(){

}

void ClassDemoApp::overRender(){

}

void ClassDemoApp::Setup(){
	//SDL and OpenGL initialization
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
	#ifdef _WINDOWS
		glewInit();
	#endif

	glViewport(0, 0, 640, 360);
	projectionMatrix.setOrthoProjection(-3.55f, 3.55f, -2.0f, 2.0f, -1.0f, 1.0f);
	program = ShaderProgram(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	GLuint playerTex = LoadTexture(RESOURCE_FOLDER"alienPink.png");
	GLuint blockTex = LoadTexture(RESOURCE_FOLDER"tiles_spritesheet.png"); //using GrassCenter.png
	GLuint enemyTex = LoadTexture(RESOURCE_FOLDER"enemies.png");

	player.sprite = SheetSprite(playerTex, 67.0f / 512.0f, 196.0f / 512.0f, 66.0f / 512.0f, 92.0f / 512.0f, 0.3f);
	player.x = 0.0f;
	player.y = -1.9f;
	player.height = 0.2f;
	player.width = 0.2f;

	for (int i = 0; i < 3; i++){
		Entity block;
		block.x = -2.5f + i * 1;
		block.y = -1.6f;
		block.height = 0.4f;
		block.width = 0.4f;
		blocks.push_back(block);
	}

	/*for (int i = 0; i < 20; i++){ //draw blocks in different positions
		Entity coin;
		coin.sprite = SheetSprite(spriteSheetTexture3, 144.0f / 576.0f, 648.0f / 576.0f, 70.0f / 576.0f, 70.0f / 576.0f, 0.2f);
		coin.y = -0.6f + (0.2 * i); //coin spawn positions
		coin.x = -1.4f + (0.7 * i);
		coin.width = 0.1f; //collision boundaries, not the sprite itself
		coin.height = 0.1f;
		coin.isStatic = true;

		entities.push_back(coin);
	}*/
}

ClassDemoApp::~ClassDemoApp(){
	//SDL and OpenGL cleanup
}

void ClassDemoApp::ProcessInput(){

}

void ClassDemoApp::Render(){
	//clear, render, and swap window
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	program.setProjectionMatrix(projectionMatrix);
	program.setViewMatrix(viewMatrix);
	program.setModelMatrix(modelMatrix);
	
	SDL_GL_SwapWindow(displayWindow);
}

void ClassDemoApp::ProcessEvents(){
	while (SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE){
			done = true;
		} else if (event.type == SDL_KEYDOWN) { //these are unsigned int types
			if (event.key.keysym.scancode == SDL_SCANCODE_LEFT){
				player.x -= 1;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT){
				player.x += 1;
			}
			
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE){
				switch (state){
				case(STATE_MENU) :
					state = STATE_GAME;

				case(STATE_GAME) :
					if (bullets.size() == 0){
						Entity bullet;
						bullet.x = player.x;
						bullet.y = player.y;
						bullet.velocity_x = 0.0f;
						bullet.velocity_y = 5.0f;
						bullets.push_back(bullet);
					}

				case(STATE_OVER) :
					state = STATE_MENU;
				}
			}
		}
	}
}

void ClassDemoApp::Update(float elapsed){
	//move things based on time passed
	//check for collisions and respond to them
	if (lives <= 0)
		done = true;

	switch (state){
	case STATE_MENU:
		menuUpdate(elapsed);
	case STATE_GAME:
		gameUpdate(elapsed);
	case STATE_OVER:
		overUpdate(elapsed);
	}
	/*if (player.collidesWith(&block)){
		float penetration = fabs(fabs(player.y - block.y)) - player.height / 2.0f - block.height / 2.0f;

		if (player.y > block.y){
			player.y += penetration + 0.0001;
		}
		else {
			player.y += penetration + 0.0001;
		}

		player.velocity_y = 0.0f;
	}

	player.x += player.velocity_x * elapsed;

	if (player.collidesWith(&block)){
		float penetration = fabs(fabs(player.x - block.x)) - player.width / 2.0f - block.width / 2.0f;

		if (player.x > block.x){
			player.x += penetration + 0.0001;
		}
		else {
			player.x += penetration + 0.0001;
		}

		player.velocity_x = 0.0f;
	}*/
}



bool ClassDemoApp::UpdateAndRender(){
	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;

	float fixedElapsed = elapsed;
	/*if (fixedElapsed > FIXED_TIMESTEP * MAX_TIMESTEPS){
		fixedElapsed = FIXED_TIMESTEP * MAX_TIMESTEPS;
	}

	while (fixedElapsed >= FIXED_TIIMSTEP){

	}*/
	ProcessEvents();
	Update(elapsed);
	Render();

	return done;
}

/*void ClassDemoApp::DrawSpriteSheetSprite(int index, int spriteCountX, int spriteCountY){ //can pass width and height to function
	float u = (float)(((int) index) % spriteCountX) / (float) spriteCountX;
	float v = (float)(((int)index) / spriteCountX) / (float)spriteCountX;
	float spriteWidth = 1.0 / (float)spriteCountX;
	float spriteHeight = 1.0 / (float)spriteCountY;

	SheetSprite sheet = SheetSprite(u, v, spriteWidth, spriteHeight, 1);

	sheet.Draw(program);
	
	/*GLfloat texCoords[] = {
		u, v + spriteHeight,
		u + spriteWidth, v,
		u, v,
		u + spriteWidth, v,
		u, v + spriteHeight,
		u + spriteWidth, v + spriteHeight
	};

	float vertices[] = {
		-0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f,
		0.5f, 0.5f,
		-0.5f, -0.5f,
		0.5f, -0.5f
	};//vertices here. sets a static sized sprite

	glVertexAttribPointer((*program).positionAttribute, 2, GL_FLOAT, false, 0, vertices);
	glEnableVertexAttribArray((*program).positionAttribute);

	glVertexAttribPointer((*program).texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
	glEnableVertexAttribArray((*program).texCoordAttribute);

	glBindTexture(GL_TEXTURE_2D, rectangle);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	//set position and texture attributes
	//draw triangles as normal
}*/