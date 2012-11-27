 #ifndef __rgp_rst_h__
 #define __rgp_rst_h__

#include<stdlib.h>
#include<stdio.h>

#include <sys/types.h>

class roadscoretable
{
  
  public:                       // list has to travesrsed in quick mode for computing param array
  
   struct rst
   {
     u_int32_t roadid;
     double timestamp;                        // exit time of vehicle which sent packet after a road segment
     double ltimeonroad;  
     bool exception;   
     struct rst* next;
   };
  
   struct rst *temp1,*temp2,*head,*r;
   
  
   roadscoretable();

   ~roadscoretable();

   void display();
   

   void insert(u_int32_t rid,double tstamp,double tor,bool ex);
   
  double getlatesttime(u_int32_t rid);

  bool getexceptionstatus(u_int32_t rid);
 
  void setexceptionstatus(u_int32_t rid,bool value);

  u_int32_t getsize();
   

 
};
#endif
