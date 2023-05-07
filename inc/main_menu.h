#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <Fl/Fl_Menu_.H>
#include <Fl/Fl_Menu_Bar.H>
#include "base_gui.h"
//#include "group_widgets.h"
#include "gui_attributes.h"
#include <iostream>
#include <cstring>


namespace Graph
{
// menu_item может содержать подменю
// представляет Fl_Box размера M x N
     //

class Text
{
 std::string lab;
 Font fnt;
 int fnt_sz;
 Point loc;  // точка отсчета для текста
public:
 Text(Point xy,const std::string &l):lab(l),fnt(fl_font()),loc(xy){}
 void draw()const;
 };

//enum status:unsigned char {
//    inactive=FL_MENU_INACTIVE,
//     submenu=FL_SUBMENU,
//   // vertical_position,  // отрисовка submenu под item (для главного меню)
//     horisontal_position  // отрисовка справа от элемента
//};
class  item // Widget???
{ public:
    enum item_state:unsigned char {as_item,as_menu};
private:
 // char *txt;
   std::string txt;
   //unsigned long shortcut
    Callback cb;
    void *u_data;
   // status flag;
    item* next_,*parent_;
    int sz_;
    item_state state_{as_item};
    //{nullptr}; // указывает на следующий,
    // размер меню вычисляется по размеру текста,

public:
    explicit item(const char* name,Callback clb=nullptr,void* ud=nullptr):txt(name),cb(clb),u_data(ud),next_(nullptr),parent_(nullptr),sz_(1){ }

    item(item&& it):txt(it.name()),cb(it.cb),u_data(it.u_data),next_(it.next_),parent_(it.parent()),sz_(it.sz_){it.next_=it.parent_=nullptr;}

    item& operator=(item&& it)
     { if(&it==this) return *this;
      item n_it(std::move(it));
       std::swap(*this,it);
       return *this;
     }
 void callback(){if(cb) cb(nullptr,u_data);}
  item(const item&)=delete;
  item&operator=(const item&)=delete;

     void add(item *it){
          if(next_) next_->add(it);
          else { next_=it;
           next_->parent_=this;
           }
          sz_++;
     }

   // item& operator[](int i) { item* it=this; for(;i<0;--i) it=it->next_; return *it;   }

    item* next()const {return next_;}
    void next(item* m)  { next_=m; m->parent_=this;}
   const item* parent() const{return parent_;}
   item* parent(){return parent_;}
   void parent(item* it) {parent_=it;}
 void set_state(item_state st){state_=st;}
 item_state state() const{return state_;}

    int width() const{ return txt.size() ; }
    int size() const {return sz_;}

    const char* name()const{return txt.c_str();}
    virtual  ~item(){
         if(next_) delete next_;
            }

//    void draw()const;  //
//    void draw(int x,int y)const; // рисует виджет и текст в нем
protected:
    const char* elem_name(const char* path,char buf[]);
};

// у меню нет Callback, либо default_callback, фиксирует отображение подменю
class menu : public item  //
{
 //item* menu_;
    //int sz{0};
 item* submenu_;
public:
 menu(item&& it):item(std::move(it)),submenu_(nullptr){set_state(item::as_menu);}
  menu(item*it):item(std::move(*it)),submenu_(nullptr){set_state(item::as_menu);delete it;}

// void add(item it);// [,const char* path=nullptr)// добавить новое меню
 void add(item *it,const char* path=nullptr); // добавление элемента в существуюшее подменю меню

 item& operator[](int i); // здесь возможно
 item const &   operator [](int i) const;
//item* find(const char* path,item* it=nullptr); // ищет только по списку меню

 //void draw(int x, int y) const; // положение мыши
 item* submenu(){return submenu_;}
 const item* submenu() const {return submenu_;}
 void submenu(item* it) {if(submenu_) submenu_->add(it);else submenu_=it;}
 ~menu(){if(submenu_) delete submenu_;}  // for(i<sz;++i) {item*del=(submenu); submenu=submenu->next(); delete del;)}
};



// при наведении на submenu должен включать в обработку размеры выпадающей области, увеличивая на

// представляет вертикальное меню, т.е.обробатывает только связи next_
// header_item
  //           -> next_->next_->next_...

// don't own resources
class Menu:public Empty
{public:
    enum status_menu:unsigned char{none_active, active,submenu_visible};
  // если у элемента status==active
    // status активного элемента == active, или submenu_visible, для меню
    // при этом submenu_visible устанавливается после нажатия на меню первого уровня

    struct active_menu
    {
     const item* active_;
     status_menu status;
     Point orig;
     const item* parent;


  void set_state(const item* elem,status_menu st=none_active){
      active_=elem;
    if(!elem) return;
      if(st==submenu_visible && elem->state()==item::as_item)
        status= active;
              else
        status=st;
           }
     void clear(){active_=nullptr; status=none_active; orig= Point(0,0);}
    };

private:
  const item* menu_;
    orientation orient;
    active_menu  curent_item={nullptr,none_active,loc,nullptr};

 Menu* submenu_{nullptr}; //
   //
public:
 //  Menu(Point p):Widget(p,0,0){}
   Menu(Point p,const item* it,orientation ort=vertical):Empty(p,0,0),menu_(it),orient(ort) {  }
Menu(const Menu&)=delete;
  void create(Point p,int x,int y);
 Widget& create(){return *this;}
  void draw()const; //const item* it,orientation orient=vertical); // отображаем одно над другим
   void draw_item(Point o,const item* it) const;
 int handle(int e);
 void set_submenu(Point o,const item* it);//{menu_=it;set_widget_size(menu_);}
  ~Menu();
 void clear(); // удаление текущего меню
protected:
   void set_widget_size(const item* it);
    // создает подменю в точке o, привязывает его к own
   Menu*create_submenu(Point o,const item* it);
};

//
class Menu_Bar:protected Menu
{

  menu*menu_;  // непосредственно меню, хранится отдельно от графического представления,
  Menu*subm_; //

};


class menu_bar:public Empty//:protected HLayout  // Layout  ???
{
    enum status_menu:unsigned char { none,menu_active, menu_unactive,submunu_visible};

  std::vector<item*>arr; //  проходим по массиву item:

  menu* menu_{nullptr};  // здесь указатель, т.к. нельзя создать меню без элементов
  //menu menu;

 // status_menu status{menu_bar::menu_unactive};
 // size_t size_menu;
  const item* active;  // указывает на активный элемент, не понятно только как активыровать боковое меню

  Widget* submenu_;
  Widget* pt; // active_menu

 struct active_menu {
      const item* active;
        status_menu flag;
 void set_state(const item*it,status_menu fg){
   active=it;
   flag=fg;}
 void clear(){ active=nullptr;flag=none;}
   } ;

   active_menu menu_curent{nullptr,none};

public:
  menu_bar(Point p):Empty(p,0,0), active(nullptr),pt(nullptr){};//:HLayout(p){}
    void draw()const;
    void draw_item(Point o,const item* it) const;
    void draw_submenu(Point o, const item*it)const;

    int handle(int event); //

//  void add(item new_item,const  item*parent=nullptr);
  void add(item* new_item, const char* path=nullptr,unsigned char ind=255);  // if(path) поиск, куда вставить
  Widget* submenu(){return pt;}
~menu_bar()
  {
      if(menu_) delete menu_;
   }
   void create(Point p,int w,int h);
    Widget& create();

protected:
    int parser(item* it);
    item* parser_path(const char* name);  // ищет в name разделитель  "file/select" /
    item* parser_path(const char* name,item* it);

};


static void win_cd(Address,Address add) {
std::cout<<"win_ callback\n;";
}

}


#endif // MAIN_MENU_H
