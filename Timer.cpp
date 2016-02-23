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
    dt=0.0;
    if(m_Started){
        dt=(current_time.tv_sec-last_time.tv_sec)+(current_time.tv_sec-last_time.tv_sec)/(float)1000 ;
    }
    return dt ;
};

