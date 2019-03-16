#pragma once
class IEngine
{
public:
	IEngine();
	virtual ~IEngine();
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void run() = 0;
	virtual void setTPS(unsigned int tps) = 0;
	virtual void setFPS(unsigned int fps) = 0;
	virtual unsigned int getTPS() = 0;
	virtual unsigned int getFPS() = 0;
	virtual void processInput() = 0;
	virtual void stop() = 0;
	virtual long long getFrameTime() = 0;
};

