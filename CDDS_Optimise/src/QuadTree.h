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
	enum SUBTREE{TOP_LEFT = 0,TOP_RIGHT,BOTTOM_LEFT,BOTTOM_RIGHT};

public:
	QuadTree<T>();
	QuadTree<T>(AABB boundry);
	~QuadTree<T>();

	bool Insert(TreeNode<T> object);
	void Subdivide();
	void Update(float deltaTime);
	void Draw();

private:
	List<QuadTree<T>*> m_children;
	int m_childrenLength;
	AABB m_boundry;
	List<TreeNode<T>*> m_objects;
	
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
	if (m_children.last() != nullptr)
	{
		m_children.destroy();
	}
	if (m_objects.last() != nullptr)
	{
		m_objects.destroy();
	}
}

template<typename T>
inline bool QuadTree<T>::Insert(TreeNode<T> object)
{
	if (m_boundry.Contains(object.boundry.center) == false)
		return false;

	if (m_children.last() == nullptr)
	{
		
		if (m_objects.getLength() == m_capacity - 1)
		{
			m_objects.pushBack(&object);
			return true;
		}

		Subdivide();
	}
	
	for (auto iter = m_children.begin(); iter != nullptr; iter++)
	{
		QuadTree<T>* value = *iter;
		if (value->Insert(object) == true)
			return true;
	}

	return false;
}

template<typename T>
inline void QuadTree<T>::Subdivide()
{

	Vector2 qSize{ m_boundry.halfsize.x / 2, m_boundry.halfsize.y / 2 };
	Vector2 qCentre{ m_boundry.center.x - qSize.x,
	m_boundry.center.y - qSize.y };
	m_children.pushBack(new QuadTree(AABB(qCentre, qSize)));
	qCentre = Vector2{ m_boundry.center.x + qSize.x,
	m_boundry.center.y - qSize.y };
	m_children.pushBack(new QuadTree(AABB(qCentre, qSize)));
	qCentre = Vector2{ m_boundry.center.x - qSize.x,
	m_boundry.center.y + qSize.y };
	m_children.pushBack(new QuadTree(AABB(qCentre, qSize)));
	qCentre = Vector2{ m_boundry.center.x + qSize.x,
	m_boundry.center.y + qSize.y };
	m_children.pushBack(new QuadTree(AABB(qCentre, qSize)));
	if (m_objects.last() != nullptr) 
	{

		for (auto t = m_objects.begin(); t != nullptr; t++) {
			if (*t == nullptr)
				continue;
			// find a subtree to insert the object into
			
			for (auto iter = m_children.begin(); iter != nullptr; iter++)
			{
				QuadTree<T>* value = *iter;
				TreeNode<T>* nodevalue = *t;
				if (value->Insert(*nodevalue) == true)
					break;
			}

			for (auto t = m_objects.begin(); t != nullptr; t++)
			{
				t = nullptr;
			}
		}
		m_objects.destroy();
	}
}


template<typename T>
inline void QuadTree<T>::Update(float deltaTime)
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

	for (auto iter = m_children.begin(); iter != nullptr; iter++)
	{
		QuadTree<T>* value = *iter;
		value->Draw();
	}


}

