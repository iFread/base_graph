#include "base_gui.h"
#include "own_fl_widgets.h"
namespace Graph
{

class Canvas:public Widget  //
{
public:
    Canvas(Point p,int w,int h):Widget(p,w,h){}
 Widget& create();
 void create(Point p,int w,int h);
// ~Canvas() {}
Fl_Widget& content();

void add(Shape*);
void remove(Shape*);


};






}

