#include "TextureManager.h"
#include "raylib.h"

TextureManager* TextureManager::m_instance = nullptr;

TextureManager& TextureManager::instance()
{
	if (!m_instance)
		m_instance = new TextureManager();
	return *m_instance;
}

Texture2D TextureManager::GetTexture(int key)
{
	return m_textures.Get(key);
}

TextureManager::TextureManager()
{
	Texture2D critter = LoadTexture("res/10.png");
	Texture2D destroyer = LoadTexture("res/9.png");
	m_textures.Insert(1, critter);
	m_textures.Insert(2, destroyer);



}

TextureManager::~TextureManager()
{
}
