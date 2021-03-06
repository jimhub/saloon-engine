
#include <iostream>
#include <sstream>

#include "Saloon/Saloon.h"
#include "Saloon/Shader.h"
#include "Saloon/Mesh.h"
#include "Saloon/Transform.h"

class MyGame : public Saloon {
private:

	Shader shader;
	Mesh mesh;
	Texture texture;
	Transform transform;

	float counter;

public:
	MyGame();
	~MyGame();

	void onCreate();
	void onRender();
	void onUpdate();
	void onDestroy();
};

MyGame::MyGame() : counter(0.0f)
{

}

MyGame::~MyGame() {

}

void MyGame::onCreate() {
	setClearColor(0.0f, 0.15f, 0.3f, 1.0f);

	shader.load("Shaders/basicShader");

	Vertex verts[] = {
			Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0)),
			Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1)),
			Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1, 0))
		};

	mesh.createFromVertices(verts, 3);

	texture.loadTexture("bricks.jpg");
}

void MyGame::onUpdate() {
	counter += 45.0f * deltaTime;
	transform.getRotation().y = counter;
}

void MyGame::onRender() {
	//
	//glDisable(GL_TEXTURE_2D);
	shader.bind();
	texture.bind();
	shader.update(transform);
	mesh.draw();
	texture.unbind();
	shader.unbind();
	//glEnable(GL_TEXTURE_2D);
}

void MyGame::onDestroy() {

}

int main(int argc, char **argv) {

	MyGame game;

	game.init("Testy Window", 640, 480, true,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	return game.start();
}

