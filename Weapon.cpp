#include "Weapon.h"

Weapon::Weapon(char* Name):Weapon(Name,NULL,NULL){
};
Weapon::Weapon(char* Name,Actor* Source):Weapon(Name,Source,NULL){
};
Weapon::Weapon(char* Name,Actor* Source,Shot* Sample):m_Name(NULL),m_Sample(Sample),m_Dt(0.0f),
                                                    m_FireSound(0),m_TimeBetweenShots(0.0f),m_Icon(NULL){
    if(Name){
        m_Name=(char*)malloc((strlen(Name)+1)*sizeof(char));
        for(int i=0;Name[i];i++)
            m_Name[i]=Name[i];
        m_Name[strlen(Name)]='\0';
    }
};
Weapon::~Weapon(){
    this->Destroy();
};
void Weapon::Destroy(){
    if(m_Name){
        free(m_Name);
        m_Name=NULL ;
    }
    if(m_Sample){
        m_Sample->Destroy();
        delete m_Sample;
        m_Sample=NULL ;
    }
    if(m_Icon){
        m_Icon->Destroy();
        delete m_Icon ;
        m_Icon=NULL ;
    }
};
void Weapon::setSample(Shot* Sample){
    m_Sample=Sample ;
};
char* Weapon::getName(){
    return m_Name ;
};
void Weapon::setOwner(Actor* Owner){
    m_Owner=Owner ;
};
StaticModel* Weapon::getIcon(){
    return m_Icon;
};
