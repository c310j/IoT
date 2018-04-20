/*
 * StringFunctions.c
 *
 *  Created on: 20 Apr 2018
 *      Author: ralfh
 */
#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */


int findSubstring(char * data, char * searchString)
{
     int i = 0;
     int d = 0;
     if (strlen(data) >= strlen(searchString)) {
         for (i = strlen(data) - strlen(searchString); i >= 0; i--) {
             int found = 1; //assume we found (wanted to use boolean)
             for (d = 0; d < strlen(searchString); d++) {
                 if (data[i + d] != searchString[d]) {
                     found = 0;
                     break;
                 }
             }
             if (found == 1) {
                 return i;
             }
         }
         return -1;
     } else {
         //fprintf(stdout, "haystack smaller\n");
     }
     return 0;
 }

char* substring(const char* str, size_t begin, size_t len)
{
  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len))
    return 0;

  return strndup(str + begin, len);
}
