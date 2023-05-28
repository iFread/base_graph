 
#include "item_list.h"
#include <dirent.h>
#include <iostream>
#include "own_fl_widgets.h"
#include "window.h"
#include "modal_window.h"
#include <algorithm>
#include <cstring>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sysmacros.h>
//#include <filesystem>
//namespace fs = std::filesystem;

namespace Graph
{

//***************************Item

bool less(const Item& it1, const Item& it2 )
{

    return    it1.name()<it2.name();// (strcmp(it1.name(),it2.name())<0);
}

//******************************************************************************************
//*****************************************************************************************
bool Simple_table::hidden(const Item& it) const
{
   const char ch=it.name()[0];
 if(ch=='.') return true;
 return false;
}



void Simple_table::draw() const // принимает какие то данные для отображения( контейнер),
{  // рисуем область видимости
  fl_rectf(loc.x(),loc.y(),w(),h(),FL_WHITE);
    // далее рисуем построчно, если есть scrolling то отображение строки начинается не с первой строки, а с +n строк
 // for(size_t sz=0;sz<table.size();++sz)
      // { table[sz]->draw(); // рисуем строку , как определить длину строки???,
    // строка состоит из  N cail, как  N  определяется,
  // ячейка имеет размер  w*h , если set_table(vector<item>& vec, item::args...> 2 ) // передано больше 2 аргументов
    // для каждого item -  int [idx rows or -1] set_row(item &, item::args)
     // иначе  в одну строку несколько item set_ceil(item & , item::args)
     // set_ceil() - сама контролирует вывод строк, с учетом размера ячейки, если ширина строки с учетом новой ячейки больше ширины table новая строка
     //   int(idx) set_cail(item & ) - возвращаем индекс установленной ячейки
       //}
begin_index=-1;
int cnt =0;
  Point next_ceil={0,0};  // начинаем сначала
data=0;
  while(next_ceil.y()+ceil_size<h())
{
    if(data>=vec.size() ) break;
     draw_row({next_ceil.x()+loc.x(),next_ceil.y()+loc.y()});
     next_ceil.y()=next_ceil.y()+ceil_size;

}



}


void Simple_table:: sort_item()
{ // using Comp = bool(*)(const Item& i1,const Item &i2);
/// auto cmpare = [](const Graph::Item &i1,const Graph::Item& i2){ };
    //qsort vector
   // Compare cmp;
  sort(vec.data(),vec.data()+vec.size()-1,Compare {});

}

int Simple_table::handle(int e)
{
    switch (e)
    {

     case FL_MOVE:


        break;
   case FL_PUSH:
// выбрать элемент на котором кликнули
// проходим по таблице выбирая ячейку
     selected=nullptr;
        std::cout<<begin_index<<"\n";
     int x_pos =Fl::event_x()-loc.x();
     int y_pos=Fl::event_y()-loc.y();
     Point orig={0,0};
     int i=begin_index-1;
   while(i<vec.size()) // идем по x,
   {
     if(orig.x()<x_pos && orig.x()+ceil_size > x_pos)
     {
          if(orig.y()<y_pos&& orig.y()+ceil_size>y_pos)
          {     selected =&vec[i];
              if(selected) {
                  std::cout<<"selected = "<<selected->name()<<"\n";
                  reference_to< open_window>(own).set_active(*selected);
               }
                  break;
           }
     }
if(orig.x()+ceil_size<x_pos ||orig.y()+ceil_size<y_pos)
{
  //if(vec[i].name()) проверка на hidden???
    i++;  // перемещаемся по вектору
    if(i<vec.size() && hidden(vec[i])) continue;

    orig.x()+=ceil_size;
 if(orig.x()+ceil_size>=w()){
  orig.x()=0;
  orig.y()+=ceil_size;
 }
}
 if(i>=vec.size()) {selected=nullptr; break;}
   }


        break;

    }

    return 0;
 }

//***************************************************************

  

  
}
