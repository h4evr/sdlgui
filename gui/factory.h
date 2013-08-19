#ifndef FACTORY_H
#define FACTORY_H

#include "widget.h"
#include "widget_type.h"

class Factory {
    public:
        static Widget* create(WidgetType type);
};

#endif
