#include<utility>
#include<limits.h>
#include<stdio.h>
#include <iostream>
#include <set>
#include<vector>
#include "ConstrainedArc.hpp"
#include "ConstrainedGraph.hpp"




class Constrained{

   public :
   
   Constrained(std::vector<double> dist, std::vector<int> prev);
   ~Constrained();
   void ShortestPath(ConstrainedGraph g, int s, int t,int limit);
   
   
   std::vector<double> distance;
   std::vector<int> previous;
   
   };
