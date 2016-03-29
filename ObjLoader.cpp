#include "ObjLoader.h"

int ObjLoader::LoadModel(char* filename,StaticModel *Dest){
    int rslt=1 ;
    ObjLoader* loader=new ObjLoader();
    rslt=loader->LoadObjFile(filename);
    if(rslt)
        rslt=loader->CopyBuffer(Dest);
    loader->Release();
    delete loader ;
    return rslt ;
};

ObjLoader::ObjLoader():v_Meshes(NULL),m_nbMeshes(0),v_Materials(NULL),m_nbMaterial(0){
};
ObjLoader::~ObjLoader(){
    Release();
};
void ObjLoader::Release(){
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
            /*if(v_Meshes[i].Name){
                free(v_Meshes[i].Name);
                v_Meshes[i].Name=NULL;
            }*/
            if(v_Meshes[i].material){
                if(v_Meshes[i].material->MaterialMap){
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
                    v_Meshes[i].material->TextureMap=NULL;}
                free((v_Meshes[i].material));
                v_Meshes[i].material=NULL ;
            }
        }
        free(v_Meshes);
        v_Meshes=NULL ;
    }
};
int ObjLoader::LoadObjFile(char* filename){
    FILE* objfile=fopen(filename,"r");
    if(!objfile)
        return 0 ;
    char line[150];
    Vertex3d tmpv;
    Vertex2d tmpt;
    Index tmpi1,tmpi2,tmpi3 ;
    AddMesh("Model");
    while(!feof(objfile)){
        ReadLine(objfile,line);
        switch(line[0]){
        case 'v': switch(line[1]){
                        case ' ':   fflush(stdin);
                                    sscanf(line,"v %f %f %f",&tmpv.x,&tmpv.y,&tmpv.z);
                                    addVertex(tmpv);
                                    break ;
                        case 'n':   fflush(stdin);
                                    sscanf(line,"vn %f %f %f",&tmpv.x,&tmpv.y,&tmpv.z);
                                    addNormal(tmpv);
                                    break ;
                        case 't':   fflush(stdin);
                                    printf("WTF\n");
                                    sscanf(line,"vt %f %f");
                                    addTexCoord(tmpt);
                                    break ;
                };break ;
        case 'f':   fflush(stdin);
                    if(contains(line,"//")){
                        sscanf(line,"f %d//%d %d//%d %d//%d",&tmpi1.VertexIndex,&tmpi1.NormalIndex,
                                                            &tmpi2.VertexIndex,&tmpi2.NormalIndex,
                                                            &tmpi3.VertexIndex,&tmpi3.NormalIndex);
                        tmpi1.TexIndex=0 ;tmpi2.TexIndex=0 ;tmpi3.TexIndex=0 ;
                    }else if(contains(line,"/")){
                        sscanf(line,"f %d/%d/%d %d/%d/%d %d/%d/%d",&tmpi1.VertexIndex,&tmpi1.TexIndex,&tmpi1.NormalIndex,
                                                                    &tmpi2.VertexIndex,&tmpi2.TexIndex,&tmpi2.NormalIndex,
                                                                    &tmpi3.VertexIndex,&tmpi3.TexIndex,&tmpi3.NormalIndex);}
                    else{
                        sscanf(line,"f %d %d %d",&tmpi1.VertexIndex,&tmpi2.VertexIndex,&tmpi3.VertexIndex);
                        tmpi1.TexIndex=0 ;tmpi2.TexIndex=0 ;tmpi3.TexIndex=0 ;
                        tmpi1.NormalIndex=0 ;tmpi2.NormalIndex=0 ;tmpi3.NormalIndex=0 ;
                        }
                    addIndices(tmpi1,tmpi2,tmpi3);
                    break ;
        case 'm': LoadMtlFile(line+6); break ;
        }
    }
    fclose(objfile);
    return 1;
};
int ObjLoader::LoadMtlFile(char* filename){

};
int ObjLoader::AddMesh(char* name){
    unsigned int i;
    Mesh* tmp = (Mesh*)malloc((m_nbMeshes+1)*sizeof(Mesh));
    if (tmp==NULL)
        return 0 ;
    for(i =0 ; i<m_nbMeshes; i++)
        tmp[i]=v_Meshes[i];
    free(v_Meshes);
   v_Meshes=tmp ;
    // copy name and init others attributs
    v_Meshes[m_nbMeshes].Name=NULL ;
    if(name!=NULL){
        v_Meshes[m_nbMeshes].Name=(char*)malloc(100*sizeof(char));
        for(i=0;name[i]!='\0';i++)
            v_Meshes[m_nbMeshes].Name[i]=name[i];
    }
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

int ObjLoader::addVertex(Vertex3d ver){
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
int ObjLoader::addNormal(Vertex3d ver){
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
int ObjLoader::addIndices(Index id1,Index id2,Index id3){
    if (m_nbMeshes>0){
        Index* tmp=(Index *)malloc(((v_Meshes[m_nbMeshes-1].Faces+1)*3)*sizeof(Index));
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
int ObjLoader::addTexCoord(Vertex2d tex){
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
int ObjLoader::CopyBuffer(StaticModel* Dest){
    if(v_Meshes){
        Dest->m_nbMeshes=m_nbMeshes;
        Dest->v_Meshes=(Mesh*)malloc(m_nbMeshes*sizeof(Mesh));
        for(unsigned int i=0;i<m_nbMeshes;i++){
            Dest->v_Meshes[i].MinVertex=v_Meshes[i].MinVertex ;
            Dest->v_Meshes[i].MaxVertex=v_Meshes[i].MaxVertex ;
            if(v_Meshes[i].VertexBuffer){
                Dest->v_Meshes[i].nbVertices=v_Meshes[i].nbVertices ;
                Dest->v_Meshes[i].VertexBuffer=(Vertex3d*)malloc(v_Meshes[i].nbVertices*sizeof(Vertex3d));
                for(unsigned int j=0 ; j<v_Meshes[i].nbVertices;j++)
                    Dest->v_Meshes[i].VertexBuffer[j]=v_Meshes[i].VertexBuffer[j];
            }
            if(v_Meshes[i].NormalsBuffer){
                Dest->v_Meshes[i].nbNormals=v_Meshes[i].nbNormals ;
                Dest->v_Meshes[i].NormalsBuffer=(Vertex3d*)malloc(v_Meshes[i].nbNormals*sizeof(Vertex3d));
                for(unsigned int j=0 ; j<v_Meshes[i].nbNormals;j++)
                    Dest->v_Meshes[i].NormalsBuffer[j]=v_Meshes[i].NormalsBuffer[j];
            }
            if(v_Meshes[i].TexCoords){
                Dest->v_Meshes[i].nbTexCoords=v_Meshes[i].nbTexCoords ;
                Dest->v_Meshes[i].TexCoords=(Vertex2d*)malloc(v_Meshes[i].nbTexCoords*sizeof(Vertex2d));
                for(unsigned int j=0 ; j<v_Meshes[i].nbTexCoords;j++)
                    Dest->v_Meshes[i].TexCoords[j]=v_Meshes[i].TexCoords[j];
            }
            if(v_Meshes[i].IndexBuffer){
                Dest->v_Meshes[i].Faces=v_Meshes[i].Faces ;
                Dest->v_Meshes[i].IndexBuffer=(Index*)malloc(v_Meshes[i].Faces*3*sizeof(Index));
                for(unsigned int j=0 ; j<v_Meshes[i].Faces*3;j++)
                    Dest->v_Meshes[i].IndexBuffer[j]=v_Meshes[i].IndexBuffer[j];
            }
            Dest->v_Meshes[i].material=NULL;
            /*if(v_Meshes[i].material){

            }*/
        }
    }
    return 1 ;
};
void ObjLoader::InitMinMaxVertices (){
    for(unsigned int i=0 ;i<m_nbMeshes ;i++){
        v_Meshes[i].MinVertex={0.0f,0.0f,0.0f};
        v_Meshes[i].MaxVertex={0.0f,0.0f,0.0f};
        for(unsigned int j=0 ;j< v_Meshes[i].nbVertices;j++){
            if(v_Meshes[i].VertexBuffer[j].x > v_Meshes[i].MaxVertex.x )
                v_Meshes[i].MaxVertex.x=v_Meshes[i].VertexBuffer[j].x ;
            if(v_Meshes[i].VertexBuffer[j].y > v_Meshes[i].MaxVertex.y )
                v_Meshes[i].MaxVertex.y=v_Meshes[i].VertexBuffer[j].y ;
            if(v_Meshes[i].VertexBuffer[j].z > v_Meshes[i].MaxVertex.z )
                v_Meshes[i].MaxVertex.z=v_Meshes[i].VertexBuffer[j].z ;
            if(v_Meshes[i].VertexBuffer[j].x < v_Meshes[i].MinVertex.x )
                v_Meshes[i].MinVertex.x=v_Meshes[i].VertexBuffer[j].x ;
            if(v_Meshes[i].VertexBuffer[j].y < v_Meshes[i].MinVertex.y )
                v_Meshes[i].MinVertex.y=v_Meshes[i].VertexBuffer[j].y ;
            if(v_Meshes[i].VertexBuffer[j].z < v_Meshes[i].MinVertex.z )
                v_Meshes[i].MinVertex.z=v_Meshes[i].VertexBuffer[j].z ;
        }
    }
};
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
bool contains(char* str1,char* str2){
    bool result ;
    if(str1==NULL || str2==NULL )
        return false ;
    int len1=strlen(str1),len2=strlen(str2);
    if(len1< len2)
        return false ;
    result=false;
    for(int i=0 ;i<len1-len2 && !result;i++){
        result=true ;
        for(int j=0;str2[j]&& result;j++)
            if(str1[i+j]!=str2[j])
                result=false ;
    }
    return result;
};
