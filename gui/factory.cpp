#include "factory.h"

#include "components/button.h"
#include "layout/vbox.h"

Widget* Factory::create(WidgetType type) {
    switch(type) {
        case WTYPE_BUTTON:
            return new Button();
        case WTYPE_VBOX:
            return new VBox();
    }

    return (Widget*)0;
}
