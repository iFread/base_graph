 #include "own_gui_widgets.h"


namespace Graph {

void Canvas::create(Point p, int w, int h){
loc=p;
w_=w;
h_=h;
    pw=new fl_canvas(p,w,h);

// связь с родителем по умолчанию, можно переопределить
    pw->user_data(this); //
}

Widget & Canvas::create(){

    return *new Canvas(std::move(*this));

}




Fl_Widget & Canvas::content() {

    return reference_to<fl_canvas>(pw);
}


void Canvas::add(Shape *sh)
{
 reference_to<fl_canvas>(pw).add(sh);
 }

void Canvas::set_parent(void *v) {

pw->user_data(v);
}


void Canvas::set_tool(creating_t p)
{
    if(t)
        delete t;
    t=new creat_tool();
reference_to<creat_tool>(t).set_shape(p);
}

int Canvas::handle(int i){

    switch (i)
    {
         //tool->action(this);
    case FL_MOVE:
        std::cout<<"move mouse in Canvas\n"<<i<<"\n";
      std::cout<< current.x()<<", "<<current.y()<<"\n";
        break;
    case FL_PUSH:
           //t->action(this); =   void action(Canvas* c) { c.add(create({current})) }

        // current, точка относительно начала canvas
         // в функции Shape::draw() следует принимать точку начала отсчета, и масштаб виджета
       //
        add(reference_to<creat_tool>(t).create({current.x(),current.y()}));

        std::cout<<"push button in Canvas\n"<<i<<"\n";
        break;

    case FL_RELEASE:
        std::cout<<"Release button in Canvas\n"<<i<<"\n";
        break;

    default:
        std::cout<<"unknown event in Canvas\n";

    }
std::cout<<" \t"<<i<<"\n";
    return 1;

}


}
