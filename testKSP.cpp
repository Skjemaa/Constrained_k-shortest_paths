
#include <iostream>

#include<stdio.h>
#include<vector>
#include "Arc.hpp"
#include "Graph.hpp"
#include "KSP.hpp"

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
   
   Graph g (graph);
   std::vector<std::vector<int> > AA;
   KSP d(AA) ;
   d.ShortestPaths(g,0,n-1,4);
                       


   for (int i =0;i<d.A.size();i++){
      for (int j =0;j<d.A[i].size();j++){
	     if(j==0){
		  std::cout<<d.A[i][0]+1;
	        }
	     else {
		  std::cout<<"->"<<d.A[i][j]+1;
	     }
	    }
	std::cout<<std::endl;
   }
   
}
