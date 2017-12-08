#pragma once
#include <Windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <DirectXMath.h>

#include <iostream>
#include <string>
using namespace DirectX;

static XMVECTORF32 zero = {0.0f, 0.0f, 0.0f, 0.0f};

XMFLOAT2 operator + (XMFLOAT2 a, XMFLOAT2 b) {
	XMFLOAT2 tmp; 
	XMStoreFloat2(&tmp, XMLoadFloat2(&a) + XMLoadFloat2(&b));
	return tmp; 
}

XMFLOAT2 operator - (XMFLOAT2 a, XMFLOAT2 b) {
	XMFLOAT2 ret;
	XMStoreFloat2(&ret, XMLoadFloat2(&a) - XMLoadFloat2(&b));
	return ret;
}

float Lenth(XMFLOAT2 v) {
	float f = 0.0f; 
	XMStoreFloat(&f, XMVector2Length(XMLoadFloat2(&v)));
	return f; 
}

float LenthSq(XMFLOAT2 v) {
	float f = 0.0f; 
	XMStoreFloat(&f, XMVector2LengthSq(XMLoadFloat2(&v)));
	return f; 
}

XMFLOAT2 Normalize(XMFLOAT2 v) {
	XMFLOAT2 ret; 
	XMStoreFloat2(&ret, XMVector2Normalize(XMLoadFloat2(&v))); 
	return ret; 
}