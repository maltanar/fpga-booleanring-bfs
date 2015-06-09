#include <iostream>
#include "sdcard.h"

const unsigned int matrixCountP2 = 17;

void * loadMatrixP2(unsigned int id) {
switch(id) {
case 0:
	readFromSDCard("rmat-16-8-csc-2/rmat-16-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-16-8-csc-2/rmat-16-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-16-8-csc-2/rmat-16-8-csc-0-inds.bin", 268701696);
	readFromSDCard("rmat-16-8-csc-2/rmat-16-8-csc-1-meta.bin", 269674496);
	readFromSDCard("rmat-16-8-csc-2/rmat-16-8-csc-1-indptr.bin", 269676544);
	readFromSDCard("rmat-16-8-csc-2/rmat-16-8-csc-1-inds.bin", 269940736);
	readFromSDCard("rmat-16-8-csc-2/config.bin", 268435456);

break;
case 1:
	readFromSDCard("rmat-16-16-csc-2/rmat-16-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-16-16-csc-2/rmat-16-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-16-16-csc-2/rmat-16-16-csc-0-inds.bin", 268699648);
	readFromSDCard("rmat-16-16-csc-2/rmat-16-16-csc-1-meta.bin", 270596096);
	readFromSDCard("rmat-16-16-csc-2/rmat-16-16-csc-1-indptr.bin", 270598144);
	readFromSDCard("rmat-16-16-csc-2/rmat-16-16-csc-1-inds.bin", 270860288);
	readFromSDCard("rmat-16-16-csc-2/config.bin", 268435456);

break;
case 2:
	readFromSDCard("rmat-16-32-csc-2/rmat-16-32-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-16-32-csc-2/rmat-16-32-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-16-32-csc-2/rmat-16-32-csc-0-inds.bin", 268699648);
	readFromSDCard("rmat-16-32-csc-2/rmat-16-32-csc-1-meta.bin", 272353280);
	readFromSDCard("rmat-16-32-csc-2/rmat-16-32-csc-1-indptr.bin", 272355328);
	readFromSDCard("rmat-16-32-csc-2/rmat-16-32-csc-1-inds.bin", 272617472);
	readFromSDCard("rmat-16-32-csc-2/config.bin", 268435456);

break;
case 3:
	readFromSDCard("rmat-17-8-csc-2/rmat-17-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-17-8-csc-2/rmat-17-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-17-8-csc-2/rmat-17-8-csc-0-inds.bin", 268961792);
	readFromSDCard("rmat-17-8-csc-2/rmat-17-8-csc-1-meta.bin", 270940160);
	readFromSDCard("rmat-17-8-csc-2/rmat-17-8-csc-1-indptr.bin", 270942208);
	readFromSDCard("rmat-17-8-csc-2/rmat-17-8-csc-1-inds.bin", 271466496);
	readFromSDCard("rmat-17-8-csc-2/config.bin", 268435456);

break;
case 4:
	readFromSDCard("rmat-17-16-csc-2/rmat-17-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-17-16-csc-2/rmat-17-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-17-16-csc-2/rmat-17-16-csc-0-inds.bin", 268961792);
	readFromSDCard("rmat-17-16-csc-2/rmat-17-16-csc-1-meta.bin", 272984064);
	readFromSDCard("rmat-17-16-csc-2/rmat-17-16-csc-1-indptr.bin", 272986112);
	readFromSDCard("rmat-17-16-csc-2/rmat-17-16-csc-1-inds.bin", 273510400);
	readFromSDCard("rmat-17-16-csc-2/config.bin", 268435456);

break;
case 5:
	readFromSDCard("rmat-17-32-csc-2/rmat-17-32-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-17-32-csc-2/rmat-17-32-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-17-32-csc-2/rmat-17-32-csc-0-inds.bin", 268963840);
	readFromSDCard("rmat-17-32-csc-2/rmat-17-32-csc-1-meta.bin", 276230144);
	readFromSDCard("rmat-17-32-csc-2/rmat-17-32-csc-1-indptr.bin", 276232192);
	readFromSDCard("rmat-17-32-csc-2/rmat-17-32-csc-1-inds.bin", 276758528);
	readFromSDCard("rmat-17-32-csc-2/config.bin", 268435456);

break;
case 6:
	readFromSDCard("rmat-18-8-csc-2/rmat-18-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-18-8-csc-2/rmat-18-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-18-8-csc-2/rmat-18-8-csc-0-inds.bin", 269486080);
	readFromSDCard("rmat-18-8-csc-2/rmat-18-8-csc-1-meta.bin", 273561600);
	readFromSDCard("rmat-18-8-csc-2/rmat-18-8-csc-1-indptr.bin", 273563648);
	readFromSDCard("rmat-18-8-csc-2/rmat-18-8-csc-1-inds.bin", 274612224);
	readFromSDCard("rmat-18-8-csc-2/config.bin", 268435456);

break;
case 7:
	readFromSDCard("rmat-18-16-csc-2/rmat-18-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-18-16-csc-2/rmat-18-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-18-16-csc-2/rmat-18-16-csc-0-inds.bin", 269488128);
	readFromSDCard("rmat-18-16-csc-2/rmat-18-16-csc-1-meta.bin", 277387264);
	readFromSDCard("rmat-18-16-csc-2/rmat-18-16-csc-1-indptr.bin", 277389312);
	readFromSDCard("rmat-18-16-csc-2/rmat-18-16-csc-1-inds.bin", 278439936);
	readFromSDCard("rmat-18-16-csc-2/config.bin", 268435456);

break;
case 8:
	readFromSDCard("rmat-18-32-csc-2/rmat-18-32-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-18-32-csc-2/rmat-18-32-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-18-32-csc-2/rmat-18-32-csc-0-inds.bin", 269486080);
	readFromSDCard("rmat-18-32-csc-2/rmat-18-32-csc-1-meta.bin", 284647424);
	readFromSDCard("rmat-18-32-csc-2/rmat-18-32-csc-1-indptr.bin", 284649472);
	readFromSDCard("rmat-18-32-csc-2/rmat-18-32-csc-1-inds.bin", 285698048);
	readFromSDCard("rmat-18-32-csc-2/config.bin", 268435456);

break;
case 9:
	readFromSDCard("rmat-19-8-csc-2/rmat-19-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-19-8-csc-2/rmat-19-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-19-8-csc-2/rmat-19-8-csc-0-inds.bin", 270534656);
	readFromSDCard("rmat-19-8-csc-2/rmat-19-8-csc-1-meta.bin", 278708224);
	readFromSDCard("rmat-19-8-csc-2/rmat-19-8-csc-1-indptr.bin", 278710272);
	readFromSDCard("rmat-19-8-csc-2/rmat-19-8-csc-1-inds.bin", 280807424);
	readFromSDCard("rmat-19-8-csc-2/config.bin", 268435456);

break;
case 10:
	readFromSDCard("rmat-19-16-csc-2/rmat-19-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-19-16-csc-2/rmat-19-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-19-16-csc-2/rmat-19-16-csc-0-inds.bin", 270534656);
	readFromSDCard("rmat-19-16-csc-2/rmat-19-16-csc-1-meta.bin", 286439424);
	readFromSDCard("rmat-19-16-csc-2/rmat-19-16-csc-1-indptr.bin", 286441472);
	readFromSDCard("rmat-19-16-csc-2/rmat-19-16-csc-1-inds.bin", 288538624);
	readFromSDCard("rmat-19-16-csc-2/config.bin", 268435456);

break;
case 11:
	readFromSDCard("rmat-19-32-csc-2/rmat-19-32-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-19-32-csc-2/rmat-19-32-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-19-32-csc-2/rmat-19-32-csc-0-inds.bin", 270536704);
	readFromSDCard("rmat-19-32-csc-2/rmat-19-32-csc-1-meta.bin", 301725696);
	readFromSDCard("rmat-19-32-csc-2/rmat-19-32-csc-1-indptr.bin", 301727744);
	readFromSDCard("rmat-19-32-csc-2/rmat-19-32-csc-1-inds.bin", 303826944);
	readFromSDCard("rmat-19-32-csc-2/config.bin", 268435456);

break;
case 12:
	readFromSDCard("rmat-20-8-csc-2/rmat-20-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-20-8-csc-2/rmat-20-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-20-8-csc-2/rmat-20-8-csc-0-inds.bin", 272633856);
	readFromSDCard("rmat-20-8-csc-2/rmat-20-8-csc-1-meta.bin", 288724992);
	readFromSDCard("rmat-20-8-csc-2/rmat-20-8-csc-1-indptr.bin", 288727040);
	readFromSDCard("rmat-20-8-csc-2/rmat-20-8-csc-1-inds.bin", 292923392);
	readFromSDCard("rmat-20-8-csc-2/config.bin", 268435456);

break;
case 13:
	readFromSDCard("rmat-20-16-csc-2/rmat-20-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-20-16-csc-2/rmat-20-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-20-16-csc-2/rmat-20-16-csc-0-inds.bin", 272631808);
	readFromSDCard("rmat-20-16-csc-2/rmat-20-16-csc-1-meta.bin", 304973824);
	readFromSDCard("rmat-20-16-csc-2/rmat-20-16-csc-1-indptr.bin", 304975872);
	readFromSDCard("rmat-20-16-csc-2/rmat-20-16-csc-1-inds.bin", 309170176);
	readFromSDCard("rmat-20-16-csc-2/config.bin", 268435456);

break;
case 14:
	readFromSDCard("rmat-20-32-csc-2/rmat-20-32-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-20-32-csc-2/rmat-20-32-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-20-32-csc-2/rmat-20-32-csc-0-inds.bin", 272633856);
	readFromSDCard("rmat-20-32-csc-2/rmat-20-32-csc-1-meta.bin", 336220160);
	readFromSDCard("rmat-20-32-csc-2/rmat-20-32-csc-1-indptr.bin", 336222208);
	readFromSDCard("rmat-20-32-csc-2/rmat-20-32-csc-1-inds.bin", 340418560);
	readFromSDCard("rmat-20-32-csc-2/config.bin", 268435456);

break;
case 15:
	readFromSDCard("rmat-21-8-csc-2/rmat-21-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-21-8-csc-2/rmat-21-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-21-8-csc-2/rmat-21-8-csc-0-inds.bin", 276828160);
	readFromSDCard("rmat-21-8-csc-2/rmat-21-8-csc-1-meta.bin", 309864448);
	readFromSDCard("rmat-21-8-csc-2/rmat-21-8-csc-1-indptr.bin", 309866496);
	readFromSDCard("rmat-21-8-csc-2/rmat-21-8-csc-1-inds.bin", 318257152);
	readFromSDCard("rmat-21-8-csc-2/config.bin", 268435456);

break;
case 16:
	readFromSDCard("rmat-21-16-csc-2/rmat-21-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-21-16-csc-2/rmat-21-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-21-16-csc-2/rmat-21-16-csc-0-inds.bin", 276826112);
	readFromSDCard("rmat-21-16-csc-2/rmat-21-16-csc-1-meta.bin", 341886976);
	readFromSDCard("rmat-21-16-csc-2/rmat-21-16-csc-1-indptr.bin", 341889024);
	readFromSDCard("rmat-21-16-csc-2/rmat-21-16-csc-1-inds.bin", 350277632);
	readFromSDCard("rmat-21-16-csc-2/config.bin", 268435456);

break;
default:
std::cout << "Matrix not found!" << std::endl;
}
return (void *) 268435456;
}


const char * getMatrixNameP2(unsigned int id) {
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
default:
return "Matrix not found!";
}}
