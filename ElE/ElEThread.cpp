#include "ElEThread.h"


void ElEThread::TesterFunc(_IN_ std::function<void()> func)
{
	active = ElEtrue;
	func();
	active = ElEfalse;
}

ElEThread::ElEThread() 
{
	t = nullptr;
	active = ElEfalse;
}


ElEThread::~ElEThread()
{
	delete t;
}

ElEThread::ElEThread(const _IN_ ElEThread & cpy) : ElEThread()
{
}

void ElEThread::StartThread(_IN_ std::function<void()> func)
{
	t = new std::thread(&ElEThread::TesterFunc,this,func);
}

void ElEThread::CloseThread()
{
	if(t->joinable())
		t->join();
	else {
#ifdef WIN32_COMPILE
		TerminateThread(t->native_handle(), 0);
#else
		pthread_cancel(t->native_handle());
#endif
	}
	active = ElEfalse;
}

void ElEThread::DetachThread()
{
	t->detach();
}

ElEThread ElEThread::operator=(const ElEThread & th)
{
	t = th.t;
	active = th.active;
	return ElEThread();
}

ElEThreadPool*	ElEThreadPool::instance;
ElEThreadPool::ElEThreadPool(const _IN_ ElEuint & amountOfThreads)
{
	threadPool = new ElEVector<ElEThread>(amountOfThreads);
	for(ElEuint i = amountOfThreads; i--;)
		threadPool->add(ElEThread());
	threadSize = amountOfThreads;
}

ElEThread * ElEThreadPool::RequestThread(_IN_ std::function<void()> func)
{
	ElEThread* ret = nullptr;
	int i = 0;
	while (ret == nullptr)
	{
		if (!threadPool->at(i)->isActive())
			ret = threadPool->at(i);
		++i %= threadSize;
	}
	ret->StartThread(func);
	return ret;
}

ElEThreadPool::~ElEThreadPool()
{
	for (ElEuint i = 0; i < threadPool->count(); ++i)
	{
		if (threadPool->at(i)->isActive())
		{
			threadPool->at(i)->CloseThread();
		}
	}
	delete threadPool;
}
