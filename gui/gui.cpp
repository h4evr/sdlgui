#include "gui.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include "widget.h"

void Gui::setRoot(Widget* root) {
    this->root = root;
}

Widget* Gui::getRoot() {
    return this->root;
}

Theme& Gui::getTheme() {
    return this->defaultTheme;
}

bool Gui::init() {
    int w = 640,
        h = 480;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_Surface* screen = SDL_SetVideoMode(w, h, 16, SDL_OPENGL);

    if (!screen) {
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return false;
    }

    if (!this->initOpenGl(w, h)) {
		printf("Unable to initialize OpenGL: %s\n", SDL_GetError());
		return false;
    }

    return true;
}

void Gui::run() {
    SDL_Event event;

    while (true) {
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    return;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        return;
                    }
                    break;
            }

            this->draw();
        }

        SDL_Delay(1);
    }
}

void Gui::destroy() {
    SDL_Quit();
}

bool Gui::initOpenGl(int w, int h) {
    glClearColor(0, 0, 0, 0);
    glEnable(GL_TEXTURE_2D);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    return true;
}

void Gui::draw() {
    root->accept(defaultTheme);
    SDL_GL_SwapBuffers();
}

