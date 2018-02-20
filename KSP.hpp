#include<utility>
#include<limits.h>
#include<stdio.h>
#include <iostream>
#include <set>
#include<vector>
#include "Arc.hpp"
#include "Graph.hpp"
#include "Dijkstra.hpp"




class KSP{

   public :
   
   KSP(std::vector<std::vector<int> > AA);
   ~KSP();
   void ShortestPaths(Graph g, int s,int t, int k);
   
   
   
   std::vector<std::vector<int> > A;
   
   };
