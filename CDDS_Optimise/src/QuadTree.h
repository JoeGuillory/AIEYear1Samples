#pragma once
#include "raylib.h"
#include "raymath.h"
#include "AABB.h"
#include "TreeNode.h"
#include "List.h"
#include "DynamicArray.h"
template<typename T>
class QuadTree
{
public:
	static const int m_capacity = 2;
	static const int m_maxDepth = 6;

public:
	QuadTree<T>();
	QuadTree<T>(AABB boundry);
	~QuadTree<T>();
	bool InsertObject(TreeNode<T>* object);
	bool Insert(TreeNode<T>* object);
	void Subdivide();
	void UnSubdivide();
	void Update(float deltaTime);
	DynamicArray<TreeNode<T>*> Search(AABB area);
	void Search(AABB area, DynamicArray<TreeNode<T>*>& list);
	bool HasItems(AABB area);
	void Items(DynamicArray<TreeNode<T>*>& list);
	bool Remove(TreeNode<T>* object);
	void Draw();

protected:
	int m_depthOfTree;
	AABB m_boundry;
	DynamicArray<QuadTree*> m_children;
	DynamicArray<TreeNode<T>*> m_objects;
	DynamicArray<TreeNode<T>*> m_allobjects;
};

template<typename T>
inline QuadTree<T>::QuadTree()
{
	if (IsWindowReady)
	{
		m_boundry.halfsize.x = GetScreenWidth() / 2 ;
		m_boundry.halfsize.y = GetScreenHeight() / 2;
		m_boundry.center = m_boundry.halfsize;

	}
}

template<typename T>
inline QuadTree<T>::QuadTree(AABB boundry) : m_boundry(boundry)
{

}

template<typename T>
inline QuadTree<T>::~QuadTree()
{
	
	m_objects.Clear();
	if (m_children.Length() != 0)
	{
		for (int i = 0; i < m_children.Length(); i++)
		{
			if (m_children[i] != nullptr)
				delete m_children[i];
		}
	}
}



template<typename T>
inline bool QuadTree<T>::InsertObject(TreeNode<T>* object)
{
	m_allobjects.Add(object);
	return Insert(object);
}

template<typename T>
inline bool QuadTree<T>::Insert(TreeNode<T>* object)
{
	if (m_boundry.Contains(object->boundry.center) == false)
		return false;

	if (m_children.Length() == 0)
	{
		if (m_objects.Length() < m_capacity)
		{
			m_objects.Add(object);
			return true;
		}

		Subdivide();
	}

	for (int i = 0; i < m_children.Length() ; i++)
	{
		if (m_children[i]->Insert(object) == true)
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
	//Top left
	m_children.Add(new QuadTree(AABB(qCentre, qSize)));

	qCentre = Vector2{ m_boundry.center.x + qSize.x,
	m_boundry.center.y - qSize.y };
	//Top Right
	m_children.Add(new QuadTree(AABB(qCentre, qSize)));
	
	qCentre = Vector2{ m_boundry.center.x - qSize.x,
	m_boundry.center.y + qSize.y };
	//Bottom Left
	m_children.Add(new QuadTree(AABB(qCentre, qSize)));
	
	qCentre = Vector2{ m_boundry.center.x + qSize.x,
	m_boundry.center.y + qSize.y };
	//Bottom Right
	m_children.Add(new QuadTree(AABB(qCentre, qSize)));
	if (m_objects.Length() != 0)
	{
		for (int i = 0; i < m_objects.Length(); i++)
		{
			for (int j = 0; j < m_children.Length(); j++)
			{
				if (m_children[j]->Insert(m_objects[i]) == true)
					break;
			}
			m_objects.Remove(m_objects[i]);
		}

	}

}

template<typename T>
inline void QuadTree<T>::UnSubdivide()
{
	for (int i = 0; i < m_children.Length(); i++)
	{
		if (m_children[i])
		{
			m_children[i]->m_objects.Clear();
			delete m_children[i];
		}
	}
}


template<typename T>
inline void QuadTree<T>::Update(float deltaTime)
{
	if (m_objects.Length() != 0)
	{
		for (int i = 0; i < m_objects.Length(); i++)
		{
			if (!m_boundry.Contains(m_objects[i]->boundry.center))
			{
				Insert(m_objects[i]);
				m_objects.Remove(m_objects[i]);
			}
		}
	}
	for (int i = 0; i < m_children.Length(); i++)
	{
		if (m_children[i])
		{
			m_children[i]->Update(deltaTime);
		}
	}
	if (!HasItems(m_boundry))
	{
		UnSubdivide();
	}

}

template<typename T>
inline DynamicArray<TreeNode<T>*> QuadTree<T>::Search(AABB area)
{
	DynamicArray<TreeNode<T>*> list;
	Search(area, list);
	return list;
}

template<typename T>
inline void QuadTree<T>::Search(AABB area, DynamicArray<TreeNode<T>*>& list)
{
	if (m_objects.Length() != 0)
	{
		for (int i = 0; i < m_objects.Length(); i++)
		{
			if(area.Overlap(m_objects[i]->boundry))
				list.Add(m_objects[i]);
		}

	}

	if (m_children.Length() != 0)
	{
		for (int i = 0; i < m_children.Length(); i++)
		{
			if (m_children[i])
			{
				if(area.Contains(m_children[i]->m_boundry.center))
					m_children[i]->Items(list);

				else if(m_children[i]->m_boundry.Overlap(area))
					m_children[i]->Search(area,list);
			}
		}
	}
}

template<typename T>
inline bool QuadTree<T>::HasItems(AABB area)
{
	DynamicArray<TreeNode<T>*> list = Search(area);

	if (list.Length() != 0)
	{
		return true;
	}
	else
	{
		return false;
	}

	
}

template<typename T>
inline void QuadTree<T>::Items(DynamicArray<TreeNode<T>*>& list)
{
	for (int i = 0; i < m_objects.Length(); i++)
	{
		list.Add(m_objects[i]);
	}
	for (int i = 0; i < m_children.Length(); i++)
	{
		if (m_children[i])
			m_children[i]->Items(list);
	}
}

template<typename T>
inline bool QuadTree<T>::Remove(TreeNode<T>* object)
{
	if (m_objects.getLength() != 0)
	{
		for (int i = 0; i < m_objects.Length(); i++)
		{
			if (m_objects[i] == object)
			{
				m_objects.Remove(m_objects[i]);
				return true;
			}
		}
	}
	else
	{
		if (m_children.Length() != 0)
		{
			for (int i = 0; i < m_children.Length(); i++)
			{
				if (m_children[i]->Remove(object))
					return true;
			}
		}
	}

	return false;

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

	if (m_children.Length() != 0)
	{
		for (int i = 0; i < m_children.Length(); i++)
		{
			m_children[i]->Draw();
		}
	}
}

