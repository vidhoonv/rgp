#ifndef __rgp_gps_h
#define __rgp_gps_h

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<math.h>

#define RANGE_MIN -0.1
#define RANGE_MAX 0.1

class gps
{

  private:

    struct road_data           // all roads are unidirectional
     {
      int roadid;                //roadids have to be from 0 to 100
      int roadlength;
      int junc1;           // src junction id
      int junc2;           // destination junction id
      double timeonfreeroad;
      char desc[200];
     };

     struct junction_data           
     {
      int juncid;              //juncids have to be from 0 to 100
      int x_position;           // x position of the junction
      int y_position;           // y position of the junction
     };

   road_data r[1000];                // data corresponding to roadid i should be road_data[i]
   
   junction_data j[1000];	// data corresponding to juncid i should be junction_data[i]

  
  public:
  
   gps();
  
     int n;                //number of roads
     int dp_count;	   //number of junctions
	double total_roadlength; //used for optimal path - factoring

   //accessing road table  
   int getroadlength(int roadid);    
   int getjunc1(int roadid);
   int getjunc2(int roadid);
   int getroadid(int j1,int j2);
   double gettimeonfreeroad(int roadid);

   //accesesing junction table
   double get_junc_x_pos(int juncid);
   double get_junc_y_pos(int juncid);
   int get_juncid(double x_pos, double y_pos);
	int isnearjunc(double x_pos, double y_pos,int);
	int get_my_road(double x3,double y3,double,double);
};
#endif
