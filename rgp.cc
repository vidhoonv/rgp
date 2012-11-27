/*

	ROUTE GUIDANCE PROTOCOL (RGP)
	
	Coded for Final year project by
	Kannan KV - 20072319
	Naveen G - 20072334
	Vidhoon V - 20072366

	under the guidance of Dr.Ranjani Parthasarathi

	The protocol has been coded in Routing layer for 
	assisting nodes in taking decisions related to movements 

	In future developments, this movement decisions can be used to
	determine the routing mechanism of packets also.



*/

#include <rgp/rgp.h>
#include <rgp/rgp_pkt.h>
#include <random.h>
#include <cmu-trace.h>


/*
  TCL Hooks
*/


/*inheriting basic packet header class members and functions for protocol packet header  */
int hdr_rgp_pkt::offset_;
static class RgpHeaderClass : public PacketHeaderClass {
public:
        RgpHeaderClass() : PacketHeaderClass("PacketHeader/Rgp",
                                              sizeof(hdr_all_rgp)) {
	  bind_offset(&hdr_rgp_pkt::offset_);
	} 
} class_Rgp_hdr;

/* inheriting Tcl methods and members for binding protocol to the Tcl interpreter*/
static class Rgpclass : public TclClass {
public:
        Rgpclass() : TclClass("Agent/Rgp") {}
        TclObject* create(int argc, const char*const* argv) {
        
        assert(argc == 5); 
	return (new Rgp((nsaddr_t)Address::instance().str2addr(argv[4]))); 
	  //return (new Rgp()); 
        }
} class_Rgp;

/* tcl to C++ bridge*/
int Rgp::command(int argc, const char*const* argv) {

  if(argc == 2) {
	//creating a tcl instance handle for access to interpreter from C++
	Tcl& tcl = Tcl::instance();
  
	//command to return the current_road_id of the vehicle 
	if(strncasecmp(argv[1], "get_current_road", 16) == 0) {
	printf("in get_current_road %d\n",current_road_id_);
      tcl.resultf("%d", current_road_id_);
      return TCL_OK;
    }
	
	if(strncasecmp(argv[1], "get_travel_time", 16) == 0) {
	printf("in get_travel_time %lf\n",travel_time);
      tcl.resultf("%lf", travel_time);
      return TCL_OK;
    }

//mandatory function to start an agent - intializations done in constructor
  if(strncasecmp(argv[1], "start", 2) == 0) {
	printf("in start I am %d\n",ra_addr_);
	return TCL_OK;
   
}
	//command to find next road_id after a timer break
 if(strncasecmp(argv[1], "quick_slave", 2) == 0) {
	printf("i am %d - in quick mode slave %d %d\n",ra_addr_,current_road_id_,destination_road_id_);
	rst.display();
	//getchar();
	int new_road_id=0;
	int src_junc=gps_object.getjunc2(current_road_id_);
	int dest_junc=gps_object.getjunc1(destination_road_id_);
	double junc_x=getx_for_dp(current_road_id_);
	double junc_y=gety_for_dp(current_road_id_);
	double new_junc_x=0;
	double new_junc_y=0;
	double xdiffer,ydiffer;
	 double actual_x,actual_y;
	double diff,duration;
	iNode->update_position();
       actual_x=iNode->X();
       actual_y=iNode->Y();


     printf("DEBUG Co-ordinates %lf %lf %lf %lf\n",actual_x,junc_x,actual_y,junc_y);
		diff=actual_x-junc_x+actual_y-junc_y;
	printf("DEBUG diff val %lf\n",diff);
		if(diff<2.0)
                     {
			
			printf("DEBUG in quick slave deciding point *******\n");
			
			//if(total_distance==0.0)
			prepare_paramArray();	
			new_road_id=choose_path(gps_object.dp_count,src_junc,dest_junc);
			printf("%lf %d\n",speed_accumulator,visits);
			//added after speed guidance
			//double speed_avg=speed_accumulator/visits;
			//duration=gps_object.getroadlength(current_road_id_)/speed_avg;
			//cache_rtt(current_road_id_,duration,false);
			current_road_id_=new_road_id;
			//re initializing 	
			visits++;
			speed_accumulator=0;
		    }	
		//	printf("after decision %d\n",current_road_id_);
			new_junc_x=getx_for_dp(current_road_id_);
			new_junc_y=gety_for_dp(current_road_id_); 

			
			printf("\nDEBUG moving from %lf %lf to %lf %lf\n",iNode->X(),iNode->Y(),new_junc_x,new_junc_y);
			
			xdiffer=new_junc_x-iNode->X();
			ydiffer=new_junc_y-iNode->Y();
                //	iNode->set_destination(new_junc_x,new_junc_y,50.0);
			printf("\nold X - %f old Y - %f New X - %f New Y - %f\n",iNode->X(),iNode->Y(),new_junc_x,new_junc_y);

				//travel_time=((new_junc_y-iNode->Y())+(new_junc_x-iNode->X()))/50.0;
				
			//if(travel_time<0)
			//	travel_time*=(-1);

			

			
		               
		//getchar();	
	
        	
        return TCL_OK;
	}
	//command to display Road trip table contents - for testing purpose only 
if(strncasecmp(argv[1], "disp_rtt", 8) == 0) {
	printf("in display rtt\n");
	rtt.display();
	return TCL_OK;
}
// to start speed guidance
if(strncasecmp(argv[1], "speed_guide", 10) == 0) {
	
	iNode->update_position();
	
	double actualx,actualy,destx,desty;
	actualx=iNode->X();
	actualy=iNode->Y();
	
	destx=getx_for_dp(current_road_id_);
	desty=gety_for_dp(current_road_id_); 

	printf("in speed guide %d pos(%lf,%lf) dest(%lf,%lf) currentroad: %d\n",ra_addr_,actualx,actualy,destx,desty,current_road_id_);
	int junc2=gps_object.getjunc2(current_road_id_);
	int juncid=gps_object.isnearjunc(actualx,actualy,current_road_id_);

	

	if(juncid==-1)
	{
		//the vehicle is not near junction, do speed processing
		mindist=INFINITY;
		send_srequest();
		tcl.resultf("1");
	}
	else
	{
		//the vehicle is near junction
	//	double distance=sqrt((localdestx-actualx)*(localdestx-actualx)+(localdesty-actualy)*(localdesty-actualy));
	//	travel_time=distance/10.0; //10.0 is slow speed near junction -> vehicles slow down near junction

		//if(destx-actualx+desty-actualy)
		iNode->set_destination(destx,desty,10.0);

		//setting speed_accum,visits
		visits++;
		speed_accumulator+=10.0;

		//after speed guidance at last stop
			double speed_avg=speed_accumulator/visits;
			double duration=gps_object.getroadlength(current_road_id_)/speed_avg;
			cache_rtt(current_road_id_,duration,false);

		//reset parameters
			visits=1;
			speed_accumulator=0.0;
			//setting roadentrytime for new road
			roadentrytime=CURRENT_TIME;
		
		tcl.resultf("0");
	}
	//getchar();
	return TCL_OK;
}
// to process speed guidance replies
if(strncasecmp(argv[1], "move_intelligent", 15) == 0) {
	printf("in moving intelligent vehicle\n");
	intelligent_move();
	return TCL_OK;
}
	
  }
  else if(argc == 3) {
 	Tcl& tcl = Tcl::instance();
	// invokes the route guidance mechanism coded in guide_agent() function
  if(strncasecmp(argv[1], "guide_me", 8) == 0) {
    op_mode_=atoi(argv[2]);
	guide_agent(); //sending mode of computation 0-shortest,1-quickest,2-optimal
	return TCL_OK;

	}
	//command to assign the destination road id
  else  if(strncasecmp(argv[1], "dest_id", 7) == 0) {
	printf("in dest_id\n");
      destination_road_id_=atoi(argv[2]);
      return TCL_OK;
    }
	//command to assign the current road id
   else if(strncasecmp(argv[1], "road_id", 7) == 0) {

      current_road_id_=atoi(argv[2]);
	printf("in roadid %d \n",current_road_id_);
      return TCL_OK;
    }
	//command to change the mode of operation
    else if(strncasecmp(argv[1], "change_mode", 11) == 0) {
      op_mode_=atoi(argv[2]);
      return TCL_OK;
    }
	//mandatory command to intialize port  called from nslib.tcl
    else  if (strcmp(argv[1], "port-dmux") == 0) {
    dmux_ = (PortClassifier*)TclObject::lookup(argv[2]);
     if (dmux_ == 0) {
         fprintf(stderr, "%s: %s lookup of %s failed\n",__FILE__,argv[1],argv[2]);
         return TCL_ERROR;
     }
     return TCL_OK;
    }
 // intializes a handle to the trace file - not yet used
   else if (strcmp(argv[1], "log-target") == 0 || strcmp(argv[1], "tracetarget") == 0) {
     logtarget_ = (Trace*)TclObject::lookup(argv[2]);
     if (logtarget_ == 0)
         return TCL_ERROR;
     return TCL_OK;
  }
else if (strcmp(argv[1], "set-ll") == 0)
    {
	
      if( (obj = TclObject::lookup(argv[2])) == 0)
      {
        fprintf(stderr, "GeocastAgent(set-ll): %s lookup of %s failed\n",argv[1], argv[2]);
        return (TCL_ERROR);
      }
      ll = (NsObject*) obj;
      return (TCL_OK);

  }
}
else if(argc == 5) {
if(strncasecmp(argv[1], "move_me", 8) == 0) {
	//printf("in move me\n");
	
	double destx,desty;
	double speed=atof(argv[4]);

	destx=atof(argv[2]);
	desty=atof(argv[3]);

	move_dummynode(destx,desty,speed);

	return TCL_OK;
}	
}
  return Agent::command(argc, argv);





 
}

/* 
   Constructor
*/

Rgp::Rgp(nsaddr_t id) : Agent(PT_RGP)
{

//printf("control in constructor\n");

/*begin of GPS code */
//pkt_timer_=new Rgp_PktTimer(this);

iNode=(MobileNode*) (Node::get_node_by_address(id));

x_pos_=iNode->X();
y_pos_=iNode->Y();



/*end of GPS code */
 


ra_addr_=id; /* assign IP address - verify with somesh */

current_road_entry_time_=CURRENT_TIME; /* assign current time initially */ 

speed_accumulator=0;
prev_junc=-1;
visits=1;
                
/* performance evaluation parameter */ 
total_time=0;

myspeed=0;
mindist=INFINITY;
localdestx=0.0;
localdesty=0.0;
lastmotiontime=0.0;
roadentrytime=0;
communicated=false;
}

Rgp::~Rgp() {
printf("destroyed\n");
}

void Rgp::intelligent_move()
{
	
	iNode->update_position();
	
	double actualx,actualy;
	
	actualx=iNode->X();
	actualy=iNode->Y();

	//no reply for speed guidance
	
	if(myspeed==0.0 &&  !communicated)
	{
		printf("no vehicles replied for speed guidance - is the road empty???\n");
		myspeed=50.0; //some default speed for empty road
		localdestx=getx_for_dp(current_road_id_);
		localdesty=gety_for_dp(current_road_id_);
		
	}
	

printf("moving intelligent move final speed:%lf currentroad %d pos(%lf,%lf) dest(%lf,%lf)\n",myspeed,current_road_id_,actualx,actualy,localdestx,localdesty);
//getchar();
	
	if(myspeed==0.0)
		travel_time=0.0;
	else
	{
		double distance=0.0;
		distance=sqrt((localdestx-actualx)*(localdestx-actualx)+(localdesty-actualy)*(localdesty-actualy));
		travel_time=distance/myspeed;
		iNode->set_destination(localdestx,localdesty,myspeed);
	}

	//setting speed_accum,visits
		visits++;
		speed_accumulator+=myspeed;

	//resetting myspeed and destination
		myspeed=0.0;
		localdestx=0.0;
		localdesty=0.0;
	
		
	//resetting communicated
		communicated=false;	
	
}

/* new version code
Mar 25 2011 
@@@@@
@ coded by vidhoon v
@@@@@
*/
void Rgp::move_dummynode(double destx,double desty,double speed) 
{
	//printf("DEBUG ctrl in move_dummynode %d\n",ra_addr_);
	//printf("here %lf %d %lf %lf %lf\n",speed_accumulator,visits,speed,destx,desty);
	int current_road_id;
	double actualx,actualy;

	iNode->update_position();
	actualx=iNode->X();
	actualy=iNode->Y();

//cache last motion time
	lastmotiontime=CURRENT_TIME;
	current_road_id=gps_object.get_my_road(actualx,actualy,destx,desty);

	if(current_road_id==-1)
	{
		//printf("old road %d for vehicle %d now am at (%lf,%lf) time %lf\n",current_road_id_,ra_addr_,actualx,actualy,CURRENT_TIME);
		//getchar();
		current_road_id_=-1;
		for(int i=1;i<20;i++)
		{
			current_road_id=gps_object.get_my_road(actualx+i,actualy,destx,desty);
			if(current_road_id!=-1)
			{
				current_road_id_=current_road_id;
				//printf("glitch correction1\n");
				break;
			}
			current_road_id=gps_object.get_my_road(actualx-i,actualy,destx,desty);
			if(current_road_id!=-1)
			{
				current_road_id_=current_road_id;
				//printf("glitch correction1b\n");
				break;
			}
			current_road_id=gps_object.get_my_road(actualx,actualy+i,destx,desty);
			if(current_road_id!=-1)
			{
				current_road_id_=current_road_id;
				//printf("glitch correction2\n");
				break;
			}
			current_road_id=gps_object.get_my_road(actualx,actualy-i,destx,desty);
			if(current_road_id!=-1)
			{
				current_road_id_=current_road_id;
				//printf("glitch correction2b\n");
				break;
			}
		}
	
		//if(current_road_id_==-1)
			//printf("NO fix\n");
		
		//move the vehicle 
		iNode->set_destination(destx,desty,speed);
		
		return;
	}	
	current_road_id_=current_road_id;
	
	if(speed<1.0)
	{
		// the vehicle is facing congestion 
		cache_rtt_dummy(current_road_id,CURRENT_TIME-roadentrytime,true);
		//cache_rtt_dummy(current_road_id,INFINITY*1.0/10.0,true); // setting exception status and inserting congestion entry to RTT

		//move the vehicle 
		iNode->set_destination(destx,desty,speed);

		//increment parameters
		visits++;
		speed_accumulator+=speed;
	//	printf("congestion road -> %d %lf\n",current_road_id_,CURRENT_TIME);
		//getchar();
	}
	else
	{
		int juncid=gps_object.isnearjunc(actualx,actualy,current_road_id);
		
		if(juncid==-1)
		{
			// the node is not near a juncton
			
		//printf("not near junc vehicle %d\n",ra_addr_);
			//cache record
			cache_rtt_dummy(current_road_id,-2,true); //setting exception status and inserting no congestion entry into RTT
			//rtt.display();
			//printf("road id cached %d\n",current_road_id);
		//	getchar();
			
			//move the node 
			iNode->set_destination(destx,desty,speed);

			//increment parameters
			visits++;
			speed_accumulator+=speed;
			
			
		}
		else
		{
			// the node is near junction
			
			//calculate duration
			if(speed_accumulator!=0)
			{
			double speed_avg=speed_accumulator/visits;
			double duration=(gps_object.getroadlength(current_road_id)*1.0)/speed_avg;

			
			//cache record
			cache_rtt_dummy(current_road_id,duration,false); //setting no exception status and inserting data to RTT
			//printf("near junc\n");
			//rtt.display();
			//getchar();
			}
			//move the node
			iNode->set_destination(destx,desty,speed);

			// resetting dummy node parameters 
			speed_accumulator=0;
			visits=1;

			//setting roadentrytime for new road
			roadentrytime=CURRENT_TIME;
			
		}
	
	}

}


/*

old version code
void Rgp::move_dummynode(double destx,double desty,double speed) 
{
	printf("DEBUG ctrl in move_dummynode %d\n",ra_addr_);

	double actual_x,actual_y;
	double junc_x,junc_y;
	double diff;
	int juncid;
	double i=0;
	iNode->update_position();

        actual_x=iNode->X();
        actual_y=iNode->Y();
	
	iNode->set_destination(destx,desty,speed);

	
	// horizontal case 
	juncid=gps_object.isnearjunc(destx,desty);
	
if(juncid==-1)
	{

		
		//if(ra_addr_==0)
		//printf("DEBUG control check %lf %lf %d %lf\n",destx,desty,ra_addr_,CURRENT_TIME);
		// it has not reached a junction 
			speed_accumulator+=speed;
			visits+=1;
		
				
	}
else if(juncid!=prev_junc)
	{
		double speed_avg=0.0;
		

		if(speed<1.0)
		 {
			
         
		cache_rtt_dummy(current_road_id_,INFINITY*1.0/100.0);

		

		speed_accumulator=0.0;
		visits=1;
		}
		else
		{
		if(visits==1)
			speed_avg=speed;
		else
			speed_avg=speed_accumulator/visits;

		// it has reached a junction 




		if(prev_junc==-1)
		{
			// this is the first junction it has come across 
			prev_junc=gps_object.getjunc2(current_road_id_);
			
		}
		else
		{
			// it has already crossed a junction -> have to change current road id 
			int new_road_id=gps_object.getroadid(prev_junc,juncid);
			current_road_id_=new_road_id;
			prev_junc=juncid;
		}

		double duration=(gps_object.getroadlength(current_road_id_)*1.0)/(speed_avg);
		
		
		cache_rtt_dummy(current_road_id_,duration);
		
		speed_accumulator=0.0;
		visits=1;
		}
	}


		
	

	
		
}

*/

/* implementation of getx_for_dp(int current_road_id) function 
   
   returns the x-coordinate of a decision point at the end of the road segment
*/

double Rgp::getx_for_dp(int current_road_id) {

	printf("control in getx_for_dp\n");
	
	int junction_id=gps_object.getjunc2(current_road_id);
	double junc_x=gps_object.get_junc_x_pos(junction_id);
	//printf("DEBUG cid %d jid %d juncx %d\n",current_road_id,junction_id,junc_x);
	return junc_x;

	
}

/* implementation of gety_for_dp(int current_road_id) function 
   
   returns the y-coordinate of a decision point at the end of the road segment
*/
double Rgp::gety_for_dp(int current_road_id) {

printf("control in gety_for_dp\n");
	int junction_id=gps_object.getjunc2(current_road_id);
	
	double junc_y=gps_object.get_junc_y_pos(junction_id);

	//printf("DEBUG cid %d jid %d juncy %d\n",current_road_id,junction_id,junc_y);
	return junc_y;
}
/* implementation of is_checkpoint(int xpos,int ypos) function 
   
   returns true if given coordinates are of a check point else false
*/



/*
	implementation of choose_path(int dp_count,int source_junc,int dest_junc) 
	computes the best path for the present state and returns the next road id to travel in 
*/
int Rgp::choose_path(int dp_count,int source_junc,int dest_junc)
{
   printf("control in choose path %d --> %d  %d --> %d %d\n",source_junc,dest_junc,current_road_id_,destination_road_id_,dp_count);

      if(source_junc==dest_junc)
	{
	//	printf("DEBUG caught return\n");
              return destination_road_id_;
	}
            int i,j;
            float L[dp_count][dp_count];
            int C[dp_count];
            float D[dp_count];
            int prev[dp_count];
            int rank = dp_count;
            int trank=0;
            for(i = 0; i < rank; i++)
            {
                for(j=0; j<rank; j++) {
                    L[i][j]=cost_array[i][j];
		//printf("%f\t",cost_array[i][j]);
                }
		//printf("\n");
            }

            for (i = 0; i < rank; i++)
            {
                C[i] = i;
                prev[i]=source_junc;
            }

            C[source_junc] = -1;          
            for (i = 0; i < rank; i++)
                D[i] = L[source_junc][i];


       for(trank = 1; trank<rank; trank++)
         {        
                
     // each iteration if dijistra

            float minValue = INFINITY;
            int minNode = source_junc;
            for (i = 0; i < rank; i++)
            {
                if (C[i] == -1)
                    continue;
                if (D[i] > 0 && D[i] < minValue)
                {
                    minValue = D[i];
                    minNode = i;
                }
            }
            C[minNode] = -1;
            for (i = 0; i < rank; i++)
            { 
                if (L[minNode][i] < 0)
                    continue;
                if (D[i] < 0) {
                    D[i] = minValue + L[minNode][i];
                    prev[i]=minNode;
                    continue;
                }
                if ((D[minNode] + L[minNode][i]) < D[i]){
                
                    D[i] = minValue + L[minNode][i];
                     prev[i]=minNode;
                }
            }

     //end of iteration

         }

      //for(i=0;i<p;i++)
       //  cout<<D[i]<<endl;

   //   printf("PREV : %d\n ",prev[0]);
   //   for(int i=0;i<dp_count;i++)
    //   { 
  //       printf("%d %d\n",i,prev[i]); 
   //    }

  int rvalue,ans;
	float total_journey=0.0;
	float total_journey_time=0.0;
        printf("\nPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPath to reach reverse %lf:\n",D[dest_junc]);
        while(dest_junc!=source_junc)  
         { 
          rvalue=dest_junc;
          printf("- %d -\t",dest_junc);
	
          dest_junc=prev[dest_junc];

	/* coded for calculating total distance of journey if completed*/
		int road_in_path=gps_object.getroadid(dest_junc,rvalue);
		total_journey+=gps_object.getroadlength(road_in_path);
		total_journey_time+=cost_array[dest_junc][rvalue];
		
         }
		printf("total journey length %lf total journey time %lf\n",total_journey,total_journey_time);
		//getchar();
        
         // printf("RRRRR :%d \t",dest_junc);
        ans=gps_object.getroadid(source_junc,rvalue);
      //  printf("AAAAAAA : %d %d %d %d  \n",source_junc,rvalue,dest_junc,ans);
 //   getchar();


       FILE *fp;
       char filename[20];
       strcpy(filename,"vehicleid");
       filename[9]=(ra_addr_/10)+'0';
       filename[10]=(ra_addr_%10)+'0';
       filename[11]='\0';
   //    strcat(filename,".txt");

     //  fp=fopen(filename,"a+");   

       
       //fprintf(fp,"\n At Junction %d \n Road ID %d { %s } ---------> Road ID %d { %s } \n",gps_object.r[current_road_id_].junc2,current_road_id_,gps_object.r[current_road_id_].desc,ans,gps_object.r[ans].desc);
 
    // if(rvalue==gps_object.r[destination_road_id_].junc1)
    //   fprintf(fp,"\n At Junction %d \n Road ID %d { %s } ---------> Road ID %d { %s }\n",gps_object.r[ans].junc2,ans,gps_object.r[ans].desc,destination_road_id_,gps_object.r[destination_road_id_].desc);

 //
     //  fclose(fp);

    //   if(rvalue==gps_object.getjunc1(destination_road_id_))
    //      ans=destination_road_id_;

/*

code for storing performance evaluation parameter
*/

  total_time+=cost_array[source_junc][rvalue];
  total_distance+=gps_object.getroadlength(ans);
printf("end of choose path %d Distance travelled so far %lf Time taken so far %lf\n",ans,total_distance,total_time);
getchar();
        return ans;       
}

/*
	implementation of prepare_paramArray()
	
	prepares the cost array for the graph to be used in evaluation of short,quick or optimal path 
*/
void Rgp::prepare_paramArray() 
{
printf("control in paramArray\n");
	int i,j;
        int juncs=gps_object.dp_count;
        int roads=gps_object.n;
	switch(op_mode_) {
	

	case SHORT_MODE:
	/*fetch road length from gpsobject and int dest_id=rq->destination_id_;fill the cost_array */
            
             for(int i=0;i<juncs;i++)
               for(int j=0;j<juncs;j++)
                   cost_array[i][j]=INFINITY;

             for(int i=0;i<roads;i++) 
                 {

                   int x,y;
                   x=gps_object.getjunc1(i);
                   y=gps_object.getjunc2(i);
				//          	printf("inside short mode %d %d %d \n",i,x,y);
                   cost_array[x][y]=gps_object.getroadlength(i);
                 }            			
		break;


	case QUICK_MODE:
		/*fetch cost of road from rstable and fill the array */
		      for(int i=0;i<juncs;i++)
               		for(int j=0;j<juncs;j++)
                   		cost_array[i][j]=INFINITY;

	             for(int i=0;i<roads;i++) 
	                 {
	                   int x,y;
	                   x=gps_object.getjunc1(i);
	                   y=gps_object.getjunc2(i);
	                   cost_array[x][y]=(gps_object.getroadlength(i)*1.0)/20.0; // 20.0 - given by KVK as avg speed on free road
 	                 }
                    // rst.display();
                     rst.r=rst.head->next;
	//	printf("%d %d my addr %d",rst.r,rst.head->next,ra_addr_);
	//	if(rst.r==NULL)
		//	printf("$$$$$$$dead\n");
		//rst.display();
		
                 while(rst.r!=NULL)
                  {	
		//	printf("$$$$$$$$$$$$$$$$$$$$$here\n");
                   // compute CI for each record   
                   int rid;
                   double t1,t0;
                   double ci;
                   rid=rst.r->roadid; 

                   t1=rst.r->ltimeonroad;

                 //  t0=gps_object.gettimeonfreeroad(rid);
                    
		//	ci=(t0-t1)/t0;
                   ci=t1;
			printf("cost %f %f %f\n",ci,t0,t1);
 			  int x,y;
	                   x=gps_object.getjunc1(rid);
	                   y=gps_object.getjunc2(rid);
	                   cost_array[x][y]=ci;

                    rst.r=rst.r->next;
                  }						

                    for(int i=0;i<juncs;i++)
               		for(int j=0;j<juncs;j++)
                   		cost_array[i][j]+=0.0;
		break;


	case OPTIMAL_MODE:
		
			double alpha=0.2;
			double beta=1-alpha;
		      for(int i=0;i<juncs;i++)
               		for(int j=0;j<juncs;j++)
                   		cost_array[i][j]=INFINITY;

	             for(int i=0;i<roads;i++) 
	                 {
	                   int x,y;
	                   x=gps_object.getjunc1(i);
	                   y=gps_object.getjunc2(i);
/*old method 
				double timefactor=(gps_object.getroadlength(i)*15.0)/(50.0*gps_object.total_roadlength);
				double distfactor=gps_object.getroadlength(i)*1.0/gps_object.total_roadlength;
*/
//new method				
				double timetaken=gps_object.getroadlength(i)/20.0;
				double timefactor=timetaken/(400+timetaken);
				double distfactor=gps_object.getroadlength(i)*1.0/(400+gps_object.getroadlength(i));

	                   cost_array[x][y]=alpha*timefactor+beta*distfactor;
	                 }

                     rst.r=rst.head->next;

                 while(rst.r!=NULL)
                  {
                   // compute CI for each record   
                   int rid;
                   double t1,t0;
                   double ci;
                   rid=rst.r->roadid; 

                   t1=rst.r->ltimeonroad;

                   t0=gps_object.getroadlength(rid)/20.0;
                    
                   ci=(t1-t0)/t0;

 			  int x,y;
                          double d,di;
	                   x=gps_object.getjunc1(rid);
	                   y=gps_object.getjunc2(rid);
	                   
                           d=gps_object.getroadlength(rid);
				
/*old method
			
			double timefactor=15*t1/gps_object.total_roadlength;
			
			
			double distfactor=d/gps_object.total_roadlength;
                       //    di=d/d0; 
			
			//if(rst.r->exception==1)
			//	timefactor=timefactor/100;
			
*/				

//new method
double timefactor=t1/(400+t1); //max time  to travel a road : 400 (assumption because in congestion values go upto 300)
double distfactor=d/(400+d); //400 is length of longest road

			   cost_array[x][y] = alpha*timefactor+beta*distfactor;  //50.0 ->speed on free road
		//	printf("time factor %lf distance factor %lf (alpha*time factor) %lf (beta*distance factor) %lf \n",timefactor,distfactor,alpha*timefactor,beta*distfactor);

	printf("time factor %lf distance factor %lf distance %lf congestion index: %lf (t1,t0): %lf %lf\n",timefactor,distfactor,d,ci,t1,t0);

			
			//getchar();
                          // cost_array[x][y]=0.5*t1+0.1*d;
                    rst.r=rst.r->next;
                  }				

		break;
	}	
	printf("at end of paramArray\n");
	
}

/*
	implementation of cache_rtt(int new_road_id)

	records the parameters used in calculation after the node reaches end of a road segment 
*/
void Rgp::cache_rtt(int road_id,double time_taken,bool exception) {
	/*currentroadid enter exit timestamp
	  newroadid add entry timestamp */
//printf("control in cache_rtt\n");
	rtt.insert(road_id,time_taken,CURRENT_TIME,exception);
	//printf("cached road id->%d by vehicle %d\n",road_id,ra_addr_);
	//getchar();
	

return;
	
}
void Rgp::cache_rtt_dummy(int road_id,double total_time_taken,bool exception) {
	/*currentroadid enter exit timestamp
	  newroadid add entry timestamp */
//printf("control in cache_rtt_dummy\n");
	rtt.insert(road_id,total_time_taken,CURRENT_TIME,exception);
	//printf("cached road id->%dby vehicle %d\n",road_id,ra_addr_);
	//getchar();

return;
	
}
/*
	implementation of the guide_agent() function

	starting point for working of the route guidance mechanism

	serves to be the main interface from TCL and calls the corresponding function based on the user mode 
*/
void Rgp::guide_agent()
{

	printf("control in guide agent for NODE %d\n",ra_addr_);
      
	
	
	printf("current road id : %d destination road id : %d\n",current_road_id_,destination_road_id_);
       
	int new_road_id=0;
	double junc_x=getx_for_dp(current_road_id_);
	double junc_y=gety_for_dp(current_road_id_);
	int src_junc=gps_object.getjunc2(current_road_id_);
	int dest_junc=gps_object.getjunc1(destination_road_id_);
	double new_junc_x=0;
	double new_junc_y=0;
	double xdiffer,ydiffer;
	 double actual_x,actual_y;
	double diff;
	iNode->update_position();
       actual_x=iNode->X();
       actual_y=iNode->Y();
	double duration;
	//iNode->set_destination(junc_x,junc_y,VEHICLE_SPEED);
	

	switch(op_mode_) {
	

	case SHORT_MODE:
		


   	 	 printf("DEBUG Co-ordinates %lf %lf %lf %lf\n",actual_x,junc_x,actual_y,junc_y);
		 diff=actual_x-junc_x+actual_y-junc_y;
		 printf("DEBUG diff val %lf\n",diff);
		if(diff<2.0)
                     {
			
			printf("DEBUG in quick slave deciding point *******\n");
			
			
			prepare_paramArray();	
			new_road_id=choose_path(gps_object.dp_count,src_junc,dest_junc);
			printf("%lf %d\n",speed_accumulator,visits);
			//added after speed guidance
			//double speed_avg=speed_accumulator/visits;
			//duration=gps_object.getroadlength(current_road_id_)/speed_avg;
			//cache_rtt(current_road_id_,duration,false);
			current_road_id_=new_road_id;
			//re initializing 	
			visits++;
			speed_accumulator=0;
		    }	
		//	printf("after decision %d\n",current_road_id_);
			new_junc_x=getx_for_dp(current_road_id_);
			new_junc_y=gety_for_dp(current_road_id_); 

			
			printf("\nDEBUG moving from %lf %lf to %lf %lf\n",iNode->X(),iNode->Y(),new_junc_x,new_junc_y);
			
			xdiffer=new_junc_x-iNode->X();
			ydiffer=new_junc_y-iNode->Y();
                //	iNode->set_destination(new_junc_x,new_junc_y,50.0);
			printf("\nold X - %f old Y - %f New X - %f New Y - %f\n",iNode->X(),iNode->Y(),new_junc_x,new_junc_y);

			//	travel_time=((new_junc_y-iNode->Y())+(new_junc_x-iNode->X()))/50.0;
				
			//if(travel_time<0)
			//	travel_time*=(-1);
	               
		getchar();	
	        
			
		break;
		
	case QUICK_MODE:
		send_request();
		
		
		
		break;
	case OPTIMAL_MODE:
		send_request();
	
		break;
		


	}
	

return;	
	
/*not possible for review 2 */

/*
	if(is_checkpoint(x_pos_,y_pos_)) {
	/*start the v2v communication sequence */
	
	/*send request packet */
	
	/*receive reply packets and wait till time out */

	/*use data to determine most suitable path */

	/* determine next road segment to be taken */
/*	}
	else if(is_decisionpoint(x_pos_,y_pos_)) {
	/*assign next road segment id to be followed */
/*	} 
	else {
	/*proceed in same segment of road and do nothing */
/*	}

*/
}


/*

	finds the possible paths from requesting node's current location 
	to its destination to send relevant replies to that node

	supplementary function for send_reply to identify which entries in RTT 
	are relevant to be sent to requesting node
*/
void Rgp::dfs(int v,int des)
{
 static int n=gps_object.dp_count;
  visited[v]=true;
  path[len]=v;
  len++;

  if(v==des)
   {
    // printf("\npath identified\n");

    //  for(int j=0;j<len;j++)
     //   printf("%d ",path[j]);

       for(int j=1;j<len;j++)
        {
          int rid;
          rid=gps_object.getroadid(path[j-1],path[j]);
          dfs_result[rid]=true;

        }   
   }
  else
  {
   for(int i=0;i<n;i++)
    {
       if(v!=i && cost_array[v][i]!=INFINITY && visited[i]==false)
         dfs(i,des);
    }
   }
  len--;
  visited[v]=false;
}



/*

	function to schedule a send event of request packet in the scheduler

	the function also populates the request packet defined in rgp_pkt.h 
	before scheduling
*/

void Rgp::send_request()
{

Packet *p = Packet::alloc();
struct hdr_cmn *ch = HDR_CMN(p);
struct hdr_ip *ih = HDR_IP(p);
struct hdr_rgp_request_pkt *rq = HDR_RGP_REQUEST_PKT(p);

// Fill out the RREQ packet 
 // ch->uid() = 0;
 ch->ptype() = PT_RGP;
 ch->direction()= hdr_cmn::DOWN;
 ch->size() = IP_HDR_LEN + sizeof(struct hdr_rgp_request_pkt);
 ch->iface() = -2;
 ch->error() = 0;
 ch->addr_type() = NS_AF_NONE;
 ch->next_hop_ = IP_BROADCAST;     

 ih->saddr() = Agent::addr();
 ih->daddr() = IP_BROADCAST;
 ih->sport() = RT_PORT;
 ih->dport() = RT_PORT;

 // Fill up some more fields. 
 rq->pkt_type_= RGPTYPE_REQUEST;
 rq->pkt_src_=ra_addr_;
 rq->current_id_=current_road_id_;
 rq->destination_id_=destination_road_id_;


printf("control in sendrequest \n");
 
 Scheduler::instance().schedule(ll, p, 0.);

}

/*
	function to schedule a send event for reply packet in the scheduler

	the function also populates the reply packet defined in rgp_pkt.h
	before scheduling
*/

void Rgp::send_reply(nsaddr_t destination_ip,int data_road_id,double data_time_stamp,double data_field,bool exception,double delay)
{
printf("control in sendreply\n");
printf("\ndata field->%lf\n dest %d excep %d\n",data_field,destination_ip,exception);
Packet *p = Packet::alloc();
struct hdr_cmn *ch = HDR_CMN(p);
struct hdr_ip *ih = HDR_IP(p);
struct hdr_rgp_reply_pkt *rq = HDR_RGP_REPLY_PKT(p);

 // ch->uid() = 0;
 ch->ptype() = PT_RGP;
 ch->direction()= hdr_cmn::DOWN;
 ch->size() = IP_HDR_LEN + sizeof(struct hdr_rgp_reply_pkt) ;
 ch->iface() = -2;
 ch->error() = 0;
 ch->addr_type() = NS_AF_INET;   
 ch->prev_hop_ = ra_addr_;     
ch->next_hop_ = destination_ip;        

 ih->saddr() = ra_addr_;
 ih->daddr() = destination_ip;
 ih->sport() = RT_PORT;
 ih->dport() = RT_PORT;

/*  included our protocol packet data here */
 rq->pkt_type_= RGPTYPE_REPLY;
 rq->pkt_src_=ra_addr_;
 rq->data_road_id_=data_road_id;
 rq->data_time_stamp_=data_time_stamp;
 rq->data_field_=data_field;
 rq->exception_state_=exception;

 Scheduler::instance().schedule(ll, p, delay);

}

/*

	public recv function involked automatically when a packet is received 
	and inturn invokes the protocol recv function

*/
void Rgp::recv(Packet *p, Handler*) {

//printf("control in recv public\n");

struct hdr_cmn *ch = HDR_CMN(p);
struct hdr_ip *ih = HDR_IP(p);

     if (ih->saddr() == ra_addr()) {
     // If there exists a loop, must drop the packet
	printf("\n---->num forwards %d<---\n",ch->num_forwards());
     if (ch->num_forwards() > 0) {
	
         drop(p, DROP_RTR_ROUTE_LOOP);
         return;
     }
     // else if this is a packet I am originating, must add IP header
     else if (ch->num_forwards() == 0)
        ch->size() += IP_HDR_LEN;
	
 }



 if(ch->ptype() == PT_RGP) {
   ih->ttl_ -= 1;
   recv_pkt(p);
   return;
   }

}

/*

	protocol specific receive function which classifies packet types and
	invokes packet specific receive function to handle them in respective ways.
*/
void Rgp::recv_pkt(Packet *p) {

//printf("control in recv_pkt\n");

 struct hdr_rgp_pkt *ah = HDR_RGP_PKT(p);

 /*
  * Incoming Packets.
  */
 switch(ah->pkt_type_) {

 case RGPTYPE_REQUEST:
   recv_request(p);
   break;

 case RGPTYPE_REPLY:
   recv_reply(p);
   break;

 case RGPTYPE_SREQ: 
	recv_srequest(p);
	break;
  case RGPTYPE_SREP:
	recv_sreply(p);
	break; 
 default:
   fprintf(stderr, "Invalid RGP type (%x)\n", ah->pkt_type_);
   exit(1);
 }

}

/*
	implementation of recv function for request packets
	and handle data obtained

	node after receiving a request packet invokes dfs() method to find relevant data 
	and fetches corresponding data from local memory to populate reply packets
*/
void Rgp::recv_request(Packet *p) {

struct hdr_ip *ih = HDR_IP(p);
struct hdr_rgp_request_pkt *rq = HDR_RGP_REQUEST_PKT(p);
int curr_id=rq->current_id_;
int dest_id=rq->destination_id_;

int roadid;
double data_ts;
double data_field;
bool exception;
double delay;
nsaddr_t reply_addr=rq->pkt_src_;
 
/*preprocessing to populate the cost array -> copied from prepare_paramArray() 

preprocessing for DFS

*/
printf("I am at road %d\n",current_road_id_);
printf("control in recv_request sent by %d recv by %d\n",rq->pkt_src_,Agent::addr());
 
 len=0;

        int juncs=gps_object.dp_count;
        int roads=gps_object.n;
	
	

	/*fetch road length from gpsobject and fill the cost_array */
            
           
             for(int i=0;i<juncs;i++)
               for(int j=0;j<juncs;j++)
                   cost_array[i][j]=INFINITY;

             for(int i=0;i<roads;i++) 
                 {
                   int x,y;
                   x=gps_object.getjunc1(i);
                   y=gps_object.getjunc2(i);
                   cost_array[x][y]=gps_object.getroadlength(i);
                 }            			

  for(int i=0;i<MAX_JUNCTIONS;i++)
   {
     visited[i]=false;
     dfs_result[i]=false;
   }

  int src=gps_object.getjunc1(curr_id);
  int dest=gps_object.getjunc2(dest_id);

 // printf("$$$$$$$$ b4 dfs : %d %d %d %d %d\n\n",curr_id,dest_id,src,dest,ra_addr_);

  rtt.display();
  //dfs(src,dest);

for (int i=0;i<gps_object.n;i++)
{
	delay=i*0.001;
	//if(dfs_result[i])
	//{
		roadid=i;
		
		if(current_road_id_==roadid)
		{
			if(iNode->speed()<1.0)
				data_field=CURRENT_TIME-roadentrytime;
			//data_field=INFINITY*1.0/10.0;
			else
			{
				//node travelling without congestion in current road - dont send anything
				printf("not replying - no congestion at road  %d by vehicle %d\n",current_road_id_,ra_addr_);
		     		continue;
			}
			data_ts=CURRENT_TIME;
			exception=true;
			printf("replying for %d\n",roadid);
			send_reply(reply_addr,roadid,data_ts,data_field,exception,delay);
		}
		else
		{ 
		//printf("Road id:%d\n",roadid);
		data_field=rtt.getdurationonroad(roadid);
		if(data_field==-1.0)
		{
		//printf("\ndata not present in table  for road id %d\n",roadid);
		continue;
		}
		else if(data_field==-2.0)
		{
				//node travelled without congestion  - junk packet
				printf("not replying - no congestion at road  %d by vehicle %d\n",roadid,ra_addr_);
		     		continue;
		}
		else
		{
		printf("\ndata field->%lf\n",data_field);
		data_ts=rtt.getexittime(roadid);
		exception=rtt.getexceptionstatus(roadid);
		printf("replying for %d\n",roadid);
			//getchar();
		}
		send_reply(reply_addr,roadid,data_ts,data_field,exception,delay);
		}
		
		
	//}
}



}

/*
	implementation of recv function for reply packets
	and handle data obtained

	node after receiving a reply packet uses data to populate 
	road score table for path evaluation
	
*/



void Rgp::recv_reply(Packet *p) {


struct hdr_ip *ih = HDR_IP(p);
struct hdr_rgp_reply_pkt *rp = HDR_RGP_REPLY_PKT(p);

printf("control in recv_reply I am %d packet from %d for road %d cid %d dest id %d at %lf excep %d\n",ra_addr_,rp->pkt_src_,rp->data_road_id_,current_road_id_,destination_road_id_,CURRENT_TIME,rp->exception_state_);


int roadid=rp->data_road_id_;
double data_ts=rp->data_time_stamp_;
double data_field=rp->data_field_;
bool exception=rp->exception_state_;

rst.insert(roadid,data_ts,data_field,exception);


//rst.display();

}

void Rgp::send_srequest()
{

Packet *p = Packet::alloc();
struct hdr_cmn *ch = HDR_CMN(p);
struct hdr_ip *ih = HDR_IP(p);
struct hdr_rgp_speedreq_pkt *rq = HDR_RGP_SREQUEST_PKT(p);

// Fill out the RREQ packet 
 // ch->uid() = 0;
 ch->ptype() = PT_RGP;
 ch->direction()= hdr_cmn::DOWN;
 ch->size() = IP_HDR_LEN + sizeof(struct hdr_rgp_request_pkt);
 ch->iface() = -2;
 ch->error() = 0;
 ch->addr_type() = NS_AF_NONE;
 ch->next_hop_ = IP_BROADCAST;     

 ih->saddr() = Agent::addr();
 ih->daddr() = IP_BROADCAST;
 ih->sport() = RT_PORT;
 ih->dport() = RT_PORT;

 // Fill up some more fields. 
 rq->pkt_type_= RGPTYPE_SREQ;
 rq->pkt_src_=ra_addr_;
 rq->current_id_=current_road_id_;
 


printf("control in send speed request \n");
 
 Scheduler::instance().schedule(ll, p, 0.);

}

/*
	function to schedule a send event for reply packet in the scheduler

	the function also populates the reply packet defined in rgp_pkt.h
	before scheduling
*/

void Rgp::send_sreply(double xpos, double ypos, double speed,nsaddr_t destination_ip)
{
printf("control in send speed reply\n");
printf("\n dest %d\n",destination_ip);

iNode->update_position();

Packet *p = Packet::alloc();
struct hdr_cmn *ch = HDR_CMN(p);
struct hdr_ip *ih = HDR_IP(p);
struct hdr_rgp_speedrep_pkt *rq = HDR_RGP_SREPLY_PKT(p);

 // ch->uid() = 0;
 ch->ptype() = PT_RGP;
 ch->direction()= hdr_cmn::DOWN;
 ch->size() = IP_HDR_LEN + sizeof(struct hdr_rgp_reply_pkt) ;
 ch->iface() = -2;
 ch->error() = 0;
 ch->addr_type() = NS_AF_INET;   
 ch->prev_hop_ = ra_addr_;     
ch->next_hop_ = destination_ip;        

 ih->saddr() = ra_addr_;
 ih->daddr() = destination_ip;
 ih->sport() = RT_PORT;
 ih->dport() = RT_PORT;

/*  included our protocol packet data here */
 rq->pkt_type_= RGPTYPE_SREP;
 rq->pkt_src_=ra_addr_;
 rq->xpos_=xpos;
 rq->ypos_=ypos;
 rq->speed_=speed;
 rq->destx=iNode->destX();
 rq->desty=iNode->destY();

 Scheduler::instance().schedule(ll, p, 0.);

}

void Rgp::recv_srequest(Packet *p) {

struct hdr_ip *ih = HDR_IP(p);
struct hdr_rgp_speedreq_pkt* rq = HDR_RGP_SREQUEST_PKT(p);

//printf("I am at road %d\n",current_road_id_);
//printf("control in recv_srequest src %d to %d for road %d\n",rq->pkt_src_,Agent::addr(),rq->current_id_);

if(current_road_id_!=rq->current_id_)
{
	//printf("irrelevant packet for this node\n");
	return;
}
else if(current_road_id_!=-1)
{
	//printf("relevant packet- preparing reply\n");
	iNode->update_position();
	double interval=CURRENT_TIME-lastmotiontime;
	if(interval>1.0)
	{
		printf("dead node not replying");
		//getchar();
		return; //dead node
	}
	else 
	{
		if(iNode->speed()==0.00 && interval<=1.0)
		{
		printf("deeply congested node replying");
		//getchar();
		
		}
		send_sreply(iNode->X(),iNode->Y(), iNode->speed(),rq->pkt_src());
	}
}


}

void Rgp::recv_sreply(Packet *p) {

struct hdr_ip *ih = HDR_IP(p);
struct hdr_rgp_speedrep_pkt* rp = HDR_RGP_SREPLY_PKT(p);

//printf("control in recv_sreply %d %d %d %d %d\n",ra_addr_,rp->pkt_src_,ih->daddr(),current_road_id_,destination_road_id_);


iNode->update_position();
double myposx=iNode->X();
double myposy=iNode->Y();

double dist=sqrt((myposx-rp->xpos())*(myposx-rp->xpos())+(myposy-rp->ypos())*(myposy-rp->ypos()));
double dist1=0.0,dist2=0.0;

double junc1=gps_object.getjunc1(current_road_id_);
double junc1x=gps_object.get_junc_x_pos(junc1);
double junc1y=gps_object.get_junc_y_pos(junc1);


if(dist<mindist) 
{
//printf("IVD %lf speed %lf ldx %lf ldy %lf pos(%lf,%lf)\n",dist,rp->speed_,rp->xpos(),rp->ypos(),myposx,myposy);
//getchar();

dist1=sqrt((myposx-junc1x)*(myposx-junc1x)+(myposy-junc1y)*(myposy-junc1y));
dist2=sqrt((rp->xpos()-junc1x)*(rp->xpos()-junc1x)+(rp->ypos()-junc1y)*(rp->ypos()-junc1y));


//if(rp->destx==myposx && rp->desty==myposy)
//	return; //creates deadlock
	

	if(dist1<=dist2) // replying node is ahead of the receiving node
	{
	communicated=true;
	printf("replying node is ahead of the receiving node\n");
	mindist=dist;
	if(mindist>50) //IVD is high.. so road is free!
	{
	myspeed=50.0; //speed on free road
	isdeeplycongested=false;
	}
	else
	{

	myspeed=rp->speed_; // IVD is low.. so road is congested to soem extent
		if(myspeed<1.0)
			isdeeplycongested=true;
	}
	localdestx=rp->xpos();
	localdesty=rp->ypos();
	}

if(myspeed<1.0 && isdeeplycongested)
{
	printf("my node is getting deeply congested\n");
	//getchar();
}

}

//printf("speed %lf dc %d (desx,desy) (%lf,%lf)\n",myspeed,isdeeplycongested,localdestx,localdesty);



}


