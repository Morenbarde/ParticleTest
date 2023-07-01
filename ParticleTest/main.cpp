#include "Renderer.h"

int main() {
	Renderer screen;

	while (screen.isRunning()) {
		screen.update();
		screen.render();
	}
	return 0;
}