# pragma once
class ConstrainedArc{

   public:
   
   
   
   ConstrainedArc(int s, int d, double w, int t);
   ~ConstrainedArc();

   int source;
   int destination;
   double weight;
   int delay;
   
   };
