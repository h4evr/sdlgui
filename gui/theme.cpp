#include "theme.h"
#include "components/button.h"
#include "default_theme.h"

#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>

#include <FTGL/ftgl.h>

SDL_Surface* surface;
GLuint texture;

FTGLTextureFont* font;

Theme::~Theme() {
    if (surface) {
        glDeleteTextures(1, &texture);
        SDL_FreeSurface(surface);
        surface = (SDL_Surface*)0;
    }

    if (font) {
        delete font;
        font = (FTGLTextureFont*)0;
    }
}

bool Theme::init() {
    GLenum texture_format;
    GLint nOfColors;

    if ((surface = SDL_LoadBMP("skin.bmp"))) {
        if ( (surface->w & (surface->w - 1)) != 0 ) {
            printf("Warning: texture width is not a power of 2\n");
        }

        if ( (surface->h & (surface->h - 1)) != 0 ) {
            printf("Warning: texture height is not a power of 2\n");
        }

        nOfColors = surface->format->BytesPerPixel;
        if (nOfColors == 4) {
            if (surface->format->Rmask == 0x000000ff) {
                texture_format = GL_RGBA;
            } else {
                texture_format = GL_BGRA;
            }
        } else if (nOfColors == 3) {
            if (surface->format->Rmask == 0x000000ff) {
                texture_format = GL_RGB;
            } else {
                texture_format = GL_BGR;
            }
        } else {
            printf("warning: texture is not truecolor.. kabom!\n");
            return false;
        }

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h,
                0, texture_format, GL_UNSIGNED_BYTE, surface->pixels);

    } else {
        printf("SDL could not load skin.bmp: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    font = new FTGLTextureFont("/usr/share/fonts/TTF/FreeMono.ttf");
    if (font->Error()) {
        printf("Error loading font\n");
        return false;
    }

    return true;
}

void Theme::setWindowSize(int w, int h) {
    this->window_w = w;
    this->window_h = h;
}

void Theme::startDraw() {
}

void Theme::visitButton(Button* btn) {
    int zIndex = btn->getZ();

    glPushMatrix();
        glTranslatef((float)btn->getX(), (float)window_h - (float)btn->getY(), 0.0f);
        glBindTexture(GL_TEXTURE_2D, texture);
        glColor3f(1.f, 1.f, 1.f);
        glBegin(GL_QUADS);
            glTexCoord2f(BUTTON_X1, BUTTON_Y1);
            glVertex3i(0, 0, zIndex);
            
            glTexCoord2f(BUTTON_X2, BUTTON_Y2);
            glVertex3i(btn->getWidth(), 0, zIndex);

            glTexCoord2f(BUTTON_X3, BUTTON_Y3);
            glVertex3i(btn->getWidth(), -btn->getHeight(), zIndex);
            
            glTexCoord2f(BUTTON_X4, BUTTON_Y4);
            glVertex3i(0, -btn->getHeight(), zIndex);
        glEnd();

        // Render label
        font->FaceSize(12);
        FTBBox box = font->BBox(btn->getLabel().c_str());

        glTranslatef(btn->getWidth() / 2.0f - (box.Upper() - box.Lower()).X() / 2.0f, -btn->getHeight() / 2.0f, 0.0f);
        glColor3f(0.f, 0.f, 0.f);
        font->Render(btn->getLabel().c_str());
    glPopMatrix();

}
