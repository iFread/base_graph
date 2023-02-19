#include <iostream>
#include <ctime>
#include <unistd.h>
#include "base_graph.h"
#include "window.h"
#include "base_gui.h"
#include "math_primitives.h"
#include "group_widgets.h"

using namespace std;

using namespace::math;
void show_area(area_t ar);
int main()
{


  //Graph::Widget wg;

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
  //Graph::Button bt1({10,10},70,20,"hello");
  // Graph::Button bt2({10,30},70,20,"hello");
  Graph::HLayout ln({200,200});
//Graph::Out_Box({200,200},70,20,"hello2"));
//  Graph::VLayout vln({10,10});
//win.attach(bt1);
//win.attach(bt2);
win.attach(ln);
//win.attach(vln);
//ln.add()
ln.attach(Graph::VLayout ({10,10}));
Graph::reference_to<Graph::VLayout>(&ln[0]).attach(Graph::Button({0,10},70,20,"hello1"));
Graph::reference_to<Graph::VLayout>(&ln[0]).attach(Graph::Button({0,10},70,20,"hello2"));



ln.attach(Graph::Button({ 0, 0},70,20,"hello3")); //bt);
ln.attach(Graph::Button({ 0, 0},70,30,"hello4")); //bt);
ln.attach(Graph::Button({ 0, 0},70,30,"hello5")); //bt);




//vln.add(Graph::Button ({0,10},90,20,"hello2"));
Graph::reference_to<Graph::Layout>(&ln[0])[0].callback(//tach(Graph::Button({0,10},70,20,"hello"));
[](Graph::Address,Graph::Address adr){
  Graph:: Layout& p=Graph::reference_to<Graph::Layout>(adr);
    p.move(20,20);
   // win.redraw();
},&ln);
Graph::reference_to<Graph::Layout>(&ln[0])[1].callback([](Graph::Address,Graph::Address adr){
  Graph:: Layout& p=Graph::reference_to<Graph::Layout>(adr);
    p.move(-20,-20);
   // win.redraw();

},&ln);

//for(int i=0;i<10;++i) {
//sleep(1);
//ln[0].move((ln.position()+10).x(),(ln.position()+10).y());
//win.redraw();
//}

//ln.add(Graph::line({199,100},{200,200}));
// win.attach(bt);
 //win.attach(Graph::Out_Box({200,200},70,20,"hello2"));
     //Graph::Widget* ptr=&bt;

  //   std::cout<<bt.get_int()<<"\n";
    // bt.callback([](Graph::Address,Graph::Address adr){
     //    std::cout<<"bye_bye\n";reinterpret_cast<Graph::window*>(adr)->hide();},&win);
//    Point p={100,100};
//      Graph::poligon rec ({p.x()+100,p.y()+50});//,{p.x()+300,p.y()+300});
//     win.attach(Graph::rectangle (p,{p.x()+100,p.y()+100}));

//        for(int i=0;i<5;i++)
//          {
//           int x_=rand()%600+1;
//           int y=rand()%500+1;
//           rec.add(Point (x_,y));
//           //p={x_,y};
//          }
// win.attach(std::move(rec));

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


