#include "widget.h"
#include "widget_visitor.h"

Widget::Widget() {
    this->x = 0;
    this->y = 0;
    this->z_index = 0;
    this->width = 1;
    this->height = 1;
}

Widget::~Widget() {
    set<Widget*>::iterator it = this->children.begin();
    for(; it != this->children.end(); ++it) {
        delete *it;
    }
    this->children.clear();
}

int Widget::getX() {
    return this->x;
}

int Widget::getY() {
    return this->y;
}

int Widget::getZ() {
    return this->z_index;
}

int Widget::getWidth() {
    return this->width;
}

int Widget::getHeight() {
    return this->height;
}

void Widget::move(int x, int y) {
    this->x = x;
    this->y = y;
    this->dirty = true;
}

void Widget::resize(int w, int h) {
    this->width = w;
    this->height = h;
    this->dirty = true;
}

void Widget::addChild(Widget* child) {
    child->parent = this;
    this->children.insert(child);
    this->dirty = true;
}

bool Widget::isDirty() {
    return this->dirty;
}

bool Widget::isVisible() {
    return this->visible;
}

void Widget::setVisible(bool visible) {
    this->visible = visible;
}

Widget* Widget::getParent() {
    return this->parent;
}

set<Widget*> Widget::getChildren() {
    return this->children;
}

void Widget::accept(WidgetVisitor& visitor) {
    std::set<Widget*>::iterator it = this->children.begin();
    for (; it != this->children.end(); it++) {
        (*it)->accept(visitor);
    }
    this->dirty = false;
}
