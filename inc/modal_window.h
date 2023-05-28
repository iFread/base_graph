#ifndef MODAL_WINDOW_H
#define MODAL_WINDOW_H

#include "window.h"
#include "base_gui.h"
#include "item_list.h"
#include "u_item.h"
#include <sys/types.h>

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

class open_window:public Graph::window
{
public:


private:




    Button* b_ok;
    Button* b_cancel;
    Button *b_up;
   // Simple_list *list;
    Simple_table *list;
    Out_Box* bx{nullptr};
    window *own;

    std::string path;
    Item *active{nullptr};


    // tree - отображение иерархии файлов в виде списка в текущей папке
// std::vector<item> vec;
   // у paret будем вызывать open(path)
       // задача класса open_window сформировать path
public:
    open_window(Point o,int w,int h,window& parent);


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
                    delete bx;
                    delete b_ok;
                    delete b_up;
                    delete b_cancel;
                    delete list;
     }

protected:
 file_type get_type(struct stat &type);
 void open_dir(const char *path);
 void set_new_path(const char* n_path);

 static void cb_open(Address, Address );
 static void cb_open_file(Address, Address);
};

}


#endif


