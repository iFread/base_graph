#include <iostream>
#include <ctime>
#include <unistd.h>
#include "base_graph.h"
#include "window.h"
#include "math_primitives.h"

using namespace std;

using namespace::math;
void show_area(area_t ar)
{
    switch (ar)
    {
    case LEFT:
        std::cout<<"left";
        break;
    case RIGHT:
        std::cout<<"right";
        break;
    case INTER:
        std::cout<<"inter";
        break;
    case ORIGIN:
        std::cout<<"ORIGIN";
        break;
    case DESTINATION:
        std::cout<<"Destination";
        break;
    case BEYOND:
        std::cout<<"Beyond";
        break;

    case BEHIND:
        std::cout<<"BEHIND";
        break;

    default:
        std::cout<<"none";
    }
    std::cout<<"\n";
}

int main()
{
vector2d ln1(Point(6,6 ),Point(1,1));
//ln1.show(std::cout);
if(ln1.contain({5,5}))
{show_area(ln1.get_area(Point{1, 0}));
show_area(ln1.get_area(Point{7,7}));
show_area(ln1.get_area(Point{3,2}));
}
//if(ln1.separates(Point(3,30),Point(12,15)))
//    std::cout<<"separaters\n";

srand(time(0));
  { Graph::window win(Point{100,100},800,600,"test");
  //Graph::Shape* sh2=  new Graph::Shape;

      Point p={100,100};
        Graph::poligon rec ({p.x()+100,p.y()+50});//,{p.x()+300,p.y()+300});
     win.attach(Graph::rectangle (p,{p.x()+100,p.y()+100}));
        //  Graph::lines ln{{p.x()+10,p.y()+10},{p.x()+100,p.y()+200}};
      // Graph::lines ln{{p.x()+10,p.y()+10}};

        for(int i=0;i<5;i++)
          {
           int x_=rand()%600+1;
           int y=rand()%500+1;
           rec.add(Point (x_,y));
           //p={x_,y};

          }
  // win.attach(std::move(ln));
 win.attach(rec);

//sh2.trace(std::cout);
     /*
    Graph::window win(Graph::Point{100,100},100,100,"test");
    Graph::Shape sh;



    for(int i=0;i<100;i++)
    {
    sh.add({i,i+1});
    }
sh->x()=-50;
std::cout<<"point "<<sh[10].x()<<" "<<sh[10].y()<<"\n";
    sh.trace(std::cout);

    Graph::Shape sh2;
    sh2.add({1000,2000});
    sh2.add({2000,3000});
    sh2.add({-100,-200});
 //   sh->operator=(sh2->content());
 sh2.trace(std::cout);
 sh->ccv()->trace(std::cout);*/


  //delete sh2;

 Graph::gui_run();
  return 0;
}
    }
