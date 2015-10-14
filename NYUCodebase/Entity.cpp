#include "Entity.h"

Entity::Entity(){

}


void Entity::Update(float elapsed){
	float gravity = -4.0f;
	float friction = 6.0f;

	velocity_x = lerp(velocity_x, 0.0, friction * elapsed);

	velocity_x += acceleration_x * elapsed;
	velocity_y += acceleration_y * elapsed;
}

void Entity::Render(ShaderProgram *program){
	Matrix modelMatrix;

	modelMatrix.Translate(x, y, 0.0);
	program->setModelMatrix(modelMatrix);

	Draw(program);
}

void Entity::Draw(ShaderProgram *program){
	sprite.Draw(program);
}

bool Entity::collidesWith(Entity *entity){
	if (x - width/2 > entity->x + (entity->width)/2 ||
		x + width/2 < entity->x - (entity->width)/2 ||
		y - height/2 > entity->y + (entity->height)/2 ||
		y + height/2 < entity->y - (entity->height)/2){ //rectangles are not intersecting
		return false;
	}
	else
		return true;
}

float Entity::lerp(float a, float b, float time){
	return (1 - time) * a + time * b ;
}