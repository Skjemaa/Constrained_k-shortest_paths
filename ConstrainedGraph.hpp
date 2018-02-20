#pragma once 
#include<utility>
#include<limits.h>
#include<stdio.h>
#include<vector>
#include "ConstrainedArc.hpp"


class ConstrainedGraph{

   public :
   
   ConstrainedGraph(std::vector<std::vector<ConstrainedArc> > g);
   ~ConstrainedGraph();
   
   
   
   std::vector<std::vector<ConstrainedArc> > graph;
   
   };
