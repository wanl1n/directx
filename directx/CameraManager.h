#pragma once
#include <vector>
#include "Windows.h"
#include "Constants.h"
#include "Camera.h"
#include "Math.h"

class Camera;

class CameraManager
{
	public:
		static CameraManager* getInstance();
		static void initialize(RECT viewport);
		static void destroy();

	private:
		std::vector<Camera*> CameraList;

		int selectedCameraIndex = 0;

	private:
		CameraManager(RECT viewport);
		~CameraManager();
		CameraManager(CameraManager const&) {};
		CameraManager& operator = (CameraManager const&) {};
		static CameraManager* sharedInstance;

	public:
		void update();

		void addCamera(OBJECT_TYPE type, RECT viewport, int count = 1);
		void removeCamera(Camera* cam);
		
		Camera* getActiveCamera();
		Matrix4x4 getActiveCameraView();
		Matrix4x4 getActiveProjection();

		void setSelectedCameraIndex(int select);
};

