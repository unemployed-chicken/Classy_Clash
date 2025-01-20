#include "Enemy.h"


Knight* Enemy::getTarget(){	return Target; }
void Enemy::setTarget(Knight* target) { Target = target; }
float Enemy::getDPS() const { return DPS; }
float Enemy::getRadius() const { return Radius; }

Vector2 Enemy::getToTarget() { 
	return Vector2Subtract(Target->getWorldPos(), World_Position);
}

bool Enemy::getIsLockedOn() {
	Vector2 diff = Vector2Subtract(World_Position, Target->getWorldPos());
	return	diff.x >= -160 - (Width * scale) && 
			diff.x <= 160 + (Height * scale) && 
			diff.y >= -160 - (Height * scale) && 
			diff.y <= 160 + (Height * scale);
}

void Enemy::drawCharacter(){
	Vector2 target_world_pos_adjusted = Vector2Subtract(Target->getWorldPos(), Target->getScreenPos());
	Screen_Position = Vector2Subtract(World_Position, target_world_pos_adjusted);
	Character::drawCharacter();
}

void Enemy::tick(float dT) {
	animateCharacter(dT);
	drawCharacter();
	setCollisionRec();

	if (debugging) {
		DrawRectangleLines(
			collisionRec.x,
			collisionRec.y,
			collisionRec.width,
			collisionRec.height,
			BLACK
		);
	}
}
