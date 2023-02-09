#include "window.h"
#include "base_graph.h"
namespace Graph {


window::window(Point p,int w,int h,const char*s):Fl_Window(p.x(),p.y(),w,h,s),w_(w),h_(h)
{
    resizable(this);
 show();
}
window::~window(){
   for(Shape* s:own_shapes)
   delete s;
   //own_shapes.clear();

}

void window::draw()
{
   Fl_Window::draw();
   for(auto &sh: shapes)
       sh->draw();
    for(auto &sh: own_shapes)
       sh->draw();

   redraw();
}
// здесь нужно определить конструктор для класса
  void window::attach(Shape&& sh){

     own_shapes.push_back(new Shape(std::move(sh)));
 }

void window::attach(Shape &sh)
{
  shapes.push_back(&sh); // перемещение
}
}
