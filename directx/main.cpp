#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "AppWindow.h"
#include "SceneWindow.h"

int main() {

	try {
		AppWindow::initialize();
		AppWindow* app = (AppWindow*)AppWindow::getInstance();
		app->initializeEngine();
		while (app->run());
	}
	catch (...) {
		return -1;
	}

	/*SceneWindow::initialize();
	SceneWindow* scene = (SceneWindow*)SceneWindow::getInstance();
	scene->initializeEngine();

	while (scene->isRunning()) {
		scene->broadcast();
	}*/

	return 0;
}