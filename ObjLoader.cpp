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
                v_Meshes[i].VertexBuffer=NULL;
            }
            if(v_Meshes[i].IndexBuffer){
                free((v_Meshes[i].IndexBuffer));
                v_Meshes[i].IndexBuffer=NULL;
            }

            if(v_Meshes[i].Name){
                free(v_Meshes[i].Name);
                v_Meshes[i].Name=NULL;
            }
            if(v_Meshes[i].material){
                v_Meshes[i].material=NULL ;
            }
            if(v_Meshes[i].NormalsBuffer){
                free(v_Meshes[i].NormalsBuffer);
                v_Meshes[i].NormalsBuffer=NULL ;
            }
        }
        free(v_Meshes);
        v_Meshes=NULL ;
    }
    if(v_Materials){
        for(int i=0;i<m_nbMaterial;i++){
            if(v_Materials[i].mtlName)
                free((v_Materials[i].mtlName));
            if(v_Materials[i].TextureMap){
                if(v_Materials[i].TextureMap->Pixels)
                    free(v_Materials[i].TextureMap->Pixels);
                free(v_Materials[i].TextureMap);
            }
        }
        free(v_Materials);
        v_Materials=NULL ;
        m_nbMaterial=0 ;
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
                         case 't':  fflush(stdin);
                                    sscanf(line,"vt %f %f",&tmpt.u,&tmpt.v);
                                    addTexCoord(tmpt);
                                    break ;

                        case 'n':   fflush(stdin);
                                    sscanf(line,"vn %f %f %f",&tmpv.x,&tmpv.y,&tmpv.z);
                                    addNormal(tmpv);
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
        case 'u': applyMaterial(line+7);break ;
        case 'm':
                    LoadMtlFile(line+7); break ;
        }
    }
    InitMinMaxVertices();
    fclose(objfile);
    return 1;
};
int ObjLoader::LoadMtlFile(char* filename){
    char *completename=NULL;
    CatStrings("Data//",filename,&completename);
    FILE* mtlfile=fopen(completename,"r");
    //free(completename);
    char line[150];
    if(!mtlfile){
        return 0 ;}
    while (!feof(mtlfile)){
        ReadLine(mtlfile,line);
        if(contains(line,"newmtl")){
            addMaterial(line+7);
        }else if(contains(line,"map_Kd")){
            if(v_Materials){
                v_Materials[m_nbMaterial-1].TextureMap=(Image*)malloc(sizeof(Image));
                if(v_Materials[m_nbMaterial-1].TextureMap){
                    v_Materials[m_nbMaterial-1].TextureMap->Pixels=NULL;
                    CatStrings("Data//",line+7,&completename);
                   lodepng_decode32_file(&(v_Materials[m_nbMaterial-1].TextureMap->Pixels),
                                          &(v_Materials[m_nbMaterial-1].TextureMap->Width),
                                          &(v_Materials[m_nbMaterial-1].TextureMap->Height),
                                          completename)!=0;

                }
            }
        }else if(contains(line,"Kd")){
              sscanf(line,"Kd %f %f %f",&(v_Materials[m_nbMaterial-1].DiffuseColor.r),
                                        &(v_Materials[m_nbMaterial-1].DiffuseColor.g),
                                        &(v_Materials[m_nbMaterial-1].DiffuseColor.b));
        }
    }
    fclose(mtlfile);
    return 1 ;

};
int ObjLoader::addMaterial(char* Name){
        Material* tmp=(Material*)malloc((m_nbMaterial+1)*sizeof(Material));
        if(!tmp)
            return 0 ;
        for(int j=0 ;j<m_nbMaterial;j++)
            tmp[j]=v_Materials[j];
        if(v_Materials)
            free(v_Materials);
        v_Materials=tmp;
        v_Materials[m_nbMaterial].mtlName=(char*)malloc((strlen(Name)+1)*sizeof(char));

        for(unsigned int i=0;Name[i];i++){
            v_Materials[m_nbMaterial].mtlName[i]=Name[i];
        }
        v_Materials[m_nbMaterial].mtlName[strlen(Name)]='\0';
        v_Materials[m_nbMaterial].TextureMap=NULL;
        m_nbMaterial++ ;
        return 1 ;
};
void ObjLoader::applyMaterial(char* mtlName){
    for(int i=0 ; i<m_nbMaterial;i++){
        if(strcmp(v_Materials[i].mtlName,mtlName)==0){
            v_Meshes[m_nbMeshes-1].material=&(v_Materials[i]);
        }
    }
};
int ObjLoader::AddMesh(char* name){
    Mesh* tmp = (Mesh*)malloc((m_nbMeshes+1)*sizeof(Mesh));
    if (tmp==NULL)
        return 0 ;
    for(unsigned int i =0 ; i<m_nbMeshes; i++)
        tmp[i]=v_Meshes[i];
    free(v_Meshes);
   v_Meshes=tmp ;
    // copy name and init others attributs
    v_Meshes[m_nbMeshes].Name=NULL ;
    if(name!=NULL){
        v_Meshes[m_nbMeshes].Name=(char*)malloc((strlen(name)+1)*sizeof(char));
        for(unsigned int i=0;name[i];i++)
            v_Meshes[m_nbMeshes].Name[i]=name[i];
        v_Meshes[m_nbMeshes].Name[strlen(name)]='\0';
    }
   v_Meshes[m_nbMeshes].Faces=0;
   v_Meshes[m_nbMeshes].nbTexCoords=0;
   v_Meshes[m_nbMeshes].nbNormals=0;
   v_Meshes[m_nbMeshes].nbVertices=0;
   v_Meshes[m_nbMeshes].IndexBuffer=NULL ;
   v_Meshes[m_nbMeshes].material=NULL;
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
        if(!(Dest->v_Meshes))
            return 0 ;
        for(unsigned int i=0;i<m_nbMeshes;i++){
            Dest->v_Meshes[i].MinVertex=v_Meshes[i].MinVertex ;
            Dest->v_Meshes[i].MaxVertex=v_Meshes[i].MaxVertex ;
            Dest->v_Meshes[i].Name=NULL ;
            Dest->v_Meshes[i].Faces=0;
            Dest->v_Meshes[i].nbTexCoords=0;
            Dest->v_Meshes[i].nbNormals=0;
            Dest->v_Meshes[i].nbVertices=0;
            Dest->v_Meshes[i].IndexBuffer=NULL ;
            Dest->v_Meshes[i].material=NULL;
            Dest->v_Meshes[i].NormalsBuffer=NULL;
            Dest->v_Meshes[i].TexCoords=NULL;
            Dest->v_Meshes[i].VertexBuffer=NULL;
            //copying vertex buffer
            if(v_Meshes[i].VertexBuffer){
                Dest->v_Meshes[i].nbVertices=v_Meshes[i].nbVertices ;
                Dest->v_Meshes[i].VertexBuffer=(Vertex3d*)malloc(v_Meshes[i].nbVertices*sizeof(Vertex3d));
                for(unsigned int j=0 ; j<v_Meshes[i].nbVertices;j++)
                    Dest->v_Meshes[i].VertexBuffer[j]=v_Meshes[i].VertexBuffer[j];
            }
            //copying normals buffer
            if(v_Meshes[i].NormalsBuffer){
                Dest->v_Meshes[i].nbNormals=v_Meshes[i].nbNormals ;
                Dest->v_Meshes[i].NormalsBuffer=(Vertex3d*)malloc(v_Meshes[i].nbNormals*sizeof(Vertex3d));
                for(unsigned int j=0 ; j<v_Meshes[i].nbNormals;j++)
                    Dest->v_Meshes[i].NormalsBuffer[j]=v_Meshes[i].NormalsBuffer[j];
            }
            //copying tecture coords buffer
            if(v_Meshes[i].TexCoords){
                Dest->v_Meshes[i].nbTexCoords=v_Meshes[i].nbTexCoords ;
                Dest->v_Meshes[i].TexCoords=(Vertex2d*)malloc(v_Meshes[i].nbTexCoords*sizeof(Vertex2d));
                for(unsigned int j=0 ; j<v_Meshes[i].nbTexCoords;j++)
                    Dest->v_Meshes[i].TexCoords[j]=v_Meshes[i].TexCoords[j];
            }
            //copying face values
            if(v_Meshes[i].IndexBuffer){
                Dest->v_Meshes[i].Faces=v_Meshes[i].Faces ;
                Dest->v_Meshes[i].IndexBuffer=(Index*)malloc(v_Meshes[i].Faces*3*sizeof(Index));
                for(unsigned int j=0 ; j<v_Meshes[i].Faces*3;j++)
                    Dest->v_Meshes[i].IndexBuffer[j]=v_Meshes[i].IndexBuffer[j];
            }
            //copying material
            Dest->v_Meshes[i].material=NULL;
            if(v_Meshes[i].material){
                Dest->v_Meshes[i].material=(Material*)malloc(sizeof(Material));
                Dest->v_Meshes[i].material->DiffuseColor=v_Meshes[i].material->DiffuseColor;
                Dest->v_Meshes[i].material->mtlName=NULL;
                Dest->v_Meshes[i].material->TextureMap=NULL;
                if(v_Meshes[i].material->TextureMap){
                    Dest->v_Meshes[i].material->TextureMap=(Image*)malloc(sizeof(Image));
                    if(Dest->v_Meshes[i].material->TextureMap) {
                        Dest->v_Meshes[i].material->TextureMap->Height=v_Meshes[i].material->TextureMap->Height ;
                        Dest->v_Meshes[i].material->TextureMap->Width=v_Meshes[i].material->TextureMap->Width ;
                        Dest->v_Meshes[i].material->TextureMap->Pixels=(unsigned char*)malloc(v_Meshes[i].material->TextureMap->Height*
                                                                                          v_Meshes[i].material->TextureMap->Width*
                                                                                          4*sizeof(unsigned char));

                    for(unsigned int j=0 ;j<v_Meshes[i].material->TextureMap->Height;j++)
                    for(unsigned int k=0;k<v_Meshes[i].material->TextureMap->Width;k++){
                        Dest->v_Meshes[i].material->TextureMap->Pixels[(j*v_Meshes[i].material->TextureMap->Width+k)*4]=
                        v_Meshes[i].material->TextureMap->Pixels[(j*v_Meshes[i].material->TextureMap->Width+k)*4];
                        Dest->v_Meshes[i].material->TextureMap->Pixels[(j*v_Meshes[i].material->TextureMap->Width+k)*4+1]=
                        v_Meshes[i].material->TextureMap->Pixels[(j*v_Meshes[i].material->TextureMap->Width+k)*4+1];
                        Dest->v_Meshes[i].material->TextureMap->Pixels[(j*v_Meshes[i].material->TextureMap->Width+k)*4+2]=
                        v_Meshes[i].material->TextureMap->Pixels[(j*v_Meshes[i].material->TextureMap->Width+k)*4+2];
                        Dest->v_Meshes[i].material->TextureMap->Pixels[(j*v_Meshes[i].material->TextureMap->Width+k)*4+3]=
                        v_Meshes[i].material->TextureMap->Pixels[(j*v_Meshes[i].material->TextureMap->Width+k)*4+3];
                    }

                    }
                }
            }
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
int CatStrings(char* str1,char* str2,char** Dest){
    if(!str1 || !str2 || !Dest)
        return 0 ;
    *Dest=(char*)malloc((strlen(str1)+strlen(str2)+1)*sizeof(char));
    if(!*Dest)
        return 0 ;
    int i,len=strlen(str1);
    for( i= 0;str1[i];i++)
        (*Dest)[i]=str1[i];
    for(;str2[i-len];i++)
        (*Dest)[i]= str2[i-len];
    (*Dest)[i]='\0';
return 1 ;
};
