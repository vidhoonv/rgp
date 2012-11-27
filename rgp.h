/*

	ROUTE GUIDANCE PROTOCOL (RGP)

	class definition
*/

#ifndef __rgp_h__
#define __rgp_h__
#include  "rgp_pkt.h"
#include  "rgp_rtt.h"
#include  "rgp_rst.h"
#include  "rgp_gps.h"
#include  <agent.h>
#include  <packet.h>
#include  <trace.h>
#include  <timer-handler.h>
#include  <random.h>
#include  <classifier-port.h>
#include <mobilenode.h>
#define CURRENT_TIME           Scheduler::instance().clock()
#define MAX_JUNCTIONS 100


#define VEHICLE_SPEED 10.0

#define SHORT_MODE 0
#define QUICK_MODE 1
#define OPTIMAL_MODE 2

#define ENTRY_CACHE 0
#define EXIT_CACHE 1

#define d0 150.0
#define INFINITY 999999.0
class Rgp;               // forward declaration
/* Timers */

/*


class Rgp_PktTimer : public TimerHandler {
public:
    Rgp_PktTimer(Rgp* agent) : TimerHandler() {
         agent_ = agent;
    }
protected:
    Rgp*    agent_;
                              
    virtual void expire(Event* e);
	
};

*/
/* Agent */
class Rgp : public Agent {

    /* Friends */
//    friend class Rgp_PktTimer;

    /* Private members  */
    nsaddr_t            ra_addr_;
 //  rgp_rttable     rttable_;
//   rgp_rstable    rstable_;
    int            x_pos_;
    int            y_pos_;
    int            current_road_id_;
    int            destination_road_id_;
    double 		current_road_entry_time_;
	int		op_mode_;
	double 		travel_time;
/*gps variable */
	gps		gps_object;

/*tables*/
	roadtriptable	rtt;
	roadscoretable	rst;
/*dijikstra array*/
	 double		cost_array[MAX_JUNCTIONS][MAX_JUNCTIONS];
/*dfs variables */
	int 		path[MAX_JUNCTIONS];
        int             len;
	bool		visited[MAX_JUNCTIONS];
	bool 		dfs_result[MAX_JUNCTIONS*MAX_JUNCTIONS];
/* included for SUMO connection */
	int prev_junc;
	int visits;
	double speed_accumulator;


/* included for performance evaluation */
	double total_time;
	double total_distance;
	double roadentrytime;

/* speed guide params */
	double myspeed;
	double mindist;
	double localdestx,localdesty;
	double lastmotiontime;
	bool isdeeplycongested;
	bool communicated;

protected:
    PortClassifier*     dmux_;      // For passing packets up to agents.
    Trace*              logtarget_; // For logging.
 //   Rgp_PktTimer *pkt_timer_; // Timer for sending packets.
   


    inline nsaddr_t&         ra_addr()        { return ra_addr_; }
    inline int&         x_pos()        { return x_pos_; }
    inline int&         y_pos()        { return y_pos_; }
    inline int&         current_road_id()        { return current_road_id_; }
    inline int&         destination_road_id()        { return destination_road_id_; }
    inline double&         current_road_entry_time()        { return current_road_entry_time_; }
  

/*get junction coordinates functions */

    double getx_for_dp(int current_road_id); 
    double gety_for_dp(int current_road_id);

   
   void guide_agent();
   void send_request();
   void send_reply(nsaddr_t destination_ip,int data_road_id,double data_time_stamp,double data_field,bool exception,double delay);
   void send_srequest();
   void send_sreply(double,double,double,nsaddr_t);


   void recv_pkt(Packet *);
   void recv_request(Packet *);
   void recv_reply(Packet *);
   void recv_srequest(Packet *);
   void recv_sreply(Packet *);
   void dfs(int v,int des);
   void intelligent_move();

public:
    Rgp(nsaddr_t);
~Rgp();
    int   command(int, const char*const*);
    void recv(Packet*, Handler*);
    int choose_path(int dp_count,int source_junc,int dest_junc); //arguments to be decided
    
    void prepare_paramArray();
    void cache_rtt(int road_id,double,bool);
	void cache_rtt_dummy(int,double,bool);
	void move_dummynode(double,double,double);

	NsObject *ll;
	TclObject * obj;
 MobileNode *iNode;
};
#endif

