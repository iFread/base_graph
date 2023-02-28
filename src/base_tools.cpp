 #include "base_tools.h"


namespace Graph {


void creat_tool::set_shape(creat_ptr ptr) {
create=ptr;
}


Shape* get_line(Point p){

    return new line(p,{p.x()+100,p.y()+100});
}

}
