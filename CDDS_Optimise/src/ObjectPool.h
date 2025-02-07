#pragma once
#include "List.h"

template <typename T>
class ObjectPool
{
public:
	ObjectPool(unsigned int size);
	~ObjectPool() = default;

	int CountActive();
	int CountInactive();
	int CountAll();

	void Clear();
	T* Get();
	List<T*> GetActive();
	void Release(T* value);


private:
	List<T*> m_inactive;
	List<T*> m_active;

};

template<typename T>
inline ObjectPool<T>::ObjectPool(unsigned int size)
{
	for (int i = 0; i < size; i++)
		m_inactive.pushBack(new T());

}

template<typename T>
inline int ObjectPool<T>::CountActive()
{
	return m_active.getLength();
}

template<typename T>
inline int ObjectPool<T>::CountInactive()
{
	return m_inactive.getLength();
}

template<typename T>
inline int ObjectPool<T>::CountAll()
{
	return m_active.getLength() + m_inactive.getLength();
}

template<typename T>
inline void ObjectPool<T>::Clear()
{
	m_active.destroy();
	m_inactive.destroy();

}

template<typename T>
inline T* ObjectPool<T>::Get()
{
	if (m_inactive.getLength() == 0)
		m_inactive.pushBack(new T());

	m_active.pushBack(m_inactive.first());
	m_inactive.popFront();

	return m_active.last();
}

template<typename T>
inline List<T*> ObjectPool<T>::GetActive()
{
	return m_active;
}

template<typename T>
inline void ObjectPool<T>::Release(T* value)
{
	m_inactive.pushBack(value);
	m_active.remove(value);

}
