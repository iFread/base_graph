#include "base_gui.h"
#include <iostream>

//bool Point<>::operator==(const Point &p) const
//{
//    return x==p.x&&y==p.y;
//}
//bool Point::operator!=(const Point &p) const
//{
//    return !(*this==p);
//}
void Shape::draw()
{
    Fl_Box::draw();
    fl_color( lcolor.as_int());
    fl_line_style(ls.style(),ls.width());

}
// поиск НОД для чисел?????


//Line::Line(Point p1,Point p2)
//{
//  a=p1.y-p2.y;
//b=p2.x-p1.x  ;
//c=p1.x*p2.y-p2.x*p1.y;
// // сократить на кратное
//// найти общий делитель чискл a,b,c
//// т.к. числа вещественные, нужно округлить их до какого то приемлимого значения


//}
//void Line::draw()
//{if(color().visibility()){
//   Shape::draw();

//   fl_line(_beg.x,_beg.y,_end.x,_end.y);
//    }
//}

//void Line::setLine(Point p1,Point p2)
//{ _beg=p1;
//  _end=p2;
////  Fl_Box::resize(1,1,1,1);
// //Fl_Box::redraw();
//}


void Lines::draw()
{
//  Fl_Box::draw();
//fl_color(FL_RED);
 if(color().visibility()){
    Shape::draw();
if(type_obj==OneLines)  // если отдельные линии
 for(unsigned i=1;i<points.size();i+=2)
{
  fl_line(points[i-1].x,points[i-1].y,points[i].x,points[i].y);

 }
else {
    for(unsigned i=1;i<points.size();++i)
    {
     fl_line(points[i-1].x,points[i-1].y,points[i].x,points[i].y);

       }

}
if(type_obj==ClosedLines && 2<points.size()) //если полигон закрытый, сооединяем первую и последнюю точки
fl_line(points[points.size()-1].x,points[points.size()-1].y,points[0].x,points[0].y);
 }
}

void Lines::add_point(Point<int> b, Point<int> e)
{   // если OneLine -отдельные линии то всегда нужно добавлять пару точек
    // если PolyLines или ClosedLines
  //if(type_obj==OneLine) // если отдельные линии
 if(type_obj==OneLines && e==Point<int>(-1,-1)) return; // невозможно добавить одну точку в объект типа OneLines
 // для типов PolyLines и ClosedLines
 points.push_back(b);
    if(e!= Point<int>(-1,-1))//&& b!=(Point(-1,-1)))
        points.push_back(e);         //Fl_Widget::resize(b.x,b.y,1,1);

      //else
      Fl_Widget::resize(1,1,1,1);

}
Point<int>& Lines::operator[](int i)
{
   return points[i];
}


int Lines::fined_point(const Point<int> &p) const
{
   for(size_t i=0;i<points.size();++i)
   {
       if(p==points[i]) return i;

   }
   return -1;
}

void Lines::change_point(int i, const Point<int> &p)
{
    if(i<0 || i>points.size()) return;
points[i].x=p.x;
points[i].y=p.y;
}




Axis::Axis(Point<int> p,int lng,int st): Lines(OneLines) ,length(lng),step(st)
{
    begin=p.x;
    end=p.x+length;//step; //10+100=110
   for(int i=p.x;i<end;i+=step)
   { // if(i%(10*step)==0)

       //    Lines::add_point(Point(i,p.y),Point(i,p.y+20));
     Lines::add_point(Point<int>(i,p.y),Point<int>(i,p.y+10));

   }

}
//Point& Lines::fined_point(int i) // operator[](int i)
//{
//    return points[i];
//}



 void Axis::draw()
 {//
     if(color().visibility())
     { //Shape::draw();
      // for(int i=1,count =0;i<this->size();i+=2,count++)
       //{
        //if(count%10==0)
          //{
           // this->o;

         //  fl_line(this->operator[](i-1).x,this->operator[](i-1).y+10,this->operator[](i).x,this->operator[](i).y);

            //}
 //  else   // fl_line(this->operator[](i-1).x,this->operator[](i-1).y,this->operator[](i).x,this->operator[](i).y);

      // }
     Lines::draw();
     }

 }
 void Axis::change_line(int x)
 {
  //change_point(1,Point(this->operator[](1).x,this->operator[](1).y+10));
  for(size_t i=1;i<this->size();i+=2)
  {
     if( !((i-1)%(x*2)))        // выбираем по начальным точкам линии , т.е. 0,2,4,...
         change_point(i,Point<int>(this->operator[](i).x,this->operator[](i).y+10)); // меняем конечную точку этой линии 1,3,5.... например если p20 соответствует условию то p21 будет смещена на 10 пикселей

  }

 }
 // здесь нужно пересечение отрезков, а не прямых
 bool Pologon::add(Point<int> p)
 { bool flag=true; //
   // в цикле проходим все стороны и проверяем, что line_t (size-1,p)
      //
     if(size()<3)
 {        add_point(p);
         return true;  }

   std::cout<<"size : "<<size()<<std::endl;
     line_t ln(point_t(point(size()-1).x,point(size()-1).y),point_t(p.x,p.y));  // создаем линию, из последней точки и данной точки
  //point_t pt;//(p.x,p.y);
 // перебирая все точки попарно( по отрезкам которые они образовывают), смотрим разделяет линия эти точки,
     // если разделяет, какую либо пару точек, то возвращает false, точка не добавляется
  //// возможно, следует добавить точку в первое возможное положение, т.е. найти линию, которая разделяет добавляемую точку от всех остальных
  /// и вставить точку разделив линию на 2
  ///

     for(unsigned i=1;i<size()-1;++i)
   {
   // if(ln.intersect(line_t(point_t(point(i-1).x,point(i-1).y),point_t(point(i).x,point(i).y))))
         if(ln.separates(point_t(point(i-1).x,point(i-1).y),point_t(point(i).x,point(i).y)))
       flag=false ;
   }
   if(flag)
       Lines::add_point(p);
   std::cout<<"size : "<<size()<<std::endl;

     return flag;
 }

 Rectangle::Rectangle(Point<int> xy, int ww,int hh):Lines{ClosedLines},w(ww),h(hh)
 {
     if(w<=0||h<=0)
          error("Ошибка, неположительная сторона");
    Lines::add_point(xy);
 }

 Rectangle::Rectangle(Point<int> lt, Point<int> rb): Lines{ClosedLines},w(rb.x-lt.x),h(rb.y-lt.y)
 {
     if(h<=0||w<=0)
         error("Ошибка : первая точка не верхняя левая");
     Lines::add_point(lt);

 }

 void Rectangle::draw()
 { Shape::draw();
     if(fill_color().visibility()){
             fl_color(fill_color().as_int());
             fl_rectf(point(0).x,point(0).y,w,h);
 }
     if(color().visibility())
     {
      fl_color(color().as_int());
      fl_rect(point(0).x,point(0).y,w,h);
     }
 }
