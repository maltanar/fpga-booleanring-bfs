#include "xparameters.h"	/* SDK generated parameters */
#include "xsdps.h"		/* SD device driver */
#include <stdio.h>
#include "ff.h"

void readFromSDCard(const char * fileName, unsigned int bufferBase);
void readIntoBuffer(const char * fileName, char * buffer, unsigned int bufsize);
unsigned int getFileSize(const char *fileName);
void mount();
void unmount();
