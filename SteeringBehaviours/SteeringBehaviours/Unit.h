#pragma once
#include "Util.h"
#include "Behaviours.h"

class BaseEntity {
public:
	BaseEntity() {
		id = ++idNum; 
	}
	XMVECTOR Pos() { return XMLoadFloat2(&position); }
	float Radius() { return radius; }
	float Width()  { return width; }
protected:
	int id; 
	static int idNum; 
	XMFLOAT2 position; 
	float radius; 
	float width; 
};

int BaseEntity::idNum = 0;

class Unit : public BaseEntity{
public:
	void Update(FXMVECTOR _force, float dt);
	virtual void Calc(); 
	float VCeil() { return velocityMax; }
	XMVECTOR Velocity() { return XMLoadFloat2(&velocity); }
protected:
	XMFLOAT2 velocity;
	XMFLOAT2 tangent; 
	XMFLOAT2 heading; 
	XMFLOAT2 acceleration;

	float velocityMax; 
	float forceMax;
	float mass; 
	BaseBehaviours* steering; 
};

class Attacker : public Unit {
	
};
