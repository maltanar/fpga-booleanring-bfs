#include <iostream>
#include "sdcard.h"

const unsigned int matrixCountP4 = 17;

void * loadMatrixP4(unsigned int id) {
switch(id) {
case 0:
	readFromSDCard("rmat-16-8-csc-4/rmat-16-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-16-8-csc-4/rmat-16-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-16-8-csc-4/rmat-16-8-csc-0-inds.bin", 268701696);
	readFromSDCard("rmat-16-8-csc-4/rmat-16-8-csc-1-meta.bin", 269199360);
	readFromSDCard("rmat-16-8-csc-4/rmat-16-8-csc-1-indptr.bin", 269201408);
	readFromSDCard("rmat-16-8-csc-4/rmat-16-8-csc-1-inds.bin", 269465600);
	readFromSDCard("rmat-16-8-csc-4/rmat-16-8-csc-2-meta.bin", 269942784);
	readFromSDCard("rmat-16-8-csc-4/rmat-16-8-csc-2-indptr.bin", 269944832);
	readFromSDCard("rmat-16-8-csc-4/rmat-16-8-csc-2-inds.bin", 270209024);
	readFromSDCard("rmat-16-8-csc-4/rmat-16-8-csc-3-meta.bin", 270712832);
	readFromSDCard("rmat-16-8-csc-4/rmat-16-8-csc-3-indptr.bin", 270714880);
	readFromSDCard("rmat-16-8-csc-4/rmat-16-8-csc-3-inds.bin", 270979072);
	readFromSDCard("rmat-16-8-csc-4/config.bin", 268435456);

break;
case 1:
	readFromSDCard("rmat-16-16-csc-4/rmat-16-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-16-16-csc-4/rmat-16-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-16-16-csc-4/rmat-16-16-csc-0-inds.bin", 268699648);
	readFromSDCard("rmat-16-16-csc-4/rmat-16-16-csc-1-meta.bin", 269658112);
	readFromSDCard("rmat-16-16-csc-4/rmat-16-16-csc-1-indptr.bin", 269660160);
	readFromSDCard("rmat-16-16-csc-4/rmat-16-16-csc-1-inds.bin", 269922304);
	readFromSDCard("rmat-16-16-csc-4/rmat-16-16-csc-2-meta.bin", 270862336);
	readFromSDCard("rmat-16-16-csc-4/rmat-16-16-csc-2-indptr.bin", 270864384);
	readFromSDCard("rmat-16-16-csc-4/rmat-16-16-csc-2-inds.bin", 271126528);
	readFromSDCard("rmat-16-16-csc-4/rmat-16-16-csc-3-meta.bin", 272078848);
	readFromSDCard("rmat-16-16-csc-4/rmat-16-16-csc-3-indptr.bin", 272080896);
	readFromSDCard("rmat-16-16-csc-4/rmat-16-16-csc-3-inds.bin", 272343040);
	readFromSDCard("rmat-16-16-csc-4/config.bin", 268435456);

break;
case 2:
	readFromSDCard("rmat-16-32-csc-4/rmat-16-32-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-16-32-csc-4/rmat-16-32-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-16-32-csc-4/rmat-16-32-csc-0-inds.bin", 268699648);
	readFromSDCard("rmat-16-32-csc-4/rmat-16-32-csc-1-meta.bin", 270487552);
	readFromSDCard("rmat-16-32-csc-4/rmat-16-32-csc-1-indptr.bin", 270489600);
	readFromSDCard("rmat-16-32-csc-4/rmat-16-32-csc-1-inds.bin", 270751744);
	readFromSDCard("rmat-16-32-csc-4/rmat-16-32-csc-2-meta.bin", 272619520);
	readFromSDCard("rmat-16-32-csc-4/rmat-16-32-csc-2-indptr.bin", 272621568);
	readFromSDCard("rmat-16-32-csc-4/rmat-16-32-csc-2-inds.bin", 272883712);
	readFromSDCard("rmat-16-32-csc-4/rmat-16-32-csc-3-meta.bin", 274630656);
	readFromSDCard("rmat-16-32-csc-4/rmat-16-32-csc-3-indptr.bin", 274632704);
	readFromSDCard("rmat-16-32-csc-4/rmat-16-32-csc-3-inds.bin", 274894848);
	readFromSDCard("rmat-16-32-csc-4/config.bin", 268435456);

break;
case 3:
	readFromSDCard("rmat-17-8-csc-4/rmat-17-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-17-8-csc-4/rmat-17-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-17-8-csc-4/rmat-17-8-csc-0-inds.bin", 268961792);
	readFromSDCard("rmat-17-8-csc-4/rmat-17-8-csc-1-meta.bin", 269928448);
	readFromSDCard("rmat-17-8-csc-4/rmat-17-8-csc-1-indptr.bin", 269930496);
	readFromSDCard("rmat-17-8-csc-4/rmat-17-8-csc-1-inds.bin", 270454784);
	readFromSDCard("rmat-17-8-csc-4/rmat-17-8-csc-2-meta.bin", 271468544);
	readFromSDCard("rmat-17-8-csc-4/rmat-17-8-csc-2-indptr.bin", 271470592);
	readFromSDCard("rmat-17-8-csc-4/rmat-17-8-csc-2-inds.bin", 271994880);
	readFromSDCard("rmat-17-8-csc-4/rmat-17-8-csc-3-meta.bin", 273020928);
	readFromSDCard("rmat-17-8-csc-4/rmat-17-8-csc-3-indptr.bin", 273022976);
	readFromSDCard("rmat-17-8-csc-4/rmat-17-8-csc-3-inds.bin", 273547264);
	readFromSDCard("rmat-17-8-csc-4/config.bin", 268435456);

break;
case 4:
	readFromSDCard("rmat-17-16-csc-4/rmat-17-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-17-16-csc-4/rmat-17-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-17-16-csc-4/rmat-17-16-csc-0-inds.bin", 268961792);
	readFromSDCard("rmat-17-16-csc-4/rmat-17-16-csc-1-meta.bin", 270974976);
	readFromSDCard("rmat-17-16-csc-4/rmat-17-16-csc-1-indptr.bin", 270977024);
	readFromSDCard("rmat-17-16-csc-4/rmat-17-16-csc-1-inds.bin", 271501312);
	readFromSDCard("rmat-17-16-csc-4/rmat-17-16-csc-2-meta.bin", 273512448);
	readFromSDCard("rmat-17-16-csc-4/rmat-17-16-csc-2-indptr.bin", 273514496);
	readFromSDCard("rmat-17-16-csc-4/rmat-17-16-csc-2-inds.bin", 274038784);
	readFromSDCard("rmat-17-16-csc-4/rmat-17-16-csc-3-meta.bin", 275845120);
	readFromSDCard("rmat-17-16-csc-4/rmat-17-16-csc-3-indptr.bin", 275847168);
	readFromSDCard("rmat-17-16-csc-4/rmat-17-16-csc-3-inds.bin", 276371456);
	readFromSDCard("rmat-17-16-csc-4/config.bin", 268435456);

break;
case 5:
	readFromSDCard("rmat-17-32-csc-4/rmat-17-32-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-17-32-csc-4/rmat-17-32-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-17-32-csc-4/rmat-17-32-csc-0-inds.bin", 268963840);
	readFromSDCard("rmat-17-32-csc-4/rmat-17-32-csc-1-meta.bin", 272564224);
	readFromSDCard("rmat-17-32-csc-4/rmat-17-32-csc-1-indptr.bin", 272566272);
	readFromSDCard("rmat-17-32-csc-4/rmat-17-32-csc-1-inds.bin", 273092608);
	readFromSDCard("rmat-17-32-csc-4/rmat-17-32-csc-2-meta.bin", 276758528);
	readFromSDCard("rmat-17-32-csc-4/rmat-17-32-csc-2-indptr.bin", 276760576);
	readFromSDCard("rmat-17-32-csc-4/rmat-17-32-csc-2-inds.bin", 277286912);
	readFromSDCard("rmat-17-32-csc-4/rmat-17-32-csc-3-meta.bin", 281034752);
	readFromSDCard("rmat-17-32-csc-4/rmat-17-32-csc-3-indptr.bin", 281036800);
	readFromSDCard("rmat-17-32-csc-4/rmat-17-32-csc-3-inds.bin", 281563136);
	readFromSDCard("rmat-17-32-csc-4/config.bin", 268435456);

break;
case 6:
	readFromSDCard("rmat-18-8-csc-4/rmat-18-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-18-8-csc-4/rmat-18-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-18-8-csc-4/rmat-18-8-csc-0-inds.bin", 269486080);
	readFromSDCard("rmat-18-8-csc-4/rmat-18-8-csc-1-meta.bin", 271517696);
	readFromSDCard("rmat-18-8-csc-4/rmat-18-8-csc-1-indptr.bin", 271519744);
	readFromSDCard("rmat-18-8-csc-4/rmat-18-8-csc-1-inds.bin", 272568320);
	readFromSDCard("rmat-18-8-csc-4/rmat-18-8-csc-2-meta.bin", 274612224);
	readFromSDCard("rmat-18-8-csc-4/rmat-18-8-csc-2-indptr.bin", 274614272);
	readFromSDCard("rmat-18-8-csc-4/rmat-18-8-csc-2-inds.bin", 275662848);
	readFromSDCard("rmat-18-8-csc-4/rmat-18-8-csc-3-meta.bin", 277676032);
	readFromSDCard("rmat-18-8-csc-4/rmat-18-8-csc-3-indptr.bin", 277678080);
	readFromSDCard("rmat-18-8-csc-4/rmat-18-8-csc-3-inds.bin", 278726656);
	readFromSDCard("rmat-18-8-csc-4/config.bin", 268435456);

break;
case 7:
	readFromSDCard("rmat-18-16-csc-4/rmat-18-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-18-16-csc-4/rmat-18-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-18-16-csc-4/rmat-18-16-csc-0-inds.bin", 269488128);
	readFromSDCard("rmat-18-16-csc-4/rmat-18-16-csc-1-meta.bin", 273285120);
	readFromSDCard("rmat-18-16-csc-4/rmat-18-16-csc-1-indptr.bin", 273287168);
	readFromSDCard("rmat-18-16-csc-4/rmat-18-16-csc-1-inds.bin", 274337792);
	readFromSDCard("rmat-18-16-csc-4/rmat-18-16-csc-2-meta.bin", 278441984);
	readFromSDCard("rmat-18-16-csc-4/rmat-18-16-csc-2-indptr.bin", 278444032);
	readFromSDCard("rmat-18-16-csc-4/rmat-18-16-csc-2-inds.bin", 279494656);
	readFromSDCard("rmat-18-16-csc-4/rmat-18-16-csc-3-meta.bin", 283322368);
	readFromSDCard("rmat-18-16-csc-4/rmat-18-16-csc-3-indptr.bin", 283324416);
	readFromSDCard("rmat-18-16-csc-4/rmat-18-16-csc-3-inds.bin", 284375040);
	readFromSDCard("rmat-18-16-csc-4/config.bin", 268435456);

break;
case 8:
	readFromSDCard("rmat-18-32-csc-4/rmat-18-32-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-18-32-csc-4/rmat-18-32-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-18-32-csc-4/rmat-18-32-csc-0-inds.bin", 269486080);
	readFromSDCard("rmat-18-32-csc-4/rmat-18-32-csc-1-meta.bin", 277368832);
	readFromSDCard("rmat-18-32-csc-4/rmat-18-32-csc-1-indptr.bin", 277370880);
	readFromSDCard("rmat-18-32-csc-4/rmat-18-32-csc-1-inds.bin", 278419456);
	readFromSDCard("rmat-18-32-csc-4/rmat-18-32-csc-2-meta.bin", 285700096);
	readFromSDCard("rmat-18-32-csc-4/rmat-18-32-csc-2-indptr.bin", 285702144);
	readFromSDCard("rmat-18-32-csc-4/rmat-18-32-csc-2-inds.bin", 286750720);
	readFromSDCard("rmat-18-32-csc-4/rmat-18-32-csc-3-meta.bin", 294526976);
	readFromSDCard("rmat-18-32-csc-4/rmat-18-32-csc-3-indptr.bin", 294529024);
	readFromSDCard("rmat-18-32-csc-4/rmat-18-32-csc-3-inds.bin", 295577600);
	readFromSDCard("rmat-18-32-csc-4/config.bin", 268435456);

break;
case 9:
	readFromSDCard("rmat-19-8-csc-4/rmat-19-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-19-8-csc-4/rmat-19-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-19-8-csc-4/rmat-19-8-csc-0-inds.bin", 270534656);
	readFromSDCard("rmat-19-8-csc-4/rmat-19-8-csc-1-meta.bin", 274587648);
	readFromSDCard("rmat-19-8-csc-4/rmat-19-8-csc-1-indptr.bin", 274589696);
	readFromSDCard("rmat-19-8-csc-4/rmat-19-8-csc-1-inds.bin", 276686848);
	readFromSDCard("rmat-19-8-csc-4/rmat-19-8-csc-2-meta.bin", 280807424);
	readFromSDCard("rmat-19-8-csc-4/rmat-19-8-csc-2-indptr.bin", 280809472);
	readFromSDCard("rmat-19-8-csc-4/rmat-19-8-csc-2-inds.bin", 282906624);
	readFromSDCard("rmat-19-8-csc-4/rmat-19-8-csc-3-meta.bin", 286945280);
	readFromSDCard("rmat-19-8-csc-4/rmat-19-8-csc-3-indptr.bin", 286947328);
	readFromSDCard("rmat-19-8-csc-4/rmat-19-8-csc-3-inds.bin", 289044480);
	readFromSDCard("rmat-19-8-csc-4/config.bin", 268435456);

break;
case 10:
	readFromSDCard("rmat-19-16-csc-4/rmat-19-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-19-16-csc-4/rmat-19-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-19-16-csc-4/rmat-19-16-csc-0-inds.bin", 270534656);
	readFromSDCard("rmat-19-16-csc-4/rmat-19-16-csc-1-meta.bin", 278523904);
	readFromSDCard("rmat-19-16-csc-4/rmat-19-16-csc-1-indptr.bin", 278525952);
	readFromSDCard("rmat-19-16-csc-4/rmat-19-16-csc-1-inds.bin", 280623104);
	readFromSDCard("rmat-19-16-csc-4/rmat-19-16-csc-2-meta.bin", 288540672);
	readFromSDCard("rmat-19-16-csc-4/rmat-19-16-csc-2-indptr.bin", 288542720);
	readFromSDCard("rmat-19-16-csc-4/rmat-19-16-csc-2-inds.bin", 290639872);
	readFromSDCard("rmat-19-16-csc-4/rmat-19-16-csc-3-meta.bin", 298700800);
	readFromSDCard("rmat-19-16-csc-4/rmat-19-16-csc-3-indptr.bin", 298702848);
	readFromSDCard("rmat-19-16-csc-4/rmat-19-16-csc-3-inds.bin", 300800000);
	readFromSDCard("rmat-19-16-csc-4/config.bin", 268435456);

break;
case 11:
	readFromSDCard("rmat-19-32-csc-4/rmat-19-32-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-19-32-csc-4/rmat-19-32-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-19-32-csc-4/rmat-19-32-csc-0-inds.bin", 270536704);
	readFromSDCard("rmat-19-32-csc-4/rmat-19-32-csc-1-meta.bin", 286072832);
	readFromSDCard("rmat-19-32-csc-4/rmat-19-32-csc-1-indptr.bin", 286074880);
	readFromSDCard("rmat-19-32-csc-4/rmat-19-32-csc-1-inds.bin", 288174080);
	readFromSDCard("rmat-19-32-csc-4/rmat-19-32-csc-2-meta.bin", 303826944);
	readFromSDCard("rmat-19-32-csc-4/rmat-19-32-csc-2-indptr.bin", 303828992);
	readFromSDCard("rmat-19-32-csc-4/rmat-19-32-csc-2-inds.bin", 305928192);
	readFromSDCard("rmat-19-32-csc-4/rmat-19-32-csc-3-meta.bin", 321349632);
	readFromSDCard("rmat-19-32-csc-4/rmat-19-32-csc-3-indptr.bin", 321351680);
	readFromSDCard("rmat-19-32-csc-4/rmat-19-32-csc-3-inds.bin", 323450880);
	readFromSDCard("rmat-19-32-csc-4/config.bin", 268435456);

break;
case 12:
	readFromSDCard("rmat-20-8-csc-4/rmat-20-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-20-8-csc-4/rmat-20-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-20-8-csc-4/rmat-20-8-csc-0-inds.bin", 272633856);
	readFromSDCard("rmat-20-8-csc-4/rmat-20-8-csc-1-meta.bin", 280719360);
	readFromSDCard("rmat-20-8-csc-4/rmat-20-8-csc-1-indptr.bin", 280721408);
	readFromSDCard("rmat-20-8-csc-4/rmat-20-8-csc-1-inds.bin", 284917760);
	readFromSDCard("rmat-20-8-csc-4/rmat-20-8-csc-2-meta.bin", 292925440);
	readFromSDCard("rmat-20-8-csc-4/rmat-20-8-csc-2-indptr.bin", 292927488);
	readFromSDCard("rmat-20-8-csc-4/rmat-20-8-csc-2-inds.bin", 297123840);
	readFromSDCard("rmat-20-8-csc-4/rmat-20-8-csc-3-meta.bin", 305510400);
	readFromSDCard("rmat-20-8-csc-4/rmat-20-8-csc-3-indptr.bin", 305512448);
	readFromSDCard("rmat-20-8-csc-4/rmat-20-8-csc-3-inds.bin", 309708800);
	readFromSDCard("rmat-20-8-csc-4/config.bin", 268435456);

break;
case 13:
	readFromSDCard("rmat-20-16-csc-4/rmat-20-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-20-16-csc-4/rmat-20-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-20-16-csc-4/rmat-20-16-csc-0-inds.bin", 272631808);
	readFromSDCard("rmat-20-16-csc-4/rmat-20-16-csc-1-meta.bin", 288854016);
	readFromSDCard("rmat-20-16-csc-4/rmat-20-16-csc-1-indptr.bin", 288856064);
	readFromSDCard("rmat-20-16-csc-4/rmat-20-16-csc-1-inds.bin", 293050368);
	readFromSDCard("rmat-20-16-csc-4/rmat-20-16-csc-2-meta.bin", 309170176);
	readFromSDCard("rmat-20-16-csc-4/rmat-20-16-csc-2-indptr.bin", 309172224);
	readFromSDCard("rmat-20-16-csc-4/rmat-20-16-csc-2-inds.bin", 313366528);
	readFromSDCard("rmat-20-16-csc-4/rmat-20-16-csc-3-meta.bin", 329340928);
	readFromSDCard("rmat-20-16-csc-4/rmat-20-16-csc-3-indptr.bin", 329342976);
	readFromSDCard("rmat-20-16-csc-4/rmat-20-16-csc-3-inds.bin", 333537280);
	readFromSDCard("rmat-20-16-csc-4/config.bin", 268435456);

break;
case 14:
	readFromSDCard("rmat-20-32-csc-4/rmat-20-32-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-20-32-csc-4/rmat-20-32-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-20-32-csc-4/rmat-20-32-csc-0-inds.bin", 272633856);
	readFromSDCard("rmat-20-32-csc-4/rmat-20-32-csc-1-meta.bin", 304838656);
	readFromSDCard("rmat-20-32-csc-4/rmat-20-32-csc-1-indptr.bin", 304840704);
	readFromSDCard("rmat-20-32-csc-4/rmat-20-32-csc-1-inds.bin", 309037056);
	readFromSDCard("rmat-20-32-csc-4/rmat-20-32-csc-2-meta.bin", 340418560);
	readFromSDCard("rmat-20-32-csc-4/rmat-20-32-csc-2-indptr.bin", 340420608);
	readFromSDCard("rmat-20-32-csc-4/rmat-20-32-csc-2-inds.bin", 344616960);
	readFromSDCard("rmat-20-32-csc-4/rmat-20-32-csc-3-meta.bin", 375687168);
	readFromSDCard("rmat-20-32-csc-4/rmat-20-32-csc-3-indptr.bin", 375689216);
	readFromSDCard("rmat-20-32-csc-4/rmat-20-32-csc-3-inds.bin", 379885568);
	readFromSDCard("rmat-20-32-csc-4/config.bin", 268435456);

break;
case 15:
	readFromSDCard("rmat-21-8-csc-4/rmat-21-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-21-8-csc-4/rmat-21-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-21-8-csc-4/rmat-21-8-csc-0-inds.bin", 276828160);
	readFromSDCard("rmat-21-8-csc-4/rmat-21-8-csc-1-meta.bin", 293431296);
	readFromSDCard("rmat-21-8-csc-4/rmat-21-8-csc-1-indptr.bin", 293433344);
	readFromSDCard("rmat-21-8-csc-4/rmat-21-8-csc-1-inds.bin", 301824000);
	readFromSDCard("rmat-21-8-csc-4/rmat-21-8-csc-2-meta.bin", 318259200);
	readFromSDCard("rmat-21-8-csc-4/rmat-21-8-csc-2-indptr.bin", 318261248);
	readFromSDCard("rmat-21-8-csc-4/rmat-21-8-csc-2-inds.bin", 326651904);
	readFromSDCard("rmat-21-8-csc-4/rmat-21-8-csc-3-meta.bin", 342935552);
	readFromSDCard("rmat-21-8-csc-4/rmat-21-8-csc-3-indptr.bin", 342937600);
	readFromSDCard("rmat-21-8-csc-4/rmat-21-8-csc-3-inds.bin", 351328256);
	readFromSDCard("rmat-21-8-csc-4/config.bin", 268435456);

break;
case 16:
	readFromSDCard("rmat-21-16-csc-4/rmat-21-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-21-16-csc-4/rmat-21-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-21-16-csc-4/rmat-21-16-csc-0-inds.bin", 276826112);
	readFromSDCard("rmat-21-16-csc-4/rmat-21-16-csc-1-meta.bin", 309248000);
	readFromSDCard("rmat-21-16-csc-4/rmat-21-16-csc-1-indptr.bin", 309250048);
	readFromSDCard("rmat-21-16-csc-4/rmat-21-16-csc-1-inds.bin", 317638656);
	readFromSDCard("rmat-21-16-csc-4/rmat-21-16-csc-2-meta.bin", 350277632);
	readFromSDCard("rmat-21-16-csc-4/rmat-21-16-csc-2-indptr.bin", 350279680);
	readFromSDCard("rmat-21-16-csc-4/rmat-21-16-csc-2-inds.bin", 358668288);
	readFromSDCard("rmat-21-16-csc-4/rmat-21-16-csc-3-meta.bin", 390637568);
	readFromSDCard("rmat-21-16-csc-4/rmat-21-16-csc-3-indptr.bin", 390639616);
	readFromSDCard("rmat-21-16-csc-4/rmat-21-16-csc-3-inds.bin", 399028224);
	readFromSDCard("rmat-21-16-csc-4/config.bin", 268435456);

break;
case 17:
	readFromSDCard("rmat-21-32-csc-4/rmat-21-32-csc-0-meta.bin", 134219008);
	readFromSDCard("rmat-21-32-csc-4/rmat-21-32-csc-0-indptr.bin", 134219776);
	readFromSDCard("rmat-21-32-csc-4/rmat-21-32-csc-0-inds.bin", 142608384);
	readFromSDCard("rmat-21-32-csc-4/rmat-21-32-csc-1-meta.bin", 205250560);
	readFromSDCard("rmat-21-32-csc-4/rmat-21-32-csc-1-indptr.bin", 205252608);
	readFromSDCard("rmat-21-32-csc-4/rmat-21-32-csc-1-inds.bin", 213641216);
	readFromSDCard("rmat-21-32-csc-4/rmat-21-32-csc-2-meta.bin", 276254720);
	readFromSDCard("rmat-21-32-csc-4/rmat-21-32-csc-2-indptr.bin", 276256768);
	readFromSDCard("rmat-21-32-csc-4/rmat-21-32-csc-2-inds.bin", 284645376);
	readFromSDCard("rmat-21-32-csc-4/rmat-21-32-csc-3-meta.bin", 348514304);
	readFromSDCard("rmat-21-32-csc-4/rmat-21-32-csc-3-indptr.bin", 348516352);
	readFromSDCard("rmat-21-32-csc-4/rmat-21-32-csc-3-inds.bin", 356904960);
	readFromSDCard("rmat-21-32-csc-4/config.bin", 134217984);
	return (void *) 134217984;
break;
case 18:
	readFromSDCard("rmat-20-64-csc-4/rmat-20-64-csc-0-meta.bin", 134219008);
	readFromSDCard("rmat-20-64-csc-4/rmat-20-64-csc-0-indptr.bin", 134219776);
	readFromSDCard("rmat-20-64-csc-4/rmat-20-64-csc-0-inds.bin", 138416128);
	readFromSDCard("rmat-20-64-csc-4/rmat-20-64-csc-1-meta.bin", 199761920);
	readFromSDCard("rmat-20-64-csc-4/rmat-20-64-csc-1-indptr.bin", 199763968);
	readFromSDCard("rmat-20-64-csc-4/rmat-20-64-csc-1-inds.bin", 203960320);
	readFromSDCard("rmat-20-64-csc-4/rmat-20-64-csc-2-meta.bin", 264949760);
	readFromSDCard("rmat-20-64-csc-4/rmat-20-64-csc-2-indptr.bin", 264951808);
	readFromSDCard("rmat-20-64-csc-4/rmat-20-64-csc-2-inds.bin", 269148160);
	readFromSDCard("rmat-20-64-csc-4/rmat-20-64-csc-3-meta.bin", 329107456);
	readFromSDCard("rmat-20-64-csc-4/rmat-20-64-csc-3-indptr.bin", 329109504);
	readFromSDCard("rmat-20-64-csc-4/rmat-20-64-csc-3-inds.bin", 333305856);
	readFromSDCard("rmat-20-64-csc-4/config.bin", 134217984);
	return (void *) 134217984;
default:
std::cout << "Matrix not found!" << std::endl;
return (void*)0;
}
	return (void *) 268435456;
}


const char * getMatrixNameP4(unsigned int id) {
switch(id) {
case 0:
  return "rmat-16-8-csc";
case 1:
  return "rmat-16-16-csc";
case 2:
  return "rmat-16-32-csc";
case 3:
  return "rmat-17-8-csc";
case 4:
  return "rmat-17-16-csc";
case 5:
  return "rmat-17-32-csc";
case 6:
  return "rmat-18-8-csc";
case 7:
  return "rmat-18-16-csc";
case 8:
  return "rmat-18-32-csc";
case 9:
  return "rmat-19-8-csc";
case 10:
  return "rmat-19-16-csc";
case 11:
  return "rmat-19-32-csc";
case 12:
  return "rmat-20-8-csc";
case 13:
  return "rmat-20-16-csc";
case 14:
  return "rmat-20-32-csc";
case 15:
  return "rmat-21-8-csc";
case 16:
  return "rmat-21-16-csc";
case 17:
  return "rmat-21-32-csc";
case 18:
  return "rmat-20-64-csc";
default:
return "Matrix not found!";
}}
