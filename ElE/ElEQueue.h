#pragma once
#include "ElENode.h"
#include "ElEDefines.h"

template <typename T>
class ElEQueue
{
public:
	ElEQueue();
	~ElEQueue();
	void ElEcall Add(_IN_ T elem);
	T ElEcall Pop();
	T ElEcall Peek();
	void ElEcall Clear();
	inline ElEbool ElEcall Empty() { return phead == nullptr ? ElEtrue : ElEfalse; }
private:
	ElENode<T>	*phead = nullptr,
				*ptail = nullptr;
};

template<typename T>
inline ElEQueue<T>::ElEQueue()
{
}

template<typename T>
inline ElEQueue<T>::~ElEQueue()
{
	Clear();
}

template<typename T>
inline void ElEQueue<T>::Add(_IN_ T elem)
{
	if (phead == nullptr)
	{
		phead = ptail = &elem;
		return;
	}
	ptail->next = elem;
	ptail = ptail->next;
}

template<typename T>
inline T ElEQueue<T>::Pop()
{
	T ret = phead->element;
	ElENode<T> *del = phead;
	phead = phead->next;
	delete del;
	return ret;
}

template<typename T>
inline T ElEQueue<T>::Peek()
{
	return phead->element;
}

template<typename T>
inline void ElEQueue<T>::Clear()
{
	ElENode<T> *ref = nullptr;
	while (phead)
	{
		ref = phead->next;
		delete phead;
		phead = ref;
	}
}
