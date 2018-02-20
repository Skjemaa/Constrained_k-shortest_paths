#include "ConstrainedArc.hpp"

ConstrainedArc::ConstrainedArc(int s, int d, double w, int t){
   
   this->source=s;
   this->destination = d;
   this->weight = w;
   this->delay = t;
   
}

ConstrainedArc::~ConstrainedArc(){}
