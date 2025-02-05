#include "Critter.h"
#include "src/AABB.h"

Critter::Critter()
{
	m_position = Vector2{ 0, 0 };
	m_velocity = Vector2{ 0, 0 };
	m_radius = 0;
	m_isLoaded = false;
}

Critter::~Critter()
{
	m_isLoaded = false;
}

void Critter::Init(Vector2 position, Vector2 velocity, float radius, Texture2D texture)
{
	m_position = position;
	m_velocity = velocity;
	m_radius = radius;
	
	m_texture = texture;

	m_isLoaded = true;
}

void Critter::Reset()
{
	m_position = { 0,0 };
	m_velocity = { 0,0 };
	m_radius = 0;
	m_isLoaded = false;
}

void Critter::Destroy()
{

	m_isLoaded = false;
}

void Critter::Update(float dt)
{
	if (m_isLoaded == false)
		return;

	m_position.x += m_velocity.x * dt;
	m_position.y += m_velocity.y * dt;

	m_isDirty = false;
}


void Critter::Draw()
{
	if (m_isLoaded == false)
		return;

	DrawTexture(m_texture, m_position.x - m_texture.width / 2, m_position.y- m_texture.height /2, WHITE);
}

AABB& Critter::GetBoundry()
{
	Vector2 box = { m_texture.width / 2, m_texture.height / 2 };
	m_boundry = { m_position,box };
	return m_boundry;


}
