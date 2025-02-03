#pragma once


template<typename T1, typename T2>
class Pair
{
public:
	Pair<T1,T2>();
	Pair<T1,T2>(T1 key, T2 value);
	~Pair() = default;

public:
	T1 key;
	T2 value;
};

template<typename T1, typename T2>
inline Pair<T1, T2>::Pair() : key(nullptr), value(nullptr)
{
}

template<typename T1, typename T2>
inline Pair<T1, T2>::Pair(T1 key, T2 value) : key(key), value(value)
{
}
