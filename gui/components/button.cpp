#include "button.h"
#include "../widget_visitor.h"

void Button::setLabel(std::string label) {
    this->label = label;
}

std::string Button::getLabel() {
    return this->label;
}

void Button::accept(WidgetVisitor& visitor) {
    visitor.visitButton(this);
}
