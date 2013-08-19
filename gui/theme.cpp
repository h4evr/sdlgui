#include "theme.h"
#include "components/button.h"

#include <iostream>

void Theme::visitButton(Button* btn) {
    std::cout << "Visiting button: " << btn->getLabel() << std::endl;
}
