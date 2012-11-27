/*

	ROAD SCORE TABLE 
file contains class to simulate internal memory of a node
to support the operation of the protocol
*/

#include "rgp_rst.h"
  
/* constructor

*/
   roadscoretable::roadscoretable()
   {
        
     head=(struct rst *)malloc(sizeof(struct rst));
     head->roadid=0;   // head is header node. head->roadid gives no of nodes in the table
     head->next=NULL;
   }
//destructor
   roadscoretable::~roadscoretable()
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

/*

function to display content of road score table 
coded for testing purpose only

*/

   void roadscoretable::display()
   {
     struct rst * r;
     r=head;

     printf("Road score Table\n");

     while(r!=NULL) 
      {
        printf("%lu %lf %lf %lu %d\n",r->roadid,r->timestamp,r->ltimeonroad,r->next,r->exception);
        r=r->next;         
      }

   }

/*

function to get the current size of the road score table
*/  

     u_int32_t roadscoretable::getsize()
      {
       return head->roadid;
     
      }

/*

	function to insert entries into the table
*/
   void roadscoretable::insert(u_int32_t rid,double tstamp,double tor,bool ex)
   {     
         // if exists
	//printf("insert\n");
        bool exists=false;

       r=head->next;
       temp1=head;
        while(r!=NULL)
         {
          if(r->roadid==rid)
           {
		
	     if(ex==true && tor==-2)
		return;
             if(r->timestamp<tstamp)
              {
                   r->timestamp=tstamp;
                   r->ltimeonroad=tor;
		   r->exception=ex;	
              }
            exists=true;
            break;
           }    
          r=r->next;
          temp1=temp1->next;
         }
         
       // if it does not exist

       if(exists==false)
        {
	    if(ex==true && tor==-2)
		return;
           if(temp1->next!=NULL)
            {
              printf("\nerror : impossible scenario!!");
            }
          
          temp2=(struct rst *)malloc(sizeof(struct rst));
          temp2->roadid=rid;
          temp2->timestamp=tstamp;
          temp2->ltimeonroad=tor;
          temp2->exception=ex; /* have to add determine part and then change */
          temp1->next=temp2;
          temp2->next=NULL;
          head->roadid=head->roadid+1;
        }  
      }


/*
	functions to retrive members of the class
*/
  double roadscoretable::getlatesttime(u_int32_t rid)
  {
     r=head->next;

     while(r!=NULL)
      {
          if(r->roadid==rid)
             return r->ltimeonroad;
       r=r->next;
      }
  
     return -1.0;
  }

  bool roadscoretable::getexceptionstatus(u_int32_t rid)
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

  void roadscoretable::setexceptionstatus(u_int32_t rid,bool value)
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
