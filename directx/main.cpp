
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

	return 0;
}