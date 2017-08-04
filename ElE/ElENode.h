#pragma once
#include "ElEDefines.h"

template <typename T>
class ElENode {
public:
	ElENode();
	ElENode(_IN_ T& obj);
	ElENode(_IN_ ElENode& obj);
	~ElENode();
	T element;
	ElENode* next = nullptr;
private:
};

template<typename T>
inline ElENode<T>::ElENode()
{
}

template<typename T>
inline ElENode<T>::ElENode(_IN_ T& obj)
{
	element = obj;
}

template<typename T>
inline ElENode<T>::ElENode(_IN_ ElENode & obj)
{
	element = obj.element;
	next = obj.next;
}

template<typename T>
inline ElENode<T>::~ElENode()
{
}
