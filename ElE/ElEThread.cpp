#include "ElEThread.h"



void ElEThread::TesterFunc(_IN_ void * func())
{
	active = ElEtrue;
	func();
	active = ElEfalse;
}

ElEThread::ElEThread()
{
	active = ElEfalse;
}


ElEThread::~ElEThread()
{
}

void ElEThread::StartThread(_IN_ void *func())
{
	t = std::thread(&ElEThread::TesterFunc,this,func);
}

void ElEThread::CloseThread()
{
	if(t.joinable())
		t.join();
	else {
#ifdef WIN32_COMPILE
		TerminateThread(t.native_handle(), 0);
#else
		pthread_cancel(t.native_handle());
#endif
	}
	active = ElEfalse;
}

void ElEThread::DetachThread()
{
	t.detach();
}

ElEThreadPool::ElEThreadPool(const _IN_ ElEuint & amountOfThreads)
{
	threadPool = new ElEVector<ElEThread>(amountOfThreads);
	threadSize = amountOfThreads;
}

ElEThread * ElEThreadPool::RequestThread(_IN_ void *func())
{
	ElEThread* ret = nullptr;
	int i = 0;
	while (ret == nullptr)
	{
		if (!threadPool->at(i)->isActive())
			ret = threadPool->at(i);
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
