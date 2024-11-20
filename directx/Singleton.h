#pragma once

class Singleton
{
	public:
		static Singleton* getInstance();
		static void initialize();
		static void destroy();

	private:
		Singleton();
		~Singleton();
		Singleton(Singleton const&) {};
		Singleton& operator = (Singleton const&) {};
		static Singleton* sharedInstance;
};

