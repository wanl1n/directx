#include "AppWindow.h"
#include "SceneWindow.h"

int main() {

	AppWindow::initialize();
	AppWindow* app = (AppWindow*)AppWindow::getInstance();
	app->initializeEngine();

	while (app->isRunning()) {
		app->broadcast();
	}

	/*SceneWindow::initialize();
	SceneWindow* scene = (SceneWindow*)SceneWindow::getInstance();
	scene->initializeEngine();

	while (scene->isRunning()) {
		scene->broadcast();
	}*/

	return 0;
}