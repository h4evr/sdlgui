#ifndef BUTTON_H
#define BUTTON_H

#include "../widget.h"
#include <string>

class Button : public Widget {
    public:
        std::string getLabel();
        void setLabel(std::string label);
        virtual void accept(WidgetVisitor& visitor);
    protected:
        std::string label;
};

#endif
