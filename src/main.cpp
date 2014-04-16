
#include <iostream>
#include <sstream>

#include "Saloon/Saloon.h"

class MyGame : public Saloon {
private:
	SaloonTexture* testure;

public:
	MyGame();
	~MyGame();

	void onCreate();
	void onRender();
	void onUpdate();
};

MyGame::MyGame()
{
	testure = NULL;
}

MyGame::~MyGame() {
	delete testure;
}

void MyGame::onCreate() {
	setClearColor(1, 0, 0);
	setVSyncEnabled();

	testure = new SaloonTexture("tiles.png");
}

void MyGame::onUpdate() {

}

void MyGame::onRender() {
	//glDrawRect(-50, -50, 50, 50);

	testure->render(0, 150);
}

int main(int argc, char **argv) {

	MyGame game;

	game.init("Testy Window", 640, 480, true,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	return game.start();
}

