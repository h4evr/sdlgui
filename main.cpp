#include "gui/gui.h"
#include "gui/factory.h"
#include "gui/theme.h"
#include "version.h"

#include "gui/layout.h"
#include "gui/components.h"

int main(int argc, char* argv[]) {
    Gui gui;
    gui.init();

    VBox* root = (VBox*)Factory::create(WTYPE_VBOX);
    root->resize(320, 240);

    Button* btn1 = (Button*)Factory::create(WTYPE_BUTTON);
    btn1->setLabel(std::string("Button 1"));
    root->addChild(btn1);

    Button* btn2 = (Button*)Factory::create(WTYPE_BUTTON);
    btn2->setLabel(std::string("Button 2"));
    root->addChild(btn2);

    Theme defaultTheme;
    root->accept(defaultTheme);

    return 0;
}
