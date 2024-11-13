#include "Singleton.h"

Singleton* Singleton::sharedInstance = nullptr;
Singleton* Singleton::getInstance()
{
	return sharedInstance;
}

void Singleton::initialize()
{
	sharedInstance = new Singleton();
	//sharedInstance->init();
}

void Singleton::destroy()
{
	delete sharedInstance;
}

Singleton::Singleton() {}
Singleton::~Singleton() {}