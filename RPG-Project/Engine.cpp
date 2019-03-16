#include "pch.h"
#include "Engine.h"
#include "Block.h"
#include "DataManager.h"
#include <cmath>

Engine::Engine(int width, int height, const std::string &title) : Display(width, height, title)
{
	fpsCount = 0;
	lastFramerate = 0;
	run();
}

Engine::~Engine()
{
	delete camera;
	delete world;
}

void Engine::init()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	setFPS(60);
	setTPS(20);
	unsigned int block = 0xFFFFFF;
	srand(time(0));
	world = new World(rand());
	camera = new Camera(70.f, 800.0f / 600.0f, 0.01f, 1000.0f);
	camera->addPos(128, 300, 128);
	
	//mcShader = new Shader("shaders/magiccircle/magicCircleFragment.glsl", "shaders/magiccircle/magicCircleVertex.glsl");
	Timer loading;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			world->loadChunk(i, j);
		}
	}
	std::cout << "Loading Time: " << loading.getEllapsedMicroSeconds() / 1000000.f << "s" << std::endl;
	//const char *files[] = { "assets/MC1-0", "assets/MC1-1", "assets/MC1-2" };
	//circle = new MagicCircleRenderer(files, 3, mcShader);
}

void Engine::update()
{

}

void Engine::draw()
{
	clear(0.f, 0.f, 0.f, 1.f);
	world->render(*camera);

	//mcShader->setMatrix4f("camera", camera->getProjectionMatrix());
	//circle->render();
}

void Engine::processInput()
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		mouseEvent.process(camera, e);
	}
	keyEvent.process(*this, camera);
}

void Engine::stop()
{
	close();
}

void Engine::run()
{
	this->init();
	while (!this->isClosed()) {
		processInput();
		if (updateTimer.getEllapsedMicroSeconds() > 1000000 / tps) {
			update();
			updateTimer.reset();
		}
		if (drawTimer.getEllapsedMicroSeconds() > 1000000 / fps) {
			deltaTime = frameTime.getEllapsedMicroSeconds();
			//printf("Draw Time: %fMs\n", deltaTime / 1000.0f);
			frameTime.reset();
			fpsCount += 1;
			draw();
			sync();
			drawTimer.reset();
		}
		if (fpsCounter.getEllapsedMicroSeconds() > 1000000) {
			lastFramerate = fpsCount;
			fpsCount = 0;
			fpsCounter.reset();
		}
	}	
}
