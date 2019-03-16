#pragma once
#include "Camera.h"
#include <SDL2/SDL_events.h>
class MouseEvent
{
public:
	MouseEvent();
	virtual ~MouseEvent();
	void process(Camera *camera, SDL_Event &event);
private:
	float sensitivity;
};

