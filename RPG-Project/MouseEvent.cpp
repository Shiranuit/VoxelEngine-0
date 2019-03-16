#include "pch.h"
#include "MouseEvent.h"
#include <iostream>


MouseEvent::MouseEvent()
{
	sensitivity = 0.05f;
}


MouseEvent::~MouseEvent()
{
}

void MouseEvent::process(Camera *camera, SDL_Event &event)
{
	if (event.type == SDL_MOUSEMOTION) {
		float xoffset = event.motion.xrel * sensitivity;
		float yoffset = -event.motion.yrel * sensitivity;

		camera->addRot(xoffset, yoffset);
		//std::cout << "Yaw: " << camera->getYaw() << " Pitch: " << camera->getPitch() << std::endl;
	}
}