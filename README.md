# OpenGL GUI Engine

## Description

Theme-able GUI engine that runs on top of OpenGL.

## Technicalities

Interface representation based on a "Widget" class. Specific widgets must extend this base class.
Widget properties:

  * position (X, Y) 
  * size (width, height) 
  * visible 
  * z-index  
  * parent
  * dirty
  * children, sorted by z-index (use a SortedSet) 

Examples: Window, button, progress bar, slider, input text, check box, radio box, combo box, scroll bar

To render the widgets, a "Theme" class is used. This class implements the necessary methods to draw each type of widget. It also implements the visitor pattern to check each widget. For each visible widget, it'll invoke the necessary method to actually draw the widget. New themes must extend this class, since it will also contain the logic for calculating the layout of the interface.

To organize the widgets in the screen, layout widgets must be used. The layouts will adjust the position and size of their children according with their intended behavior and avaliable area. Examples: hbox, vbox, fill, card, column, etc.

Rendering must be optimized. Using OpenGL to gain hardware acceleration, together with the smallest amount of textures possible, it is expected that rendering will be fast. But pruning can be used to optimize the rendering. Hidden widgets and their children will be skipped. Sibling widgets will be checked for total occlusion, comparing their size, position and z-index.
Widgets also have a "dirty" which indicates if any change as occurred that impacts rendering. After each render, this flag is reset to false.

Also, a busy main loop must be avoided. The interface must be redraw only when
something has changed, in response to an action by the user or because of a
force refresh by a widget (like a timer or a animated widget).
