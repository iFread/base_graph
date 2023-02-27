 #ifndef BASE_TOOL_H_
#define  BASE_TOOL_H_

namespace Graph {
class Canvas;
  // intrface
class base_tool {

virtual void action(Canvas* p_can)=0;
};




class creat_tool:public base_tool
 {

};



class modify_tool:public base_tool {



};

}






#endif
