/*

	ROAD  TRIP TABLE 
file contains class to simulate internal memory of a node
to support the operation of the protocol
*/

#include "rgp_rtt.h"

//Constructor
   roadtriptable::roadtriptable()
   {
     head=(struct rtt *)malloc(sizeof(struct rtt));
     head->roadid=0;   // head is header node. head->roadid gives no of nodes in the table
     head->next=NULL;
   }

//destructor
   roadtriptable::~roadtriptable()
    {
     temp1=head;
     temp2=head->next;

     while(temp2!=NULL) 
      {
       free(temp1);
       temp1=temp2;
       temp2=temp2->next;
      }
      free(temp1);
 
    }
//display contents of road trip table
   void roadtriptable::display()
   {
     r=head;

     printf("Road Trip Table\n");

     while(r!=NULL) 
      {
        printf("%lu %lf %lf %lu %d\n",r->roadid,r->duration_timestamp,r->exit_timestamp,r->next,r->exception);
        r=r->next;         
      }

   }  
// insert entries into the road trip table
   void roadtriptable::insert(u_int32_t rid,double duration,double exitts,bool except)
   {

   //exit timestamp
/*     if(en_ex==1)
     {

      if(head->roadid==0)
        {
   //      printf("error : rtt table is empty\n");
   //      exit(1);
        }
        
     r=head->next;
 
    bool present=false; 

       while(r!=NULL)
        {
          if(r->roadid==rid)
           {
            r->exit_timestamp=tstamp;
            present=true;
            break;
           }
         r=r->next;
        }

       if(present==false)
        {
          printf("error : no record exists for the roadid\n");
        //  exit(1);
        }
     }*/

     //entry timeStamp

    // if(en_ex==0)
      {
         // if exists

        bool exists=false;

       r=head->next;
       temp1=head;
        while(r!=NULL)
         {
          if(r->roadid==rid)
           {
            r->duration_timestamp=duration;
            r->exit_timestamp=exitts;
	    r->exception=except;
            exists=true;
            break;
           }    
          r=r->next;
          temp1=temp1->next;
         }
         
       // if it does not exist

       if(exists==false)
        {
           if(temp1->next!=NULL)
            {
              printf("\nerror : impossible scenario!!");
            }
          
          temp2=(struct rtt *)malloc(sizeof(struct rtt));
          temp2->roadid=rid;
          temp2->duration_timestamp=duration;
          temp2->exit_timestamp=exitts;  
 	  temp2->exception=except;
          temp1->next=temp2;
          temp2->next=NULL;
          head->roadid=head->roadid+1;
        }  
      } 

   }
// functions to retrieve and change values of members of the class


 double roadtriptable::getexittime(u_int32_t rid)
  {
     r=head->next;

     while(r!=NULL)
      {
          if(r->roadid==rid)
             return r->exit_timestamp;
        r=r->next;
      }
  
     return -1;
  }

 double roadtriptable::getdurationonroad(u_int32_t rid)
  {
     r=head->next;

     while(r!=NULL)
      {
          if(r->roadid==rid)
             return r->duration_timestamp;
        r=r->next;
      }
  
     return -1;
  }

  bool roadtriptable::getexceptionstatus(u_int32_t rid)
   {
    r=head->next;

     while(r!=NULL)
      {
          if(r->roadid==rid)
             return r->exception;
       r=r->next;
      }

      printf("Road ID does not exist :: getexceptionstatus");
   }

  void roadtriptable::setexceptionstatus(u_int32_t rid,bool value)
   {
    r=head->next;

     while(r!=NULL)
      {
          if(r->roadid==rid)
             r->exception=value;
       r=r->next;
      }

      printf("Road ID does not exist :: setexceptionstatus");        
   }




