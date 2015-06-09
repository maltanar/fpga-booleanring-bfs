#include <iostream>
#include "sdcard.h"
void * loadMatrixP5(unsigned int id) {
switch(id) {
case 11:
	readFromSDCard("rmat-19-32-csc-5/rmat-19-32-csc-0-meta.bin", 134219008);
	readFromSDCard("rmat-19-32-csc-5/rmat-19-32-csc-0-indptr.bin", 134219776);
	readFromSDCard("rmat-19-32-csc-5/rmat-19-32-csc-0-inds.bin", 136316928);
	readFromSDCard("rmat-19-32-csc-5/rmat-19-32-csc-1-meta.bin", 148967424);
	readFromSDCard("rmat-19-32-csc-5/rmat-19-32-csc-1-indptr.bin", 148969472);
	readFromSDCard("rmat-19-32-csc-5/rmat-19-32-csc-1-inds.bin", 151066624);
	readFromSDCard("rmat-19-32-csc-5/rmat-19-32-csc-2-meta.bin", 163405824);
	readFromSDCard("rmat-19-32-csc-5/rmat-19-32-csc-2-indptr.bin", 163407872);
	readFromSDCard("rmat-19-32-csc-5/rmat-19-32-csc-2-inds.bin", 165505024);
	readFromSDCard("rmat-19-32-csc-5/rmat-19-32-csc-3-meta.bin", 177631232);
	readFromSDCard("rmat-19-32-csc-5/rmat-19-32-csc-3-indptr.bin", 177633280);
	readFromSDCard("rmat-19-32-csc-5/rmat-19-32-csc-3-inds.bin", 179730432);
	readFromSDCard("rmat-19-32-csc-5/rmat-19-32-csc-4-meta.bin", 192163840);
	readFromSDCard("rmat-19-32-csc-5/rmat-19-32-csc-4-indptr.bin", 192165888);
	readFromSDCard("rmat-19-32-csc-5/rmat-19-32-csc-4-inds.bin", 194263040);
	readFromSDCard("rmat-19-32-csc-5/config.bin", 134217984);

break;
default:
std::cout << "Matrix not found!" << std::endl; return (void*)0;
}
 return (void *)134217984;
}


const char * getMatrixNameP5(unsigned int id) {
switch(id) {
case 11:
  return "rmat-19-32-csc";
default:
return "Matrix not found!";
}}
