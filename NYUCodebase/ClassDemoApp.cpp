#include "ClassDemoApp.h"

ClassDemoApp::ClassDemoApp(){
	Setup();
}

void DrawText(int fontTexture, std::string text, float size, float spacing, ShaderProgram *program,
				float xOffset, float yOffset) {
	float texture_size = 1.0 / 16.0f;
	std::vector<float> vertexData;
	std::vector<float> texCoordData;
	for (int i = 0; i < text.size(); i++) {
		float texture_x = (float)(((int)text[i]) % 16) / 16.0f;
		float texture_y = (float)(((int)text[i]) / 16) / 16.0f;
		vertexData.insert(vertexData.end(), {
			((size + spacing) * i) + (-0.5f * size), 0.5f * size,
			((size + spacing) * i) + (-0.5f * size), -0.5f * size,
			((size + spacing) * i) + (0.5f * size), 0.5f * size,
			((size + spacing) * i) + (0.5f * size), -0.5f * size,
			((size + spacing) * i) + (0.5f * size), 0.5f * size,
			((size + spacing) * i) + (-0.5f * size), -0.5f * size,
		});
		texCoordData.insert(texCoordData.end(), {
			texture_x, texture_y,
			texture_x, texture_y + texture_size,
			texture_x + texture_size, texture_y,
			texture_x + texture_size, texture_y + texture_size,
			texture_x + texture_size, texture_y,
			texture_x, texture_y + texture_size,
		});
	}
	Matrix modelMatrix;
	modelMatrix.identity();
	modelMatrix.Translate(xOffset, yOffset, 0.0f);
	program->setModelMatrix(modelMatrix);
	glUseProgram(program->programID);
	glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertexData.data());
	glEnableVertexAttribArray(program->positionAttribute);
	glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoordData.data());
	glEnableVertexAttribArray(program->texCoordAttribute);
	glBindTexture(GL_TEXTURE_2D, fontTexture);
	glDrawArrays(GL_TRIANGLES, 0, text.size() * 6);
	glDisableVertexAttribArray(program->positionAttribute);
	glDisableVertexAttribArray(program->texCoordAttribute);
}

GLuint LoadTexture(const char *image_path){
	SDL_Surface *surface = IMG_Load(image_path);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surface);

	return textureID;
}

void ClassDemoApp::spawnSpinner(){
	Entity spinner;
	spinner.sprite = SheetSprite(enemyTex, 134.0f / 1024.0f, 372.0f / 512.0f, 63.0f / 1024.0f, 62.0f / 512.0f, 0.3f);
	spinner.x = -2.5f;
	spinner.y = 1.7f;
	spinner.width = 63.0f/1024.0f;
	spinner.height = 62.0f/512.0f;
	enemies.push_back(spinner); 
}

bool ClassDemoApp::shouldRemoveSpinner(Entity spinner){
	if (spinner.y < -1.2f){
		lives--;
		return true;
	} else
		return false;
}

void ClassDemoApp::menuUpdate(float elapsed){
	
}

void ClassDemoApp::gameUpdate(float elapsed){ 
	spawnTimer++;
	if ((spawnTimer % 10000) == 0){
		spawnSpinner();
	}
	for (int i = 0; i < enemies.size(); i++){
		if ((rand() % 100 + 1) > 90){
			if (enemyBullets.size() == 0){
				Entity enemyBullet;
				enemyBullet.sprite = SheetSprite(bulletTex, 0.0f, 0.0f, 0.1f, 0.3f, 0.3f);
				enemyBullet.x = enemies[i].x;
				enemyBullet.y = enemies[i].y;
				enemyBullet.width = 0.05f;
				enemyBullet.height = 0.15f;
				enemyBullet.velocity_x = 0.0f;
				enemyBullet.velocity_y = -1.0f;
				enemyBullets.push_back(enemyBullet);
			}
		}
		if ((spawnTimer % 10000) == 0){
			if (enemies[i].x <= 2.0f)
				enemies[i].x += 0.5f;
			else{
				enemies[i].x = -2.5f;
				enemies[i].y -= 0.7f;
			}
		}
		if (shouldRemoveSpinner(enemies[i]))
			enemies.erase(enemies.begin() + i);

		if (bullets.size() > 0){
			bullets[0].y += bullets[0].velocity_y * elapsed;
			if (enemies[i].collidesWith(&(bullets[0]))){
				enemies.erase(enemies.begin() + i);
				bullets.erase(bullets.begin()); 
			}
		}
	}
	if (bullets.size() > 0){
		for (int i = 0; i < blocks.size(); i++){
			if (blocks[i].collidesWith(&(bullets[0]))){
				blocks.erase(blocks.begin() + i);
				bullets.erase(bullets.begin());
				break;
			}
		}
	}
	if (bullets.size() > 0){
		if (bullets[0].y >= 1.9)
			bullets.erase(bullets.begin());
	}
	if (enemyBullets.size() > 0){
		enemyBullets[0].y += enemyBullets[0].velocity_y*elapsed;
		/*for (int j = 0; j < blocks.size(); j++){
			if (blocks[j].collidesWith(&(enemyBullets[0]))){
				blocks.erase(blocks.begin() + j);
				enemyBullets.erase(enemyBullets.begin());
				break;
			}
		}*/
			if (player.collidesWith(&(enemyBullets[0]))){
				lives--;
				enemyBullets.erase(enemyBullets.begin());
			}
	}
	if (enemyBullets.size() > 0){
		if (enemyBullets[0].y <= -2.2)
			enemyBullets.erase(enemyBullets.begin());
	}
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
	program = new ShaderProgram(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	playerTex = LoadTexture(RESOURCE_FOLDER"alienPink.png");
	blockTex = LoadTexture(RESOURCE_FOLDER"tiles_spritesheet.png"); //using GrassCenter.png
	enemyTex = LoadTexture(RESOURCE_FOLDER"enemies.png");
	bulletTex = LoadTexture(RESOURCE_FOLDER"laserRed02.png");
	fontTex = LoadTexture(RESOURCE_FOLDER"font1.png");

	player.sprite = SheetSprite(playerTex, 70.0f / 256.0f, 92.0f / 512.0f, 66.0f / 256.0f, 92.0f / 512.0f, 0.3f);
	player.x = 0.0f;
	player.y = -1.9f;
	player.height = 0.2f;
	player.width = 0.2f;

	for (int i = 0; i < 4; i++){
		Entity block;
		block.sprite = SheetSprite(blockTex, 288.0f / 914.0f, 792.0f / 936.0f, 70.0f / 914.0f, 70.0f / 936.0f, 0.3f);
		block.x = -2.0f + i * 1.5;
		block.y = -1.3f;
		block.height = 0.4f;
		block.width = 0.4f;
		block.Render(program);
		blocks.push_back(block);
	}

	spawnSpinner();
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

	(*program).setProjectionMatrix(projectionMatrix);
	(*program).setViewMatrix(viewMatrix);
	(*program).setModelMatrix(modelMatrix);
	
	glUseProgram((*program).programID);

	switch (state){
	case STATE_MENU:
		DrawText(fontTex, "Press space to start!", 0.25f, 0.0f, program, -2.0f, 0.0f);
		break;
	case STATE_GAME:
		for (int i = 0; i < blocks.size(); i++){
			blocks[i].Render(program);
		}
		for (int i = 0; i < enemies.size(); i++){
			enemies[i].Render(program);
		}
		for (int i = 0; i < bullets.size(); i++){
			bullets[i].Render(program);
		}
		for (int i = 0; i < enemyBullets.size(); i++){
			enemyBullets[i].Render(program);
		}
		player.Render(program);
		DrawText(fontTex, "LIVES=" + std::to_string(lives), 0.15f, 0.0f, program, -3.3f, -1.7f);
		break;
	case STATE_OVER:
		DrawText(fontTex, "Game over.. space to exit", 0.20f, 0.0f, program, -2.5f, 0.0f);
		break;
	}
	SDL_GL_SwapWindow(displayWindow);
}

void ClassDemoApp::ProcessEvents(){
	while (SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE){
			done = true;
		} else if (event.type == SDL_KEYDOWN) { //these are unsigned int types
			if (event.key.keysym.scancode == SDL_SCANCODE_LEFT){
				if (state == STATE_GAME)
					player.x -= 0.1f;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT){
				if (state == STATE_GAME)
					player.x += 0.1f;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_D){
				lives--;
			}
			
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE){
				switch (state){
				case(STATE_MENU) :
					state = STATE_GAME;
					break;
				case(STATE_GAME) :
					if (bullets.size() == 0){
						Entity bullet;
						bullet.sprite = SheetSprite(bulletTex, 0.0f, 0.0f, 0.1f, 0.3f, 0.3f);
						bullet.x = player.x;
						bullet.y = player.y;
						bullet.width = 0.05f;
						bullet.height = 0.15f;
						bullet.velocity_x = 0.0f;
						bullet.velocity_y = 1.0f;
						bullets.push_back(bullet);
					}
					 break;
				case(STATE_OVER) :
					done = true;
					break;
				}
			}
		}
	}
}

void ClassDemoApp::Update(float elapsed){
	//move things based on time passed
	//check for collisions and respond to them
	if (lives <= 0)
		state = STATE_OVER;

	switch (state){
	case STATE_MENU:
		menuUpdate(elapsed);
		break;
	case STATE_GAME:
		gameUpdate(elapsed);
		break;
	case STATE_OVER:
		overUpdate(elapsed);
		break;
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
	
	float ticks = SDL_GetTicks() / 1000.0f;
	float elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;

	float fixedElapsed = elapsed;
	srand(time(NULL));
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