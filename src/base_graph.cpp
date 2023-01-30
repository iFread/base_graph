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


//*****************************

void Shape:: draw()const{

      Fl_Color old=fl_color();
        fl_color(lcolor.as_int());
        fl_line_style(ls.style(),ls.width());
        draw_lines();
        fl_color(old);
        fl_line_style(0);
    }


 void Shape:: draw_lines()const{
     Vertex *w= this->v(); // no const
     for(;w->cv()!=v;w=w->cv())
     {
       fl_line(w->_x,w->_y,w->cv()->_x,w->cv()->_y);
     }


 }
}




