#include "AppWindow.h"
#include "SceneWindow.h"
#include "InspectorWindow.h"

int main() {

	SceneWindow::initialize();
	SceneWindow* app = (SceneWindow*)SceneWindow::getInstance();
	app->initializeEngine();

	while (app->isRunning()) {
		app->broadcast();
	}

	return 0;
}