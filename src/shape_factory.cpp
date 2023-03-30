 

#include "shape_factory.h"

namespace Graph {


Shape* Factory::create(Point p)
{
    switch (prod_type)
    {
    case sh_line_t:
        return new line(p,p);
    case sh_polyline_t:
    {   lines* ln=new lines(p);
       ln->add(p);
        return ln;
     } break;
    case sh_polygon_t:
    {  polygon *pl=new polygon(p);
      pl->add(p);
        return pl;
     }
     case sh_rectangle_t:
        return new rectangle(p,p);
     case sh_circle_t:
        return new circle(p,1);
    case sh_none_t:
    default:
        break;
    }
    return nullptr;
}


}