#include "Enemy.h"

bool Enemy::getIsLockedOn() {
	Vector2 diff = Vector2Subtract(World_Position, Target->getWorldPos());
	return diff.x >= -160 && diff.x <= 160 && diff.y >= -160 && diff.y <= 160;
}
Knight* Enemy::getTarget(){	return Target; }
void Enemy::setTarget(Knight* target) { Target = target; }

Vector2 Enemy::getToTarget() { 
	return Vector2Subtract(Target->getWorldPos(), World_Position);
}

void Enemy::drawCharacter(){
	Vector2 target_world_pos_adjusted = Vector2Subtract(Target->getWorldPos(), Target->getScreenPos());
	Screen_Position = Vector2Subtract(World_Position, target_world_pos_adjusted);
	Character::drawCharacter();
}


void Enemy::tick(float dT) {
	animateCharacter(dT);
	drawCharacter();
}
