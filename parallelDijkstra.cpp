#include<stdio.h>
#include<limits.h>
#include <iostream>
#include <set>
#include <utility> // for pair
#include "parallelDijkstra.hpp"
#include "Arc.hpp"
#include <mpi.h>

parallelDijkstra::parallelDijkstra(std::vector<double> dist, std::vector<int> prev){
   
   this->distance = dist;
   this->previous = prev;
}

void parallelDijkstra::ShortestPath (Graph g, int source,int id, int p){
   
   
   
   double  max_weight = 100000;
   int n = g.graph.size();
   
   
   bool visited[n];
   for (int i =0;i<n;i++){
      visited[i]=false;
   }
   
   
   this->distance.resize(n,max_weight);
   this->previous.resize(n,-1);
   this->previous[source] = source;
   this->distance[source]=0;
   
   
   
   // Calcul de delta0
   double delta0 [n];
   for(int i =0; i<n ; i++){
      double minDelta0 = max_weight;
      for (std::vector<Arc >::iterator j = g.graph[i].begin(); j
            != g.graph[i].end();++j) {
         if (j->weight < minDelta0){
            minDelta0 = j->weight;
         }
      }
      delta0[i]=minDelta0;
   }
   
   // initialisation de ind : le tableau qui a chaque point assicie un processeur
   int ind [n];
   for(int i =0; i<n ; i++){
      ind[i] = i%p;
   }
   //delta0 et ind ont ete calcule par tous le monde
   
   // initialisation de Q et QQ (QQ a ete nommee Q* dans la reference)
   std::set<std::pair<double,int> > Q;
   std::set<std::pair<double,int> > QQ;
   //std::cout<<id<<std::endl;
   if ( id == ind[source] ){
      Q.insert(std::make_pair(0,source));
      std::pair<double,int> pai = std::make_pair(0,source);
      QQ.insert(std::make_pair(delta0[source],source));
   }
   
   int enter; 
   int enterLocal;
   if(!Q.empty()){
      enterLocal =1;  
   }
   if(Q.empty()){
      enterLocal=0;  
   }
   //MPI_Wait(&request, &status);
   MPI_Reduce(&enterLocal, &enter, 1, MPI_INT, MPI_SUM,0, MPI_COMM_WORLD);
   MPI_Bcast(&enter, 1, MPI_INT, 0, MPI_COMM_WORLD);
   std::cout<<id<<" apres barrier"<<std::endl;
   
   
   
   while(enter>0){
      std::cout<<id<<"    in the while boucle"<<std::endl;
      
      // Step 1
      double localL;
      localL = max_weight;
      std::cout<<localL<<std::endl;
      if (!QQ.empty()){
         localL = QQ.begin()->first;
         std::cout<<"proc "<<id<<" lit locL "<<localL<<std::endl;
      }
      
      double L ;
      MPI_Allreduce(&localL,&L,1,MPI_DOUBLE,MPI_MIN,MPI_COMM_WORLD);
      std::cout<<"L pro "<<id<<" "<<L<<std::endl;
      // Step 2
      std::vector<int> RLocal1;
      std::vector<double> RLocal2;
      
      std::cout<<id<<"    before the boucle"<<std::endl;
      if(!Q.empty()){
         std::cout<<id<<"    entre dans step2"<<std::endl;
         std::set<std::pair<double,int> > queue;
         queue =Q;
         
         for (std::set<std::pair<double,int> >::iterator z = queue.begin(); z
               != queue.end();++z) {
            
            std::cout<<id<<"    entre dans boucle for de step2"<<std::endl;
            std::cout<<"queue size "<<queue.size()<<std::endl;
            std::vector<Arc> arcVector;
            arcVector= g.graph[z->second];
            if (z->first<=L){
               for (std::vector<Arc >::iterator j = arcVector.begin(); j
                     != arcVector.end();++j) {
                  std::cout<<"pas encore de corruption"<<std::endl;
                  std::cout<<"arcVector size "<<arcVector.size()<<std::endl;
                  std::cout<<j->destination<<std::endl;
                  RLocal1.push_back(j->destination);
                  
                  std::cout<<"rloc1 size "<<RLocal1.size()<<std::endl;
                  
                  RLocal2.push_back(z->first + j->weight);
                  
                  
               }
               //std::cout<<"sort de la boucle if de la boucle for for de step 2"<<std::endl;
               
               Q.erase(z);  // a verifier : la modification de Q ->boucle 8alta ?
               std::cout<<id<<"    efface ds Q"<<std::endl;
               
               QQ.erase(std::make_pair(this->distance[z->second]+delta0[z->second],z->second));
               std::cout<<id<<"    efface ds QQ"<<std::endl;
            }
            
         }
         
      }
      
      
      //Sending the sizes of RLoclal to the root 
      int r = RLocal1.size();
      int RLocal1_tab [r];
      double RLocal2_tab [r]; //converting RLocal to tableau for easier MPI 
       for (int i =0;i<r;i++){
          RLocal1_tab[i]=0;
         RLocal2_tab[i]=0;
       }
      for (int i =0;i<r;i++){
         RLocal1_tab[i]=RLocal1[i];
         RLocal2_tab[i]=RLocal2[i];
      }
      std::cout<<id<<"    a construit les rlocstab"<<std::endl;
      
      
      int recvcounts1 [p];
      int RLocalSizes [p];
      
      for (int i =0;i<p;i++){
         recvcounts1[i]=1;
      }
      
      int displs1 [p];
      
      for (int i =0;i<p;i++){
         displs1[i]=i;
      }
      
      MPI_Gatherv(&r,1,MPI_INT,&RLocalSizes,recvcounts1,displs1,MPI_INT,0,MPI_COMM_WORLD);
      
      std::cout<<id<<"    a envoye r"<<std::endl;
      
      //Broadcasting these sizes to everyone 
      
      MPI_Bcast(&RLocalSizes,p,MPI_INT,0,MPI_COMM_WORLD);
      
      std::cout<<id<<"    a recu RLocalSizes"<<std::endl;
      for (int i = 0; i<p;i++){
         
         std::cout<<"RlocS "<<i<<" "<<RLocalSizes[i]<<std::endl;
      } 
      
      // Gathering all the RLocals
      
      int sum;
      sum = 0;
      int displs2 [p];
      for(int i =0;i<p;i++){
         displs2[i]=sum;
         sum = sum + RLocalSizes[i];
         
      }
      
      int R1 [sum];
      double R2 [sum];
      for (int i = 0; i<sum; i++){
       R1[i]=0;
       R2[i]=0;  
      }
      
      //MPI_Wait(&request, &status);
      //MPI_Barrier(MPI_COMM_WORLD);
      MPI_Gatherv(&RLocal1_tab,r,MPI_INT,&R1,RLocalSizes,displs2,MPI_INT,0,MPI_COMM_WORLD);
      //std::cout<<id<<"    a envoye rlocal1tab"<<std::endl;
      MPI_Gatherv(&RLocal2_tab,r,MPI_DOUBLE,&R2,RLocalSizes,displs2,MPI_DOUBLE,0,MPI_COMM_WORLD);
      //std::cout<<id<<"    a envoye rlocal2tab"<<std::endl;
      
      // broadcating R1 and R2
      MPI_Bcast(&R1, sum, MPI_INT, 0, MPI_COMM_WORLD);
      MPI_Bcast(&R2, sum, MPI_DOUBLE, 0, MPI_COMM_WORLD);
      
      //std::cout<<id<<"    a recu r1 et r2 "<<R1[0]<<std::endl;
      for (int i = 0; i<sum; i++){
         std::cout<<R2[i]<<" ";
      }std::cout<<std::endl;
      
      std::vector<double> BLocal;
      
      for (int i = 0; i<sum; i++){
         if(ind[R1[i]]==id){
            BLocal.push_back(R2[i]);  
         }
      }
      /*std::cout<<"Bloc "<<BLocal.size()<<std::endl;
      for (int i = 0; i<BLocal.size();i++){
       std::cout<<BLocal[i]<<std::endl ;
      }*/
      
      //step 5 :
      MPI_Barrier(MPI_COMM_WORLD);
      for (int i = 0 ; i<BLocal.size(); i++){
         double x = BLocal[i];
         if (this->distance[i]>x){
            Q.erase(std::make_pair(this->distance[i],i));
            QQ.erase(std::make_pair(this->distance[i]+delta0[i],i));
            
            this->distance[i]=x;
            
            Q.insert(std::make_pair(this->distance[i],i));
            QQ.insert(std::make_pair(this->distance[i]+delta0[i],i));
         }
      }
      
      if(!Q.empty()){
         enterLocal =1;  
      }
      MPI_Allreduce(&enterLocal, &enter, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
      
      std::cout<<enter<<std::endl;
   }
}





parallelDijkstra::~parallelDijkstra(){}

