#pragma once
#include "AABB.h"
#include "raylib.h"
template<typename T>
class QuadTree
{
public:
	static const int m_capacity = 2;
	enum SUBTREE{TOP_LEFT = 0,TOP_RIGHT,BOTTOM_LEFT,BOTTOM_RIGHT};

public:
	QuadTree<T>();
	QuadTree<T>(AABB boundry);
	~QuadTree<T>();

	bool Insert(T* object);
	void Subdivide();
	void Update(float deltaTime);
	void Draw();

private:
	QuadTree** m_children;
	int m_childrenLength;
	AABB m_boundry;
	T* m_objects;
};

template<typename T>
inline QuadTree<T>::QuadTree() : m_objects(nullptr), m_children(nullptr), m_childrenLength(0)
{
	if (IsWindowReady)
	{
		m_boundry.halfsize.x = GetScreenWidth() / 2 ;
		m_boundry.halfsize.y = GetScreenHeight() / 2;
		m_boundry.center = m_boundry.halfsize;

	}
}

template<typename T>
inline QuadTree<T>::QuadTree(AABB boundry) : m_boundry(boundry), m_objects(nullptr), m_children(nullptr), m_childrenLength(0)
{

}

template<typename T>
inline QuadTree<T>::~QuadTree()
{
	if (m_children != nullptr)
	{
		for (int i = 0; i < 4; i++)
		{
			if (m_children[i] != nullptr)
				delete m_children[i];
		}
	}
	if(m_objects != nullptr)
		for (int i = 0; i < m_capacity; i++)
		{
			if (m_objects[i] != nullptr)
				delete m_objects[i];
		}
	delete m_objects;
	m_objects = nullptr;
}

template<typename T>
inline bool QuadTree<T>::Insert(T* object)
{
	
}

template<typename T>
inline void QuadTree<T>::Subdivide()
{
}

template<typename T>
inline void QuadTree<T>::Update(float deltaTime)
{
}

template<typename T>
inline void QuadTree<T>::Draw()
{
}

