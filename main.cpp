#include <iostream>
#include <ctime>
#include <unistd.h>
#include "base_graph.h"
#include "window.h"


using namespace std;



int main()
{



srand(time(0));
  { Graph::window win({100,100},800,600,"test");
  //Graph::Shape* sh2=  new Graph::Shape;

        Graph::Point p={100,100};
        Graph::rectangle rec ({p.x()+100,p.y()+50},{p.x()+300,p.y()+300});
     win.attach(Graph::rectangle (p,{p.x()+100,p.y()+100}));
        //  Graph::lines ln{{p.x()+10,p.y()+10},{p.x()+100,p.y()+200}};
      // Graph::lines ln{{p.x()+10,p.y()+10}};

     /*   for(int i=0;i<3;i++)
          {
           int x_=rand()%600+1;
           int y=rand()%500+1;
           ln.add({x_,y});
           //p={x_,y};

          }*/
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
