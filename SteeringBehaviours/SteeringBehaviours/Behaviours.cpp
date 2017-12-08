#include "Behaviours.h"

BaseBehaviours* BaseBehaviours::Instance = NULL;

XMVECTOR BaseBehaviours::Seek(Unit* master, FXMVECTOR pos) {
	XMVECTOR ret = pos - master->Pos();
	XMVector2Normalize(ret);
	ret *= master->VCeil();
	return ret - master->Velocity();
}

XMVECTOR BaseBehaviours::Flee(Unit* master, FXMVECTOR pos) {
	XMVECTOR ret = -pos + master->Pos();
	XMVector2Normalize(ret);
	ret *= master->VCeil();
	return ret - master->Velocity();
}

XMVECTOR BaseBehaviours::Arrive(Unit* master, FXMVECTOR pos) {
	XMVECTOR ret = pos - master->Pos();
	float dist;
	XMStoreFloat(&dist, XMVector2Length(ret));
	float speed = dist; 
	speed = min(speed, master->VCeil());
	return XMVector2Normalize(ret) * speed - master->Velocity();
}

XMVECTOR BaseBehaviours::Hide(Unit* master, Unit* target) {
	return zero;
}

XMVECTOR BaseBehaviours::Pursuit(Unit* master, Unit* target) {
	return zero;
}

XMVECTOR BaseBehaviours::Avoid(Unit* master) {
	return zero;
}

XMVECTOR BaseBehaviours::WallDetection(Unit* master) {
	return zero;
}

XMVECTOR BaseBehaviours::Wander(Unit* master) {
	return zero;
}

XMVECTOR BaseBehaviours::Seperation(Unit* master) {
	return zero; 
}

XMVECTOR BaseBehaviours::Alignment(Unit* master) {
	return zero; 
}

XMVECTOR BaseBehaviours::Cohesion(Unit* master) {
	return zero; 
}


