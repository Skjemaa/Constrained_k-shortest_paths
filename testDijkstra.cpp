
#include <iostream>
#include<list>
#include<stdio.h>
#include<vector>
#include "Arc.hpp"
#include "Graph.hpp"
#include "Dijkstra.hpp"

int main(int argc, char** argv) {
   int n = 0;
   int m = 0;
   int k = 0;
   int p = 0;
   
   std::cin >> n;
   std::cin >> m;
   std::cin >> k;
   for (int i = 0;i<2*k+n;i++){
      std::cin >> p;
      
   }
   
   std::vector<std::vector<Arc> > graph ;
   graph.resize(n);
   
   
   for (int i = 0;i<m;i++){ 
      int s;
      int t;
      double w ;
      std::cin >> s;
       
      std::cin >> t;
      std::cin >> w;
       std::cin >> p;
       
      Arc a (s-1,t-1,w);
      
      
      
      graph[s-1].push_back(a);
      
     
   }
   int t = n-1;
   int s = 0;
   
   Graph g (graph);
   std::vector<double> dist;
   std::vector<int> prev;
   Dijkstra d(dist,prev) ;
   d.ShortestPath(g,s);
   std::list<int> L;
   
   int u = t;
     while (d.previous[u]!=-1 && d.previous[u]!=u){
         L.push_front(u);
         u = d.previous[u];
      }
      std::cout<<s+1;
      for (std::list<int >::iterator p = L.begin(); p
               != L.end();++p) {
         std::cout<<"->"<<(*p)+1;
      }
   
   
}
