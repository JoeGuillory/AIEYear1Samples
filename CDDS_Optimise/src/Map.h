#pragma once
#include "Pair.h"
#include "List.h"
template<typename T, typename J>
class Map
{
public:

	Map<T,J>();
	~Map();



private:
	List<Pair<T, J>> m_pairlist;
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





