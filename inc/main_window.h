 #ifndef  MAIN_WINDOW_H_
#define   MAIN_WINDOW_H_

#include "window.h"
#include "main_menu.h"
#include "group_widgets.h"
#include "own_gui_widgets.h"
#include "cmd_list.h"
namespace Graph
{

// class m_menu:public menu
// {
// public:
//     m_menu()
// };
// Формат записи файла:
//  1 РАсширение файла,(придумать), размер записанных данных(количество фигур), масштаб, с которым отображаются фигуры(или масштаб всегда 1.0)
// 2. Каждая фигура может/содержит дополнительные свойства: тольшину линии, тип линии, цвет,тип заливки(определить типы заливки фигур)
   // 2.1 Под заливкой понимаем заштрихованную фигуру,
//  3. дополнительные данные?? например радиус для circle, или угол поворота  ???

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

Shape* read(std::istream& is);


public:

File():path(""){}
File(const char* pth);




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

    void convertion(const char* fl); // преобразовать в файл

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

   void convert_shape(std::ostream &s,const Shape& sh);
   void trace_cmd(std::ostream &s,const command::cmd&c);

   // Callback- metods:

   static void cb_open_win(Address ,Address us );
   static void cb_save_new_file(Address, Address adr);
   static void cb_save_file(Address, Address a);
   static void cb_convertion(Address,Address a);


 };

}







#endif
