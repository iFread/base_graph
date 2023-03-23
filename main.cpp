#include <iostream>
#include <ctime>
#include <unistd.h>
#include "base_graph.h"
#include "window.h"
#include "base_gui.h"
#include "math_primitives.h"
#include "group_widgets.h"
#include "own_gui_widgets.h"
#include "base_tools.h"
using namespace std;

using namespace::math;



void show_area(area_t ar);

void tst_rbtree();

int common_tests();

int main()
{

 // tst_rbtree();
     common_tests();
    return 0;
    }

int common_tests()
{  Graph::window win(Point{100,100},800,600,"test");

        Graph::HLayout ln({ 10,  70});

        Graph::VLayout vln({10,10});

      win.attach(ln);


      Graph::Scroll scrl({230,70},550,500);


       win.attach(scrl);

       scrl.attach(Graph::Canvas  ({150,50},1000 ,1000));

      ln.attach(Graph::VLayout ({10,210}));
       Graph::reference_to<Graph::VLayout>(&ln[0]).attach(Graph::Button({10,200},70,20,"line"));
       Graph::reference_to<Graph::VLayout>(&ln[0]).attach(Graph::Button({10,200},70,20,"polyline"));
        Graph::reference_to<Graph::VLayout>(&ln[0]).attach(Graph::Button({10,200},70,20,"rectangle"));
       Graph::reference_to<Graph::VLayout>(&ln[0]).attach(Graph::Button({10,200},70,20,"polygon"));
      Graph::reference_to<Graph::VLayout>(&ln[0]).attach(Graph::Button({10,200},70,20,"circle"));


      vln.attach(Graph::Button({0,10},70,20,"move+"));
      vln.attach(Graph::Button({0,10},70,20,"move-"));



       ln.attach(Graph::Button({ 0, 0},80,20,"transform")); //bt);
        ln.attach(vln);



      vln[0].callback([](Graph::Address,Graph::Address adr){
          Graph:: Canvas& p=Graph::reference_to<Graph::Canvas>(adr);
           //p.set_tool(Graph::get_line);
      p.move(10,10);
      },&scrl[0]);
      vln[1].callback([](Graph::Address,Graph::Address adr){
          Graph:: Canvas& p=Graph::reference_to<Graph::Canvas>(adr);
           //p.set_tool(Graph::get_line);
      p.move(-10,-10);
      },&scrl[0]);
      //vln.add(Graph::Button ({0,10},90,20,"hello2"));
      Graph::Layout& l=Graph::reference_to<Graph::Layout>(&ln[0]);

      Graph::Button& btn=Graph::reference_to<Graph::Button>(&ln[1]);

      btn.callback([](Graph::Address,Graph::Address adr){
          Graph:: Canvas& p=Graph::reference_to<Graph::Canvas>(adr);
      p.set_tool(new Graph::transform_tool(&p));
      },&scrl[0]);

      l[0].callback([](Graph::Address,Graph::Address adr){
            Graph:: Canvas& p=Graph::reference_to<Graph::Canvas>(adr);
        p.set_tool( Graph::get_line);
      //p.move(-10,-10);
      },&scrl[0]);
      l[1].callback([](Graph::Address,Graph::Address adr){
            Graph:: Canvas& p=Graph::reference_to<Graph::Canvas>(adr);
        p.set_tool( Graph::get_polyline);
      //p.move(-10,-10);
      },&scrl[0]);


      //Graph::reference_to<Graph::Layout>(&ln[0])[1].
       l[2].callback([](Graph::Address,Graph::Address adr){
        Graph:: Canvas& p=Graph::reference_to<Graph::Canvas>(adr);
        //p.move(10,10);
       p.set_tool(Graph::get_rectangle);
       //p.content().redraw();
       },&scrl[0]);

       l[3].callback([](Graph::Address,Graph::Address adr){
        Graph:: Canvas& p=Graph::reference_to<Graph::Canvas>(adr);
        //p.move(10,10);
       p.set_tool(Graph::get_polygon);
       //p.content().redraw();
       },&scrl[0]);
       l[4].callback([](Graph::Address,Graph::Address adr){
        Graph:: Canvas& p=Graph::reference_to<Graph::Canvas>(adr);
        //p.move(10,10);
       p.set_tool(Graph::get_circle);
       //p.content().redraw();
       },&scrl[0]);




       return    Graph::gui_run();




}


void tst_rbtree()
{ using namespace Graph ;

    window win(Point {100.,100.},800,600,"test rbtree");
    Graph::Scroll scrl({230,70},550,500);
     win.attach(scrl);
     scrl.attach(Graph::Canvas  ({150,50},1000 ,1000));
Canvas &can= reference_to<Canvas>(&scrl[0]);

Point p1={10,10};
for(int i=0;i<1000;i++)
{
    can.add(new rectangle(p1,{p1.x()+20,p1.y()+30}));
    p1={p1.x()+22,p1.y()};
   if(i&& i%50==0)
      p1={10,p1.y()+50};
}
can.set_tool(new transform_tool(&can));

int res= Graph::gui_run();
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


