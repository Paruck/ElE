#pragma once
#include "ElEDefines.h"
#include "ElEVector.h"
#include <thread>

#ifdef WIN32_COMPILE
#include <Windows.h>

#else
#include <pthread.h>
#endif

class ElEThread
{
private:
	std::thread t;
	ElEbool		active;
	void __cdecl TesterFunc(_IN_ void *func());
public:
	ElEThread();
	~ElEThread();
	void __cdecl StartThread(_IN_ void *func());
	inline ElEbool __cdecl isActive() { return active; }
	void __cdecl CloseThread();
	void __cdecl DetachThread();
	ElEbool __cdecl isJoinable() { return t.joinable() ? ElEtrue : ElEfalse; }
};

class ElEThreadPool {
private:
	ElEVector<ElEThread>*	threadPool = nullptr;
	ElEuint					threadSize;
public:
	ElEThreadPool(const _IN_ ElEuint& amountOfThreads);
	ElEThread* __cdecl RequestThread(_IN_ void *func());
	ElEThreadPool() = delete;
	~ElEThreadPool();
};

