#include "pch.h"
#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent()
{
}


KeyboardEvent::~KeyboardEvent()
{
}

void KeyboardEvent::process(IEngine &engine, Camera *camera) {
	const Uint8 *state = SDL_GetKeyboardState(NULL);

		glm::vec3 forward = camera->getForward();
		glm::vec3 left = camera->getLeft();
		float speed = 0.01f * engine.getFrameTime() / 1000000.0f;	
		if (state[SDL_SCANCODE_ESCAPE])
			engine.stop();

		if (state[SDL_SCANCODE_UP])
			camera->addPos(forward.x * speed, 0.f, forward.z * speed);

		if (state[SDL_SCANCODE_LEFT])
			camera->addPos(left.x * speed, 0.f, left.z * speed);

		if (state[SDL_SCANCODE_DOWN])
			camera->addPos(forward.x * -speed, 0.f, forward.z * -speed);

		if (state[SDL_SCANCODE_RIGHT])
			camera->addPos(left.x * -speed, 0.f, left.z * -speed);

		if (state[SDL_SCANCODE_SPACE])
			camera->addPos(0.f, speed, 0.f);

		if (state[SDL_SCANCODE_LCTRL])
			camera->addPos(0.f, -speed, 0.f);
	
}