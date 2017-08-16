#pragma once
#include <assert.h>
#include "ElEDefines.h"
template <typename T>
class ElEVector
{
private:
	T**		arr = nullptr;
	ElEuint	size,
			currRealSize;
public:
	ElEVector();
	ElEVector(const _IN_ ElEuint& _size);
	~ElEVector();
	const T* __cdecl data();
	T __cdecl at(const _IN_ ElEuint& _index);
	void __cdecl add(_IN_ T _obj);
	void __cdecl clear();
	ElEuint __cdecl count();
	void __cdecl insert(_IN_ T* _objs, const _IN_ ElEuint& _size);
	T __cdecl pop();
	ElEbool __cdecl empty();
	void __cdecl remove(const _IN_ ElEuint& _start, const _IN_ ElEuint& _end);
	void __cdecl resize(const _IN_ ElEuint& _size);
	T __cdecl operator[](const ElEuint& _index);
	ElEVector<T> __cdecl operator=(ElEVector<T>& cpy);
};

template<typename T>
inline ElEVector<T>::ElEVector()
{
	arr = new T*[16];
	size = 0;
	currRealSize = 16;
}

template<typename T>
inline ElEVector<T>::ElEVector(const _IN_ ElEuint & _size)
{
	arr = new T*[_size];
	size = 0;
	currRealSize = _size;
}
 
template<typename T>
inline ElEVector<T>::~ElEVector()
{
	for (ElEint i = 0; i < size; i++)
		delete arr[i];
	delete[] arr;
}

template<typename T>
const inline T * ElEVector<T>::data()
{
	T* retCpy = new T[size];
	for (ElEint i = 0; i < size; i++)
		retCpy[i] = this->at(i);
	return retCpy;
}

template<typename T>
inline T ElEVector<T>::at(const _IN_ ElEuint & index)
{
	assert(index < size);
	return *(arr[index]);
}

template<typename T>
inline void ElEVector<T>::add(_IN_ T obj)
{
	if (size >= currRealSize)
		this->resize(currRealSize + 16);
	(arr[size]) = new T();
	(arr[size++]) = &obj;
}

template<typename T>
inline void ElEVector<T>::clear()
{
	for (ElEint i = 0; i < size; i++)
		delete arr[i];
	delete[] arr;
	size = 0;
	arr = new T*[currRealSize];
}

template<typename T>
inline ElEuint ElEVector<T>::count()
{
	return size;
}

template<typename T>
inline void ElEVector<T>::insert(_IN_ T* _objs, const _IN_ ElEuint & _size)
{

	for (int i = 0; i < _size; ++i)
		this->add(_objs[i]);
}

template<typename T>
inline T ElEVector<T>::pop()
{
	assert(!empty());
	T ret = *(arr[size - 1]);
	delete arr[size];
	*(arr[size--]) = nullptr;
	return ret;
}

template<typename T>
inline ElEbool ElEVector<T>::empty()
{
	return (size == 0) ? ElEtrue : ElEfalse;
}

template<typename T>
inline void ElEVector<T>::remove(const _IN_ ElEuint & _start, const _IN_ ElEuint & _end)
{
	int end;
	if (_start >= size) return;
	end = (_end >= size) ? size - 1 : _end;
	for (int i = _end; i-- >= _start;)
	{
		delete arr[i];
		arr[i] = nullptr;
		--size;
	}
}

template<typename T>
inline void ElEVector<T>::resize(const _IN_ ElEuint & _size)
{
	if (size > _size)
		size = _size;
	T** copyArr = new T*[_size];
	currRealSize = _size;
	for (ElEuint i = currRealSize; i--;)
		copyArr[i] = arr[i];
	delete[] arr;
	arr = copyArr;
}

template<typename T>
inline T ElEVector<T>::operator[](const ElEuint & _index)
{
	return this->at(_index);
}

template<typename T>
inline ElEVector<T> ElEVector<T>::operator=(ElEVector<T>& cpy)
{
	this->clear();
	for (ElEuint i = cpy.count(); i--;)
		this->add(cpy.at(i));
	return *this;
}
