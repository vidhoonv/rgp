 #ifndef __rgp_rtt_h__
 #define __rgp_rtt_h__

#include<stdlib.h>
#include<stdio.h>

#include <sys/types.h>
class roadtriptable
{
  
  private:

   struct rtt
   {
     u_int32_t roadid;
     double duration_timestamp;
     double exit_timestamp;     
     bool exception;
     struct rtt* next;
   };

   struct rtt *temp1,*temp2,*head,*r;
   

 public :

   roadtriptable();
   ~roadtriptable();

   void display();

   void insert(u_int32_t rid,double tstamp,double,bool);

//   double getentrytime(u_int32_t rid);
   double getexittime(u_int32_t rid);
   double getdurationonroad(u_int32_t rid);
   bool getexceptionstatus(u_int32_t rid);
   void setexceptionstatus(u_int32_t rid,bool value);


};

#endif


