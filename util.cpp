#include "util.h"

void ReadLine(FILE* file ,char* buffer){
    char c ;
    unsigned int i=0 ;
    c=fgetc(file);
    while (c!='\n' && c!='\0'&& c!=EOF && i<100){
        buffer[i]=c;
        i++;
        c=fgetc(file);
    }
    buffer[i]='\0';

};
int contains(char* str1,char* str2){
    int result ;
    if(str1==NULL || str2==NULL )
        return 0 ;
    int len1=strlen(str1),len2=strlen(str2);
    if(len1< len2)
        return 0 ;
    result=0;
    for(int i=0 ;i<len1-len2+1 && !result;i++){
        result=i+1 ;
        for(int j=0;str2[j]&& result;j++)
            if(str1[i+j]!=str2[j])
                result=0 ;
    }
    return result;
};
int CatStrings(char* str1,char* str2,char** Dest){
    if(!str1 || !str2 || !Dest)
        return 0 ;
    *Dest=(char*)malloc((strlen(str1)+strlen(str2)+1)*sizeof(char));
    if(!*Dest)
        return 0 ;
    int i,len=strlen(str1);
    for( i= 0;str1[i];i++)
        (*Dest)[i]=str1[i];
    for(;str2[i-len];i++)
        (*Dest)[i]= str2[i-len];
    (*Dest)[i]='\0';
return 1 ;
};
char* ExtractString(char* source,char* borderstr1,char* borderstr2){
    int border1,border2;
    char* rslt=NULL ;
    int length,str1len ;
    if((border1=contains(source,borderstr1))){
        border1--;
        str1len=strlen(borderstr1);
    if((border2=contains(source+border1+str1len,borderstr2))){
        length=border2-1;
        rslt=(char*)malloc((length+1)*sizeof(char));
        if(!rslt){
            return rslt ;}
        for(int i=0;i<length;i++){
            rslt[i]=source[i+border1+str1len];
        }
        rslt[length]='\0';
    }
    }
    return rslt;
};
