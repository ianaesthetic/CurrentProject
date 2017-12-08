#include "Unit.h"

void Unit::Update(FXMVECTOR force, float dt) {	
	XMStoreFloat2(&acceleration, force / mass); 
	XMStoreFloat2(&acceleration, force / mass * dt); 
}
