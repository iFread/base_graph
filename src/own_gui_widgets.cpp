 #include "own_gui_widgets.h"


namespace Graph {

Canvas:: ~Canvas() {
    if(tl_) delete tl_;
       for(Shape*p: vec)
         delete p;

}


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
    vec.push_back(sh);
// reference_to<fl_canvas>(pw).add(sh);
 }

void Canvas::remove(Shape *sh){


    for(size_t i=0;i<vec.size();++i)
 {
   if(sh==vec[i])
     {
        *vec.erase(vec.begin()+i);
       delete sh;
       break;
      }
 }
   // reference_to<fl_canvas>(pw).remove(sh);
}
void Canvas::set_parent(void *v) {

pw->user_data(v);
}

Shape& Canvas::operator[](int i)
{
   // return reference_to<fl_canvas>(pw)[i];
    return *vec[i] ;
}

void Canvas::draw()const
{
    // здесь передается реальная позиция fl_canvas, т.к. смещение позиции может быть по Fl_scroll
     //  в дальнейшем подумать, как передавать позицию pw, в loc, помещенного в Scroll контейнера
   for(size_t i=0;i<vec.size();++i)
     vec[i]->draw(Point(pw->x(),pw->y()));//reference_to<>position());
if(tl_) tl_->draw(loc);
 //   std::cout<<"Draw Canvas calling\n";
}

size_t Canvas::count()const
{
    return vec.size();
    //return reference_to<fl_canvas>(pw).count();
}

void Canvas::set_tool(cb_creating_t p)
{
    if( tl_ )
   {   if(tl_->type()!=tool::creating_t)
     {
       delete tl_;
     tl_=new creat_tool();
     }
    } else
        tl_=new creat_tool();

    reference_to<creat_tool>(tl_).set_shape(p);
     pw->redraw();
}

void Canvas::set_tool(tool* tl){
if(tl_) {delete tl_; }
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
 // по ссылке удобнее: it(tl_)tl_-action(*this,i)
    if(tl_) tl_->action(this,i);
// Подумать :1. если canvas будет выбирать tool который устанавливается в данный момент???
    // 2.canvas содержит стек tool = после создания фигуры (creat_tool), в стек добавляется transform_tool
    // после завершения модификации убираем transform_tool
    // transform_tool так же может иметь различия по изменениям фигур,
    // например в полигон можно добавить вершину, в прямоугольник нельзя,
        //  для изменения класса фигур отдельная функция: transform_to() // варианты трансформирования (прямоугольник - полигон, или ломанная)
     // окружнось- элипс/ элипс- окружность(с явным выбором центра)// окружность- дуга окружности, и т.д.

 // отрисовку виджета следует выполнять по необходимости,
 // будет вызываться по результатам action()
 // так в режиме модификации вызывать при движении, в режиме ready_sh вызывать по нажатию
   //  pw->redraw();

    return i;
}



}
