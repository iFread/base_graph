

#include "own_fl_widgets.h"
#include "own_gui_widgets.h"
#include "point.h"
#include "group_widgets.h"
#include "main_menu.h"

#include <Fl/fl_draw.H>

//using Graph::Shape;


fl_canvas::fl_canvas(Point p, int w,int h):Fl_Widget(p.x(),p.y(),w,h,""),w_(w),h_(h)
 {}
fl_canvas::~fl_canvas(){
//   for(Shape*p: vec)
//       delete p;

}
//size_t fl_canvas::count() const
//{
//    return vec.size();
//}

//Shape& fl_canvas::operator[](int i)
//{
//  i=(i<vec.size()-1?i:vec.size()-1);
//     return *vec[i];
//}

void fl_canvas::draw(){

    fl_rectf(x(),y(),w_,h_,FL_WHITE);
   // отрисовка фигуры должна происходить с учетом положения scroll()
//    for(size_t i=0;i<vec.size();++i)//Shape*p: vec)
//        vec[i]->draw(Point(x(),y()));
//  так же можно отрисовывать изменения инструментов,
   // Graph::reference_to<Graph::Canvas*>(user_data())->draw();
  static_cast<Graph::Canvas*>(user_data())->draw();
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
    case FL_DRAG:
   //  reinterpret_cast <Graph::Canvas*>(user_data())->cursor_position( {(float)Fl::event_x()-x(),(float) Fl::event_y()-y()});
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

fl_empty::fl_empty(Point p,int w,int h):Fl_Widget(p.x(),p.y(),w,h){user_data(nullptr);}

void fl_empty::draw()
{

  if(user_data())
    reinterpret_cast<Graph::menu_bar*>(user_data())->draw();   // к чему cast
}

int fl_empty::handle(int ev)
{
  if(user_data())
      return static_cast<Graph::menu_bar*>(user_data())->handle(ev);   // к чему cast
  return ev;
}

//void fl_canvas::add(Shape* sh){
//    vec.push_back(sh);
//}

//void fl_canvas::remove(Shape*sh){

//    for(size_t i=0;i<vec.size();++i)
// {
//   if(sh==vec[i])
//     {
//        *vec.erase(vec.begin()+i);
//       delete sh;
//       break;
//      }
// }
//}


