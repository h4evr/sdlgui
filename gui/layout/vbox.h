#ifndef VBOX_H
#define VBOX_H

#include "../widget.h"
#include <map>

class VBox : public Widget {
    public:
        virtual void addChild(Widget* child);
        virtual void addChild(Widget* child, int flex);
        virtual void accept(WidgetVisitor& visitor);
    protected:
        std::map<Widget*, int> flex_store;
        virtual void calculateLayout();
};

#endif
