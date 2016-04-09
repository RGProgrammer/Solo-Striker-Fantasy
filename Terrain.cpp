#include "Terrain.h"

Terrain::Terrain():DnU(),m_Sample(NULL),v_Points(NULL),m_Speed(0.0f){
};
Terrain::~Terrain(){
    this->Destroy();
};
void Terrain::Destroy(){
    if(m_Sample){
        delete m_Sample;
        m_Sample=NULL ;
    }
    if(v_Points){
        free(v_Points);
        v_Points=NULL;
    }
};
int Terrain::LoadFromFile(char* filename){
    if(!(m_Sample=StaticModel::LoadFile(filename)))
        return 0 ;
    if(!(v_Points=(Vertex3d*)malloc(12*sizeof(Vertex3d))))
        return 0 ;
    m_Offset= m_Sample->getRadius()*1.4142135f;//62f;
    for(int i=-1;i<3;i++)
        for(int j=-1;j<2;j++){
            v_Points[(i+1)*3+j+1].x=m_Offset*j;
            v_Points[(i+1)*3+j+1].y=75.0f;
            v_Points[(i+1)*3+j+1].z=m_Offset*i;
        }
    m_Speed=20.0f ;
    return 1 ;
};
void Terrain::setSpeed(float Speed ){
    if(Speed>=0.0f)
        m_Speed=Speed;
};
void Terrain::Update(float dt){
    if(dt==0)
        dt=0.01f;
    for(int i=0 ; i<12 ;i++){
        v_Points[i].z-=m_Speed*dt;
        if(v_Points[i].z<=-(m_Offset*3/2))
            v_Points[i].z=m_Offset;
    }
};
void Terrain::Draw(float* ViewMtx){
for(int i=0;i<12;i++){
        m_Sample->setPosition(v_Points[i]);
        m_Sample->Draw(ViewMtx);
    }
};
