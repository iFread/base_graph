#ifndef MODAL_WINDOW_H
#define MODAL_WINDOW_H

#include "window.h"
#include "base_gui.h"
#include "item_list.h"
#include "u_item.h"
#include <sys/types.h>
#include "main_window.h"

//class Control
//{
// Widget* w;
//     //   1, 2 , 3, 4  : если select = button activ, else button unactive();
//      // если select =dir, то button->callback() должет вызывать set_list; // переопределение пути и перерисовка виджета Simple_list
//     // если select = file , button->callback() должен открыть этот файл, или передать путь к файлу главному окну
//     // список состояний виджета???
//    // swich()
//     // {   case 1:
//   //     case 2:
//   // }
// std::vector<Widget*> widgets;  // связаныне виджеты,
//   // как определить список состояний класса
//  //
// //

//};


namespace Graph
{
//class main_window;

template <typename T>
class func
{
    using f= void(T::*)(const char*);
   f t_;
 //  void (T::*f1)(const char*);

public:
     func(f t):t_(t){}
    virtual void operator()(T& t,const char* fl)
   {
   //  window* win= new window({100,100},100,100,"");

         (t.*t_)(fl);}
  };


class func_save: public func<main_window>
{
    using f= void(main_window::*)(const char*);
   f f1;
public:
   func_save(f  f1):func<main_window>(f1){}
   void operator()(main_window &t,const char* cl)
   {
       (t.*f1)(cl);
   }
};

// чтобы поле класса не являлось шаблоном, унаследовать от нешаблонного класса
class base_functor {
public:
    virtual void operator()(const char*) =0;
    virtual ~base_functor(){}
};

template <typename T>
class my_functor:public base_functor
{
  window& w_;
  void (T::*method)(const char* pth);
public:
  my_functor(window& w,void (T::*m)(const char* pth)):w_(w),method(m){}
  void operator()(const char* pth){
      (static_cast<T&>(w_).*method)(pth);}
  ~my_functor(){}
 };

 // простое окно, для общения с пользователем,
 //  и одной/двумя кнопками и вопросом, допустим  подтверждения действия или сохранения изменений перед закрытием файла  ==>

// 1, простое модальное окно  содержит одну кнопку и ваводит какую либо информацию

class base_modal_window:public window
{
    // для доступа классам наследникам
protected:
    Button *b_ok;
    Button* b_cancel;  // нужно позиционировние кнопок
    base_functor* fun; // принимается по ссылке,т.е. объект создается и удаляется в той же функции, где создается модальное окно
public:
    template<typename T>
    base_modal_window(Point p,int w,int h,const char* ttl,my_functor<T> & t):window(p,w,h,ttl),
       b_ok(new Button(Point(10,h-30),70,20,"Ok")),b_cancel(new Button(Point(w-80,h-30),70,20,"Cancel")),fun(&t)
    {
     init();
    }

// 1, определение callback для кнопок

    virtual void init(){
        hide();
        set_modal();
      attach(*b_ok);
      attach(*b_cancel);
       show();
    } // определить

    ~base_modal_window()
    {
        detach(*b_ok);
        detach(*b_cancel);
        delete b_ok;
        delete b_cancel;

    }
};



class  modal_window:public base_modal_window
{
 // общий интерфейс
 // Button *b_ok;
 // Button* b_cancel;
protected:
    bool fl_visible{false};
  Button *b_up;
  Simple_table* list; // список элементов
  Out_Box* c_path;  // здесь combo_box с разложением пути на элементы
  const Item* active{nullptr};// выбранный элемент

// данные для работы с окном
 std::string path;  // путь к отображаемому каталогу
// window* own;   // окно  родитель,

 //base_functor*fun;
 // func*f;  определить функтор, для хранения окна родителя и его метода

 // далее нужно определять поля спецефичные для каждого класся
public:
 template<typename T>
 modal_window(Point p,int w,int h,const char* ttl,my_functor<T> & fu/*functor<T> f(window *w,window::*metod) =my_functor(window& w,void (window::*f)(const char* p)) */):
    base_modal_window(p,w,h,ttl,fu),//,b_ok(new Button(Point(w-100,h-45),70,20,"open")),b_cancel(new Button( Point(w-100,h-25),70,20,"Cancel")),
    b_up(new Button(Point(w/4*3+10,10),30,30,"Up")),
    list(new Simple_table(Point((w-20)/4,50),w/4*3,h-120)),//, fun(&fu)
    c_path(new Out_Box(Point((w-20)/4,10),(w-20)/4*2,30))
 {  // расстановка элементов:
      //
    init();

  }
 bool visible()const{return fl_visible;}
 void visible(bool st){fl_visible=st;}
 void set_new_path(const char* pth);
 void set_items(const char* pth);
file_type get_type(struct stat* st);
 /* virtual void action_*/ void open_file();
virtual void action();

void init();

 virtual ~ modal_window()
 { // detach(*b_ok);
    // detach(*b_cancel);
//     detach(*b_up);
//     detach(*list);
//     detach(*c_path);
     delete c_path;
    // delete b_ok;
     delete b_up;
   //  delete b_cancel;
     delete list;
 }

};



class new_open:public modal_window
{
 Out_Box fl_name;

public:
 template< typename T>
 new_open(Point p,int w,int h,const char* ttl,my_functor<T>& f):modal_window(p,w,h,ttl,f),fl_name(Out_Box(Point(w/2,h-45),w/4,20))
 {  init(); }

 void init();
void action();
 ~new_open()
 {
 detach(fl_name);
 // delete fl_name;
 }
};


class save_window:public modal_window // open_window
{

In_Box fl_name;
public:
   // save_window(Point p)
    template<typename T>
    save_window(Point p,int w,int h,const char* ttl,my_functor<T> &f): modal_window(p,w,h,ttl,f),fl_name(In_Box(Point(w/2,h-45),w/4,20)){ init();}
void init();
void action();
~save_window()
{
 detach(fl_name);
  //  delete fl_name;
}

protected:
    static void cb_open(Address, Address);

};


class open_window:public Graph::window
{

public:


private:
    Button* b_ok;
    Button* b_cancel;
    Button *b_up;
   // Simple_list *list;
    Simple_table *list;
    Out_Box* bx{nullptr}; // выпадающий список
    Out_Box *fl_name;
    window *own;
 //   void (window::*foo)(const char* pth);
   func<main_window> *futh;
    std::string path;
    Item *active{nullptr};


    // tree - отображение иерархии файлов в виде списка в текущей папке
// std::vector<item> vec;
   // у paret будем вызывать open(path)
       // задача класса open_window сформировать path

public:

 open_window(Point o,int w,int h,window& parent, func<main_window> *f);//void(window::*f)(const char* pth)=nullptr);

 void set_items(const char* path); // заполняем вектор,
       // => simple_list->set_table(std::vector<>&,... )  //  устанавливает число ячеек в таблице = vector.size() при этом, если  переменное число аргументов>2,
       // каждый элемент выводится с новой строки, если меньше 2, то размер ячейки определяется по  fl_width(v.name);
void set_active(Item &it) ;

    ~open_window() {
        detach(*b_ok);
        detach(*b_cancel);
        detach(*b_up);
        detach(*list);
        detach(*bx);
        detach(*fl_name);
                    delete fl_name;
                    delete bx;
                    delete b_ok;
                    delete b_up;
                    delete b_cancel;
                    delete list;
     }
//void set_callback(Callback cb);
std::string get_path() const { return this->path;}
void open_file();
protected:
// если будут указатели на callback:
//  child в Window : имеем void set_callback(Widget&w, Callback cb); установить callback
// void
//using Callback =void (*) (Address, Address);
//Callback b_ok_callback{nullptr};

 file_type get_type(struct stat &type);
 void open_dir(const char *path);
 void set_new_path(const char* n_path);


 // эти методы должны быть для класса открытия
 //static void cb_open(Address, Address );     // открыть directory
// static void cb_open_file(Address, Address); // открыть file
};
//static void cb_open_file(Address, Address);



}


#endif


