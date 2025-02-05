#pragma once
#include "raylib.h"
#include "raymath.h"
#include "AABB.h"
#include "TreeNode.h"
#include "List.h"
template<typename T>
class QuadTree
{
public:
	static const int m_capacity = 2;
	

public:
	QuadTree<T>();
	QuadTree<T>(AABB boundry);
	~QuadTree<T>();

	bool Insert(TreeNode<T>* object);
	void Subdivide();
	void Update(float deltaTime);
	void Remove(TreeNode<T>* object);
	void Draw();

private:
	QuadTree<T>** m_children;
	int m_childrenLength;
	AABB m_boundry;
	TreeNode<T>** m_objects;
	
};

template<typename T>
inline QuadTree<T>::QuadTree() : 	m_childrenLength(0)
{
	if (IsWindowReady)
	{
		m_boundry.halfsize.x = GetScreenWidth() / 2 ;
		m_boundry.halfsize.y = GetScreenHeight() / 2;
		m_boundry.center = m_boundry.halfsize;

	}
}

template<typename T>
inline QuadTree<T>::QuadTree(AABB boundry) : m_boundry(boundry), m_childrenLength(0)
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
	if (m_objects != nullptr)
	{
		for (int i = 0; i < m_capacity; i++)
		{
			if (m_objects[i] != nullptr)
				delete m_objects[i];
		}
		delete m_objects;
		m_objects = nullptr;
	}
}

template<typename T>
inline bool QuadTree<T>::Insert(TreeNode<T>* object)
{
	if (m_boundry.Contains(object->boundry->center) == false)
		return false;

	if (m_children == nullptr)
	{
		if (m_objects == nullptr)
		{
			m_objects = new TreeNode<T>*[m_capacity];
			memset(m_objects, 0, sizeof(TreeNode<T>*) * m_capacity);
		}
		if (m_objects[m_capacity -1] == nullptr)
		{
			for (int i = 0; i < m_capacity; i++)
			{
				if (m_objects[i] == nullptr)
				{
					m_objects[i] = object;
					return true;
				}
			}
		}

		Subdivide();
	}
	
	for (int i = 0; i < 4; i++)
	{
		if (m_children[i]->Insert(object) == true)
			return true;
	}

	return false;
}

template<typename T>
inline void QuadTree<T>::Subdivide()
{
	m_children = new QuadTree<T> * [4];
	Vector2 qSize{ m_boundry.halfsize.x / 2, m_boundry.halfsize.y / 2 };
	Vector2 qCentre{ m_boundry.center.x - qSize.x,
	m_boundry.center.y - qSize.y };
	m_children[0] = new QuadTree<T>(AABB(qCentre, qSize));
	qCentre = Vector2{ m_boundry.center.x + qSize.x,
	m_boundry.center.y - qSize.y };
	m_children[1] = new QuadTree<T>(AABB(qCentre, qSize));
	qCentre = Vector2{ m_boundry.center.x - qSize.x,
	m_boundry.center.y + qSize.y };
	m_children[2] = new QuadTree<T>(AABB(qCentre, qSize));
	qCentre = Vector2{ m_boundry.center.x + qSize.x,
	m_boundry.center.y + qSize.y };
	m_children[3] = new QuadTree<T>(AABB(qCentre, qSize));
	if (m_objects != nullptr) 
	{
		for (int i = 0; i < m_capacity; i++)
		{
			if (m_objects[i] == nullptr)
				continue;

			for (int j = 0; j < 4; j++)
				if (m_children[j]->Insert(m_objects[i]) == true)
					break;

			m_objects[i] = nullptr;
		}
	}

	delete m_objects;
	m_objects = nullptr;
}


template<typename T>
inline void QuadTree<T>::Update(float deltaTime)
{
	if (m_objects != nullptr)
	{
		for (int i = 0; i < m_capacity -1; i++)
		{
			if (m_boundry.Contains(m_objects[i]->boundry->center))
			{


			}

		}
	}


	if (m_children != nullptr)
	{
		for (int i = 0; i < 4; i++)
		{
			m_children[i]->Update(deltaTime);
		}
	}

}

template<typename T>
inline void QuadTree<T>::Remove(TreeNode<T>* object)
{





}

template<typename T>
inline void QuadTree<T>::Draw()
{
	DrawLine(
		m_boundry.center.x - m_boundry.halfsize.x,
		m_boundry.center.y - m_boundry.halfsize.y,
		m_boundry.center.x + m_boundry.halfsize.x,
		m_boundry.center.y - m_boundry.halfsize.y, RED);
	DrawLine(
		m_boundry.center.x - m_boundry.halfsize.x,
		m_boundry.center.y + m_boundry.halfsize.y -1,
		m_boundry.center.x + m_boundry.halfsize.x,
		m_boundry.center.y + m_boundry.halfsize.y -1, RED);
	DrawLine(
		m_boundry.center.x - m_boundry.halfsize.x,
		m_boundry.center.y + m_boundry.halfsize.y + 1,
		m_boundry.center.x - m_boundry.halfsize.x,
		m_boundry.center.y - m_boundry.halfsize.y + 1, RED);
	DrawLine(
		m_boundry.center.x + m_boundry.halfsize.x,
		m_boundry.center.y + m_boundry.halfsize.y,
		m_boundry.center.x + m_boundry.halfsize.x,
		m_boundry.center.y - m_boundry.halfsize.y, RED);

	if (m_children != nullptr)
	{
		for (int i = 0; i < 4; i++)
			m_children[i]->Draw();
	}


}

