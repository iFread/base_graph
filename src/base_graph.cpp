#include "base_graph.h"
#include <typeinfo>

namespace Graph {

// добавляем к последней вершине, перед собой
Node* Node::insert(Node*n){

    n->next_=this; // мы - следующая для добавляемой
    n->prev_=prev_;// а предыдущая - наша предыдущая

    prev_->next_=n; // для текушей последней - следующей будет n
    prev_=n; // для нас n будет предыдущей
    return n;


//    next_->prev_=n;
//    n->next_=next_;   //
//    n->prev_=this;
//     next_=n;
//     return n;

}
// удаление
Node* Node::remove()
{
prev_->next_=next_;
next_->prev_=prev_;
// свои указатели на себя
prev_=this;
next_=this;
return this;

}



Point Vertex_list::remove(int index)
{
  // если есть что удалять удаляем,
 index=(index>size()-1)?size()-1:index;
if(ptr)
 {
 Vertex*v= operator[](index);//->remove();
 Point r=v->content();
 delete v;
 size_--;
  return r;
  }
return {NAN,NAN};
}
//********************
Vertex_list::Vertex_list(const Vertex_list& cv){
for(int i=0;i<cv.size();++i){
   add(*cv[i]);
}

}
Vertex_list& Vertex_list:: operator=(const Vertex_list& cv)
{
      //remove();  // нужно удалить все существующие точки
   clear(); //
    for(int i=0;i<size();++i){
       add(*cv[i]);
     }

    return *this;
}


Vertex_list::Vertex_list(Vertex_list&& cv):ptr(cv.ptr),size_(cv.size_){
 // move ptr;
cv.ptr=nullptr;
cv.size_=0;
}

Vertex_list& Vertex_list::operator=(Vertex_list&& vl)
{
   if(this==&vl)
       return *this;

    int tmp_sz=size_;
       size_=vl.size_;
   vl.size_=tmp_sz;
  Vertex*tmp=ptr;
 ptr=vl.ptr;
vl.ptr=tmp;

    return *this;
}

void Vertex_list::clear()
{

  for(int i=size();i>0;--i){
    remove(i);
    }

}

Vertex_list::~Vertex_list()
{
clear();
}


void Vertex_list::add(Point p)
{if(ptr)
    {     ptr->insert(new Vertex(p));
        }
    else ptr=new Vertex(p);
     std::cout<<"insert "<<p.x()<<", "<<p.y()<<"\n";
                   size_++;
                  }

Vertex* Vertex_list::operator[](int i)
{
 int cnt=(i<size_)?i:size_;
 Vertex*w=ptr;

 while(cnt>0) // while(cnt--){}
 {
 w=w->cv();
 cnt--;
 }

    return w;}

  Vertex* Vertex_list::operator[](int i) const
{
     Vertex*w=ptr;
   int cnt=(i<size()-1)?i:size()-1;
   while(cnt > 0) // while(cnt--){}
        {
       w=w->cv();
       cnt--;
      }
   return w;
   }



//*****************************

  Shape& Shape:: operator=(Shape&& sh){
if(this==&sh)
    return *this ;
  v=std::move(sh.v);  // заберем данные
 lcolor=sh.lcolor;
 ls=sh.ls;
 fcolor=sh.fcolor;
 type_=sh.type_;
 return *this;
}

  Shape::line_type Shape:: type() const {return type_;}

void Shape:: draw()const{

      Fl_Color old=fl_color();
        fl_color(lcolor.as_int());
        fl_line_style(ls.style(),ls.width());
        draw_lines();
    //draw_lines()
        fl_color(old);
        fl_line_style(0);
    }

void Shape::add(Point p){
    v.add(p);
}

void Shape::remove(int index)
{
  index=(index>size()-1)?size()-1:index;
  v.remove(index);

}
void Shape::draw(Point o,int sc) const {

    Fl_Color old=fl_color();
      fl_color(lcolor.as_int());
      fl_line_style(ls.style(),ls.width());
      draw_lines(o,sc);
      fl_color(old);
      fl_line_style(0);
}


// здесь const  метод, он не может вызывать не константные методы
 void Shape:: draw_lines()const {

 // std::cout<<typeid (this).name()<<"\n";
for(int i=1;i<v.size();i++) // перемещение
{
  fl_line(v[i-1]->x(),v[i-1]->y(),v[i]->x(),v[i]->y());
}

 }

 void Shape:: draw_lines(Point p, int scale)const{

     for(int i=1;i<v.size();i++) // перемещение
     {
       fl_line(v[i-1]->x()*scale+p.x(), v[i-1]->y()*scale+p.y(), v[i]->x()*scale+p.x(),v[i]->y()*scale+p.y());
     }


 }



 void line::draw_lines()const{
 //    Shape::draw_lines();
     for(int i=1;i<v.size();i++) // перемещение
     {
       fl_line(v[i-1]->x(),v[i-1]->y(),v[i]->x(),v[i]->y());
     }
 }

 void line:: draw_lines(Point p, int scale)const{

     for(int i=1;i<v.size();i++) // перемещение
     {
       fl_line(v[i-1]->x()*scale+p.x(), v[i-1]->y()*scale+p.y(), v[i]->x()*scale+p.x(),v[i]->y()*scale+p.y());
     }
 }

 void line:: change( Point p, int i)
 {
     i=(v.size()<i)?v.size()-1:i;
 if(p.isValid())
     v[i]->change(p);
  }



//***************************lines
 void lines::draw_lines()const{
for(int b=1,e= (type_==close_line)?v.size():v.size()-1;b<=e;++b) // на последней вершине так же итерируемся
{
if(type_==close_line && b==e ) {
    fl_line(v[0]->x(),v[0]->y(),v[b-1]->x(),v[b-1]->y());
    break;
}
fl_line(v[b-1]->x(),v[b-1]->y(),v[b]->x(),v[b]->y());
 }
 }

 void lines::draw_lines(Point p, int sc)const{
for(int b=1,e= (type_==open_line)?v.size():v.size();b<e;) // на последней вершине так же итерируемся
{
    std::cout<<v.size()<<" : "<<e<<"\n";

fl_line(v[b-1]->x()*sc+p.x(),v[b-1]->y()*sc+p.y(),v[b]->x()*sc+p.x(),v[b]->y()*sc+p.y());
++b;
//if(b==e)
//    break;
}
 }
 void lines:: change( Point p,int i)
 {
  // i=(v.size()-1<i)?v.size() :i;
   if(i==-1) {
        i=size()-1 ;
      }
   if(p.isValid())
      v[i]->change(p);

 }




 //******************
 rectangle::rectangle(Point a,Point b,line_type tp):Shape(a,tp)
{ // добавляет еще три вершины
 Shape::add({b.x(),a.y()});
 Shape:: add(b);
 Shape::add({a.x(),b.y()});
}
 void rectangle::draw_lines() const
 {    std::cout<<typeid (this).name()<<"\n";
    std::cout<<"size is "<<v.size()<<"\n";
     for(int b=1,e=  v.size()+1;b<=e;++b) // на последней вершине так же итерируемся
     {
     if(b==e ) {
         fl_line(v[0]->x(),v[0]->y(),v[b-1]->x(),v[b-1]->y());
         break;
     }
     fl_line(v[b-1]->x(),v[b-1]->y(),v[b]->x(),v[b]->y());
     std::cout<<"iteration\n";
     }

 }
void rectangle::draw_lines(Point p,int sc) const {

    for(int b=1,e=  v.size()+1;b<=e;++b) // на последней вершине так же итерируемся
    {
    if(b==e ) {
        fl_line(v[0]->x()*sc+p.x(),v[0]->y()*sc+p.y(),v[b-1]->x()*sc+p.x(),v[b-1]->y()*sc+p.y());
        break;
    }
    fl_line(v[b-1]->x()*sc+p.x(),v[b-1]->y()*sc+p.y(),v[b]->x()*sc+p.x(),v[b]->y()*sc+p.y());

 }
}

void rectangle:: change( Point p,int i)
{ // сохранить инвариант прямоугольника
   // для этого нужна вершина диагональная данной
i=(v.size()<i)?v.size():i;
v[i]->change(p);// меняем нужную вершину
Vertex* cross=v[i]->ccv()->ccv();//->content(); // соординаты противоположной точки
 // для импользования move operator, всеравно вызывать конструктор
// v= rectangle(*cross,*v[i]).v ;
int w=v[i]->x()-cross->x();//(v[i]->content()<cross)?v[i]->x()-cross.x():v[i]->x()-cross.x();
 int h=v[i]->y()-cross->y();
// меняем остальные фигуры
 cross->ccv()->change({cross->x(),cross->y()+h});
 cross->cv()->change({cross->x()+w,cross->y()});
}


 //******************* poligon


 void poligon::add(Point o){
//Здесь проверить что новые грани не пересекают уже существующие
     Shape::add(o);

 }

 void poligon::change( Point p,int i) {

    lines:: change(p,i);

 }

}




