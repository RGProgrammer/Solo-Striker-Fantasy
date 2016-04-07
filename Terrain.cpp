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
    if(!(v_Points=(Vertex3d*)malloc(9*sizeof(Vertex3d))))
        return 0 ;
    float offset= m_Sample->getRadius()*1.414213562f;
    for(int i=-1;i<2;i++)
        for(int j=-1;j<2;j++){
            v_Points[(i+1)*3+j+1].x=offset*j;
            v_Points[(i+1)*3+j+1].y=0.0f;
            v_Points[(i+1)*3+j+1].z=offset*i;
        }
    m_Speed=2.0f ;
    return 1 ;
};
void Terrain::setSpeed(float Speed ){
    if(Speed>=0.0f)
        m_Speed=Speed;
};
void Terrain::Update(float dt){
    /*m_Velocity= ;
    for(int i=0 ; i<9 ;i++)
        v_Points[i]=AddVertex3d(v_Points[i],m_Velocity);*/
};
void Terrain::Draw(float* ViewMtx){
for(int i=0;i<9;i++){
        m_Sample->setPosition(v_Points[i]);
        m_Sample->Draw(ViewMtx);
    }
};
