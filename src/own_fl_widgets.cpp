

#include "own_fl_widgets.h"
#include "own_gui_widgets.h"
#include "point.h"
#include "group_widgets.h"


#include <Fl/fl_draw.H>

//using Graph::Shape;


fl_canvas::fl_canvas(Point p, int w,int h):Fl_Widget(p.x(),p.y(),w,h,""),w_(w),h_(h)
 {}
fl_canvas::~fl_canvas(){
   for(Shape*p: vec)
       delete p;

}

void fl_canvas::draw(){

    fl_rectf(x(),y(),w_,h_,FL_WHITE);
   // отрисовка фигуры должна происходить с учетом положения scroll()
    for(Shape*p: vec)
        p->draw(Point(x(),y()));
//  так же можно отрисовывать изменения инструментов,
   // Graph::reference_to<Graph::Canvas*>(user_data())->draw();
}


// зная что обращаемся к canvas

int fl_canvas::handle(int e){
 //Fl::focus(reinterpret_cast<Graph::Canvas*>(user_data()));
    switch (e)
    {
    case FL_PUSH:
 //std::cout<<Fl::event_x()-x()<<", "<<Fl::event_y()-y()<<"\n";
        break;
    case FL_MOVE:
     reinterpret_cast <Graph::Canvas*>(user_data())->cursor_position( {(float)Fl::event_x()-x(),(float) Fl::event_y()-y()});
     break;
    }
   //
  // do_callback(this,e);

   if(e)
   { reinterpret_cast<Graph::Canvas*>(user_data())->handle(e); // user_data = tool*
    //redraw();
    //   return 0;
   }
   return e;
}
void fl_canvas::add(Shape* sh){
    vec.push_back(sh);
}

void fl_canvas::remove(Shape*sh){

    for(size_t i=0;i<vec.size();++i)
 {
   if(sh==vec[i])
     {
      delete *vec.erase(vec.begin()+i);
       break;
      }
 }
}


