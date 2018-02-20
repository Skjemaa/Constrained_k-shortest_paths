
#include <iostream>
#include <mpi.h>

#include<stdio.h>
#include<vector>
#include "Arc.hpp"
#include "Graph.hpp"
#include "parallelDijkstra.hpp"

int main(int argc, char** argv) {
   // Initialize MPI.
   MPI_Init(&argc, &argv);
   int id, p;
   
   
   // Get the number of processes.
   MPI_Comm_size(MPI_COMM_WORLD, &p);
   
   // Get the individual process ID.
   MPI_Comm_rank(MPI_COMM_WORLD, &id);
   
   int n = 0;
   int m = 0;
   int k = 0;
   int p1 = 0;
   if (id ==0){
      std::cin >> n;
      std::cin >> m;
      std::cin >> k;
      for (int i = 0;i<2*k+n;i++){
         std::cin >> p1;
      
      }
   }
   MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
   MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
   
   
   
   
   std::vector<std::vector<Arc> > graph ;
   graph.resize(n);
   
   
   std::cout<<"juste avant la lecture des arcs"<<std::endl;
   for (int i = 0;i<m;i++){ 
      
      int s;
      int t;
      double w ;
      if (id ==0){
         
         std::cin >> s;
         std::cin >> t;
         std::cin >> w;
         std::cin >> p1;
      }
      MPI_Bcast(&s,1,MPI_INT,0,MPI_COMM_WORLD);
      MPI_Bcast(&t,1,MPI_INT,0,MPI_COMM_WORLD);
      MPI_Bcast(&w,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
      
      Arc a (s-1,t-1,w);
      
      
      
      graph[s-1].push_back(a);
     
      
   }
   //std::cout<<id<< "lecture finie"<<std::endl;
   
   Graph g (graph);
   std::vector<double> dist;
   std::vector<int> prev;
   parallelDijkstra d(dist,prev) ;
   std::cout<<id<<std::endl;
   d.ShortestPath(g,0,id,p);
   for (int i =0;i<n;i++){
      if(id == i%p){
         
         std::cout<<id<<"   "<<d.distance[i]<<std::endl;
      }
   }
   
    MPI_Finalize();   
   
}
