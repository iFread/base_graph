#include "window.h"
#include "base_graph.h"
namespace Graph {


window::window(Point p,int w,int h,const char*s):Fl_Window(p.x(),p.y(),w,h,s),w_(w),h_(h)
{
  init();
}

void window::init(){
    resizable(this);
   show();

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
  // std::cout<<"window dtor coll\n";
}

void window::resize(int x, int y, int w, int h){

    w_=w;
    h_=h;
//std::cout<<"x = "<<x<<", "<<"y = "<<y<<"\n";
  Fl_Window::resize(x,y,w,h);
  //  Fl_Widget::resize(x,y,w_,h_);
 // Fl_Group::resize(x,y,w,h);
 //
// после изменения размера Fl_Widgets
 // поогнать размер  Widgets виджетов
 // std::cout<<"in window size pw: "<<w_<<", "<<h_<<"\n";
for(Widget*w :wid){
 //   std::cout<<"in window size pw: "<<w->content().w()<<", "<<w->content().h()<<"\n";
 //  w->set_position(Point( w->position().x(), w->position().y()));
 // w->move(x,y);   w->resize(w->content().w(),w->content().h());
 // w->set_position(Point{static_cast<float>(w->content().x()),static_cast<float>(w->content().y())});
  w->resize(w->w(),w->h());

}


//    for(Widget*w :owns){

////       // w->set_position(Point(x,y));
//         w->resize(w->w(),w->h());
//     }

Fl_Window::redraw();
//Fl_Group::redraw();
//  for(Widget*w :wid){
//   //  w->set_position(Point( w->position().x(), w->position().y()));
//      w->content().redraw();
//      }

    //  {
//// w->~Widget();

//}
//for(Widget*w :wid)
//  {
//// w->~Widget();
// w->resize(w->position().x(),w->position().y());

//}

}

void window::attach(Widget &sh)
{
       wid.push_back(&sh);
        begin();
        (*wid.back()).attach(*this);
        end();
 }

void window::attach(Widget &&N)
{
   owns.push_back(&(N.create()));
   begin();
   (owns.back())->attach(*this);
    end();
}


int window::handle(int e){
Fl_Window::handle(e);

  return 1;

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
