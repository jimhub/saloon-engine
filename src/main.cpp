
#include <iostream>
#include <sstream>

#include "Saloon/Saloon.h"

class MyGame : public Saloon {
public:
	void onCreate();
	void onRender();
	void onUpdate();
};

void MyGame::onCreate() {
	setClearColor(1, 0, 0);
	setVSyncEnabled();
}

void MyGame::onUpdate() {

}

void MyGame::onRender() {
	glDrawRect(-50, -50, 50, 50);
}

int main(int argc, char **argv) {

	MyGame game;

	game.init("Testy Window", 640, 480, true,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	return game.start();
}

