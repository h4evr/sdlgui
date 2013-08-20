#ifndef GUI_H
#define GUI_H

#include "theme.h"

class Widget;

class Gui {
    public:
        bool init();
        void setRoot(Widget* root);
        Widget* getRoot();
        void run();
        void destroy();
        Theme& getTheme();
    private:
        bool initOpenGl(int w, int h);
        void draw();

        Widget* root;
        Theme defaultTheme;
};

#endif
