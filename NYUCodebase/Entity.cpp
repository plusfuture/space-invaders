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
	modelMatrix.identity();
	modelMatrix.Translate(x, y, 0.0);
	program->setModelMatrix(modelMatrix);

	sprite.Draw(program);
}

void Entity::Draw(ShaderProgram *program){
	sprite.Draw(program);
}

bool Entity::collidesWith(Entity *entity){
	if (((x - width) > (entity->x + (entity->width))) ||
		((x + width) < (entity->x - (entity->width))) ||
		((y - height) > (entity->y + (entity->height))) ||
		((y + height) < (entity->y - (entity->height)))){ //rectangles are not intersecting
		return false;
	}
	else
		return true;
}

float Entity::lerp(float a, float b, float time){
	return (1 - time) * a + time * b ;
}