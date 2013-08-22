#include "gui/gui.h"
#include "gui/factory.h"
#include "gui/theme.h"
#include "version.h"

#include "gui/layout.h"
#include "gui/components.h"

int main(int argc, char* argv[]) {
    Gui gui;
    if (!gui.init()) {
        return 1;
    }

    VBox* root = (VBox*)Factory::create(WTYPE_VBOX);

    Button* btn1 = (Button*)Factory::create(WTYPE_BUTTON);
    btn1->setLabel(std::string("Button 1"));
    root->addChild(btn1, 1);

    Button* btn2 = (Button*)Factory::create(WTYPE_BUTTON);
    btn2->setLabel(std::string("Button 2"));
    root->addChild(btn2, 2);

    Button* btn3 = (Button*)Factory::create(WTYPE_BUTTON);
    btn3->setLabel(std::string("Button 3"));
    root->addChild(btn3, 3);

    gui.setRoot(root);
    gui.run();
    gui.destroy();

    return 0;
}
