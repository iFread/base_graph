#ifndef BASE_GUI_H
#define BASE_GUI_H
#include <FL/Fl_Box.H>
#include<Fl/Fl.H>
#include <Fl/fl_draw.H>
#include <vector>
#include <cmath>
#include "base_data.h"
#include <exception>
#include <stdexcept>
//#include <>

inline void error(const char *str)
{
 throw std::runtime_error(str);
}
//
// нужно связать точки представленные на шкале axis(c вещественными координатами) с точками на экране с целыми координатами
  template <class T>
struct Point
{
   T x;
   T y;

   bool operator==(const Point<T> &p) const
   {
       return(std::abs(p.x-x)<0.001&& std::abs(p.y-y)<0.001);
   }
   bool operator!=(const Point<T> &p) const
   {
       return !(*this==p);
   }
  //Point():x(0),y(0){}
//  template<typename T>
   Point(T a={},T b={}):x(a),y(b){}

};


struct Color
{
 enum Color_type{
  red=  FL_RED,
 blue = FL_BLUE,
 green =FL_GREEN,
 yellow=FL_YELLOW,
 white= FL_WHITE,
 black =FL_BLACK,
 magenta=FL_MAGENTA,
 cyan= FL_CYAN,
 dark_red= FL_DARK_RED,
 dark_green= FL_DARK_GREEN,
 dark_yellow= FL_DARK_YELLOW,
 dark_blue=   FL_DARK_BLUE,
 dark_magenta= FL_DARK_MAGENTA,
 dark_cyan = FL_DARK_CYAN
 };
enum Transparency {invisible=0,visible=255};
Color(Color_type cc):c(cc),v{visible}{}
Color (Color_type cc,Transparency vv):c(cc),v(vv){}
Color(int cc):c{Fl_Color(cc)},v{visible}{}
Color(Transparency vv): c{Fl_Color()},v(vv) {} //цвет по умолчанию

int as_int()const {return c;}
char visibility() const {return v;}
void set_visibility(Transparency vv){v=vv;}

private:
  Fl_Color c;
  unsigned char v;
};

class Line_style
{
public:
   enum Line_style_type{
      solid = FL_SOLID,
       dash=  FL_DASH,
       dot =  FL_DOT,
       dashdot= FL_DASHDOT,
       dashdotdot= FL_DASHDOTDOT
   } ;
   Line_style(Line_style_type ss):s(ss),w(0){}
   Line_style(Line_style_type lst,int ww):s(lst),w(ww){}
   Line_style(int ss):s(ss),w(0){}
   int width() const {return w;}
   int style() const {return s;}
private:
   int s;
   int w;
};

class Shape: public Fl_Box
{
public:
    void set_color(Color cl){lcolor=cl;}
    void set_style(Line_style st) {ls=st;}
    void set_fill_color(Color fc){fcolor=fc;}
    Line_style style() const {return ls;}
    Color color() const {return lcolor;}
    Color fill_color() const {return fcolor;}
protected:
   Shape():Fl_Box(FL_NO_BOX,1,0,1,1,""){} // созвается Shape нулевого размера, для изменения методы resize
   Shape(Point<int> p1,Point<int> p2):Fl_Box(FL_NO_BOX,p1.x,p1.y,p2.x,p2.y,"") {}
   Shape(int a,int b):Fl_Box(FL_NO_BOX,a,b,1,1,""){} // точка
virtual void draw() ;
   virtual ~Shape(){}
private:
   Color lcolor =FL_RED;
   Line_style ls=0;
   Color fcolor =Color::invisible;


};


 template <typename T>
class Line //:public Shape
{ // линия определена уравнением a*x+b*y+c=0

// точки не нужны здесь
    //template<class T>

public:
 //   Line(); // нулевая линия
// template<typename T>
     Line(Point<T> a,Point<T> b):_beg{a},_end{b} //:Shape(a,b),
  {}
  //     template<class T>
 void setLine(Point<T> p1,Point<T> p2={-1,-1})
 {_beg=p1;
     _end=p2;

 }  // меняет линию полностью или  конечную точки линии
     //void setLine(Point p1);
protected:
   // void draw() override ;
private:
    float a,b,c;
   Point<T> _beg;
   Point<T>  _end;

};


// Графика
class Lines : public Shape // связанные между собой линии
{ public:
    enum line_type {OneLines, PolyLines,ClosedLines};

private:
    line_type type_obj;
    std::vector<Point<int>> points;

public:


    Lines(line_type ln=OneLines): type_obj{ln} {}  // устанавливает связь линий между собой: OneLine -одиночные линни заданные двумя точками,
                                                   // PolyLines - линии связанные друг с другом, т.е. каждая точка связана с предыдущей, но линяя открытая, т.е. может закончится
                                                   // где угодно,
                                                    // ClosedLines - закрытые линии, последняя точка должна быть связанна с начальной точкой, если ClosedLines имеет две точки -это просто линия

Lines(line_type tp,Point<int> b,Point<int> e):Shape(),type_obj{tp}  // initialyse_list
{
    points.push_back(b);
    points.push_back(e);
}
void add_point(Point<int> b,Point<int> e={-1,-1}); //добавить следующую точку, либо линию
//Point & fined_point(int i);// ищет точку по index
int fined_point(const Point<int> &p) const;// ищет точку по соответствию
void change_point(int i,const Point<int> & p={0,0});


protected:
   void draw() override;
   Point<int>& operator[](int i);
   Point<int> point(int i){return points[i];}
   unsigned num_of_points()const {return points.size();}
   unsigned size(){return points.size();}
};

class Pologon: public Lines  // без возможности менять тип
{
public:
    Pologon(): Lines(ClosedLines){} // только закрытый полигон
    bool add(Point<int>p);// должны проверять, что линия не пересекает какую либо сторону полигона,
        // для этого встраиваем точку в нужное место массива,
    // возможно представить полигон как список векторов точек определенного размера,
     /* смысл в том что точка не добавляется в конец вектора,
         а добавляется между первой пары точек составляющих линию, для которой данная точка находится в противоположной полуплоскости от остальных вершин.
       1. проверить, что последняя точка, и точка добавленная не пересекает ни одну из существующих сторон,
         если пересекает, тогда нужно найти сторону для которой выполняется условие - добавленная точка и следующая вершина фигуры лежат в разных полуплоскостях
            найдя такую сторону, поместить данную точку между вершинами стороны
    */

};


class Axis:public Lines
{

public:
   enum axis_type {_x,_y};
   Axis(Point<int> p,int lng ,int stp);
void setDiap(int x,int y);
void setStep(int st);
void change_line(int x);

protected:
 void draw() override;

private:
 int begin;
 int end;
 int length;
 int step;

};


class Rectangle:public Lines
{
public:
Rectangle(Point<int> xy, int ww,int hh);
Rectangle(Point<int> lt, Point<int> rb);

void draw() override;
int width() const;
int height() const;

private:
int w;
int h;
void change_point(int i, const  Point<int> &p) =delete; // изменение точек недоступно

};

#endif // BASE_GUI_H
