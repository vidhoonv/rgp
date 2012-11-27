/*
file contains class to simulate a GPS system 
to support the operation of the protocol
*/
#include "rgp_gps.h"


/*constructor 

  populates road details and junction details
  used in simulation setup
*/

  
 gps::gps()
    {
       //populate values

 
    n=180;

r[0].roadid=0;
r[0].roadlength=309;
r[0].junc1=56;
r[0].junc2=5;
r[0].timeonfreeroad=22.247822;

r[1].roadid=1;
r[1].roadlength=94;
r[1].junc1=53;
r[1].junc2=56;
r[1].timeonfreeroad=6.767946;

r[2].roadid=2;
r[2].roadlength=60;
r[2].junc1=41;
r[2].junc2=53;
r[2].timeonfreeroad=4.319965;

r[3].roadid=3;
r[3].roadlength=45;
r[3].junc1=6;
r[3].junc2=41;
r[3].timeonfreeroad=3.239974;

r[4].roadid=4;
r[4].roadlength=226;
r[4].junc1=24;
r[4].junc2=7;
r[4].timeonfreeroad=16.271870;

r[5].roadid=5;
r[5].roadlength=74;
r[5].junc1=6;
r[5].junc2=24;
r[5].timeonfreeroad=5.327957;

r[6].roadid=6;
r[6].roadlength=80;
r[6].junc1=3;
r[6].junc2=23;
r[6].timeonfreeroad=5.759954;

r[7].roadid=7;
r[7].roadlength=6;
r[7].junc1=22;
r[7].junc2=3;
r[7].timeonfreeroad=0.431997;

r[8].roadid=8;
r[8].roadlength=76;
r[8].junc1=0;
r[8].junc2=16;
r[8].timeonfreeroad=5.471956;

r[9].roadid=9;
r[9].roadlength=80;
r[9].junc1=28;
r[9].junc2=0;
r[9].timeonfreeroad=5.759954;

r[10].roadid=10;
r[10].roadlength=368;
r[10].junc1=72;
r[10].junc2=28;
r[10].timeonfreeroad=26.495788;

r[11].roadid=11;
r[11].roadlength=74;
r[11].junc1=2;
r[11].junc2=22;
r[11].timeonfreeroad=5.327957;

r[12].roadid=12;
r[12].roadlength=57;
r[12].junc1=19;
r[12].junc2=2;
r[12].timeonfreeroad=4.103967;

r[13].roadid=13;
r[13].roadlength=24;
r[13].junc1=38;
r[13].junc2=19;
r[13].timeonfreeroad=1.727986;

r[14].roadid=14;
r[14].roadlength=34;
r[14].junc1=18;
r[14].junc2=38;
r[14].timeonfreeroad=2.447980;

r[15].roadid=15;
r[15].roadlength=3;
r[15].junc1=43;
r[15].junc2=18;
r[15].timeonfreeroad=0.215998;

r[16].roadid=16;
r[16].roadlength=47;
r[16].junc1=1;
r[16].junc2=43;
r[16].timeonfreeroad=3.383973;

r[17].roadid=17;
r[17].roadlength=75;
r[17].junc1=34;
r[17].junc2=1;
r[17].timeonfreeroad=5.399957;

r[18].roadid=18;
r[18].roadlength=6;
r[18].junc1=16;
r[18].junc2=34;
r[18].timeonfreeroad=0.431997;

r[19].roadid=19;
r[19].roadlength=281;
r[19].junc1=0;
r[19].junc2=10;
r[19].timeonfreeroad=20.231838;

r[20].roadid=20;
r[20].roadlength=286;
r[20].junc1=16;
r[20].junc2=15;
r[20].timeonfreeroad=20.591835;

r[21].roadid=21;
r[21].roadlength=294;
r[21].junc1=17;
r[21].junc2=1;
r[21].timeonfreeroad=21.167831;

r[22].roadid=22;
r[22].roadlength=298;
r[22].junc1=18;
r[22].junc2=11;
r[22].timeonfreeroad=21.455828;

r[23].roadid=23;
r[23].roadlength=300;
r[23].junc1=20;
r[23].junc2=19;
r[23].timeonfreeroad=21.599827;

r[24].roadid=24;
r[24].roadlength=287;
r[24].junc1=12;
r[24].junc2=22;
r[24].timeonfreeroad=20.663835;

r[25].roadid=25;
r[25].roadlength=154;
r[25].junc1=24;
r[25].junc2=3;
r[25].timeonfreeroad=11.087911;

r[26].roadid=26;
r[26].roadlength=395;
r[26].junc1=26;
r[26].junc2=4;
r[26].timeonfreeroad=28.439772;

r[27].roadid=27;
r[27].roadlength=86;
r[27].junc1=13;
r[27].junc2=26;
r[27].timeonfreeroad=6.191950;

r[28].roadid=28;
r[28].roadlength=166;
r[28].junc1=27;
r[28].junc2=31;
r[28].timeonfreeroad=11.951904;

r[29].roadid=29;
r[29].roadlength=83;
r[29].junc1=25;
r[29].junc2=27;
r[29].timeonfreeroad=5.975952;

r[30].roadid=30;
r[30].roadlength=54;
r[30].junc1=27;
r[30].junc2=26;
r[30].timeonfreeroad=3.887969;

r[31].roadid=31;
r[31].roadlength=187;
r[31].junc1=29;
r[31].junc2=27;
r[31].timeonfreeroad=13.463892;

r[32].roadid=32;
r[32].roadlength=50;
r[32].junc1=28;
r[32].junc2=29;
r[32].timeonfreeroad=3.599971;

r[33].roadid=33;
r[33].roadlength=62;
r[33].junc1=33;
r[33].junc2=28;
r[33].timeonfreeroad=4.463964;

r[34].roadid=34;
r[34].roadlength=79;
r[34].junc1=29;
r[34].junc2=32;
r[34].timeonfreeroad=5.687954;

r[35].roadid=35;
r[35].roadlength=169;
r[35].junc1=30;
r[35].junc2=29;
r[35].timeonfreeroad=12.167903;

r[36].roadid=36;
r[36].roadlength=107;
r[36].junc1=70;
r[36].junc2=34;
r[36].timeonfreeroad=7.703938;

r[37].roadid=37;
r[37].roadlength=80;
r[37].junc1=40;
r[37].junc2=70;
r[37].timeonfreeroad=5.759954;

r[38].roadid=38;
r[38].roadlength=73;
r[38].junc1=35;
r[38].junc2=40;
r[38].timeonfreeroad=5.255958;

r[39].roadid=39;
r[39].roadlength=70;
r[39].junc1=35;
r[39].junc2=36;
r[39].timeonfreeroad=5.039960;

r[40].roadid=40;
r[40].roadlength=10;
r[40].junc1=51;
r[40].junc2=35;
r[40].timeonfreeroad=0.719994;

r[41].roadid=41;
r[41].roadlength=85;
r[41].junc1=50;
r[41].junc2=51;
r[41].timeonfreeroad=6.119951;

r[42].roadid=42;
r[42].roadlength=82;
r[42].junc1=37;
r[42].junc2=50;
r[42].timeonfreeroad=5.903953;

r[43].roadid=43;
r[43].roadlength=124;
r[43].junc1=69;
r[43].junc2=38;
r[43].timeonfreeroad=8.927929;

r[44].roadid=44;
r[44].roadlength=69;
r[44].junc1=42;
r[44].junc2=69;
r[44].timeonfreeroad=4.967960;

r[45].roadid=45;
r[45].roadlength=105;
r[45].junc1=49;
r[45].junc2=40;
r[45].timeonfreeroad=7.559940;

r[46].roadid=46;
r[46].roadlength=74;
r[46].junc1=42;
r[46].junc2=49;
r[46].timeonfreeroad=5.327957;

r[47].roadid=47;
r[47].roadlength=93;
r[47].junc1=41;
r[47].junc2=42;
r[47].timeonfreeroad=6.695946;

r[48].roadid=48;
r[48].roadlength=122;
r[48].junc1=44;
r[48].junc2=43;
r[48].timeonfreeroad=8.783930;

r[49].roadid=49;
r[49].roadlength=68;
r[49].junc1=49;
r[49].junc2=46;
r[49].timeonfreeroad=4.895961;

r[50].roadid=50;
r[50].roadlength=79;
r[50].junc1=50;
r[50].junc2=49;
r[50].timeonfreeroad=5.687954;

r[51].roadid=51;
r[51].roadlength=134;
r[51].junc1=47;
r[51].junc2=50;
r[51].timeonfreeroad=9.647923;

r[52].roadid=52;
r[52].roadlength=261;
r[52].junc1=48;
r[52].junc2=47;
r[52].timeonfreeroad=18.791850;

r[53].roadid=53;
r[53].roadlength=136;
r[53].junc1=68;
r[53].junc2=51;
r[53].timeonfreeroad=9.791922;

r[54].roadid=54;
r[54].roadlength=266;
r[54].junc1=52;
r[54].junc2=68;
r[54].timeonfreeroad=19.151847;

r[55].roadid=55;
r[55].roadlength=91;
r[55].junc1=59;
r[55].junc2=54;
r[55].timeonfreeroad=6.551948;

r[56].roadid=56;
r[56].roadlength=56;
r[56].junc1=55;
r[56].junc2=59;
r[56].timeonfreeroad=4.031968;

r[57].roadid=57;
r[57].roadlength=62;
r[57].junc1=57;
r[57].junc2=56;
r[57].timeonfreeroad=4.463964;

r[58].roadid=58;
r[58].roadlength=23;
r[58].junc1=61;
r[58].junc2=57;
r[58].timeonfreeroad=1.655987;

r[59].roadid=59;
r[59].roadlength=20;
r[59].junc1=59;
r[59].junc2=61;
r[59].timeonfreeroad=1.439988;

r[60].roadid=60;
r[60].roadlength=23;
r[60].junc1=63;
r[60].junc2=59;
r[60].timeonfreeroad=1.655987;

r[61].roadid=61;
r[61].roadlength=148;
r[61].junc1=8;
r[61].junc2=63;
r[61].timeonfreeroad=10.655915;

r[62].roadid=62;
r[62].roadlength=94;
r[62].junc1=57;
r[62].junc2=66;
r[62].timeonfreeroad=6.767946;

r[63].roadid=63;
r[63].roadlength=135;
r[63].junc1=58;
r[63].junc2=57;
r[63].timeonfreeroad=9.719922;

r[64].roadid=64;
r[64].roadlength=30;
r[64].junc1=61;
r[64].junc2=60;
r[64].timeonfreeroad=2.159983;

r[65].roadid=65;
r[65].roadlength=68;
r[65].junc1=62;
r[65].junc2=61;
r[65].timeonfreeroad=4.895961;

r[66].roadid=66;
r[66].roadlength=51;
r[66].junc1=64;
r[66].junc2=63;
r[66].timeonfreeroad=3.671971;

r[67].roadid=67;
r[67].roadlength=315;
r[67].junc1=65;
r[67].junc2=41;
r[67].timeonfreeroad=22.679819;

r[68].roadid=68;
r[68].roadlength=186;
r[68].junc1=54;
r[68].junc2=9;
r[68].timeonfreeroad=13.391893;

r[69].roadid=69;
r[69].roadlength=53;
r[69].junc1=66;
r[69].junc2=54;
r[69].timeonfreeroad=3.815969;

r[70].roadid=70;
r[70].roadlength=55;
r[70].junc1=53;
r[70].junc2=66;
r[70].timeonfreeroad=3.959968;

r[71].roadid=71;
r[71].roadlength=94;
r[71].junc1=71;
r[71].junc2=53;
r[71].timeonfreeroad=6.767946;

r[72].roadid=72;
r[72].roadlength=98;
r[72].junc1=47;
r[72].junc2=67;
r[72].timeonfreeroad=7.055944;

r[73].roadid=73;
r[73].roadlength=70;
r[73].junc1=68;
r[73].junc2=47;
r[73].timeonfreeroad=5.039960;

r[74].roadid=74;
r[74].roadlength=292;
r[74].junc1=21;
r[74].junc2=2;
r[74].timeonfreeroad=21.023832;

r[75].roadid=75;
r[75].roadlength=75;
r[75].junc1=45;
r[75].junc2=70;
r[75].timeonfreeroad=5.399957;

r[76].roadid=76;
r[76].roadlength=31;
r[76].junc1=46;
r[76].junc2=45;
r[76].timeonfreeroad=2.231982;

r[77].roadid=77;
r[77].roadlength=8;
r[77].junc1=44;
r[77].junc2=46;
r[77].timeonfreeroad=0.575995;

r[78].roadid=78;
r[78].roadlength=46;
r[78].junc1=69;
r[78].junc2=44;
r[78].timeonfreeroad=3.311974;

r[79].roadid=79;
r[79].roadlength=113;
r[79].junc1=1;
r[79].junc2=45;
r[79].timeonfreeroad=8.135935;

r[80].roadid=80;
r[80].roadlength=68;
r[80].junc1=71;
r[80].junc2=42;
r[80].timeonfreeroad=4.895961;

r[81].roadid=81;
r[81].roadlength=10;
r[81].junc1=37;
r[81].junc2=71;
r[81].timeonfreeroad=0.719994;

r[82].roadid=82;
r[82].roadlength=133;
r[82].junc1=67;
r[82].junc2=37;
r[82].timeonfreeroad=9.575923;

r[83].roadid=83;
r[83].roadlength=255;
r[83].junc1=39;
r[83].junc2=67;
r[83].timeonfreeroad=18.359853;

r[84].roadid=84;
r[84].roadlength=152;
r[84].junc1=2;
r[84].junc2=6;
r[84].timeonfreeroad=10.943912;

r[85].roadid=85;
r[85].roadlength=49;
r[85].junc1=32;
r[85].junc2=0;
r[85].timeonfreeroad=3.527972;

r[86].roadid=86;
r[86].roadlength=189;
r[86].junc1=25;
r[86].junc2=32;
r[86].timeonfreeroad=13.607891;

r[87].roadid=87;
r[87].roadlength=25;
r[87].junc1=36;
r[87].junc2=25;
r[87].timeonfreeroad=1.799986;

r[88].roadid=88;
r[88].roadlength=19;
r[88].junc1=13;
r[88].junc2=36;
r[88].timeonfreeroad=1.367989;

r[89].roadid=89;
r[89].roadlength=383;
r[89].junc1=14;
r[89].junc2=13;
r[89].timeonfreeroad=27.575779;

r[90].roadid=90;
r[90].roadlength=309;
r[90].junc1=5;
r[90].junc2=56;
r[90].timeonfreeroad=22.247822;

r[91].roadid=91;
r[91].roadlength=94;
r[91].junc1=56;
r[91].junc2=53;
r[91].timeonfreeroad=6.767946;

r[92].roadid=92;
r[92].roadlength=60;
r[92].junc1=53;
r[92].junc2=41;
r[92].timeonfreeroad=4.319965;

r[93].roadid=93;
r[93].roadlength=45;
r[93].junc1=41;
r[93].junc2=6;
r[93].timeonfreeroad=3.239974;

r[94].roadid=94;
r[94].roadlength=226;
r[94].junc1=7;
r[94].junc2=24;
r[94].timeonfreeroad=16.271870;

r[95].roadid=95;
r[95].roadlength=74;
r[95].junc1=24;
r[95].junc2=6;
r[95].timeonfreeroad=5.327957;

r[96].roadid=96;
r[96].roadlength=80;
r[96].junc1=23;
r[96].junc2=3;
r[96].timeonfreeroad=5.759954;

r[97].roadid=97;
r[97].roadlength=6;
r[97].junc1=3;
r[97].junc2=22;
r[97].timeonfreeroad=0.431997;

r[98].roadid=98;
r[98].roadlength=76;
r[98].junc1=16;
r[98].junc2=0;
r[98].timeonfreeroad=5.471956;

r[99].roadid=99;
r[99].roadlength=80;
r[99].junc1=0;
r[99].junc2=28;
r[99].timeonfreeroad=5.759954;

r[100].roadid=100;
r[100].roadlength=370;
r[100].junc1=28;
r[100].junc2=72;
r[100].timeonfreeroad=26.639787;

r[101].roadid=101;
r[101].roadlength=74;
r[101].junc1=22;
r[101].junc2=2;
r[101].timeonfreeroad=5.327957;

r[102].roadid=102;
r[102].roadlength=57;
r[102].junc1=2;
r[102].junc2=19;
r[102].timeonfreeroad=4.103967;

r[103].roadid=103;
r[103].roadlength=24;
r[103].junc1=19;
r[103].junc2=38;
r[103].timeonfreeroad=1.727986;

r[104].roadid=104;
r[104].roadlength=34;
r[104].junc1=38;
r[104].junc2=18;
r[104].timeonfreeroad=2.447980;

r[105].roadid=105;
r[105].roadlength=3;
r[105].junc1=18;
r[105].junc2=43;
r[105].timeonfreeroad=0.215998;

r[106].roadid=106;
r[106].roadlength=47;
r[106].junc1=43;
r[106].junc2=1;
r[106].timeonfreeroad=3.383973;

r[107].roadid=107;
r[107].roadlength=75;
r[107].junc1=1;
r[107].junc2=34;
r[107].timeonfreeroad=5.399957;

r[108].roadid=108;
r[108].roadlength=6;
r[108].junc1=34;
r[108].junc2=16;
r[108].timeonfreeroad=0.431997;

r[109].roadid=109;
r[109].roadlength=281;
r[109].junc1=10;
r[109].junc2=0;
r[109].timeonfreeroad=20.231838;

r[110].roadid=110;
r[110].roadlength=286;
r[110].junc1=15;
r[110].junc2=16;
r[110].timeonfreeroad=20.591835;

r[111].roadid=111;
r[111].roadlength=294;
r[111].junc1=1;
r[111].junc2=17;
r[111].timeonfreeroad=21.167831;

r[112].roadid=112;
r[112].roadlength=298;
r[112].junc1=11;
r[112].junc2=18;
r[112].timeonfreeroad=21.455828;

r[113].roadid=113;
r[113].roadlength=300;
r[113].junc1=19;
r[113].junc2=20;
r[113].timeonfreeroad=21.599827;

r[114].roadid=114;
r[114].roadlength=287;
r[114].junc1=22;
r[114].junc2=12;
r[114].timeonfreeroad=20.663835;

r[115].roadid=115;
r[115].roadlength=154;
r[115].junc1=3;
r[115].junc2=24;
r[115].timeonfreeroad=11.087911;

r[116].roadid=116;
r[116].roadlength=392;
r[116].junc1=4;
r[116].junc2=26;
r[116].timeonfreeroad=28.223774;

r[117].roadid=117;
r[117].roadlength=86;
r[117].junc1=26;
r[117].junc2=13;
r[117].timeonfreeroad=6.191950;

r[118].roadid=118;
r[118].roadlength=166;
r[118].junc1=31;
r[118].junc2=27;
r[118].timeonfreeroad=11.951904;

r[119].roadid=119;
r[119].roadlength=83;
r[119].junc1=27;
r[119].junc2=25;
r[119].timeonfreeroad=5.975952;

r[120].roadid=120;
r[120].roadlength=54;
r[120].junc1=26;
r[120].junc2=27;
r[120].timeonfreeroad=3.887969;

r[121].roadid=121;
r[121].roadlength=187;
r[121].junc1=27;
r[121].junc2=29;
r[121].timeonfreeroad=13.463892;

r[122].roadid=122;
r[122].roadlength=50;
r[122].junc1=29;
r[122].junc2=28;
r[122].timeonfreeroad=3.599971;

r[123].roadid=123;
r[123].roadlength=62;
r[123].junc1=28;
r[123].junc2=33;
r[123].timeonfreeroad=4.463964;

r[124].roadid=124;
r[124].roadlength=79;
r[124].junc1=32;
r[124].junc2=29;
r[124].timeonfreeroad=5.687954;

r[125].roadid=125;
r[125].roadlength=169;
r[125].junc1=29;
r[125].junc2=30;
r[125].timeonfreeroad=12.167903;

r[126].roadid=126;
r[126].roadlength=107;
r[126].junc1=34;
r[126].junc2=70;
r[126].timeonfreeroad=7.703938;

r[127].roadid=127;
r[127].roadlength=80;
r[127].junc1=70;
r[127].junc2=40;
r[127].timeonfreeroad=5.759954;

r[128].roadid=128;
r[128].roadlength=73;
r[128].junc1=40;
r[128].junc2=35;
r[128].timeonfreeroad=5.255958;

r[129].roadid=129;
r[129].roadlength=70;
r[129].junc1=36;
r[129].junc2=35;
r[129].timeonfreeroad=5.039960;

r[130].roadid=130;
r[130].roadlength=10;
r[130].junc1=35;
r[130].junc2=51;
r[130].timeonfreeroad=0.719994;

r[131].roadid=131;
r[131].roadlength=85;
r[131].junc1=51;
r[131].junc2=50;
r[131].timeonfreeroad=6.119951;

r[132].roadid=132;
r[132].roadlength=82;
r[132].junc1=50;
r[132].junc2=37;
r[132].timeonfreeroad=5.903953;

r[133].roadid=133;
r[133].roadlength=124;
r[133].junc1=38;
r[133].junc2=69;
r[133].timeonfreeroad=8.927929;

r[134].roadid=134;
r[134].roadlength=69;
r[134].junc1=69;
r[134].junc2=42;
r[134].timeonfreeroad=4.967960;

r[135].roadid=135;
r[135].roadlength=105;
r[135].junc1=40;
r[135].junc2=49;
r[135].timeonfreeroad=7.559940;

r[136].roadid=136;
r[136].roadlength=74;
r[136].junc1=49;
r[136].junc2=42;
r[136].timeonfreeroad=5.327957;

r[137].roadid=137;
r[137].roadlength=93;
r[137].junc1=42;
r[137].junc2=41;
r[137].timeonfreeroad=6.695946;

r[138].roadid=138;
r[138].roadlength=122;
r[138].junc1=43;
r[138].junc2=44;
r[138].timeonfreeroad=8.783930;

r[139].roadid=139;
r[139].roadlength=68;
r[139].junc1=46;
r[139].junc2=49;
r[139].timeonfreeroad=4.895961;

r[140].roadid=140;
r[140].roadlength=79;
r[140].junc1=49;
r[140].junc2=50;
r[140].timeonfreeroad=5.687954;

r[141].roadid=141;
r[141].roadlength=134;
r[141].junc1=50;
r[141].junc2=47;
r[141].timeonfreeroad=9.647923;

r[142].roadid=142;
r[142].roadlength=261;
r[142].junc1=47;
r[142].junc2=48;
r[142].timeonfreeroad=18.791850;

r[143].roadid=143;
r[143].roadlength=136;
r[143].junc1=51;
r[143].junc2=68;
r[143].timeonfreeroad=9.791922;

r[144].roadid=144;
r[144].roadlength=266;
r[144].junc1=68;
r[144].junc2=52;
r[144].timeonfreeroad=19.151847;

r[145].roadid=145;
r[145].roadlength=91;
r[145].junc1=54;
r[145].junc2=59;
r[145].timeonfreeroad=6.551948;

r[146].roadid=146;
r[146].roadlength=56;
r[146].junc1=59;
r[146].junc2=55;
r[146].timeonfreeroad=4.031968;

r[147].roadid=147;
r[147].roadlength=62;
r[147].junc1=56;
r[147].junc2=57;
r[147].timeonfreeroad=4.463964;

r[148].roadid=148;
r[148].roadlength=23;
r[148].junc1=57;
r[148].junc2=61;
r[148].timeonfreeroad=1.655987;

r[149].roadid=149;
r[149].roadlength=20;
r[149].junc1=61;
r[149].junc2=59;
r[149].timeonfreeroad=1.439988;

r[150].roadid=150;
r[150].roadlength=23;
r[150].junc1=59;
r[150].junc2=63;
r[150].timeonfreeroad=1.655987;

r[151].roadid=151;
r[151].roadlength=148;
r[151].junc1=63;
r[151].junc2=8;
r[151].timeonfreeroad=10.655915;

r[152].roadid=152;
r[152].roadlength=94;
r[152].junc1=66;
r[152].junc2=57;
r[152].timeonfreeroad=6.767946;

r[153].roadid=153;
r[153].roadlength=135;
r[153].junc1=57;
r[153].junc2=58;
r[153].timeonfreeroad=9.719922;

r[154].roadid=154;
r[154].roadlength=30;
r[154].junc1=60;
r[154].junc2=61;
r[154].timeonfreeroad=2.159983;

r[155].roadid=155;
r[155].roadlength=68;
r[155].junc1=61;
r[155].junc2=62;
r[155].timeonfreeroad=4.895961;

r[156].roadid=156;
r[156].roadlength=51;
r[156].junc1=63;
r[156].junc2=64;
r[156].timeonfreeroad=3.671971;

r[157].roadid=157;
r[157].roadlength=315;
r[157].junc1=41;
r[157].junc2=65;
r[157].timeonfreeroad=22.679819;

r[158].roadid=158;
r[158].roadlength=187;
r[158].junc1=9;
r[158].junc2=54;
r[158].timeonfreeroad=13.463892;

r[159].roadid=159;
r[159].roadlength=53;
r[159].junc1=54;
r[159].junc2=66;
r[159].timeonfreeroad=3.815969;

r[160].roadid=160;
r[160].roadlength=55;
r[160].junc1=66;
r[160].junc2=53;
r[160].timeonfreeroad=3.959968;

r[161].roadid=161;
r[161].roadlength=94;
r[161].junc1=53;
r[161].junc2=71;
r[161].timeonfreeroad=6.767946;

r[162].roadid=162;
r[162].roadlength=98;
r[162].junc1=67;
r[162].junc2=47;
r[162].timeonfreeroad=7.055944;

r[163].roadid=163;
r[163].roadlength=70;
r[163].junc1=47;
r[163].junc2=68;
r[163].timeonfreeroad=5.039960;

r[164].roadid=164;
r[164].roadlength=292;
r[164].junc1=2;
r[164].junc2=21;
r[164].timeonfreeroad=21.023832;

r[165].roadid=165;
r[165].roadlength=75;
r[165].junc1=70;
r[165].junc2=45;
r[165].timeonfreeroad=5.399957;

r[166].roadid=166;
r[166].roadlength=31;
r[166].junc1=45;
r[166].junc2=46;
r[166].timeonfreeroad=2.231982;

r[167].roadid=167;
r[167].roadlength=8;
r[167].junc1=46;
r[167].junc2=44;
r[167].timeonfreeroad=0.575995;

r[168].roadid=168;
r[168].roadlength=46;
r[168].junc1=44;
r[168].junc2=69;
r[168].timeonfreeroad=3.311974;

r[169].roadid=169;
r[169].roadlength=113;
r[169].junc1=45;
r[169].junc2=1;
r[169].timeonfreeroad=8.135935;

r[170].roadid=170;
r[170].roadlength=68;
r[170].junc1=42;
r[170].junc2=71;
r[170].timeonfreeroad=4.895961;

r[171].roadid=171;
r[171].roadlength=10;
r[171].junc1=71;
r[171].junc2=37;
r[171].timeonfreeroad=0.719994;

r[172].roadid=172;
r[172].roadlength=133;
r[172].junc1=37;
r[172].junc2=67;
r[172].timeonfreeroad=9.575923;

r[173].roadid=173;
r[173].roadlength=255;
r[173].junc1=67;
r[173].junc2=39;
r[173].timeonfreeroad=18.359853;

r[174].roadid=174;
r[174].roadlength=152;
r[174].junc1=6;
r[174].junc2=2;
r[174].timeonfreeroad=10.943912;

r[175].roadid=175;
r[175].roadlength=49;
r[175].junc1=0;
r[175].junc2=32;
r[175].timeonfreeroad=3.527972;

r[176].roadid=176;
r[176].roadlength=189;
r[176].junc1=32;
r[176].junc2=25;
r[176].timeonfreeroad=13.607891;

r[177].roadid=177;
r[177].roadlength=25;
r[177].junc1=25;
r[177].junc2=36;
r[177].timeonfreeroad=1.799986;

r[178].roadid=178;
r[178].roadlength=19;
r[178].junc1=36;
r[178].junc2=13;
r[178].timeonfreeroad=1.367989;

r[179].roadid=179;
r[179].roadlength=383;
r[179].junc1=13;
r[179].junc2=14;
r[179].timeonfreeroad=27.575779;

dp_count=73;

j[0].juncid=0;
j[0].x_position=286;
j[0].y_position=521;

j[1].juncid=1;
j[1].x_position=327;
j[1].y_position=700;

j[2].juncid=2;
j[2].x_position=373;
j[2].y_position=909;

j[3].juncid=3;
j[3].x_position=395;
j[3].y_position=1008;

j[4].juncid=4;
j[4].x_position=536;
j[4].y_position=88;

j[5].juncid=5;
j[5].x_position=1068;
j[5].y_position=772;

j[6].juncid=6;
j[6].x_position=535;
j[6].y_position=880;

j[7].juncid=7;
j[7].x_position=622;
j[7].y_position=1184;

j[8].juncid=8;
j[8].x_position=796;
j[8].y_position=1155;

j[9].juncid=9;
j[9].x_position=717;
j[9].y_position=1170;

j[10].juncid=10;
j[10].x_position=0;
j[10].y_position=562;

j[11].juncid=11;
j[11].x_position=38;
j[11].y_position=819;

j[12].juncid=12;
j[12].x_position=102;
j[12].y_position=1046;

j[13].juncid=13;
j[13].x_position=607;
j[13].y_position=473;

j[14].juncid=14;
j[14].x_position=986;
j[14].y_position=388;

j[15].juncid=15;
j[15].x_position=12;
j[15].y_position=649;

j[16].juncid=16;
j[16].x_position=305;
j[16].y_position=610;

j[17].juncid=17;
j[17].x_position=26;
j[17].y_position=737;

j[18].juncid=18;
j[18].x_position=341;
j[18].y_position=769;

j[19].juncid=19;
j[19].x_position=358;
j[19].y_position=844;

j[20].juncid=20;
j[20].x_position=61;
j[20].y_position=924;

j[21].juncid=21;
j[21].x_position=82;
j[21].y_position=987;

j[22].juncid=22;
j[22].x_position=392;
j[22].y_position=991;

j[23].juncid=23;
j[23].x_position=419;
j[23].y_position=1090;

j[24].juncid=24;
j[24].x_position=556;
j[24].y_position=962;

j[25].juncid=25;
j[25].x_position=546;
j[25].y_position=483;

j[26].juncid=26;
j[26].x_position=589;
j[26].y_position=376;

j[27].juncid=27;
j[27].x_position=526;
j[27].y_position=389;

j[28].juncid=28;
j[28].x_position=268;
j[28].y_position=429;

j[29].juncid=29;
j[29].x_position=332;
j[29].y_position=422;

j[30].juncid=30;
j[30].x_position=302;
j[30].y_position=250;

j[31].juncid=31;
j[31].x_position=497;
j[31].y_position=220;

j[32].juncid=32;
j[32].x_position=349;
j[32].y_position=512;

j[33].juncid=33;
j[33].x_position=199;
j[33].y_position=441;

j[34].juncid=34;
j[34].x_position=307;
j[34].y_position=616;

j[35].juncid=35;
j[35].x_position=596;
j[35].y_position=561;

j[36].juncid=36;
j[36].x_position=580;
j[36].y_position=480;

j[37].juncid=37;
j[37].x_position=650;
j[37].y_position=751;

j[38].juncid=38;
j[38].x_position=351;
j[38].y_position=811;

j[39].juncid=39;
j[39].x_position=1044;
j[39].y_position=665;

j[40].juncid=40;
j[40].x_position=514;
j[40].y_position=577;

j[41].juncid=41;
j[41].x_position=589;
j[41].y_position=869;

j[42].juncid=42;
j[42].x_position=564;
j[42].y_position=769;

j[43].juncid=43;
j[43].x_position=338;
j[43].y_position=755;

j[44].juncid=44;
j[44].x_position=472;
j[44].y_position=730;

j[45].juncid=45;
j[45].x_position=451;
j[45].y_position=675;

j[46].juncid=46;
j[46].x_position=466;
j[46].y_position=713;

j[47].juncid=47;
j[47].x_position=762;
j[47].y_position=616;

j[48].juncid=48;
j[48].x_position=1022;
j[48].y_position=559;

j[49].juncid=49;
j[49].x_position=540;
j[49].y_position=689;

j[50].juncid=50;
j[50].x_position=626;
j[50].y_position=662;

j[51].juncid=51;
j[51].x_position=598;
j[51].y_position=571;

j[52].juncid=52;
j[52].x_position=1005;
j[52].y_position=478;

j[53].juncid=53;
j[53].x_position=658;
j[53].y_position=855;

j[54].juncid=54;
j[54].x_position=675;
j[54].y_position=983;

j[55].juncid=55;
j[55].x_position=836;
j[55].y_position=962;

j[56].juncid=56;
j[56].x_position=760;
j[56].y_position=835;

j[57].juncid=57;
j[57].x_position=768;
j[57].y_position=907;

j[58].juncid=58;
j[58].x_position=907;
j[58].y_position=889;

j[59].juncid=59;
j[59].x_position=775;
j[59].y_position=970;

j[60].juncid=60;
j[60].x_position=737;
j[60].y_position=943;

j[61].juncid=61;
j[61].x_position=772;
j[61].y_position=940;

j[62].juncid=62;
j[62].x_position=844;
j[62].y_position=929;

j[63].juncid=63;
j[63].x_position=778;
j[63].y_position=1003;

j[64].juncid=64;
j[64].x_position=834;
j[64].y_position=995;

j[65].juncid=65;
j[65].x_position=658;
j[65].y_position=1182;

j[66].juncid=66;
j[66].x_position=665;
j[66].y_position=921;

j[67].juncid=67;
j[67].x_position=789;
j[67].y_position=720;

j[68].juncid=68;
j[68].x_position=741;
j[68].y_position=539;

j[69].juncid=69;
j[69].x_position=486;
j[69].y_position=784;

j[70].juncid=70;
j[70].x_position=425;
j[70].y_position=593;

j[71].juncid=71;
j[71].x_position=640;
j[71].y_position=753;

j[72].juncid=72;
j[72].x_position=213;
j[72].y_position=60;



	//initializing total road length
		total_roadlength=0.0;
		for(int k=0;k<n;k++)
			total_roadlength+=getroadlength(k);
       }

	/*
		implementation of getroadlength(int roadid) function
		returns the roadlength given a road id
	*/
   int gps::getroadlength(int roadid)
    {
         if(roadid>=n)
            return -1;
       return r[roadid].roadlength;
    }

	/*
		implementation of getjunc1(int roadid) function
		returns the junction at the beginning for a given a road id
	*/

   int gps::getjunc1(int roadid)
    {
         if(roadid>=n)
            return -1;
       return r[roadid].junc1;
    }
	/*
		implementation of getjunc2(int roadid) function
		returns the junction at the end for a given a road id
	*/
   

   int gps::getjunc2(int roadid)
    {
         if(roadid>=n)
            return -1;
       return r[roadid].junc2;
    }
	/*
		implementation of getroadid(int j1,int j2) function
		returns the road id given the junction at the beginning,end of a road 
	*/

   int gps::getroadid(int j1,int j2)
    {
       for(int i=0;i<n;i++)
         if(r[i].junc1==j1 && r[i].junc2==j2)
           return r[i].roadid;
       return -1;
    }

	/*
		implementation of gettimeonfreeroad(int roadid) function
		returns the time taken for crossing the road segment when road is empty
		data used for cost evaluation method	
	*/
   double gps::gettimeonfreeroad(int roadid)
    {
         if(roadid>=n)
            return -1;
       return r[roadid].timeonfreeroad;
    }
 
	/*
		implementation of get_junc_x_pos(int juncid) function
		returns the x coordinate of the given junction
	*/
    //junction table functions
    double gps::get_junc_x_pos(int juncid)
    {
         if(juncid>=dp_count)
	    return -1;
	return j[juncid].x_position;
    }

	/*
		implementation of get_junc_y_pos(int juncid) function
		returns the y coordinate of the given junction
	*/
    double gps::get_junc_y_pos(int juncid)
    {
         if(juncid>=dp_count)
	    return -1;
	return j[juncid].y_position;
    }

	/*
		implementation of get_juncid(int x_pos, int y_pos) function
		returns the junction id for given x and y coordinates
	*/
    int gps::get_juncid(double x_pos, double y_pos)
    {
	for(int i=0;i<dp_count;i++)
         if(j[i].x_position==x_pos && j[i].y_position==y_pos)
           return j[i].juncid;
       return -1; 
    }
 int gps::isnearjunc(double xpos, double ypos,int roadid)
    {
		double differ=7.0;
		double xdiffer,ydiffer;
		
		int juncid=getjunc2(roadid);		
	
		xdiffer=j[juncid].x_position-xpos;
		ydiffer=j[juncid].y_position-ypos;

		if(xdiffer<0.0)
			xdiffer*=(-1);
		if(ydiffer<0.0)
			ydiffer*=(-1);
         if(xdiffer<=differ && ydiffer<=differ)
	{
		//printf("xdiff %lf ydiff %lf diff %lf /// xpos %lf ypos %lf junction->%d roadid->\n",xdiffer,ydiffer,differ,xpos,ypos,juncid,roadid);
                return juncid;
	}	
// printf("Flop xdiff %lf ydiff %lf diff %lf /// xpos %lf ypos %lf junction->%d road->%d\n",xdiffer,ydiffer,differ,xpos,ypos,juncid,roadid);
       return -1; 
    }
  int gps::get_my_road(double x3,double y3,double desx,double desy)
{
	double junc1x,junc1y;
	double junc2x,junc2y;
	double dist1=0.0,dist2=0.0;
//printf("in get my road\n");
	for(int i=0;i<n;i++)
	{
		//printf("start %d\n",i);
		junc1x=j[r[i].junc1].x_position;
		junc1y=j[r[i].junc1].y_position;
		junc2x=j[r[i].junc2].x_position;	
		junc2y=j[r[i].junc2].y_position;


		

if((junc1y-junc2y > RANGE_MIN && junc1y-junc2y < RANGE_MAX && junc2y-y3 > RANGE_MIN && junc2y-y3 < RANGE_MAX) || (junc1x-junc2x > RANGE_MIN && junc1x-junc2x < RANGE_MAX && junc2x-x3 > RANGE_MIN && junc2x-x3 < RANGE_MAX))
{
		
			dist1=sqrt((junc2x-x3)*(junc2x-x3)+(junc2y-y3)*(junc2y-y3));
			dist2=sqrt((junc2x-desx)*(junc2x-desx)+(junc2y-desy)*(junc2y-desy));
			
			if(dist2<dist1) {
				return i;
			}	
			else {
				
				//getchar();
				continue;
			}
	
}
// if both the points not collinear. for example, if junc1x = 0, junc2x = 0 and x3 is not 0
if((junc1y-junc2y > RANGE_MIN && junc1y-junc2y < RANGE_MAX && (junc2y-y3 > RANGE_MAX || junc2y-y3 < RANGE_MIN)) || ((junc1y-junc2y > RANGE_MAX || junc1y-junc2y < RANGE_MIN) && junc2y-y3 < RANGE_MAX && junc2y-y3 > RANGE_MIN) || (junc1x-junc2x >RANGE_MIN && junc1x-junc2x <RANGE_MAX && (junc2x-x3 > RANGE_MAX || junc2x-x3 < RANGE_MIN)) || ((junc1x-junc2x >RANGE_MAX || junc1x-junc2x < RANGE_MIN) && junc2x-x3 < RANGE_MAX && junc2x-x3 > RANGE_MIN))
{

continue;
}


//	printf("2here\n");
//printf("point (%lf ,%lf) j1 (%lf ,%lf) j2 (%lf ,%lf) dest(%lf ,%lf)\n",x3,y3,junc1x,junc1y,junc2x,junc2y,desx,desy);



// if all the points are in the same slope
if(((junc2x-junc1x)/(junc2y-junc1y) - (x3-junc2x)/(y3-junc2y) > RANGE_MIN) && ((junc2x-junc1x)/(junc2y-junc1y) - (x3-junc2x)/(y3-junc2y) < RANGE_MAX))
{ 
// if the sum of distance between (junc1x,junc1y)-(x3,y3) and (junc2x,junc2y)-(x3,y3) is equal to (junc1x,junc1y)-(junc2x,junc2y)
if((sqrt(pow(x3-junc1x,2)+pow(y3-junc1y,2)) + sqrt(pow(x3-junc2x,2)+pow(y3-junc2y,2)) - sqrt(pow(junc1x-junc2x,2)+pow(junc1y-junc2y,2)) > RANGE_MIN) && (sqrt(pow(x3-junc1x,2)+pow(y3-junc1y,2)) + sqrt(pow(x3-junc2x,2)+pow(y3-junc2y,2)) - sqrt(pow(junc1x-junc2x,2)+pow(junc1y-junc2y,2)) < RANGE_MAX))
{

			dist1=sqrt((junc2x-x3)*(junc2x-x3)+(junc2y-y3)*(junc2y-y3));
			dist2=sqrt((junc2x-desx)*(junc2x-desx)+(junc2y-desy)*(junc2y-desy));
			
			if(dist2<dist1) {
				return i;
			}	
			else {
				
				//getchar();
				continue;
			}
}
}

}

return -1;
}
