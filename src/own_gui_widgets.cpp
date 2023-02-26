 #include "own_gui_widgets.h"


namespace Graph {

void Canvas::create(Point p, int w, int h){
loc=p;
w_=w;
h_=h;
    pw=new fl_canvas(p,w,h);
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
}
