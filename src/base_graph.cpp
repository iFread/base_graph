#include "base_graph.h"


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
Vertex_list& Vertex_list:: operator=(const Vertex_list& cv)
{
    this->size_=cv.size_;
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
}

Vertex_list& Vertex_list::operator=(Vertex_list&& vl)
{int tmp_sz=size_;
       size_=vl.size_;
   vl.size_=tmp_sz;
  Vertex*tmp=ptr;
ptr=vl.ptr;
vl.ptr=tmp;
    return *this;
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
for(int i=1;i<v.size();i++) // перемещение
{
  fl_line(v[i-1]->x(),v[i-1]->y(),v[i]->x(),v[i]->y());
}

 }

 void line::draw_lines()const{
     Shape::draw_lines();
 }

}




