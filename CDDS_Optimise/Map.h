#pragma once

template<typename T, typename J>
struct Pair
{
	Pair();
	Pair(T* key, J* value);
	~Pair();

	T* m_key;
	J* m_value;
};

template<typename T, typename J>
class Map
{
public:

	Map();
	~Map();

	Insert(Pair* pair);
	Remove(Pair* pair);
	



private:
	Pair** m_pairArray;
	int m_length;
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





//Funtions for Pair
template<typename T, typename J>
inline Pair<T, J>::Pair()
{

}

template<typename T, typename J>
inline Pair<T, J>::Pair(T* key, J* value)
{
	m_key = key;
	m_value = value;
}

template<typename T, typename J>
inline Pair<T, J>::~Pair()
{
	delete m_key;
	delete m_value;
}

