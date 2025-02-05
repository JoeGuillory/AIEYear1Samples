#pragma once
#include "Map.h"
class Texture2D;


class TextureManager
{
public:
	static TextureManager& instance();

	Texture2D GetTexture(int key);

private:
	TextureManager();
	~TextureManager();

	static TextureManager* m_instance;
	Map<int, Texture2D> m_textures;
};
