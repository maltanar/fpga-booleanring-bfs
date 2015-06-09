#include <iostream>
#include "sdcard.h"

const unsigned int matrixCountP1 = 17;

void * loadMatrixP1(unsigned int id) {
switch(id) {
case 0:
	readFromSDCard("rmat-16-8-csc-1/rmat-16-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-16-8-csc-1/rmat-16-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-16-8-csc-1/rmat-16-8-csc-0-inds.bin", 268701696);
	readFromSDCard("rmat-16-8-csc-1/config.bin", 268435456);

break;
case 1:
	readFromSDCard("rmat-16-16-csc-1/rmat-16-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-16-16-csc-1/rmat-16-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-16-16-csc-1/rmat-16-16-csc-0-inds.bin", 268699648);
	readFromSDCard("rmat-16-16-csc-1/config.bin", 268435456);

break;
case 2:
	readFromSDCard("rmat-16-32-csc-1/rmat-16-32-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-16-32-csc-1/rmat-16-32-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-16-32-csc-1/rmat-16-32-csc-0-inds.bin", 268699648);
	readFromSDCard("rmat-16-32-csc-1/config.bin", 268435456);

break;
case 3:
	readFromSDCard("rmat-17-8-csc-1/rmat-17-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-17-8-csc-1/rmat-17-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-17-8-csc-1/rmat-17-8-csc-0-inds.bin", 268961792);
	readFromSDCard("rmat-17-8-csc-1/config.bin", 268435456);

break;
case 4:
	readFromSDCard("rmat-17-16-csc-1/rmat-17-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-17-16-csc-1/rmat-17-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-17-16-csc-1/rmat-17-16-csc-0-inds.bin", 268961792);
	readFromSDCard("rmat-17-16-csc-1/config.bin", 268435456);

break;
case 5:
	readFromSDCard("rmat-17-32-csc-1/rmat-17-32-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-17-32-csc-1/rmat-17-32-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-17-32-csc-1/rmat-17-32-csc-0-inds.bin", 268963840);
	readFromSDCard("rmat-17-32-csc-1/config.bin", 268435456);

break;
case 6:
	readFromSDCard("rmat-18-8-csc-1/rmat-18-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-18-8-csc-1/rmat-18-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-18-8-csc-1/rmat-18-8-csc-0-inds.bin", 269486080);
	readFromSDCard("rmat-18-8-csc-1/config.bin", 268435456);

break;
case 7:
	readFromSDCard("rmat-18-16-csc-1/rmat-18-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-18-16-csc-1/rmat-18-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-18-16-csc-1/rmat-18-16-csc-0-inds.bin", 269488128);
	readFromSDCard("rmat-18-16-csc-1/config.bin", 268435456);

break;
case 8:
	readFromSDCard("rmat-18-32-csc-1/rmat-18-32-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-18-32-csc-1/rmat-18-32-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-18-32-csc-1/rmat-18-32-csc-0-inds.bin", 269486080);
	readFromSDCard("rmat-18-32-csc-1/config.bin", 268435456);

break;
case 9:
	readFromSDCard("rmat-19-8-csc-1/rmat-19-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-19-8-csc-1/rmat-19-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-19-8-csc-1/rmat-19-8-csc-0-inds.bin", 270534656);
	readFromSDCard("rmat-19-8-csc-1/config.bin", 268435456);

break;
case 10:
	readFromSDCard("rmat-19-16-csc-1/rmat-19-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-19-16-csc-1/rmat-19-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-19-16-csc-1/rmat-19-16-csc-0-inds.bin", 270534656);
	readFromSDCard("rmat-19-16-csc-1/config.bin", 268435456);

break;
case 11:
	readFromSDCard("rmat-19-32-csc-1/rmat-19-32-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-19-32-csc-1/rmat-19-32-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-19-32-csc-1/rmat-19-32-csc-0-inds.bin", 270536704);
	readFromSDCard("rmat-19-32-csc-1/config.bin", 268435456);

break;
case 12:
	readFromSDCard("rmat-20-8-csc-1/rmat-20-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-20-8-csc-1/rmat-20-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-20-8-csc-1/rmat-20-8-csc-0-inds.bin", 272633856);
	readFromSDCard("rmat-20-8-csc-1/config.bin", 268435456);

break;
case 13:
	readFromSDCard("rmat-20-16-csc-1/rmat-20-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-20-16-csc-1/rmat-20-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-20-16-csc-1/rmat-20-16-csc-0-inds.bin", 272631808);
	readFromSDCard("rmat-20-16-csc-1/config.bin", 268435456);

break;
case 14:
	readFromSDCard("rmat-20-32-csc-1/rmat-20-32-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-20-32-csc-1/rmat-20-32-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-20-32-csc-1/rmat-20-32-csc-0-inds.bin", 272633856);
	readFromSDCard("rmat-20-32-csc-1/config.bin", 268435456);

break;
case 15:
	readFromSDCard("rmat-21-8-csc-1/rmat-21-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-21-8-csc-1/rmat-21-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-21-8-csc-1/rmat-21-8-csc-0-inds.bin", 276828160);
	readFromSDCard("rmat-21-8-csc-1/config.bin", 268435456);

break;
case 16:
	readFromSDCard("rmat-21-16-csc-1/rmat-21-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-21-16-csc-1/rmat-21-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-21-16-csc-1/rmat-21-16-csc-0-inds.bin", 276826112);
	readFromSDCard("rmat-21-16-csc-1/config.bin", 268435456);
break;
case 17:
	readFromSDCard("rmat-21-32-csc-1/rmat-21-32-csc-0-meta.bin", 134219008);
	readFromSDCard("rmat-21-32-csc-1/rmat-21-32-csc-0-indptr.bin", 134219776);
	readFromSDCard("rmat-21-32-csc-1/rmat-21-32-csc-0-inds.bin", 142608384);
	readFromSDCard("rmat-21-32-csc-1/config.bin", 134217984);
	return (void *) 134217984;
break;
case 18:
	readFromSDCard("rmat-20-64-csc-1/rmat-20-64-csc-0-meta.bin", 134219008);
	readFromSDCard("rmat-20-64-csc-1/rmat-20-64-csc-0-indptr.bin", 134219776);
	readFromSDCard("rmat-20-64-csc-1/rmat-20-64-csc-0-inds.bin", 138416128);
	readFromSDCard("rmat-20-64-csc-1/config.bin", 134217984);
	return (void *) 134217984;
break;
default:
std::cout << "Matrix not found!" << std::endl;
return (void *) 0;
}
	return (void *) 268435456;
}


const char * getMatrixNameP1(unsigned int id) {
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
