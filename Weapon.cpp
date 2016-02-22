#include "Weapon.h"

Weapon::Weapon(char* Name):Weapon(Name,NULL,NULL){};
Weapon::Weapon(char* Name,Actor* Source):Weapon(Name,Source,NULL){
};
Weapon::Weapon(char* Name,Actor* Source,Shot* Sample):m_Name(NULL),m_Sample(Sample),m_Dt(0.0f){
    if(Name){
        m_Name=(char*)malloc(20);
        int i=0;
        for(;Name[i];i++)
            m_Name[i]=Name[i];
    }
};
void Weapon::setSample(Shot* Sample){
    m_Sample=Sample ;
};
char* Weapon::getName(){
    return m_Name ;
};
