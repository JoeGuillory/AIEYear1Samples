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





private:
	Pair* m_pairArray;

};

//Functions for Map
template<typename T, typename J>
inline Map<T, J>::Map()
{
	m_pairArray = new 
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

