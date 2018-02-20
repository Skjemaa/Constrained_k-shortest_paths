#include "Graph.hpp"
#include "Arc.hpp"

#include<vector>

Graph::Graph(std::vector<std::vector<Arc> > g){
   
   this->graph = g;
}



Graph::~Graph(){}
   


