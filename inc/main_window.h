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
  bool write(std::ostream& os,Shape* sh)
  {  shape_type st=shape_type::sh_line_t;//sh->type();
    os<<st<<(*sh)[0].x()<<(*sh)[0].y()<<(*sh)[1].x()<<(*sh)[1].y(); // пишем две точки

  }
  Shape* read(std::istream &is);
public:
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
