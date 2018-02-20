# pragma once
#include<utility>
#include<limits.h>
#include<stdio.h>
#include <iostream>
#include <set>
#include<vector>
#include "Arc.hpp"
#include "Graph.hpp"




class Dijkstra{

   public :
   
   Dijkstra(std::vector<double> dist, std::vector<int> prev);
   ~Dijkstra();
   void ShortestPath(Graph g, int source);
   
   
   std::vector<double> distance;
   std::vector<int> previous;
   
   };
