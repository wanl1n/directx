#pragma once
#include <fstream>
#include <iostream>

class FileManager
{
	public:
		static FileManager* getInstance();
		static void initialize();
		static void destroy();

	private:
		FileManager();
		~FileManager();
		FileManager(FileManager const&) {};
		FileManager& operator = (FileManager const&) {};
		static FileManager* sharedInstance;
		
	public:
		void saveLevel();
};

