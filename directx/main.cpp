#include "AppWindow.h"
#include "SceneWindow.h"

int main() {

	AppWindow::initialize();
	AppWindow* app = (AppWindow*)AppWindow::getInstance();
	app->initializeEngine();

	while (app->isRunning()) {
		app->broadcast();
	}

	return 0;
}