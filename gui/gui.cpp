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
    window_w = 640;
    window_h = 480;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

//    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    if (!this->onResize(window_w, window_h)) {
        return false;
    }

    return defaultTheme.init();
}

void Gui::run() {
    SDL_Event event;

    while (true) {
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_VIDEORESIZE:
                    this->onResize(event.resize.w, event.resize.h);
                    break;
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

bool Gui::onResize(int w, int h) {
    window_w = w;
    window_h = h;
    SDL_Surface* screen = SDL_SetVideoMode(window_w, window_h, 16, SDL_OPENGL|SDL_RESIZABLE|SDL_DOUBLEBUF);

    if (!screen) {
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return false;
    }

    if (!this->initOpenGl(window_w, window_h)) {
		printf("Unable to initialize OpenGL: %s\n", SDL_GetError());
		return false;
    }
    
    defaultTheme.setWindowSize(w, h);

    return this->initOpenGl(w, h);
}

bool Gui::initOpenGl(int w, int h) {
    glClearColor(0, 0, 0, 0);
    glEnable(GL_TEXTURE_2D);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    return true;
}

void Gui::draw() {
    defaultTheme.startDraw();
    root->resize(window_w, window_h);
    root->accept(defaultTheme);
    SDL_GL_SwapBuffers();
}

