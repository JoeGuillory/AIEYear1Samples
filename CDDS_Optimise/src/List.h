#pragma once
#include "Node.h"
#include "Iterator.h"
#include <initializer_list>
template<typename T>
class List
{
public:
	List<T>();
	List<T>(std::initializer_list<T> list);
	~List<T>();

	List<T>& operator=(const List<T> other);
	const bool operator==(const List<T> other);
	const bool operator!=(const List<T> other);

	void pushFront(const T& value);
	void pushBack(const T& value);
	T popFront();
	T popBack();
	bool insert(const T& value, int index);
	bool remove(const T& value);
	T first() const;
	T last() const;
	Iterator<T> begin() const;
	Iterator<T> end() const;
	void destroy();
	int getLength() const;





private:
	Node<T>* m_head;
	Node<T>* m_tail;
	int m_length;
};

template<typename T>
inline List<T>::List() : m_head(nullptr), m_tail(nullptr), m_length(0)
{
}

template<typename T>
inline List<T>::List(std::initializer_list<T> list) : m_length(0), m_head(nullptr), m_tail(nullptr)
{
	if (list.size() == 0)
		return;
	for (T item : list)
	{
		pushBack(item);
	}
}

template<typename T>
inline List<T>::~List()
{
	destroy();
	delete m_head;
	m_head = nullptr;
	delete m_tail;
	m_tail = nullptr;
}

template<typename T>
inline List<T>& List<T>::operator=(const List<T> other)
{

	destroy();

	for (auto t = other.begin(); t != other.end(); t++)
	{
		auto value = *t;
		pushBack(value);

	}
	auto value = other.last();
	pushBack(value);
	
	return *this;
}

template<typename T>
inline const bool List<T>::operator==(const List<T> other)
{
	if (m_length != other.getLength())
		return false;


	Iterator<T> iter;
	Iterator<T> iter2;
	iter = begin();
	iter2 = other.begin();

	while (iter != nullptr)
	{
		if (*iter != *iter2)
			return false;
		iter++;
		iter2++;
	}
	return true;
}

template<typename T>
inline const bool List<T>::operator!=(const List<T> other)
{

	if (m_length != other.getLength())
		return true;
	if (m_head != other.m_head)
		return true;
	if (m_tail != other.m_tail)
		return true;

	Iterator<T> iter;
	Iterator<T> iter2;
	iter = begin();
	iter2 = other.begin();
	iter++;
	iter2++;
	while (iter != m_tail)
	{
		if (*iter != *iter2)
			return true;
		iter++;
		iter2++;
	}

	return true;
}

template<typename T>
inline void List<T>::pushFront(const T& value)
{
	Node<T>* newNode = new Node<T>(value);
	m_length++;
	
	if (!m_tail)
	{
		m_head = newNode;
		m_tail = newNode;
		return;
	}

	m_head->previous = newNode;
	newNode->next = m_head;
	m_head = newNode;

}

template<typename T>
inline void List<T>::pushBack(const T& value)
{
	Node<T>* newNode = new Node<T>(value);
	m_length++;
	if (!m_tail)
	{
		m_head = newNode;
		m_tail = newNode;
		return;
	}

	m_tail->next = newNode;
	newNode->previous = m_tail;
	m_tail = newNode;
}

template<typename T>
inline T List<T>::popFront()
{
	if (!m_tail)
		return T();
	
	T value = m_head->value;


	if (!m_head->next)
	{
		delete m_head;
		m_head = nullptr;
		m_tail = nullptr;
		m_length = 0;
	}
	else
	{
		m_head = m_head->next;
		delete m_head->previous;
		m_head->previous = nullptr;
		m_length--;
	}
	return value;
}

template<typename T>
inline T List<T>::popBack()
{
	if (!m_tail)
		return T();

	T value = m_tail->value;


	if (!m_tail->previous)
	{
		delete m_tail;
		m_tail = nullptr;
		m_head = nullptr;
		m_length = 0;
	}
	else
	{
		m_tail = m_tail->previous;
		delete m_tail->next;
		m_tail->next = nullptr;
		m_length--;
	}
	return value;
}

template<typename T>
inline bool List<T>::insert(const T& value, int index)
{
	if (index < 0 || index > m_length)
		return false;

	if (!m_tail || index == 0)
	{
		pushFront(value);
		return true;
	}
	
	if (index == m_length-1)
	{
		pushBack(value);
		return true;
	}

	Node<T>* node = m_head;
	for (int i = 0; i < index + 1; i++)
	{
		if (node->next == nullptr)
			return false;
		node = node->next;
	}
	Node<T>* newNode = new Node<T>(value);
	newNode->previous = node->previous;
	newNode->next = node;
	node->previous = newNode;
	newNode->previous->next = newNode;
	m_length++;
	return true;

}

template<typename T>
inline bool List<T>::remove(const T& value)
{
	if (!m_tail)
		return false;

	if (m_head->value == value)
	{
		popFront();
		return true;
	}

	if (!m_head->next)
		return false;

	if (m_tail->value == value)
	{
		popBack();
		return true;
	}


	Node<T>* node = m_head->next;
	while (node != m_tail)
	{
		if (node->value == value)
		{
			node->previous->next = node->next;
			node->next->previous = node->previous;
			m_length--;
			delete node;
			node = nullptr;
			return true;
		}
		node = node->next;
	}
	return false;

}

template<typename T>
inline T List<T>::first() const
{
	if (!m_head)
	{
		return T();
	}
	return m_head->value;
}

template<typename T>
inline T List<T>::last() const
{
	if (!m_tail)
		return T();
	return m_tail->value;
}

template<typename T>
inline Iterator<T> List<T>::begin() const
{
	if(!m_head)
		return Iterator<T>();
	return Iterator<T>(m_head);
}

template<typename T>
inline Iterator<T> List<T>::end() const
{
	if(!m_tail)
		return Iterator<T>();
	return Iterator<T>(m_tail);
}

template<typename T>
inline void List<T>::destroy()
{
	if (!m_tail)
		return;

	for (int i = 0; i < m_length; i++)
	{
		popBack();
	}

	m_head = nullptr;
	m_tail = nullptr;
	m_length = 0;
}

template<typename T>
inline int List<T>::getLength() const
{
	return m_length;
}
