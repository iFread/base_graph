// простой список элементов
//  - меню, без вложенных подменю
#include "base_gui.h"
#include <string>
#include <vector>
#include <Fl/fl_draw.H>
#include "gui_attributes.h"
#include <iostream>
#include "u_item.h"
#ifndef ITEM_LIST_H
#define ITEM_LIST_H

namespace Graph {


// Отображает элементы в табличном виде
  // 1 один элемент -  одна ячейка
 //  2. Один элемент - одна строка  из N ячеек ??
// scroll только  по вертикали

class Item
{
 std::string name_item;
 file_type tp_; // ссылку на icons
 size_t size_item;  // размер в байтах...


public:
 Item(const char* nm, file_type tp,size_t sz=0):name_item(nm),tp_(tp),size_item(sz) // для каталога не передается
 { }

~Item(){}

std::string name() const {return name_item;}
 file_type type() const {return tp_;}
 size_t size() const{return size_item;}


};
bool less(const Item& it1, const Item& it2 );


class Simple_table:public Empty  // либо свободная таблица
{
    const int  ceil_size=115;


    mutable int data{0};
    mutable  int begin_index{-1}; // указатель на начало , первый выводимый элемент

    Item* selected{nullptr};

public:
   Simple_table(Point o,int w,int h):Empty(o,w,h){}


   void draw_row(Point o)  const // рисуем прямоугольник от orig
 {
  //  fl_rect(loc.x()+o.x(),loc.y()+o.y(),w(),ceil_size,FL_CYAN);
  // перемещаем точку по горизонтали
     Point orig=o;
       while(orig.x()+ceil_size<w()+loc.x())
       {if(data >= vec.size()) break;
         if(draw_ceil(next_data(),orig))
              orig.x()=orig.x()+ceil_size;
       }

   }

   ////  template<typename T>
   bool draw_ceil(const Item& it,Point o) const
   {
     if( hidden(it)) return false;
       std::string s=it.name();
      // if((!s.empty()))//&& s[0]!='.')       //
       //{
           // поиск hiden_item
           if(begin_index<0)  begin_index=data;  // если начальный индекс сброшен, устанавливаем начало = data

  // fl_rect(o.x() ,o.y() ,ceil_size,ceil_size,FL_BLACK);

//         if(s.size()>16)       // разбить имя на несколько строк  методы  draw_txt(), int height_name(); // возвращает на сколько строк разбит текст
//        {  std::string s0(s.data(), 16);//,s.size()-13);
//            std::string s1(s.data()+16);
//            fl_color(FL_BLACK);
//         fl_draw(s0.c_str(),o.x()+loc.x(),o.y()+loc.y()+ceil_size-fl_height());
//         fl_draw(s1.c_str(),o.x()+loc.x()+(ceil_size-fl_width(s1.c_str()))/2,o.y()+loc.y()+ceil_size);
//         return true;
//        }
//           fl_color(FL_BLACK);
//           fl_draw(s.c_str() ,o.x()+loc.x()+(ceil_size-fl_width(s.c_str()))/2,o.y()+loc.y()+ceil_size);
//           return true;
     int h=height_text(it.name().c_str());
    if(selected==&it) fl_rectf(o.x() ,o.y()+ceil_size/3*2,ceil_size,h,FL_CYAN);
     draw_name({o.x() ,o.y()+ceil_size/3*2 },it.name(),14);
        return true;
   }

void draw_name(Point o,std::string str,int w/* ширина строки в символах */) const
{  // текст рисуется от нижней точки, o.y() - низ яцейки,
   int remains= str.size();
   int pos=0;
   fl_color(FL_BLACK);
 //  int h= fl_height()*(remains/w+1);
   o.y()+=fl_height();//+ ((h>fl_height())?o.y():o.y()-h);
 std:: string s;
   while(pos<remains)
   {
       s=str.substr(pos,pos+w+1);

        o.x()+=(ceil_size-fl_width(s.c_str()))/2;
        fl_draw(s.c_str(),o.x(),o.y()) ;
       o.y()=o.y()+fl_height();
       //o.x()+=(ceil_size-fl_width(s.c_str()))/2;
    pos+=w;
   }



}

int height_text(const char* s) const
{
    int remains=strlen(s);
   int res= fl_height()*(remains /14+1);
 std::cout<<" высота текста : "<<s<< " = "<<res<<"\n";
 return res;
}
 const Item& next_data() const   // возвращает следующе данные для вывода
{
//std::string s;

 // if(data < static_cast<int>(vec.size())) {
 // проверить что данные не относятся к скрытым

//     while(hidden(vec[data++]))
//          ;
     //if(data<vec.size())
           return vec[data++];
//   return ;

  //}

    //  return s;// std::string{};

   }
 // для хранения нужен элемент item
 // для этого нужно формировать вектор, т.е.
  //1 . set_item()

  // std::vector<Item> vec;???




std::vector<Item> vec;
 // передаем T, и методы класса T,






void set_item(const char* nm,file_type tp,size_t sz=0)
{
  Item it(nm,tp,sz);
  vec.push_back(it);

}


class Compare
{
public:
    bool operator()(const Item& i1,const Item& i2){
    // условия сравнения
 if((i1.type()==file_type::dir_t) && (i2.type()!=file_type::dir_t))
 {
      return true;  // directory less then file
   } else
 if((i2.type()==file_type::dir_t) && (i1.type()!=file_type::dir_t))
     return false;
    // иначе проверка по имени
     std::string s1=i1.name();
     std::string s2= i2.name();
 for(size_t i=0;i<s1.length();++i)
 {
   s1[i]=tolower(s1[i]);
 }
 for(size_t i=0;i<s2.length();++i)
 {
   s2[i]=tolower(s2[i]);
 }
 return  s1<s2;
    }
};
void sort_item();//


void clear() {vec.clear();}

bool hidden(const Item& it) const;

void draw()const;
 int handle(int e);
        // сказать что у нас есть друзья??
};




class Text
{           // Точка определяет нижний угол первой буквы
public:
    Text(const std::string &s):lab(s){}//,orig(px.x(),px.y()-fl_height()){}

void set_label(const std::string &s){lab=s;}
const char* label() const{return lab.c_str();}

void set_font(Font ff){fn=ff;}
Font font() const{return fn;}
//std::string text() {return lab;}
//void set_point(Point p){ point(0)=p;}
void set_font_size(int fz){fnt_sz=fz;}
int font_size() const {return fnt_sz;}
~Text(){}
protected:
void draw_lines(Point orig)const{ fl_font(font().as_int(),fnt_sz);
                        fl_draw(lab.c_str(),orig.x(),orig.y());}
public:
void draw(Point p)const
{
    Fl_Font old=fl_font();
    int old_sz=fl_size();
    draw_lines(p);
    fl_font(old,old_sz);

}
private:
std::string lab;
Font fn {Font::times_italic};
int fnt_sz {20};//(fl_size()<14)?14:fl_size()}; // шрифт по умолчанию
//Point orig;
           };

}
#endif
