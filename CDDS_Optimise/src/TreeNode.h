#pragma once
#include "AABB.h"

template<typename T>
class TreeNode
{
public:
	TreeNode<T>();
	TreeNode<T>(T value, AABB box);
	~TreeNode<T>() = default;
	
	T value;
	AABB boundry;
};


template<typename T>
inline TreeNode<T>::TreeNode() : value(nullptr), boundry(nullptr)
{
}

template<typename T>
inline TreeNode<T>::TreeNode(T value, AABB box) : value(value), boundry(box)
{
}
