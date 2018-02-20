
#include <iostream>
#include <list>
#include<stdio.h>
#include<vector>
#include "ConstrainedArc.hpp"
#include "ConstrainedGraph.hpp"
#include "Constrained.hpp"

int main(int argc, char** argv) {
   int n = 0;
   int m = 0;
   int k = 0;
   int p = 0;
   int T = 0;
   
   std::cin >> n;
   std::cin >> m;
   std::cin >> k;
    std::cin >> p;
    std::cin >> T;
   for (int i = 0;i<n;i++){
      std::cin >> p;
      
   }
   
   std::vector<std::vector<ConstrainedArc> > graph ;
   graph.resize(n);
   
   
   for (int i = 0;i<m;i++){ 
      int s;
      int t;
      double w ;
      std::cin >> s;
       
      std::cin >> t;
      std::cin >> w;
       std::cin >> p;
       
      ConstrainedArc a (s-1,t-1,w,p);
      
      
      
      graph[s-1].push_back(a);
      
      
   }
   int s = 0;
   int t = n-1;
   ConstrainedGraph g (graph);
   std::vector<double> dist;
   std::vector<int> prev;
   Constrained d(dist,prev) ;
   d.ShortestPath(g,0,t,T);
   
   std::cout<<d.distance[n-1]<<std::endl;
   int u = t;
   if (d.previous[t]==-1){
      std::cout<<"Pas de de chemin de "<<s+1<<" a "<<t+1<<std::endl;
   }
   else {
      
      std::list<int> L;
      while (d.previous[u]!=-1 && d.previous[u]!=u){
         L.push_front(u+1);
         u = d.previous[u];
      }
      std::cout<<s+1;
      for (std::list<int >::iterator p = L.begin(); p
               != L.end();++p) {
         std::cout<<"->"<<*p;
      }
   }
         
      
   
   
   
}
