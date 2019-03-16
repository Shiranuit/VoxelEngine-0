#ifndef ENGINE_H
#define ENGINE_H

#include "Display.h"
#include "Timer.h"
#include "IEngine.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "Chunk.h"
#include "Shader.h"
#include "MagicCircleRenderer.h"
#include "World.h"

class Engine : public Display, public IEngine
{
public:
	Engine(int width, int height, const std::string &title);
	virtual ~Engine();
	void init();
	void update();
	void draw();
	void run();
	void setTPS(unsigned int tps) { this->tps = tps; };
	void setFPS(unsigned int fps) { this->fps = fps; };
	unsigned int getTPS() { return this->tps; };
	unsigned int getFPS() { return this->fps; };
	void processInput();
	void stop();
	unsigned int getRealFPS() { return this->lastFramerate; };
	long long getFrameTime() { return this->deltaTime; };
	
private:
	Timer updateTimer;
	Timer drawTimer;
	Timer fpsCounter;
	Timer frameTime;

	MouseEvent mouseEvent;
	KeyboardEvent keyEvent;

	long long deltaTime;
	unsigned int tps;
	unsigned int fps;
	unsigned int fpsCount;
	unsigned int lastFramerate;

	Camera *camera;
	Shader *mcShader;
	World *world;
	MagicCircleRenderer *circle;
};
#endif