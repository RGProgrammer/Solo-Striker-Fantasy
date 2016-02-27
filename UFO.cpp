#include "UFO.h"

UFO::UFO():Enemy(){
};
UFO::UFO(Vertex3d Pos):Enemy(Pos){
};
UFO::UFO(Vertex3d Pos, Vertex3d Dir, Vertex3d Up):Enemy(Pos,Dir,Up){
};
int UFO::LoadFromFile(){
    StaticModel::LoadFromFile("Data//UFO.obj");
    this->setColor({5.0f,0.0f,0.5f});
    m_Health=1 ;
    m_Dt=0.0f;
    /*m_nbActions=2;
    v_Actions=(Action*)malloc(m_nbActions*sizeof(Action));
    v_Actions[0].ActionType=MOVEACTION ;
    v_Actions[0].Instance=0.0f;
    v_Actions[0].Data=malloc(sizeof(Movement));
    ((Movement*)v_Actions[0].Data)->Translate={50.0f,0.0f,0.0f};
    ((Movement*)v_Actions[0].Data)->Rotate={0.0f,0.0f,0.0f};
    ((Movement*)v_Actions[0].Data)->Speed=1.0f;
    v_Actions[1].ActionType=MOVEACTION ;
    v_Actions[1].Instance=50.0f;
    v_Actions[1].Data=malloc(sizeof(Movement));
    ((Movement*)v_Actions[1].Data)->Translate={-50.0f,0.0f,0.0f};
    ((Movement*)v_Actions[1].Data)->Rotate={0.0f,0.0f,0.0f};
    ((Movement*)v_Actions[1].Data)->Speed=1.0f;

    m_CurrentAction=0;*/
};
void UFO::Update(float dt){
    /*if(v_Actions)
        if(m_CurrentAction< m_nbActions)
            for(int i = m_CurrentAction;i<m_nbAction && v_Action[i].Instance<=m_Dt; i++){
                if(v_Actions[i].ActionType==MOVEACTION)
                    m_Velocity=AddVertex3d(m_Velocity,ScaleVertex3d(v_Actions[i].Data->Translate,1/v_Actions[i].Data->Speed));
                    m_Pos=AddVertex3d(m_Pos,)
    }*/
};

