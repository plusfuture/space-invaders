#ifndef ENTITY_H
#define ENTITY_H

#include "ShaderProgram.h"
#include "SheetSprite.h"

//enum EntityType{ENTITY_PLAYER, ENTITY_ENEMY, ENTITY_COIN};

class Entity{
public:
	Entity();

	void Update(float elapsed);
	void Render(ShaderProgram *program);
	void Draw(ShaderProgram *program);
	float lerp(float a, float b, float time);
	bool collidesWith(Entity *entity);

	SheetSprite sprite;

	float hitCount;

	float x;
	float y;

	float width;
	float height;

	float velocity_x;
	float velocity_y;
	
	float acceleration_x;
	float acceleration_y;

	bool isStatic;
	//EntityType entityType;
};

#endif