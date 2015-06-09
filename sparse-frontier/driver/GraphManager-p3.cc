#include <iostream>
#include "sdcard.h"
void * loadMatrixP3(unsigned int id) {
switch(id) {
case 11:
	readFromSDCard("rmat-19-32-csc-3/rmat-19-32-csc-0-meta.bin", 134219008);
	readFromSDCard("rmat-19-32-csc-3/rmat-19-32-csc-0-indptr.bin", 134219776);
	readFromSDCard("rmat-19-32-csc-3/rmat-19-32-csc-0-inds.bin", 136316928);
	readFromSDCard("rmat-19-32-csc-3/rmat-19-32-csc-1-meta.bin", 157214720);
	readFromSDCard("rmat-19-32-csc-3/rmat-19-32-csc-1-indptr.bin", 157216768);
	readFromSDCard("rmat-19-32-csc-3/rmat-19-32-csc-1-inds.bin", 159313920);
	readFromSDCard("rmat-19-32-csc-3/rmat-19-32-csc-2-meta.bin", 179980288);
	readFromSDCard("rmat-19-32-csc-3/rmat-19-32-csc-2-indptr.bin", 179982336);
	readFromSDCard("rmat-19-32-csc-3/rmat-19-32-csc-2-inds.bin", 182079488);
	readFromSDCard("rmat-19-32-csc-3/config.bin", 134217984);

break;
default:
std::cout << "Matrix not found!" << std::endl; return (void*)0;
}
 return (void *)134217984;
}


const char * getMatrixNameP3(unsigned int id) {
switch(id) {
case 11:
  return "rmat-19-32-csc";
default:
return "Matrix not found!";
}}
