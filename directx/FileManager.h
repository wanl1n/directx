#pragma once
#include <fstream>
#include <iostream>

#include "Math.h"
#include "Constants.h"

class FileManager
{
	private:
		struct Object {
			std::string name;
			std::string type;
			bool active;
			Math::Vector3 position;
			Math::Vector3 scale;
			Math::Vector3 rotation;
			std::string physics;
			std::string physicsType;
		};

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
		void saveLevel(std::string filename);
		void loadLevel(std::string filename);
		void createGameObjectsFromFile(std::vector<Object> objects);

	private:
		bool contains(std::string str, std::string substr);
		Math::Vector3 readVector3(std::string csfloat3);
		OBJECT_TYPE stringToObjType(std::string type);
};

