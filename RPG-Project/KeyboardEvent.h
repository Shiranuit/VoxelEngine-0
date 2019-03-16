#pragma once

#include "IEngine.h"
#include "Camera.h"
#include <SDL2/SDL_events.h>

class KeyboardEvent
{
public:
	KeyboardEvent();
	virtual ~KeyboardEvent();
	void process(IEngine &engine, Camera *camera);
};

