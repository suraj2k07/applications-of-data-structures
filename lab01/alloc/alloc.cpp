#include "alloc.h"

void alloc_measure( unsigned VSIZE_RANGE, unsigned REPEAT, std::map<unsigned,float>& m ) {
  ClockCounter time; 
  int n = 0;
  while(REPEAT>0){
    std::vector<int> v;
    n = 0;
    REPEAT--;
    for (int i=0;i<VSIZE_RANGE;i++){
      n+=1;
      time.start();
      v.push_back((1));
      m[n] += float(time.stop());
    }}
  for(auto c : m){
    m[c.second] /= REPEAT;
  }
}
