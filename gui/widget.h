#ifndef WIDGET_H
#define WIDGET_H

#include <set>

using std::set;

class WidgetVisitor;

class Widget {
    protected:
        int x;
        int y;
        int width;
        int height;
        int z_index;
        bool visible;
        bool dirty;
        Widget* parent;
        set<Widget*> children;

    public:
        Widget();
        ~Widget();
        int getX();
        int getY();
        int getWidth();
        int getHeight();
        virtual void move(int x, int y);
        virtual void resize(int w, int h);
        virtual void addChild(Widget* child);
        virtual bool isDirty();
        virtual bool isVisible();
        virtual void setVisible(bool visible);
        virtual Widget* getParent();
        virtual set<Widget*> getChildren();
        virtual void accept(WidgetVisitor& visitor);
};

#endif
