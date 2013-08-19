#include "vbox.h"

void VBox::addChild(Widget* child) {
    this->addChild(child, 1);
}

void VBox::addChild(Widget* child, int flex) {
    Widget::addChild(child);
    this->flex_store[child] = flex;
}

void VBox::calculateLayout() {
    int flex, total_flex = 0;
    Widget* child;
    int available_height = this->height;
 
    // First pass: remove fixed heights from available height.
    std::set<Widget*>::iterator it = this->children.begin();
    for (; it != this->children.end(); it++) {
        child = *it;
        flex = this->flex_store[child];

        if (flex < 0) {
            available_height -= child->getHeight();
        } else {
            total_flex += flex;
        }
    }

    if (available_height < 0) {
        available_height = 0;
    }

    if (total_flex == 0) {
        total_flex = 1;
    }

    int y = 0, h;
    int flex_unit = available_height / total_flex;

    // Second pass: place the components
    it = this->children.begin();
    for (; it != this->children.end(); it++) {
        child = *it;
        flex = this->flex_store[child];
        child->move(0, y);
        
        if (flex == 0) {
            h = child->getHeight();
        } else {
            h = flex * flex_unit;
        }

        child->resize(this->width, h);

        y += h;
    }
}

void VBox::accept(WidgetVisitor& visitor) {
    this->calculateLayout();
    Widget::accept(visitor);
}

