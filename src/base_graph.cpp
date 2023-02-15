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



Vertex* Vertex_list::remove()
{
  // если есть что удалять удаляем,
 if(ptr)
     return  (Vertex*)ptr->prev()->remove();
 return nullptr;
}
//********************
Vertex_list::Vertex_list(const Vertex_list& cv){
for(int i=0;i<cv.size();++i){
   add(*cv[i]);
}

}
Vertex_list& Vertex_list:: operator=(const Vertex_list& cv)
{
  //  this->size_=cv.size_;
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
    Vertex*p=ptr->ccv();
    while (p!=ptr)
    {
     delete p->remove();
  p=ptr->ccv();
    }
  delete ptr;

ptr=nullptr;
}

Vertex_list::~Vertex_list()
{
//    Vertex *p=ptr->ccv();
  if(ptr) {
    Vertex*p=ptr->ccv();
    while (p!=ptr)
    {
     delete p->remove();
  p=ptr->ccv();
    }
  delete ptr;
 }}


void Vertex_list::add(Point p)
{if(ptr)
         ptr->insert(new Vertex(p));
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
   int cnt=(i<size())?i:size();
//  std::cout<<"cnt = "<<cnt<<"\n";
   while(cnt > 0) // while(cnt--){}
        {

    w=w->cv();
cnt--;
     }
 //std::cout<<"cnt = "<<cnt<<"\n";

 //  std::cout<<"w = "<<w->x()<<", "<<w->y()<<"\n";
   return w;
   }



//*****************************

void Shape:: draw()const{

      Fl_Color old=fl_color();
        fl_color(lcolor.as_int());
        fl_line_style(ls.style(),ls.width());
        draw_lines();

        fl_color(old);
        fl_line_style(0);
    }

// здесь const  метод, он не может вызывать не константные методы
 void Shape:: draw_lines()const {
     //const  Vertex * w=v->v(); // no const
//     for(;v->v();)//;v->cv()!=v->v();w=w->cv())
//     {
//       fl_line(w->_x,w->_y,w->cv()->_x,w->cv()->_y);
//     }
 //* * * *
  std::cout<<typeid (this).name()<<"\n";
for(int i=1;i<v.size();i++) // перемещение
{
  fl_line(v[i-1]->x(),v[i-1]->y(),v[i]->x(),v[i]->y());
}

 }

 void line::draw_lines()const{
 //    Shape::draw_lines();
     for(int i=1;i<v.size();i++) // перемещение
     {
       fl_line(v[i-1]->x(),v[i-1]->y(),v[i]->x(),v[i]->y());
     }
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

 //******************
 rectangle::rectangle(Point a,Point b):Shape(a)
{ // добавляет еще три вершины
add({b.x(),a.y()});
add(b);
add({a.x(),b.y()});
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

 //******************* poligon


 void poligon::add(Point o){
//Здесь проверить что новые грани не пересекают уже существующие
     Shape::add(o);

 }

}




