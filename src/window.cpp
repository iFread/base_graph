#include "window.h"
#include "base_graph.h"
namespace Graph {

int gui_run(){return Fl::run();}

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
    hide();
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

//  for(Widget*w :wid){

//  w->resize(w->w(),w->h());

//}
  Fl_Window::redraw();
}
void window::set_active(Widget &w, int event)
{
 waiting.w=&w;
 waiting.ev=event;
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
    owns.push_back(&N);
    //begin();
   attach(*owns.back());
    //  (owns.back())->attach(*this);
    //end();
}

void window::detach(Widget &w)
{// w.hide();
 for(size_t i=0;i<wid.size();++i)
 {
     if(wid[i]==&w)
     { //Widget *del=wid[i];
     //  w.hide();
      remove(&w.content());
        wid.erase(wid.begin()+i);
//        for(size_t j=0;j<owns.size();j++)
//        {
//          if(owns[j]==&w)
//          {
//              owns.erase(owns.begin()+j);
//              delete &w;
//          }

     //   }
        break;
     }
 }
}

//void window::hide()
//{
//  for(Widget* w:wid)
//  {

//   detach(*w);
//  }
//  wid.clear();
//for(int i=0;i<owns.size();++i)
//{ detach(*owns[i]);
//    delete owns[i];
//}

// Fl_Window::hide();
//}

int window::handle(int e){


//for(size_t i=0;i<waiting.size();++i)
//{
// if(waiting[i])  //flag
// {
//    waiting[i]->content().handle(e);
// }
//}
    if(waiting.w&&e==waiting.ev)
    {
      Widget* ptr=waiting.w;
      waiting={nullptr,FL_NO_EVENT};
      return ptr->content().handle(e);
    }

  Fl_Group::handle(e);
 //redraw();
  return 0;

}

void window::draw()
{
    Fl_Window::draw();
//  for(size_t sz=0;sz<wid.size();++sz)
//  {
//   wid[sz]->draw();
//  }
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
