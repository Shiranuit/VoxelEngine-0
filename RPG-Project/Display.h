#include "pch.h"
#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>

class Display
{
    public:
        Display(int width, int height, const std::string &title);
        virtual ~Display();

		void close();
        bool isClosed();
        void sync();
        void clear(float r, float g, float b, float a);
        void event();


    protected:

    private:
        SDL_Window *m_window;
        SDL_GLContext m_glContext;
        bool m_isClosed;
};

#endif // DISPLAY_H
