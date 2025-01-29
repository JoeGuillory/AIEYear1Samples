#pragma once

template<typename T, typename J>
class Map
{
public:

	Map();
	~Map();



private:

};

//Functions for Map
template<typename T, typename J>
inline Map<T, J>::Map()
{
	m_pairArray = new Pair * [m_length];
	
}

template<typename T, typename J>
inline Map<T, J>::~Map()
{
	delete m_pairArray;
}





