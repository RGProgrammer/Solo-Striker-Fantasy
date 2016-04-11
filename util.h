#ifndef PFE_UTILLITY_H_
#define PFE_UTILLITY_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void ReadLine(FILE* file,char* buffer);
int contains(char* str1,char* str2);//the resturn the index of the occurence starting from 1
int CatStrings(char* str1,char* str2,char** Dest);//concat 2 string
char* ExtractString(char* source,char* borderstr1,char* borderstr2);//extract a string form the source
#endif // PFE_UTILLITY_H_
