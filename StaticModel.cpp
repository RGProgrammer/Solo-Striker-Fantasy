#include "StaticModel.h"

StaticModel::StaticModel():Drawable(),m_nbMeshes(0),v_Meshes(NULL),m_Color({0.0f,1.0f,0.0f}),
                                m_Scale(1.0f){
};
StaticModel::StaticModel(Vertex3d Pos):StaticModel(){
    m_Pos=Pos;
};
StaticModel::StaticModel(Vertex3d Pos,Vertex3d Dir,Vertex3d Up):StaticModel(Pos)
{
    if(DotProduct3d(Dir,Up)==0.0f){
        m_Dir=Dir ;
        m_Up=Up ;
    }
};
StaticModel::~StaticModel(){
    Actor::Destroy();
    this->Destroy();
};
int StaticModel::LoadFromFile(char* filename){
    return ObjLoader::LoadFile(this,filename);
};
StaticModel* StaticModel::LoadFile(char* filename){
    StaticModel* obj=new StaticModel();
    if(!obj)
        return NULL ;
    if(!obj->LoadFromFile(filename)){
        delete obj ;
        return NULL ;
    }
    return obj;
};
void StaticModel::Draw(float * ViewMtx){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(ViewMtx){
        float tmp[16];
        Multi4x4Mtx(ViewMtx,this->getTransMtx(),tmp);
        glLoadMatrixf(tmp);
    }else
        glLoadMatrixf(this->getTransMtx());
    glBegin(GL_TRIANGLES);
    glColor3f(m_Color.r,m_Color.g,m_Color.b);
        for(unsigned int i=0;i<m_nbMeshes ; i++){
            for(unsigned int j=0;j<v_Meshes[i].Faces;j++){
                glNormal3f(v_Meshes[i].NormalsBuffer[j].x,v_Meshes[i].NormalsBuffer[j].y,v_Meshes[i].NormalsBuffer[j].z);
                glVertex3f(v_Meshes[i].VertexBuffer[v_Meshes[i].IndexBuffer[j*3]-1].x,
                          v_Meshes[i].VertexBuffer[v_Meshes[i].IndexBuffer[j*3]-1].y,
                          v_Meshes[i].VertexBuffer[v_Meshes[i].IndexBuffer[j*3]-1].z);
                glVertex3f(v_Meshes[i].VertexBuffer[v_Meshes[i].IndexBuffer[j*3+1]-1].x,
                          v_Meshes[i].VertexBuffer[v_Meshes[i].IndexBuffer[j*3+1]-1].y,
                          v_Meshes[i].VertexBuffer[v_Meshes[i].IndexBuffer[j*3+1]-1].z);
                glVertex3f(v_Meshes[i].VertexBuffer[v_Meshes[i].IndexBuffer[j*3+2]-1].x,
                          v_Meshes[i].VertexBuffer[v_Meshes[i].IndexBuffer[j*3+2]-1].y,
                          v_Meshes[i].VertexBuffer[v_Meshes[i].IndexBuffer[j*3+2]-1].z);
            }
        }
    glEnd();
};
void StaticModel::Scale(float value ){
    this->m_Scale=value;
};
void StaticModel::Destroy(){
    if(v_Meshes){
        for(unsigned int i = 0 ; i<m_nbMeshes ; i++){
            free((v_Meshes[i].Name));
            if(v_Meshes[i].VertexBuffer){
                free((v_Meshes[i].VertexBuffer));
                v_Meshes[i].VertexBuffer=NULL;}
            if(v_Meshes[i].IndexBuffer){
                free((v_Meshes[i].IndexBuffer));
                v_Meshes[i].IndexBuffer=NULL;}
            if(v_Meshes[i].NormalsBuffer){
                free(v_Meshes[i].NormalsBuffer);
                v_Meshes[i].NormalsBuffer=NULL ;}
            if(v_Meshes[i].material){
                /*if(v_Meshes[i].material->MaterialMap){
                    if(v_Meshes[i].material->MaterialMap->Pixels)
                        free(v_Meshes[i].material->MaterialMap->Pixels);
                    free(v_Meshes[i].material->MaterialMap);
                    v_Meshes[i].material->MaterialMap=NULL;}
                if(v_Meshes[i].material->ReflexionMap){
                    if(v_Meshes[i].material->ReflexionMap->Pixels)
                        free(v_Meshes[i].material->ReflexionMap->Pixels);
                    free(v_Meshes[i].material->ReflexionMap);
                    v_Meshes[i].material->ReflexionMap=NULL ;}
                if(v_Meshes[i].material->BumpMap){
                    if(v_Meshes[i].material->BumpMap->Pixels)
                        free(v_Meshes[i].material->BumpMap->Pixels);
                    free(v_Meshes[i].material->BumpMap);
                    v_Meshes[i].material->BumpMap=NULL;}
                if(v_Meshes[i].material->TextureMap){
                    if(v_Meshes[i].material->TextureMap->Pixels)
                        free(v_Meshes[i].material->TextureMap->Pixels);
                    free(v_Meshes[i].material->TextureMap);
                    v_Meshes[i].material->TextureMap=NULL;}*/
                free((v_Meshes[i].material));
                v_Meshes[i].material=NULL ;
            }
        }
        free(v_Meshes);
    }
};
void StaticModel::setColor(ColorRGB Color){
    m_Color=Color ;
};
ColorRGB StaticModel::getColor(){
    return m_Color ;
};
void StaticModel::UpdateMtx(){
        m_Right=Normalize3d(m_Right);m_Up=Normalize3d(m_Up);m_Dir=Normalize3d(m_Dir);
        m_TransMtx[0]=m_Right.x*m_Scale; m_TransMtx[4]=m_Up.x; m_TransMtx[8]=m_Dir.x ; m_TransMtx[12]=m_Pos.x ;
        m_TransMtx[1]=m_Right.y; m_TransMtx[5]=m_Up.y*m_Scale; m_TransMtx[9]=m_Dir.y ; m_TransMtx[13]=m_Pos.y ;
        m_TransMtx[2]=m_Right.z; m_TransMtx[6]=m_Up.z; m_TransMtx[10]=m_Dir.z*m_Scale; m_TransMtx[14]=m_Pos.z;
        m_TransMtx[3]=0.0f    ; m_TransMtx[7]=0.0f  ; m_TransMtx[11]=0.0f   ; m_TransMtx[15]=1.0f   ;
};
StaticModel* StaticModel::CreateCube(){
     StaticModel *Obj=new StaticModel();
    Vertex3d* v_buffer ;
    unsigned int *i_buffer ;
    Obj->m_nbMeshes=1;
    Obj->v_Meshes=(pMesh)malloc(Obj->m_nbMeshes*sizeof(Mesh));
    if(Obj->v_Meshes==NULL){
        delete Obj;
        return NULL;
    }
    Obj->v_Meshes->IndexBuffer=NULL ;
    Obj->v_Meshes->NormalsBuffer=NULL ;
    Obj->v_Meshes->TexCoords=NULL ;
    Obj->v_Meshes->VertexBuffer=NULL ;
    Obj->v_Meshes->nbVertices=8 ;
    Obj->v_Meshes->Faces=12 ;
    Obj->v_Meshes->VertexBuffer=(Vertex3d*)malloc(8*sizeof(Vertex3d));
    if(Obj->v_Meshes->VertexBuffer==NULL){
        Obj->Destroy();
        delete Obj ;
        return NULL ;
        }
    Obj->v_Meshes->IndexBuffer=(unsigned int*)malloc(36*sizeof(unsigned int ));
    if(Obj->v_Meshes->IndexBuffer==NULL){
        Obj->Destroy();
        delete Obj ;
        return NULL ;
    }
        v_buffer=Obj->v_Meshes->VertexBuffer ;
        v_buffer[0]={10.0f,10.0f,10.0f};
        v_buffer[1]={-10.0f,10.0f,10.0f};
        v_buffer[2]={-10.0f,-10.0f,10.0f};
        v_buffer[3]={10.0f,-10.0f,10.0f};
        v_buffer[4]={10.0f,10.0f,-10.0f};
        v_buffer[5]={-10.0f,10.0f,-10.0f};
        v_buffer[6]={-10.0f,-10.0f,-10.0f};
        v_buffer[7]={10.0f,-10.0f,-10.0f};

        i_buffer=Obj->v_Meshes->IndexBuffer ;
        i_buffer[0]=0 ;i_buffer[1]=1 ;i_buffer[2]=2 ;
        i_buffer[3]=1 ;i_buffer[4]=2 ;i_buffer[5]=3 ;

        i_buffer[6]=0 ;i_buffer[7]=1 ;i_buffer[8]=5 ;
        i_buffer[9]=1 ;i_buffer[10]=5 ;i_buffer[11]=4 ;

        i_buffer[12]=4 ;i_buffer[13]=5 ;i_buffer[14]=6 ;
        i_buffer[15]=5 ;i_buffer[16]=6 ;i_buffer[17]=7 ;

        i_buffer[18]=7 ;i_buffer[19]=6 ;i_buffer[20]=2 ;
        i_buffer[21]=6 ;i_buffer[22]=2 ;i_buffer[23]=3 ;

        i_buffer[24]=0 ;i_buffer[25]=4 ;i_buffer[26]=7 ;
        i_buffer[27]=4 ;i_buffer[28]=7 ;i_buffer[29]=3 ;

        i_buffer[30]=1 ;i_buffer[31]=5 ;i_buffer[32]=6 ;
        i_buffer[33]=5 ;i_buffer[34]=6 ;i_buffer[35]=2 ;
        Obj->v_Meshes->MinVertex={-10.0f,-10.0f,-10.0f} ;
        Obj->v_Meshes->MaxVertex={10.0f,10.0f,10.0f} ;
        return Obj ;
};
int StaticModel::AddMesh(char* name){
    unsigned int i;
    Mesh* tmp = (Mesh*)malloc((m_nbMeshes+1)*sizeof(Mesh));
    if (tmp==NULL)
        return 0 ;
    for(i =0 ; i<m_nbMeshes; i++)
        tmp[i]=v_Meshes[i];
    free(v_Meshes);
   v_Meshes=tmp ;
    // copy name and init others attributs
   v_Meshes[m_nbMeshes].Name=(char*)malloc(100*sizeof(char));
    for(i=0;name[i]!='\0';i++)
       v_Meshes[m_nbMeshes].Name[i]=name[i];
   v_Meshes[m_nbMeshes].Name[i]=name[i];
   v_Meshes[m_nbMeshes].Faces=0;
   v_Meshes[m_nbMeshes].IndexBuffer=NULL ;
   v_Meshes[m_nbMeshes].material=NULL;
   v_Meshes[m_nbMeshes].nbNormals=0;
   v_Meshes[m_nbMeshes].nbTexCoords=0;
   v_Meshes[m_nbMeshes].nbVertices=0;
   v_Meshes[m_nbMeshes].NormalsBuffer=NULL;
   v_Meshes[m_nbMeshes].TexCoords=NULL;
   v_Meshes[m_nbMeshes].VertexBuffer=NULL;
   v_Meshes[m_nbMeshes].MaxVertex={0.0f,0.0f,0.0f};
   v_Meshes[m_nbMeshes].MinVertex={0.0f,0.0f,0.0f};
    m_nbMeshes++ ;
    return 1 ;
};

int StaticModel::addVertex(Vertex3d ver){
    if (m_nbMeshes>0){
        Vertex3d* tmp=(Vertex3d*)malloc((v_Meshes[m_nbMeshes-1].nbVertices+1)*sizeof(Vertex3d));
        if(!tmp)
            return 0;
        for(unsigned int i =0 ;i<v_Meshes[m_nbMeshes-1].nbVertices;i++)
            tmp[i]=v_Meshes[m_nbMeshes-1].VertexBuffer[i];
        free(v_Meshes[m_nbMeshes-1].VertexBuffer);
        v_Meshes[m_nbMeshes-1].VertexBuffer=tmp ;
        v_Meshes[m_nbMeshes-1].VertexBuffer[v_Meshes[m_nbMeshes-1].nbVertices]=ver ;
        v_Meshes[m_nbMeshes-1].nbVertices++;
        return 1 ;
    }
    return 0;
};
int StaticModel::addNormal(Vertex3d ver){
    if (m_nbMeshes>0){
        Vertex3d* tmp=(Vertex3d*)malloc((v_Meshes[m_nbMeshes-1].nbNormals+1)*sizeof(Vertex3d));
        if(!tmp)
            return 0;
        for(unsigned int i =0 ;i<v_Meshes[m_nbMeshes-1].nbNormals;i++)
            tmp[i]=v_Meshes[m_nbMeshes-1].NormalsBuffer[i];
        free(v_Meshes[m_nbMeshes-1].NormalsBuffer);
        v_Meshes[m_nbMeshes-1].NormalsBuffer=tmp ;
        v_Meshes[m_nbMeshes-1].NormalsBuffer[v_Meshes[m_nbMeshes-1].nbNormals]=ver ;
        v_Meshes[m_nbMeshes-1].nbNormals++;
        return 1 ;
    }
    return 0 ;
};
int StaticModel::addIndices(unsigned int id1,unsigned int id2,unsigned int id3){
    if (m_nbMeshes>0){
        unsigned int * tmp=(unsigned int *)malloc(((v_Meshes[m_nbMeshes-1].Faces+1)*3)*sizeof(unsigned int ));
        if(!tmp)
            return 0;
        for(unsigned int i =0 ;i<v_Meshes[m_nbMeshes-1].Faces*3;i++)
            tmp[i]=v_Meshes[m_nbMeshes-1].IndexBuffer[i];
        free(v_Meshes[m_nbMeshes-1].IndexBuffer);
        v_Meshes[m_nbMeshes-1].IndexBuffer=tmp ;
        v_Meshes[m_nbMeshes-1].IndexBuffer[v_Meshes[m_nbMeshes-1].Faces*3]=id1 ;
        v_Meshes[m_nbMeshes-1].IndexBuffer[v_Meshes[m_nbMeshes-1].Faces*3+1]=id2 ;
        v_Meshes[m_nbMeshes-1].IndexBuffer[v_Meshes[m_nbMeshes-1].Faces*3+2]=id3 ;
        v_Meshes[m_nbMeshes-1].Faces++;
        return 1;
    }
    return 0 ;
};
int StaticModel::addTexCoord(Vertex2d tex){
    if (m_nbMeshes>0){
        Vertex2d* tmp=(Vertex2d*)malloc((v_Meshes[m_nbMeshes-1].nbTexCoords+1)*sizeof(Vertex2d));
        if(!tmp)
            return 0;
        for(unsigned int i =0 ;i<v_Meshes[m_nbMeshes-1].nbTexCoords;i++)
            tmp[i]=v_Meshes[m_nbMeshes-1].TexCoords[i];
        free(v_Meshes[m_nbMeshes-1].TexCoords);
        v_Meshes[m_nbMeshes-1].TexCoords=tmp ;
        v_Meshes[m_nbMeshes-1].TexCoords[v_Meshes[m_nbMeshes-1].nbTexCoords]=tex ;
        v_Meshes[m_nbMeshes-1].nbTexCoords++;
        return 1 ;
    }
    return 0 ;
};

int StaticModel::Clone (StaticModel* Model){
    unsigned int j ;
    m_nbMeshes=Model->m_nbMeshes ;
    if(!m_nbMeshes)
        return 0 ;
    v_Meshes=(pMesh)malloc(m_nbMeshes*sizeof(Mesh));
    if(!v_Meshes)
        return 0 ;
    for(unsigned int i=0;i<Model->m_nbMeshes;i++){
        v_Meshes[i].MinVertex=Model->v_Meshes[i].MinVertex;
        v_Meshes[i].MaxVertex=Model->v_Meshes[i].MaxVertex;
        //copying Name
        v_Meshes[i].Name=(char*)malloc(100*sizeof(char));
        for(j=0;Model->v_Meshes[i].Name[j];j++)
            v_Meshes[i].Name[i]=Model->v_Meshes[i].Name[j];
        v_Meshes[i].Name[j]='\0';
        //copying vertices
        v_Meshes[i].nbVertices=Model->v_Meshes[i].nbVertices ;
        v_Meshes[i].VertexBuffer=(Vertex3d*)malloc(v_Meshes[i].nbVertices*sizeof(Vertex3d));
        for(j=0;j<v_Meshes[i].nbVertices;j++)
            v_Meshes[i].VertexBuffer[j]=Model->v_Meshes[i].VertexBuffer[j];
        //copying Normals
        v_Meshes[i].nbNormals=Model->v_Meshes[i].nbNormals ;
        v_Meshes[i].NormalsBuffer=(Vertex3d*)malloc(v_Meshes[i].nbNormals*sizeof(Vertex3d));
        for(j=0;j<v_Meshes[i].nbNormals;j++)
            v_Meshes[i].NormalsBuffer[j]=Model->v_Meshes[i].NormalsBuffer[j];
        //copying Indices
        v_Meshes[i].Faces=Model->v_Meshes[i].Faces ;
        v_Meshes[i].IndexBuffer=(unsigned int*)malloc(v_Meshes[i].Faces*3*sizeof(unsigned int));
        for(j=0;j<v_Meshes[i].Faces*3;j++)
            v_Meshes[i].IndexBuffer[j]=Model->v_Meshes[i].IndexBuffer[j];
        //copying Texture coordinates
        v_Meshes[i].nbTexCoords=Model->v_Meshes[i].nbTexCoords ;
        v_Meshes[i].TexCoords=(Vertex2d*)malloc(v_Meshes[i].nbTexCoords*sizeof(Vertex2d));
        for(j=0;j<v_Meshes[i].nbTexCoords;j++)
            v_Meshes[i].TexCoords[j]=Model->v_Meshes[i].TexCoords[j];
        v_Meshes[i].material=NULL;

    }
    return 1 ;
};
void StaticModel::getAABB(Vertex3d* MinVertex ,Vertex3d* MaxVertex){
    if(MinVertex && MaxVertex){
        MinVertex->x=v_Meshes[0].MinVertex.x ;MinVertex->y=v_Meshes[0].MinVertex.y ;MinVertex->z=v_Meshes[0].MinVertex.z ;
        MaxVertex->x=v_Meshes[0].MaxVertex.x ;MaxVertex->y=v_Meshes[0].MaxVertex.y ;MaxVertex->z=v_Meshes[0].MaxVertex.z ;
        for (unsigned int i=1;i<m_nbMeshes;i++){
            if(v_Meshes[i].MinVertex.x < MinVertex->x)
                MinVertex->x=v_Meshes[i].MinVertex.x ;
            if(v_Meshes[i].MaxVertex.x > MaxVertex->x)
                MaxVertex->x=v_Meshes[i].MaxVertex.x ;
            if(v_Meshes[i].MinVertex.y < MinVertex->y)
                MinVertex->y=v_Meshes[i].MinVertex.y ;
            if(v_Meshes[i].MaxVertex.y > MaxVertex->y)
                MaxVertex->y=v_Meshes[i].MaxVertex.y ;
            if(v_Meshes[i].MinVertex.z < MinVertex->z)
                MinVertex->z=v_Meshes[i].MinVertex.z ;
            if(v_Meshes[i].MaxVertex.z > MaxVertex->z)
                MaxVertex->z=v_Meshes[i].MaxVertex.z ;
        }
        MinVertex->x+=m_Pos.x ;MinVertex->y+=m_Pos.y ;MinVertex->z+=m_Pos.z ;
        MaxVertex->x+=m_Pos.x ;MaxVertex->y+=m_Pos.y ;MaxVertex->z+=m_Pos.z ;
    }
};
float StaticModel::getRadius(){
    float rslt=0.0f, d ;
    for(unsigned int i=0;i< m_nbMeshes;i++){
        d=Magnitude3d(v_Meshes[i].MaxVertex);
        if(d>rslt)
            rslt=d ;
    }
    return rslt ;
};
