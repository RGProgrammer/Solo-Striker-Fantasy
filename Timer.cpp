#include "Timer.h"

void Timer::Stop(){
    m_Started=false ;
};
Timer::Timer(){
    gettimeofday(&current_time,NULL);
    last_time=current_time ;
	m_Started=false;
};
Timer::~Timer(){

};
void Timer::Reset(){
    gettimeofday(&current_time,NULL);
    last_time=current_time ;
    m_Started=true ;
};
double Timer::getDeltaTime(){
    dt=0.0f;
    if(m_Started){
        if(gettimeofday(&current_time,NULL)==0){
            dt=(float)(current_time.tv_sec-last_time.tv_sec)/(float)1000+(current_time.tv_usec-last_time.tv_usec)/(float)1000000 ;
            last_time=current_time ;
            if(dt<0.0f)
                dt=0.0f;
        }
    }
    return dt ;
};

