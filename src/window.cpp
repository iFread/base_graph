#include "window.h"
#include "base_graph.h"
namespace Graph {


window::window(Point p,int w,int h,const char*s):Fl_Window(p.x(),p.y(),w,h,s),w_(w),h_(h)
{
   resizable(this);
Fl_Window::show();
}
window::~window(){
//   for(Shape* s:own_shapes)
//   delete s;
//  own_shapes.clear();
wid.clear();
    for(Widget*w :owns)
      {
    // w->~Widget();
        delete w;

    }
}

void window::resize(int x, int y, int w, int h){
w_=w;
h_=h;
 Fl_Window::resize(x,y,w_,h_);
// после изменения размера Fl_Widgets
 // поогнать размер  Widgets виджетов
for(Widget*w :wid)
    w->resize(w->content().w(),w->content().h());
//Fl_Window::redraw();
    //  {
//// w->~Widget();

//}
//for(Widget*w :wid)
//  {
//// w->~Widget();
// w->resize(w->position().x(),w->position().y());

//}

}
int window::handle(int e){

    Fl_Window::handle(e);
  return e;
}

void window::draw()
{
    Fl_Window::draw();
//   for(auto &sh: shapes)
//       sh->draw();
//    for(auto *sh: own_shapes)
//       sh->draw();
//std::cout<<shapes.size()<<"\n"<<own_shapes.size()<<"\n";
  //  redraw();
}
// здесь нужно определить конструктор для класса

//void window::attach(Shape&& sh){
//// Shape* create(){return new Line;}
//     own_shapes.push_back(new Shape(std::move(sh)));
// }

//void window::attach(Shape &sh)
//{
//  shapes.push_back(&sh); // перемещение
//}
}
