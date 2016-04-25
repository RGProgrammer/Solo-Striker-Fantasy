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
    return ObjLoader::LoadModel(filename,this);
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
    GLuint textureId=0;
    glEnable(GL_TEXTURE_2D);
    //initializing transformation matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(ViewMtx){
        float tmp[16];
        Multi4x4Mtx(ViewMtx,this->getTransMtx(),tmp);
        glLoadMatrixf(tmp);
    }else
        glLoadMatrixf(this->getTransMtx());
    //start drawing;
        for(unsigned int i=0;i<m_nbMeshes ; i++){
        if(v_Meshes[i].material && v_Meshes[i].material->TextureId){
				 glBindTexture(GL_TEXTURE_2D,v_Meshes[i].material->TextureId);
				 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }
        if(v_Meshes[i].IndexBuffer){
            glBegin(GL_TRIANGLES);
            glColor3f(1.0f,1.0f,1.0f);
            for(unsigned int j=0;j <v_Meshes[i].Faces*3;j++){
                ////////////////////////////////////////////////////////////
                if(v_Meshes[i].IndexBuffer[j].NormalIndex==0)
                    glNormal3f(0.0f,0.0f,0.0f);
                else
                    glNormal3f(v_Meshes[i].NormalsBuffer[v_Meshes[i].IndexBuffer[j].NormalIndex-1].x,
                               v_Meshes[i].NormalsBuffer[v_Meshes[i].IndexBuffer[j].NormalIndex-1].y,
                               v_Meshes[i].NormalsBuffer[v_Meshes[i].IndexBuffer[j].NormalIndex-1].z);
                //////////
                if(v_Meshes[i].IndexBuffer[j].TexIndex!=0){
                    glTexCoord2f(v_Meshes[i].TexCoords[v_Meshes[i].IndexBuffer[j].TexIndex-1].u,
                                 v_Meshes[i].TexCoords[v_Meshes[i].IndexBuffer[j].TexIndex-1].v);
                }else
                    glColor3f(m_Color.r,m_Color.g,m_Color.b);
                //////////
                glVertex3f(v_Meshes[i].VertexBuffer[v_Meshes[i].IndexBuffer[j].VertexIndex-1].x,
                           v_Meshes[i].VertexBuffer[v_Meshes[i].IndexBuffer[j].VertexIndex-1].y,
                           v_Meshes[i].VertexBuffer[v_Meshes[i].IndexBuffer[j].VertexIndex-1].z);

            }
            glEnd();
        }
            if(textureId!=0){
                glDeleteTextures(1,&textureId);
            }
        }

    glDisable(GL_TEXTURE_2D);
};
void StaticModel::Scale(float value ){
    this->m_Scale=value;
};
void StaticModel::Destroy(){
    if(v_Meshes){
        for(unsigned int i = 0 ; i<m_nbMeshes ; i++){
            if(v_Meshes[i].VertexBuffer){
                free((v_Meshes[i].VertexBuffer));
                v_Meshes[i].VertexBuffer=NULL;}
            if(v_Meshes[i].IndexBuffer){
                free((v_Meshes[i].IndexBuffer));
                v_Meshes[i].IndexBuffer=NULL;}
            if(v_Meshes[i].NormalsBuffer){
                free(v_Meshes[i].NormalsBuffer);
                v_Meshes[i].NormalsBuffer=NULL ;}
            if(v_Meshes[i].Name){
                free(v_Meshes[i].Name);
                v_Meshes[i].Name=NULL;
            }
            if(v_Meshes[i].material){
                if(v_Meshes[i].material->TextureMap){
                    if(v_Meshes[i].material->TextureMap->Pixels)
                        free(v_Meshes[i].material->TextureMap->Pixels);
                    free(v_Meshes[i].material->TextureMap);
                    v_Meshes[i].material->TextureMap=NULL;}
                if(v_Meshes[i].material->TextureId)
                    glDeleteTextures(1,&v_Meshes[i].material->TextureId);
                free((v_Meshes[i].material));
                v_Meshes[i].material=NULL ;
            }
        }
        free(v_Meshes);
        v_Meshes=NULL ;
    }
};
void StaticModel::setColor(ColorRGB Color){
    m_Color=Color ;
};
ColorRGB StaticModel::getColor(){
    return m_Color ;
};
void StaticModel::UpdateMtx(){
        Actor::UpdateMtx();
        m_TransMtx[0]*=m_Scale ;
        m_TransMtx[5]*= m_Scale;
        m_TransMtx[10]*= m_Scale;
};

int StaticModel::AddMesh(char* name){
    Mesh* tmp = (Mesh*)malloc((m_nbMeshes+1)*sizeof(Mesh));
    if (tmp==NULL)
        return 0 ;
    for(unsigned int i =0 ; i<m_nbMeshes; i++)
        tmp[i]=v_Meshes[i];
    free(v_Meshes);
   v_Meshes=tmp ;
    // copy name and init others attributs
   v_Meshes[m_nbMeshes].Name=(char*)malloc((strlen(name)+1)*sizeof(char));
    for(unsigned int i=0;name[i];i++)
       v_Meshes[m_nbMeshes].Name[i]=name[i];
   v_Meshes[m_nbMeshes].Name[strlen(name)]='\0';
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
int StaticModel::addIndices(Index id1,Index id2,Index id3){
    if (m_nbMeshes>0){
        Index * tmp=(Index *)malloc(((v_Meshes[m_nbMeshes-1].Faces+1)*3)*sizeof(Index));
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
    m_nbMeshes=Model->m_nbMeshes ;
    if(!m_nbMeshes){
        this->Destroy();
        return 0 ;
    }
    v_Meshes=(Mesh*)malloc(m_nbMeshes*sizeof(Mesh));
    if(!v_Meshes){
        this->Destroy();
        return 0 ;
    }
    for(unsigned int i=0;i<Model->m_nbMeshes;i++){
        v_Meshes[i].MinVertex=Model->v_Meshes[i].MinVertex;
        v_Meshes[i].MaxVertex=Model->v_Meshes[i].MaxVertex;
        v_Meshes[i].Name=NULL;
        v_Meshes[i].Faces=0;
        v_Meshes[i].nbNormals=0;
        v_Meshes[i].nbTexCoords=0;
        v_Meshes[i].nbVertices=0;
        v_Meshes[i].NormalsBuffer=NULL;
        v_Meshes[i].TexCoords=NULL;
        v_Meshes[i].VertexBuffer=NULL;
        v_Meshes[i].IndexBuffer=NULL ;
        v_Meshes[i].material=NULL;
    }
    for(unsigned int i=0;i<m_nbMeshes;i++){
        //copying Texture coordinates
        if(Model->v_Meshes[i].TexCoords ){
            v_Meshes[i].nbTexCoords=Model->v_Meshes[i].nbTexCoords ;
            v_Meshes[i].TexCoords=(Vertex2d*)malloc(v_Meshes[i].nbTexCoords*sizeof(Vertex2d));
            for(unsigned int j=0;j<v_Meshes[i].nbTexCoords;j++){
                v_Meshes[i].TexCoords[j]=Model->v_Meshes[i].TexCoords[j];}
        }
        //copying Name
        /*if(Model->v_Meshes[i].Name){
            v_Meshes[i].Name=(char*)malloc((strlen(Model->v_Meshes[i].Name)+1)*sizeof(char));
            for(unsigned int j=0;(Model->v_Meshes[i].Name[j]);j++)
                v_Meshes[i].Name[j]=Model->v_Meshes[i].Name[j];
            v_Meshes[i].Name[strlen((Model->v_Meshes[i].Name))]='\0';
        }*/

        //copying vertices
        v_Meshes[i].nbVertices=Model->v_Meshes[i].nbVertices ;
        v_Meshes[i].VertexBuffer=(Vertex3d*)malloc(v_Meshes[i].nbVertices*sizeof(Vertex3d));
        for(unsigned int j=0;j<v_Meshes[i].nbVertices;j++)
            v_Meshes[i].VertexBuffer[j]=Model->v_Meshes[i].VertexBuffer[j];
        //copying Normals
        v_Meshes[i].nbNormals=Model->v_Meshes[i].nbNormals ;
        v_Meshes[i].NormalsBuffer=(Vertex3d*)malloc(v_Meshes[i].nbNormals*sizeof(Vertex3d));
        for(unsigned int j=0;j<v_Meshes[i].nbNormals;j++)
            v_Meshes[i].NormalsBuffer[j]=Model->v_Meshes[i].NormalsBuffer[j];
        //copying Indices
        v_Meshes[i].Faces=Model->v_Meshes[i].Faces ;
        v_Meshes[i].IndexBuffer=(Index*)malloc(v_Meshes[i].Faces*3*sizeof(Index));
        for(unsigned int j=0;j<v_Meshes[i].Faces*3;j++)
            v_Meshes[i].IndexBuffer[j]=Model->v_Meshes[i].IndexBuffer[j];

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
