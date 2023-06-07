 #ifndef  MAIN_WINDOW_H_
#define   MAIN_WINDOW_H_

#include "window.h"
#include "main_menu.h"
#include "group_widgets.h"
#include "own_gui_widgets.h"

namespace Graph
{

// class m_menu:public menu
// {
// public:
//     m_menu()
// };
// файл представлен как вектор shape: std::vector<Shape*>;
// 1. Создание объекта через Canvas factory.create();
// 2. Чтение объекта Shape из файла,
// 3. запись объекта Shape в файл
struct File
{
   std::string path;
   ref_list<Shape> list;

protected:
//  bool write(std::ostream& os,Shape* sh)
//  {  shape_type st= sh->get_shape_type();
//    //os<<st<<"("<<(*sh)[0].x()<<", "<<(*sh)[0].y()<<") ("<<(*sh)[1].x()<<", "<<(*sh)[1].y()<<")"; // пишем две точки
//  (*sh)[0].trace
//      if(os)
//      return true;
//  return false;
//  }





 Shape* read(std::istream &is)
{
       unsigned char tp=0;
       size_t sz=0;
        is>>tp>>sz;
// то что считывается далее, зависит от типа

std::vector<Point> vec;
 int x=0,y=0;
 Shape *res=nullptr;
 for(size_t i=0;i<sz;++i)
 {
    is>>x>>y;
    vec.push_back(Point(x,y));
 }


     switch (tp)
   {
         case '1':
                    // считать две точки
    res=new line(vec[0],vec[1]);
         break;


 case '2':
            // считать
     res=new lines(vec[0]); // polyline
case '4':
    if(!res)
        res=new polygon(vec[0]);

for(size_t i=1;i<vec.size();++i)
   res->add(vec[i]);
            break;

     case '3':
 res=new rectangle(vec[0],vec[2]);
         break;

        case '5':
 {int r;
    is>>r;
    res=new circle(vec[0],r) ;
     }
            break;
        default:
     res=nullptr;
     }
     return res;
  }
public:


 void read_list(std::istream &is)
 {
  while(is)
  {
    Shape* c=read(is);
    if(c)
     list.push_back(c);
  }

 }

  void write_list(std::ostream& os)
  {
    for(size_t i=0;i<list.size();++i)
    {
     // write(os,&list[i]);
      list[i].trace(os);
    }

  }

  ~File() {
  // list.clear();
  }
};

//static void cb_quit_win(Address,Address adr);

 class main_window:public window
 {


 public:
     main_window(Point p, int w,int h, const char* title);
     ~main_window();
    void open_file(const char* fl);  // открыть
    void save_file(const char* fl); // сохранить

 private:
  menu* m;
  Menu * main_menu;
  VLayout* panels{nullptr};
  Scroll* scrl{nullptr};
  Canvas* can{nullptr};
  std::string path;
  File curent_file;
 private:
   // лучше определить по другому
   menu* create_menu() noexcept;
   VLayout* create_panel(Point p,Widget&w);


   // Callback- metods:
   static void cb_open_win();
   static void open_win(Address ,Address us );
   static void cb_save_file(Address, Address adr);
   static shape_type cb_set_type(const char* s);
 };

}







#endif
