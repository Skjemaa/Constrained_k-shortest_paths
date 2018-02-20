#include "ConstrainedGraph.hpp"
#include "ConstrainedArc.hpp"

#include<vector>

ConstrainedGraph::ConstrainedGraph(std::vector<std::vector<ConstrainedArc> > g){
   
   this->graph = g;
}



ConstrainedGraph::~ConstrainedGraph(){}
   


