#include <iostream>
#include <set>
#include "experience.h"
experience::experience(){
   
   this->d = new std::vector<int>();
}
struct C
{
    bool operator()(const int &a, const int &b) const
    {
        return d[a] > d[b];
    }
};

int main() {
   d.push_back(1);
    d.push_back(3);
     d.push_back(2);
      d.push_back(5);
       d.push_back(4);
        d.push_back(8);
        d.push_back(7);
        d.push_back(9);
  

  std::set<int,C> Q ;
  Q.insert(5);
  Q.insert(4);
  Q.insert(1);
  Q.insert(6);
  Q.insert(2);
  int a = *Q.begin();
  std::cout<<a;
  Q.erase(Q.begin());
   a = *Q.begin();
  std::cout<<a;
  Q.erase(Q.begin());
   a = *Q.begin();
  std::cout<<a;
  Q.erase(Q.begin());
   a = *Q.begin();
  std::cout<<a;
  return 0;
}
 
