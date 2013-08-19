#ifndef THEME_H
#define THEME_H

#include "widget_visitor.h"

class Theme : public WidgetVisitor {
    public:
        virtual void visitButton(Button* btn);
};

#endif

