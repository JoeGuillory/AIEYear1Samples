#include "AABB.h"

AABB::AABB()
{
}

AABB::~AABB()
{
}

bool AABB::Contains(Vector2 point)
{
	if (point.x < center.x + halfsize.x &&
		point.x > center.x - halfsize.x &&
		point.y < center.y + halfsize.y &&
		point.y > center.y - halfsize.y)
		return true;
	return false;
}

bool AABB::Intersects(AABB other)
{
	if (center.x + halfsize.x < other.center.x - other.halfsize.x ||
		center.x - halfsize.x > other.center.x + other.halfsize.x ||
		center.y + halfsize.y < other.center.y - other.halfsize.y ||
		center.y - halfsize.y > other.center.y + other.halfsize.y)
		return false;
	return true;
}
