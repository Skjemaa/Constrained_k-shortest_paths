#include<utility>
#include<limits.h>
#include<stdio.h>
#include <iostream>
#include <set>
#include<vector>
#include "Arc.hpp"
#include "Graph.hpp"




class parallelDijkstra{

   public :
   
   parallelDijkstra(std::vector<double> dist, std::vector<int> prev);
   ~parallelDijkstra();
   void ShortestPath(Graph g, int source,int id, int p);
   
   
   std::vector<double> distance;
   std::vector<int> previous;
   
   };
