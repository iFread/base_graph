

#include "own_fl_widgets.h"
#include "point.h"

#include <Fl/fl_draw.H>

//using Graph::Shape;


fl_canvas::fl_canvas(Point p, int w,int h):Fl_Widget(p.x(),p.y(),w,h,""),w_(w),h_(h)
{

}
fl_canvas::~fl_canvas(){
   for(Shape*p: vec)
       delete p;

}

void fl_canvas::draw(){

    fl_rectf(x(),y(),w_,h_,FL_WHITE);
    for(Shape*p: vec)
        p->draw();
}


int fl_canvas::handle(int e){

    switch (e)
    {
    case FL_PUSH:
        std::cout<<"can_handle\n";
        break;
    }
    return e;
}
void fl_canvas::add(Shape* sh){
    vec.push_back(sh);
}


