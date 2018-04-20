/*
 * ProcessResponse.c
 *
 *  Created on: 20 Apr 2018
 *      Author: ralfh
 */

int processResponse (char* response)
{

    /* total length of response */
   int len = strlen(response);

   /* Temporary variables needed for extracting JSON Data */
   char * sTempC="Temp_C";
   char * sTempF="Temp_F";
   char * sPressure="Pressure";
   char * sAlt="Altitude";
   char * sep1=":";
   char * sep2=",";
   char * sep3="}";
   char * alt;
   char * pressure;
   char * tempC;
   char * tempF;

   int tempCPos = 0;
   int tempFPos = 0;
   int altPos = 0;
   int pressPos = 0;
   int sep1Pos = 0;
   int sep2Pos = 0;

   /* Find substring positions of data */
   altPos = findSubstring( response, sAlt);
   pressPos = findSubstring( response, sPressure);
   tempCPos = findSubstring( response, sTempC);
   tempFPos = findSubstring( response, sTempF);

   /* Extract data sections into separate string variables */
   alt = strndup(response + altPos, pressPos-altPos);
   pressure = strndup(response + pressPos,  tempCPos-pressPos);
   tempC = strndup(response + tempCPos, tempFPos-tempCPos);
   tempF = strndup(response + tempFPos, len-tempFPos);

   /* Extract Altitude value */
   char * altVal;

   sep1Pos = findSubstring(alt, sep1);
   sep2Pos = findSubstring(alt, sep2);

   /* Correct positions */
   sep1Pos = sep1Pos + 1;
   sep2Pos = sep2Pos - 1;

   altVal = strndup(alt + sep1Pos, sep2Pos - sep1Pos);

   /* Extract Pressure value */
   char * pressVal;

   sep1Pos = findSubstring(pressure, sep1);
   sep2Pos = findSubstring(pressure, sep2);

   /* Correct positions */
   sep1Pos = sep1Pos + 1;
   sep2Pos = sep2Pos - 1;

   pressVal = strndup(pressure + sep1Pos, sep2Pos - sep1Pos);

   /* Extract Temperature C value */
   char * tempCVal;

   sep1Pos = findSubstring(tempC, sep1);
   sep2Pos = findSubstring(tempC, sep2);

   /* Correct positions */
   sep1Pos = sep1Pos + 1;
   sep2Pos = sep2Pos - 1;

   tempCVal = strndup(tempC + sep1Pos, sep2Pos - sep1Pos);

    /* Extract Temperature F value */
   char * tempFVal;

   sep1Pos = findSubstring(tempF, sep1);
   sep2Pos = findSubstring(tempF, sep3);

   /* Correct positions */
   sep1Pos = sep1Pos + 1;
   sep2Pos = sep2Pos - 1;

   tempFVal = strndup(tempF + sep1Pos, sep2Pos - sep1Pos);

   /* Print result */
   printf("Altitude: %s\n", altVal );
   printf("Pressure: %s\n", pressVal);
   printf("Temp C: %s\n", tempCVal);
   printf("Temp F: %s\n", tempFVal);

  return 0;

}
