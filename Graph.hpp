#pragma once 
#include<utility>
#include<limits.h>
#include<stdio.h>
#include<vector>
#include "Arc.hpp"


class Graph{

   public :
   
   Graph(std::vector<std::vector<Arc> > g);
   ~Graph();
   
   
   
   std::vector<std::vector<Arc> > graph;
   
   };
