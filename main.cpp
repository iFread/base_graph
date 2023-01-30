#include <iostream>
#include "base_graph.h"
#include "window.h"


using namespace std;

int main()
{
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
 sh->ccv()->trace(std::cout);
    return 0;
}
