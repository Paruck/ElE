#pragma once
#include "ElEDefines.h"
#include "ElEVector.h"
#include <thread>
#include <functional>

#ifdef WIN32_COMPILE
#include <Windows.h>

#else
#include <pthread.h>
#endif

class ElEThread
{
private:
	std::thread*	t;
	ElEbool			active;
	void __cdecl TesterFunc(_IN_ std::function<void()> func);
public:
	ElEThread();
	~ElEThread();
	ElEThread(const _IN_ ElEThread& cpy);
	void __cdecl StartThread(_IN_ std::function<void()> func);
	inline ElEbool __cdecl isActive() { return active; }
	void __cdecl CloseThread();
	void __cdecl DetachThread();
	ElEbool __cdecl isJoinable() { return t->joinable() ? ElEtrue : ElEfalse; }
	ElEThread operator =(const ElEThread& th);
};

class ElEThreadPool {
private:
	ElEVector<ElEThread>*	threadPool = nullptr;
	ElEuint					threadSize;
	static ElEThreadPool*	instance;
public:
	ElEThread* __cdecl RequestThread(_IN_ std::function<void()> func);
	inline static ElEThreadPool* __cdecl getInstance()
		{ return instance == nullptr ? instance = nullptr : instance; }
	inline static ElEThreadPool* __cdecl getInstance(const _IN_ ElEuint& thread)
		{ return instance == nullptr ? instance = new ElEThreadPool(thread) : instance; }
	ElEThreadPool() = delete;
	~ElEThreadPool();
private:
	ElEThreadPool(const _IN_ ElEuint& amountOfThreads);
};

