#pragma once
#include "raymath.h"

class AABB
{
public:
	AABB();
	AABB(Vector2 center, Vector2 halfsize) : center(center), halfsize(halfsize) {}
	~AABB();

	bool Contains(Vector2 point);
	bool Intersects(AABB other);
	bool Overlap(AABB other);

	Vector2 center;
	Vector2 halfsize;
};

