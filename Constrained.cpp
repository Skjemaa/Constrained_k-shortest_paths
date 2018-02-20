#include<stdio.h>
#include<limits.h>
#include <iostream>
#include <set>
#include <map>
#include <stack>
#include <utility> // for pair
#include "Constrained.hpp"


Constrained::Constrained(std::vector<double> dist, std::vector<int> prev){
   
   this->distance = dist;
   this->previous = prev;
}

   void Constrained::ShortestPath (ConstrainedGraph g, int s, int t,int
         limit){
   int n = g.graph.size();
   double max_weight = 100000;
   
   this->distance.resize(n,max_weight);
   this->previous.resize(n,-1);
   this->previous[s]=s;
   this->distance[s]=0;
   
   //Construire graph1, le graph inverse de graph
   std::vector<std::vector<ConstrainedArc> > graph1;
   graph1.resize(n);
   for(int i =0;i<n;i++){
      for (std::vector<ConstrainedArc >::iterator p = g.graph[i].begin(); p
               != g.graph[i].end();++p) {
         ConstrainedArc a(p->destination,p->source,p->weight,p->delay);
         graph1[p->destination].push_back(a);
      }
   }
   
   
   
     // initialiser visited
   std::map<std::pair< int,int> , double> visited;
   
   for (int i =0; i<limit; i++){
      visited.insert(std::make_pair( std::make_pair( s,i), 0));
   }
   for (int i =0; i<n; i++){
      if (i!=s){
      visited.insert(std::make_pair( std::make_pair( i,0), max_weight));
   }

   }
   
   
   
   
   
   std::stack<std::pair<int,int> > Q;
   Q.push(std::make_pair(t,limit));
   
   while (!Q.empty()){
      std::pair<int,int> u = Q.top();
      if (visited.count(u)>0){
	       Q.pop();
	   }
      else {
         if (u.second<0){
            visited.insert(std::make_pair(u,max_weight));
            Q.pop();
         }
         else{
            bool uCalculable = true;
          
         
            for (std::vector<ConstrainedArc >::iterator p = graph1[u.first].begin(); p
                  != graph1[u.first].end();++p) {
               std::pair<int,int> v = std::make_pair(p->destination,u.second-p->delay);
               if (visited.count(v)==0){
                   uCalculable = false;
                  Q.push(v);
               }
            }
         
         
            if (uCalculable){
               double min = max_weight;
               for (std::vector<ConstrainedArc >::iterator p = graph1[u.first].begin(); p
                  != graph1[u.first].end();++p) {
                  std::pair<int,int> v = std::make_pair(p->destination,u.second-p->delay);
                  double m = visited.at(v) + p->weight;
                  if (m<min){
                     this->previous[u.first] = v.first ;
                     min = m;
                  }
               }
            
            
               
               this->distance[u.first] = min ;
               visited.insert(std::make_pair(u,min));
            }
         }
      }
               
            
         
      
   
   }
   
   
}
   
   
   
   
   

Constrained::~Constrained(){}
