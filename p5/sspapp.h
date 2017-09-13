/*@brief sspapp.h
 * @author Kyle Kruskamp   
 * @date: May 18th 2016
 */

#ifndef __SSPAPP_H
#define __SSPAPP_H

#include <string>
#include "minpriority.h"
#include "graph.h"

using namespace std;

int main();

class SSPapp {
    
   public:
      void process();
      Graph nGraph;
};

#endif
