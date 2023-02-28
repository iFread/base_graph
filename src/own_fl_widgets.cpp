

#include "own_fl_widgets.h"
#include "own_gui_widgets.h"
#include "point.h"
#include "group_widgets.h"


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
   // отрисовка фигуры должна происходить с учетом положения scroll()
std::cout<<"fl_canvas_x = "<<x()<<" fl_canvas_y "<<y()<<"\n";
    for(Shape*p: vec)
              p->draw();
//  так же можно отрисовывать изменения инструментов,
   // Graph::reference_to<Graph::Canvas*>(user_data())->draw();
}


// зная что обращаемся к canvas

int fl_canvas::handle(int e){

    switch (e)
    {
    case FL_PUSH:

 std::cout<<Fl::event_x()-x()<<", "<<Fl::event_y()-y()<<"\n";
        break;
    case FL_MOVE:
     reinterpret_cast <Graph::Canvas*>(user_data())->cursor_position( {(float)Fl::event_x()-x(),(float) Fl::event_y()-y()});
     break;
    }
   //
  // do_callback(this,e);
   if(e)
   { reinterpret_cast<Graph::Canvas*>(user_data())->handle(e); // user_data = tool*
 redraw();
 return 1;
   }
   return 0;
}
void fl_canvas::add(Shape* sh){
    vec.push_back(sh);
}


