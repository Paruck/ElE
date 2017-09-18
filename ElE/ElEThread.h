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
	void ElEcall TesterFunc(_IN_ std::function<void()> func);
public:
	ElEThread();
	~ElEThread();
	ElEThread(const _IN_ ElEThread& cpy);
	void ElEcall StartThread(_IN_ std::function<void()> func);
	inline ElEbool ElEcall isActive() { return active; }
	void ElEcall CloseThread();
	void ElEcall DetachThread();
	ElEbool ElEcall isJoinable() { return t->joinable() ? ElEtrue : ElEfalse; }
	ElEThread operator =(const ElEThread& th);
};

class ElEThreadPool {
private:
    std::vector<ElEThread>*	threadPool = nullptr;
	ElEuint					    threadSize;
	static ElEThreadPool*	    instance;
public:
	ElEThread* ElEcall RequestThread(_IN_ std::function<void()> func);
	inline static ElEThreadPool* ElEcall getInstance()
		{ return instance == nullptr ? instance = nullptr : instance; }
	inline static ElEThreadPool* ElEcall getInstance(const _IN_ ElEuint& thread)
		{ return instance == nullptr ? instance = new ElEThreadPool(thread) : instance; }
	ElEThreadPool() = delete;
	~ElEThreadPool();
private:
	ElEThreadPool(const _IN_ ElEuint& amountOfThreads);
};

