#pragma once
#include "Pair.h"
#include "List.h"
template<typename T, typename J>
class Map
{
public:

	Map<T,J>();
	~Map();

	void Insert(T key, J value);
	void Insert(Pair<T, J>* pair);
	void Remove(T key);
	J Get(T key);
private:
	List<Pair<T, J>*> m_pairlist;
};

//Functions for Map
template<typename T, typename J>
inline Map<T, J>::Map()
{	
}

template<typename T, typename J>
inline Map<T, J>::~Map()
{
}

template<typename T, typename J>
inline void Map<T, J>::Insert(T key, J value)
{
	m_pairlist.pushBack(new Pair<T, J>(key, value));
}

template<typename T, typename J>
inline void Map<T, J>::Insert(Pair<T, J>* pair)
{
	m_pairlist.pushBack(pair);
}

template<typename T, typename J>
inline J Map<T, J>::Get(T key)
{
	for (auto t = m_pairlist.begin(); t != nullptr; t++)
	{
		if ((*t)->key == key)
			return (*t)->value;
	}
	return J();
}

template<typename T, typename J>
inline void Map<T, J>::Remove(T key)
{
	for (auto t = m_pairlist.begin(); t != nullptr; t++)
	{
		if (*(t).key == key)
			m_pairlist.remove(*t);
	}
}





