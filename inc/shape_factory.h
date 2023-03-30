 #ifndef SHAPE_FACTORY_H
#define SHAPE_FACTORY_H

#include <stdint.h>
#include "base_graph.h"

namespace Graph {


enum shape_type:uint8_t {sh_none_t,sh_line_t,sh_polyline_t,sh_rectangle_t,sh_polygon_t,sh_circle_t} ;

class shape_factory
{
public:
    virtual Shape* create(Point p) =0;
    void set_type(shape_type tp){prod_type=tp;}
    shape_type type()const{return prod_type;}

protected:
    shape_type prod_type{sh_none_t};
};


class Factory:public shape_factory
{

public:
    Factory(){}
    Shape* create(Point p);
};

//************************************************
class transform {
public:
    enum mod_type:uint8_t { none_t, move_t, change_t, rotate_t};
public:
    mod_type type(){return type_;}
    void set_type(mod_type tp){type_=tp;}


     void modify(Shape* sh,const Point &p,Point p2)  // modify(Shape* sh,Point p) / modify(Shape* sh )???
     {
         switch (type_)
         {
         case move_t:

             break;
         case change_t:    //  изменение предполагает наличие вершины или пересечение ребра в области курсора,

             break;
         case rotate_t: // флаг rotate_t предполагает: 1. Возможность установить(изменить точку вращения), 2 вращать фигуру вокруг точки вращения

             break;
         case none_t:

         default:
             break;
         }
        std::cout<<"set modify with shape\n";
       }
private:
    mod_type type_{none_t};
};

// если есть захваченная фигура, установим mode_t в звыисимости от положения
class mod2
{
public:
enum modify_type:uint8_t {none_t, change_t,rotate_t,move_t};
private:
modify_type md{none_t};

public:

void set_type(modify_type tp){md=tp;}

void operator()(Shape&s,Point p,int i=-1)
{
 if(md==change_t)
        s.change(p,i);
// }  //
//void operator()(Shape& s,Point p)  // int i, для вращения, для расчетов необходимо знать центр вращения и смещение на угол,
//{
  if(md==move_t)
    s.move(p.x(),p.y());

  if(md==rotate_t)
      return ;//
}
};

}
#endif
