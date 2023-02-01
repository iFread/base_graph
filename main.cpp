#include <iostream>
#include "base_graph.h"
#include "window.h"


using namespace std;

int main()
{

{    Graph::window win({100,100},300,400,"test");
  //Graph::Shape* sh2=  new Graph::Shape;

        Graph::Point p={0,0};
          for(int i=0;i<200;i++)
          {
           int x_=rand()%600+1;
           int y=rand()%500+1;
           win.attach(Graph::line{p,{x_,y}});
           p={x_,y};

          }

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
  Graph::gui_run();

  //delete sh2;
    }

  return 0;

    }
