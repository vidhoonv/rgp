/*

	ROUTE GUIDANCE PROTOCOL (RGP)
	
	Coded for Final year project by
	Kannan KV - 20072319
	Naveen G - 20072334
	Vidhoon V - 20072366

	under the guidance of Dr.Ranjani Parthasarathi

	The file contains the packet structure to be used in RGP protocol
	for communication between nodes


*/



 #ifndef __rgp_pkt_h__
 #define __rgp_pkt_h__

 #include <packet.h>


/* =====================================================================
   Packet Formats...
   ===================================================================== */

#define RGPTYPE_REQUEST  	0x01
#define RGPTYPE_REPLY   	0x02
#define RGPTYPE_SREQ   		0x03
#define RGPTYPE_SREP 	  	0x04
/*
 * Route Guidance Protocol Header Macros
 */
#define HDR_RGP_PKT(p)		((struct hdr_rgp_pkt*)hdr_rgp_pkt::access(p))
#define HDR_RGP_REQUEST_PKT(p)  ((struct hdr_rgp_request_pkt*)hdr_rgp_pkt::access(p))
#define HDR_RGP_REPLY_PKT(p)  	((struct hdr_rgp_reply_pkt*)hdr_rgp_pkt::access(p))       

//specific for speed guidance 
#define HDR_RGP_SREQUEST_PKT(p)  ((struct hdr_rgp_speedreq_pkt*)hdr_rgp_pkt::access(p))
#define HDR_RGP_SREPLY_PKT(p)  	((struct hdr_rgp_speedrep_pkt*)hdr_rgp_pkt::access(p))  

//header for RGP packets
struct hdr_rgp_pkt {

     int pkt_type_; // type of packet inside
	
	inline     int&   pkt_type() { return pkt_type_; }

     static int offset_;
     inline static int& offset() { return offset_; }
     inline static hdr_rgp_pkt* access(const Packet* p) {
         return (hdr_rgp_pkt*)p->access(offset_);
	}

};
//header for RGP request packet
struct hdr_rgp_request_pkt {

     int pkt_type_; // type of packet inside
     nsaddr_t   pkt_src_;     // IP address of node which originated this packet


   int   current_id_; // Id of current road 
     int   destination_id_; // Id of destination road to be reached
    
	inline     int&   pkt_type() { return pkt_type_; }
	inline     int&   current_id() { return current_id_; }
	inline     int&   destination_id() { return destination_id_; }
        inline     nsaddr_t&   pkt_src()     { return pkt_src_; }


 };
//header for RGP reply packet
struct hdr_rgp_reply_pkt {

     int pkt_type_; // type of packet inside
     nsaddr_t   pkt_src_;     // IP address of node which originated this packet

     int   data_road_id_; // road ID for which data is sent
     double   data_time_stamp_; // timestamp at which values were taken 
     double   data_field_; // cost calculation parameter
     bool exception_state_; // exception condition 


     inline     int&   pkt_type() { return pkt_type_; }
     inline     int&   data_road_id() { return data_road_id_; }
     inline     double&   data_time_stamp() { return data_time_stamp_; }
     inline     double&   data_field() { return data_field_; }
     inline     bool&   exception_state() { return exception_state_; }
     inline     nsaddr_t&   pkt_src()     { return pkt_src_; }



 };

//header for RGP speed request packet
struct hdr_rgp_speedreq_pkt {

     int pkt_type_; // type of packet inside
     nsaddr_t   pkt_src_;     // IP address of node which originated this packet


   int   current_id_; // Id of current road 
  
    
	inline     int&   pkt_type() { return pkt_type_; }
	inline     int&   current_id() { return current_id_; }
      inline     nsaddr_t&   pkt_src()     { return pkt_src_; }


 };

//header for RGP reply packet
struct hdr_rgp_speedrep_pkt {

     int pkt_type_; // type of packet inside
     nsaddr_t   pkt_src_;     // IP address of node which originated this packet

     int   data_road_id_; // road ID for which data is sent
     double   xpos_; // x loc 
     double   ypos_;// y loc
     double speed_; // speed of vehicle 
     double destx;
     double desty;


     inline     int&   pkt_type() { return pkt_type_; }
     inline     int&   data_road_id() { return data_road_id_; }
     inline     double&   xpos() { return xpos_; }
     inline     double&  ypos() { return ypos_; }
     inline     double&   speed() { return speed_; }
     inline     nsaddr_t&   pkt_src()     { return pkt_src_; }



 };


// for size calculation of header-space reservation
union hdr_all_rgp {
  hdr_rgp_pkt          dummy1;
  hdr_rgp_request_pkt  dummy2;
  hdr_rgp_reply_pkt    dummy3;
  
};

 #endif

