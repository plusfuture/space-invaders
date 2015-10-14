#include "ClassDemoApp.h"

/*GLuint LoadTexture(const char *image_path){
	SDL_Surface *surface = IMG_Load(image_path);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surface);

	return textureID;
};*/

int main(int argc, char *argv[])
{
	ClassDemoApp app;
	app.Setup();
	while (!app.UpdateAndRender()) {}
	/*SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
#ifdef _WINDOWS
	glewInit();
#endif

	//SETUP
	glViewport(0, 0, 640, 360);

	Matrix modelMatrix;
	Matrix viewMatrix;
	Matrix projectionMatrix;

	projectionMatrix.setOrthoProjection(-3.55, 3.55, -2.0, 2.0, -1.0, 1.0);

	ShaderProgram program = ShaderProgram(RESOURCE_FOLDER"vertex.glsl", RESOURCE_FOLDER"fragment.glsl");

	float lastFrameTicks = 0.0f;
	float speed = 1.5f;

	bool lowerBoundHit = false;
	bool upperBoundHit = false;

	bool playerWin = false;
	bool spinnerWin = false;

	//left paddle
	float blVertX = -3.00f;
	float blVertY = -0.3f;
	float tlVertX = -3.00f;
	float tlVertY = 0.3f;
	float trVertX = -2.9f;
	float trVertY = 0.3f;
	float brVertX = -2.9f;
	float brVertY = -0.3f;

	//right paddle
	float blVertX2 = 2.9f;
	float blVertY2 = -0.3f;
	float tlVertX2 = 2.9f;
	float tlVertY2 = 0.3f;
	float trVertX2 = 3.0f;
	float trVertY2 = 0.3f;
	float brVertX2 = 3.0f;
	float brVertY2 = -0.3f;

	//ball
	float blVertXB = -0.1f;
	float blVertYB = -0.2f;
	float tlVertXB = -0.1f;
	float tlVertYB = 0.0f;
	float trVertXB = 0.1f;
	float trVertYB = 0.0f;
	float brVertXB = 0.1f;
	float brVertYB = -0.2f;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SDL_Event event;
	bool done = false;
	while (!done) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
			else if (event.type == SDL_KEYDOWN) { //these are unsigned int types
				if (event.key.keysym.scancode == SDL_SCANCODE_LEFT){
					angle = 0.0;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT){

				}
			}
		}

		float ticks = (float)SDL_GetTicks() / 1000.0f;
		float elapsed = ticks - lastFrameTicks;
		elapsed = elapsed * speed;
		lastFrameTicks = ticks;

		modelMatrix.identity();
		//modelMatrix.Rotate(angle);

		program.setModelMatrix(modelMatrix);
		program.setViewMatrix(viewMatrix);
		program.setProjectionMatrix(projectionMatrix);


		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); //use this before you start drawing

		const Uint8 *keys = SDL_GetKeyboardState(NULL);

		/*if (keys[SDL_SCANCODE_LEFT]){
			angle += elapsed * M_PI;
			} else if (keys[SDL_SCANCODE_RIGHT]){
			angle -= elapsed * M_PI;
			}

		glUseProgram(program.programID); //tells openGL which program to use

		//define paddle animation
		if (keys[SDL_SCANCODE_S]){
			if (lowerBoundHit == false){ //define initial animation behavior
				blVertY -= elapsed;
				tlVertY -= elapsed;
				trVertY -= elapsed;
				brVertY -= elapsed;
			}
		}

		if (keys[SDL_SCANCODE_W]){
			if (upperBoundHit == false){ //define initial animation behavior
				blVertY += elapsed;
				tlVertY += elapsed;
				trVertY += elapsed;
				brVertY += elapsed;
			}
		}

		if (keys[SDL_SCANCODE_DOWN]){
			if (lowerBoundHit == false){ //define initial animation behavior
				blVertY2 -= elapsed;
				tlVertY2 -= elapsed;
				trVertY2 -= elapsed;
				brVertY2 -= elapsed;
			}
		}

		if (keys[SDL_SCANCODE_UP]){
			if (upperBoundHit == false){ //define initial animation behavior
				blVertY2 += elapsed;
				tlVertY2 += elapsed;
				trVertY2 += elapsed;
				brVertY2 += elapsed;
			}
		}

		if (tlVertY >= 2.1){
			upperBoundHit = true;
			lowerBoundHit = false;
		}
		else{
			upperBoundHit = false;
		}

		if (blVertY <= -2.1){
			lowerBoundHit = true;
			upperBoundHit = false;
		}
		else{
			lowerBoundHit = false;
		}


		//start bg texture/////////////////////
		/*float bgVerts[] = { -3.55, -2, 3.55, 2, -3.55, 2, 3.55, 2, -3.55, -2, 3.55, -2 };
		glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, bgVerts);
		glEnableVertexAttribArray(program.positionAttribute);

		float texCoords[] = { 0.0, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0 };
		glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
		glEnableVertexAttribArray(program.texCoordAttribute);

		glBindTexture(GL_TEXTURE_2D, rectangle);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(program.positionAttribute);

		//make left paddle
		float vertices[] = { blVertX, blVertY, trVertX, trVertY, tlVertX, tlVertY,
			trVertX, trVertY, blVertX, blVertY, brVertX, brVertY };
		glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
		glEnableVertexAttribArray(program.positionAttribute);

		/*float texCoords[] = { 0.0, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0 };
		glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
		glEnableVertexAttribArray(program.texCoordAttribute);

		glBindTexture(GL_TEXTURE_2D, emojiTexture);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(program.positionAttribute);

		//start right paddle//////////////////////////////////////////
		modelMatrix.identity();
		//modelMatrix.Rotate(angle2);
		//program.setModelMatrix(modelMatrix);

		float rightVertices[] = { blVertX2, blVertY2, trVertX2, trVertY2, tlVertX2, tlVertY2,
			trVertX2, trVertY2, blVertX2, blVertY2, brVertX2, brVertY2 };

		glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, rightVertices);
		glEnableVertexAttribArray(program.positionAttribute);

		/*glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
		glEnableVertexAttribArray(program.texCoordAttribute);

		glBindTexture(GL_TEXTURE_2D, emojiFrownTex);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(program.positionAttribute);
		//glDisableVertexAttribArray(program.texCoordAttribute);

		//draw ball///////////////////////////////////////
		//check for ball collision on left paddle
		if (blVertY > tlVertYB ||
			tlVertY < blVertYB ||
			blVertX > brVertXB ||
			brVertX < blVertXB){ //rectangles are not intersecting
			//do nothing	
		}
		else{
			if (angle <= M_PI && angle >= M_PI/2){
				angle = angle - M_PI/2;
			}
			if(angle >=M_PI/2 && angle <= 3*M_PI/2){
				angle = angle + M_PI/2;
			}
		}

		//check for ball collision on right paddle
		if (blVertY2 > tlVertYB ||
			tlVertY2 < blVertYB ||
			blVertX2 > brVertXB ||
			brVertX2 < blVertXB){ //rectangles are not intersecting
			//do nothing	
		}
		else{
			if (angle <= M_PI/2 && angle >= 0){
				angle = angle + M_PI/2;
			}
			if (angle >= 3*M_PI/2 && angle <= 2*M_PI){
				angle = angle - M_PI/2;
			}
		}

		//check for ball collision on bottom wall
		if (blVertYB < -2.0f){
			if (angle >= M_PI && angle <= 3 * M_PI / 2){
				angle = angle - M_PI/2;
			}
			if (angle >= 3*M_PI/2 && angle <= 2*M_PI){
				angle = angle - 3*M_PI/2;
			}
		}

		//check for ball collision on top wall
		if (tlVertYB >= 2.0f){
			if (angle <= M_PI/2 && angle >= 0){
				angle = angle + 3*M_PI/2;
			}
			if (angle >= M_PI/2 && angle <= M_PI){
				angle = angle + M_PI/2;
			}
		}

		//program.setModelMatrix(modelMatrix);

		//animate ball

		blVertYB += sin(angle) * elapsed;
		tlVertYB += sin(angle) * elapsed;
		trVertYB += sin(angle) * elapsed;
		brVertYB += sin(angle) * elapsed;
		blVertXB += cos(angle) * elapsed;
		tlVertXB += cos(angle) * elapsed;
		trVertXB += cos(angle) * elapsed;
		brVertXB += cos(angle) * elapsed;

		float ballVertices[] = { 
			tlVertXB, tlVertYB, 
			blVertXB, blVertYB, 
			trVertXB, trVertYB, 
			trVertXB, trVertYB,
			blVertXB, blVertYB,
			brVertXB, brVertYB };

		glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, ballVertices);
		glEnableVertexAttribArray(program.positionAttribute);

		/*glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
		glEnableVertexAttribArray(program.texCoordAttribute);
		
		glBindTexture(GL_TEXTURE_2D, emojiSmileTex);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(program.positionAttribute);
		//glDisableVertexAttribArray(program.texCoordAttribute);

		if (blVertXB < -3.55){
			spinnerWin = true;
		}

		if (brVertXB > 3.55){
			playerWin = true;
		}

		SDL_GL_SwapWindow(displayWindow);
	}

	SDL_Quit();*/
	return 0;
}