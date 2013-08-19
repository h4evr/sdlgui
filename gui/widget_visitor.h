#ifndef WIDGET_VISITOR_H
#define WIDGET_VISITOR_H

#include "widget.h"

class Button;

class WidgetVisitor {
    public:
        virtual void visitButton(Button* button) = 0;
        // TODO Add visits to specific widget types.
};

#endif
