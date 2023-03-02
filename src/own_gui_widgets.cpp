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

void Canvas::remove(Shape *sh){
 reference_to<fl_canvas>(pw).remove(sh);
}
void Canvas::set_parent(void *v) {

pw->user_data(v);
}


void Canvas::set_tool(cb_creating_t p)
{
    if(!(tl_ && tl_->type()==tool::creating_t))
    {      delete tl_;
        tl_=new creat_tool();
         }
    reference_to<creat_tool>(tl_).set_shape(p);
     pw->redraw();
}

void Canvas::set_tool(tool* tl){
if(tl_) delete tl_;
tl_=tl;
  }


// этапы создания  фигуры:
     /*
1. Создать фигуру в заданной точке          // левая кнопка мыши
2. Модифицировать ее до нужного состояния   // движение мыши, после создания фигуры
3. Передать в canvas или удалить    // левая кнопка мыши=зафиксировать состояние фигуры (и передать в canvas)
 // либо правая кнопка удаляет фигуру


*/

int Canvas::handle(int i){
 if(tl_) tl_->action(this,i);
//    switch (i)
//    {
//         //tool->action(this);
//    case FL_MOVE:

//      std::cout<< current.x()<<", "<<current.y()<<"\n";
//        break;
//    case FL_PUSH:
//           //t->action(this); =   void action(Canvas* c) { c.add(create({current})) }
//        break;

//    case FL_RELEASE:

//        break;

//    default:
//        std::cout<<"unknown event in Canvas : "<<i<<"\n";

//    }


 // отрисовку виджета следует выполнять по необходимости,
 // будет вызываться по результатам action()
 // так в режиме модификации вызывать при движении, в режиме ready_sh вызывать по нажатию
    pw->redraw();

    return i;
}
//***************************
//        switch (Fl::event_button())
//        {
//        case FL_LEFT_MOUSE:
//           std::cout<<"left mouse button pushed\n";
//            break;
//        case FL_RIGHT_MOUSE:
//            std::cout<<"right mouse button pushed\n";
//            break;

//        }


}
