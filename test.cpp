
#include <iostream>
#include<map>
#include<stack>
#include <utility>
#include<stdio.h>
#include<vector>
#include "Arc.hpp"
#include "Graph.hpp"
#include "Dijkstra.hpp"

int main(int argc, char** argv) {
   std::stack<int > Q;
   Q.push(20);
   std::map<int, int> visited;
   visited.insert(std::make_pair(0,1));
   visited.insert(std::make_pair(1,1));
   
   
   while (!Q.empty()){
      int u = Q.top();
      if (visited.count(u)>0){
	Q.pop();
	}
	else{
	  bool ucalculable = true;
   for (int i =0;i<2;i++){
      int v = u-i-1;
	
	if (visited.count(v)==0) {
      ucalculable = false;
	   Q.push(v);
	  }
  }
  if (ucalculable){
     visited.insert(std::make_pair(u,visited.at(u-1)+ visited.at(u-2)));
     
	}

	}
}
	


   std::cout << visited.at(20);
   return 0;
}
