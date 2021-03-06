#ifndef SHEETSPRITE_HEADER
#define SHEETSPRITE_HEADER
#include "ShaderProgram.h"
#using <System.dll>
using namespace System;
using namespace System::Diagnostics;
#define DEBUG

class SheetSprite{
public:
	SheetSprite();
	//SheetSprite(float u, float v, float width, float height, float size);
	SheetSprite(unsigned int textureID, float u, float v, float width, float height, float size);

	void Draw(ShaderProgram *program);

	float size;
	unsigned int textureID;
	float u;
	float v;
	float width;
	float height;
};

#endif