#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit */
#include "helperIncludes/ProcessResponse.h"
#include "helperIncludes/getSensorData.h"
#include "helperIncludes/StringFunctions.h"


void error(const char *msg) { perror(msg); exit(0); }



int sensorRest(char* host, int portno, char* uri)
{


   char* dataResponse;
   int result;

   /* Call the sensor and get data */
   dataResponse = getSensorData (host, portno, uri);

   /* Call data processing code */
   result = processResponse (dataResponse);

   return 0;

}

