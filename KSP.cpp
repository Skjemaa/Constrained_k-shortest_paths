#include<stdio.h>
#include<limits.h>
#include <iostream>
#include <set>
#include <vector>
#include <utility> // for pair
#include "KSP.hpp"
#include "Arc.hpp"
#include <list>




KSP::KSP(std::vector<std::vector<int> > AA){
   
   this->A = AA;
   
}

   void KSP::ShortestPaths (Graph g, int s, int t , int k){
   int n = g.graph.size();
   double max_weight = 100000;
  
   
   // graph1 is a duplicate of g.graph
   std::vector<std::vector<Arc> > graph1;
   graph1.resize(n);
   for(int i =0;i<n;i++){
      for (std::vector<Arc >::iterator p = g.graph[i].begin(); p
               != g.graph[i].end();++p) {
         
         Arc b (p->source,p->destination,p->weight);
         graph1[i].push_back(b);
      }
   }
   
   
   std::set<std::pair<double,std::vector<int> > > B;
   
   // Calculating A[0] par dijsktra
   std::vector<double> dist;
   std::vector<int> prev;
   Dijkstra d(dist,prev) ;
   d.ShortestPath(g,s);
   std::list<int> L;
   std::vector<int> V;
   int u = t;
     while (d.previous[u]!=-1 && d.previous[u]!=u){
         L.push_front(u);
         u = d.previous[u];
      }
      V.push_back(s);
      for (std::list<int >::iterator p = L.begin(); p
               != L.end();++p) {
         V.push_back(*p);
      }
    this->A.push_back (V);
    
    
    
    
    // Calculating A[k], k>0
    
    for (int q=1;q<k+1;q++){
       
       
       
       
       
       for(int i =0;i<this->A[q-1].size()-1;i++){
        
          int spurNode = this->A[q-1][i];
          std::vector<int> rootPath;
          for(int j =0;j<i+1;j++){
             rootPath.push_back(this->A[q-1][j]);
          }
          
          
          for (int p=0;p<q;p++){
             bool same=true;
             if (A[p].size() < i+1){
                same = false;
             }
             else{
                for(int j =0;j<i+1;j++){
                    if(A[p][j]!=rootPath[j]){
                    same=false;
                     }
                 }
              }
              
             if(same && A[p].size()>i+1){
                for(int z =0;z<g.graph[spurNode].size();z++){
                   if(g.graph[spurNode][z].destination==A[p][i+1]){
                      g.graph[spurNode][z].weight = max_weight;
                   }
                }
             }
          }
          
          
          for(int j =0;j<i;j++){
             for(int z =0;z<g.graph[rootPath[j]].size();z++){
                g.graph[rootPath[j]][z].weight=max_weight;
             }
             
          }
          
          
          
          
          // Calculate the spurPath
          std::vector<double> dist1;
          std::vector<int> prev1;
          Dijkstra d1(dist1,prev1) ;
          d1.ShortestPath(g,spurNode);
          std::list<int> L1;
          std::vector<int> spurPath;
          int u = t;
          while (d1.previous[u]!=-1 && d1.previous[u]!=u){
               
               L1.push_front(u);
               u = d1.previous[u];
          }
          
          
      
          for (std::list<int >::iterator p = L1.begin(); p
                     != L1.end();++p) {
               spurPath.push_back(*p);
           }
           
           // total Path calculation
           std::vector<int> totalPath;
           for(int j =0;j<i+1;j++){
              totalPath.push_back(rootPath[j]);
              
           }
           for(int j =0;j<spurPath.size();j++){
              totalPath.push_back(spurPath[j]);
              
           }
           
           
           //adding totalPath to B
           double cost=0;
             for(int u =0;u<totalPath.size()-1;u++){
                for(int z =0;z<graph1[totalPath[u]].size();z++){
                   if(graph1[totalPath[i]][z].destination==totalPath[u+1]){
                      cost += graph1[totalPath[u]][z].weight;
                   }
                }
             }
             if (totalPath[0]==s && totalPath[totalPath.size()-1]==t){
             B.insert(std::make_pair(cost,totalPath));
          }
                         
                         
                         
                         
            //restoring
           for (int p=0;p<q;p++){
              for(int z =0;z<g.graph[spurNode].size();z++){
                   if(g.graph[spurNode][z].destination==A[p][i+1]){
                      g.graph[spurNode][z].weight = graph1[spurNode][z].weight;
                   }
                }
             }
             for(int j =0;j<i;j++){
               for(int z =0;z<g.graph[rootPath[j]].size();z++){
                  g.graph[rootPath[j]][z].weight=graph1[rootPath[j]][z].weight;
               }
             }
             
             
             
              
          }
             
          
           
             
             //if B empty...
             if(B.empty()){
                break;
             }
            
             std::set<std::pair<double,std::vector<int> > >::iterator p =
                   B.begin();
              
             this->A.push_back(p->second);
              
             B.erase(p);
             
            
             
          
          
                  
                
   
   
   
   
   }
}
   
   
   
   
   

KSP::~KSP(){}
