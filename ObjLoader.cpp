#include "ObjLoader.h"
ObjLoader::ObjLoader():v_Meshes(NULL),
                        m_nbMeshes(0),
                        m_Scale(1.0f),
                        m_Color({0.0f,1.0f,0.0f}) {
};
ObjLoader::~ObjLoader(){
//    this->Release() ;
};
void ObjLoader::Release(){
    if(v_Meshes){
        for(unsigned int i = 0 ; i<m_nbMeshes ; i++){
            free(v_Meshes[i].Name);
            if(v_Meshes[i].VertexBuffer){
                free(v_Meshes[i].VertexBuffer);
                v_Meshes[i].VertexBuffer=NULL;}
            if(v_Meshes[i].IndexBuffer){
                free(v_Meshes[i].IndexBuffer);
                v_Meshes[i].IndexBuffer=NULL;}
            if(v_Meshes[i].NormalsBuffer){
                free(v_Meshes[i].NormalsBuffer);
                v_Meshes[i].NormalsBuffer=NULL ;}
            if(v_Meshes[i].material){
                if(v_Meshes[i].material->TextureMap){
                    free(v_Meshes[i].material->TextureMap);
                    v_Meshes[i].material->TextureMap=NULL;}
                if(v_Meshes[i].material->MaterialMap){
                    free(v_Meshes[i].material->MaterialMap);
                    v_Meshes[i].material->MaterialMap=NULL;}
                if(v_Meshes[i].material->ReflexionMap){
                    free(v_Meshes[i].material->ReflexionMap);
                    v_Meshes[i].material->ReflexionMap=NULL ;}
                if(v_Meshes[i].material->BumpMap){
                    free(v_Meshes[i].material->BumpMap);
                    v_Meshes[i].material->BumpMap=NULL;}
                free(v_Meshes[i].material);
                v_Meshes[i].material=NULL ;
            }
        }
        free(v_Meshes);
    }
};

int ObjLoader::loadObjfile(char* objfilename){
//open file file
Vertex3d tmp ;
unsigned int id1,id2,id3 ;
FILE* objfile=fopen(objfilename,"r");
//allocation of templates
char* line =(char*)malloc(100*sizeof(char));
//start reading lines
while(!feof(objfile)){
    //fscanf(objfile,"%s\n",line);
    ReadLine(objfile,line);
    switch(line[0]){
    case 'v':switch(line[1]){
                case ' ':sscanf(line,"v %f %f %f\n",&tmp.x,&tmp.y,&tmp.z);addVertex(tmp);  break ;
                case 'n':  break;
                case 't':  break ;
                }break ;
    case 'f':   extractFace(line,&id1,&id2,&id3);
                addIndices(id1,id2,id3);
                //sscanf(line+2,"%d////%d %d////%d %d////%d\n",&id1,NULL,&id2,NULL,&id3,NULL);
                break ;
    case 'o':
                AddMesh(line+2); break;
    }
}
free(line);
fclose(objfile);
return 1 ;
};
int ObjLoader::loadMaterial(char* mtlfilename){

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
    v_Meshes[m_nbMeshes].material=NULL ;
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
int ObjLoader::addIndices(unsigned int id1,unsigned int id2,unsigned int id3){
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
void ObjLoader::extractFace(char* line,unsigned int * id1,unsigned int *id2,unsigned int *id3){
    char* part1=(char*)malloc(20*sizeof(char));
    unsigned int i,j ;
    for(i=0;line[i]!='\0' && line[i]!=' ' ;i++)
        part1[i]=line[i];
    part1[i]='\0';
    for(j=0;part1[j]!=' ' && part1[j]!='//' &&part1[j]!='\0' ;j++);
    part1[j]='\0';
    *id1=atoi(part1);
    i++;
    for(j=0;line[i]!='\0' && line[i]!=' ' ;j++,i++)
        part1[j]=line[i];
    part1[j]='\0';
    for(j=0;part1[j]!=' ' && part1[j]!='//' &&part1[j]!='\0' ;j++);
    part1[j]='\0';
    *id2=atoi(part1);
    i++;
    for(j=0;line[i]!='\0' && line[i]!=' ' ;j++,i++)
        part1[j]=line[i];
    part1[j]='\0';
    for(j=0;part1[j]!=' ' && part1[j]!='//' &&part1[j]!='\0' ;j++);
    part1[j]='\0';
    *id3=atoi(part1);
    free(part1);

};
void ObjLoader::ReadLine(FILE* file ,char* buffer){
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
int ObjLoader::LoadFile(StaticModel* dest,char* filename){
    ObjLoader* Loader=new ObjLoader() ;
    Loader->loadObjfile(filename);
    Loader->CopyBuffer(dest);
    Loader->Release();
    delete Loader ;
    return 1 ;
};
int ObjLoader::CopyBuffer(StaticModel* Dest){
unsigned int j ;
    Dest->setColor(m_Color) ;
    Dest->m_nbMeshes=m_nbMeshes ;
    if(!Dest->m_nbMeshes)
        return 0 ;
    Dest->v_Meshes=(pMesh)malloc(Dest->m_nbMeshes*sizeof(Mesh));
    if(!Dest->v_Meshes)
        return 0 ;
    for(unsigned int i=0;i<m_nbMeshes;i++){
        Dest->v_Meshes[i].MinVertex=v_Meshes[i].MinVertex;
        Dest->v_Meshes[i].MaxVertex=v_Meshes[i].MaxVertex;
        //copying Name
        Dest->v_Meshes[i].Name=(char*)malloc(100*sizeof(char));
        for(j=0;v_Meshes[i].Name[j];j++)
            Dest->v_Meshes[i].Name[i]=v_Meshes[i].Name[j];
        Dest->v_Meshes[i].Name[j]='\0';
        //copying vertices
        Dest->v_Meshes[i].nbVertices=v_Meshes[i].nbVertices ;
        Dest->v_Meshes[i].VertexBuffer=(Vertex3d*)malloc(Dest->v_Meshes[i].nbVertices*sizeof(Vertex3d));
        for(j=0;j<Dest->v_Meshes[i].nbVertices;j++)
            Dest->v_Meshes[i].VertexBuffer[j]=v_Meshes[i].VertexBuffer[j];
        //copying Normals
        Dest->v_Meshes[i].nbNormals=v_Meshes[i].nbNormals ;
        Dest->v_Meshes[i].NormalsBuffer=(Vertex3d*)malloc(Dest->v_Meshes[i].nbNormals*sizeof(Vertex3d));
        for(j=0;j<Dest->v_Meshes[i].nbNormals;j++)
            Dest->v_Meshes[i].NormalsBuffer[j]=v_Meshes[i].NormalsBuffer[j];
        //copying Indices
        Dest->v_Meshes[i].Faces=v_Meshes[i].Faces ;
        Dest->v_Meshes[i].IndexBuffer=(unsigned int*)malloc(Dest->v_Meshes[i].Faces*3*sizeof(unsigned int));
        for(j=0;j<Dest->v_Meshes[i].Faces*3;j++)
            Dest->v_Meshes[i].IndexBuffer[j]=v_Meshes[i].IndexBuffer[j];
        //copying Texture coordinates
        Dest->v_Meshes[i].nbTexCoords=v_Meshes[i].nbTexCoords ;
        Dest->v_Meshes[i].TexCoords=(Vertex2d*)malloc(Dest->v_Meshes[i].nbTexCoords*sizeof(Vertex2d));
        for(j=0;j<Dest->v_Meshes[i].nbTexCoords;j++)
            Dest->v_Meshes[i].TexCoords[j]=v_Meshes[i].TexCoords[j];
        v_Meshes[i].material=NULL;

    }
    return 1 ;
};
