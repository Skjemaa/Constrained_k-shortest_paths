#include<stdio.h>
#include<limits.h>
#include <iostream>
#include <set>
#include <utility> // for pair
#include "Dijkstra.hpp"
#include "Arc.hpp"

Dijkstra::Dijkstra(std::vector<double> dist, std::vector<int> prev){
   
   this->distance = dist;
   this->previous = prev;
}

   void Dijkstra::ShortestPath (Graph g, int source){
   int n = g.graph.size();
   bool visited[n];
   
   for (int i =0;i<n;i++){
      visited[i]=false;
   }
   std::set<std::pair<double,int> > Q;
   this->distance.resize(n,100000);
   this->previous.resize(n,-1);
   this->previous[source]=source;
   
   
   this->distance[source]=0;
   
   Q.insert(std::make_pair(0,source));
   
   while(!Q.empty()){
      double d = Q.begin()->first;
      int u = Q.begin()->second;
      Q.erase(Q.begin());
      if (!visited[u]){
         visited[u]=true;
         
         for (std::vector<Arc >::iterator p = g.graph[u].begin(); p
               != g.graph[u].end();++p) {
            int v = p->destination;
            if(!visited[v]){
               double w = p->weight;
               double alt = this->distance[u]+w;
               if(alt<this->distance[v]){ //amelioration
                  Q.erase(std::make_pair(this->distance[v],v));
                  this->distance[v]=alt;
                  this->previous[v]=u;
                  Q.insert(std::make_pair(alt,v));
               }
            }
         }
      }
   }
}
   
   
   
   
   

Dijkstra::~Dijkstra(){}
