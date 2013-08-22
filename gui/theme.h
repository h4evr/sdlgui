#ifndef THEME_H
#define THEME_H

#include "widget_visitor.h"

class Theme : public WidgetVisitor {
    public:
        ~Theme();

        virtual void setWindowSize(int w, int h);

        virtual bool init();
        virtual void startDraw();

        virtual void visitButton(Button* btn);
    private:
        int window_w;
        int window_h;
};

#endif

