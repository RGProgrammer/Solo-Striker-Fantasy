#include "Text.h"
Text::Text():Drawable(),m_Value(0),m_nbDigit(4),v_VertexBuffer(NULL),m_nbVertices(0),v_IndexBuffer(NULL),m_Faces(0),
                v_NormalsBuffer(NULL),m_nbNormals(0),v_TexCoords(NULL),m_nbTexCoords(0),m_Material(NULL),m_Scale(1.0f){
    GenerateMesh();
};
Text::~Text(){this->Destroy();};
void Text::Destroy(){
    if(v_VertexBuffer){
        free(v_VertexBuffer);
        v_VertexBuffer=NULL;
        m_nbVertices=0;
    }
    if(v_IndexBuffer){
        free(v_IndexBuffer);
        v_IndexBuffer=NULL;
        m_Faces=0;
    }
    if(v_NormalsBuffer){
        free(v_NormalsBuffer);
        v_NormalsBuffer=NULL;
        m_nbNormals=0;
    }
    if(v_TexCoords){
        free(v_TexCoords);
        v_TexCoords=NULL;
        m_nbTexCoords=0;
    }
    if(m_Material){
        if(m_Material->TextureMap){
            if(m_Material->TextureMap->Pixels)
                free(m_Material->TextureMap->Pixels);
            free(m_Material->TextureMap);}
        if(m_Material->TextureId){
            glDeleteTextures(1,&(m_Material->TextureId));
        }
        free(m_Material);
        m_Material=NULL;
    }
};
void Text::AddValue(unsigned int  Value){
    if(Value>=9999 || m_Value+Value>= 9999)
        m_Value=9999 ;
    else
        m_Value+=Value ;
    this->RegenTextureCoord();
};
void Text::setValue(unsigned int Value){
    if(Value<=9999)
        m_Value=Value ;
    else
        m_Value=9999 ;
    this->RegenTextureCoord();
};
unsigned int Text::getValue(){return m_Value;};
void Text::setScale(float value){
    m_Scale=value ;
};
/*void Text::setPosition(Vertex2d Pos){
    m_Pos.x=Pos.u;
    m_Pos.y=Pos.v;
    m_Pos.z=0.0f;
};
int Text::setOrientation(Vertex2d Dir){
    m_Dir.x=Dir.u;
    m_Dir.y=Dir.v;
    m_Dir.z=0.0f;
    m_Up=CrossProduct3d(m_Dir,{1.0,0.0f,0.0f});
    return 1 ;
};*/
void Text::Draw(float* ViewMtx){
bool verif=false ;
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
     glEnable(GL_TEXTURE_2D);
        if(m_Material && m_Material->TextureId){
                glBindTexture(GL_TEXTURE_2D,m_Material->TextureId);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                verif=true ;
        }else verif= false  ;
        if(v_IndexBuffer){
            glBegin(GL_TRIANGLES);
            if(!verif)
                glColor3f(1.0f,1.0f,1.0f);
            for(unsigned int j=0;j <m_Faces*3;j++){
                ////////////////////////////////////////////////////////////
                if(v_IndexBuffer[j].NormalIndex==0)
                    glNormal3f(0.0f,0.0f,0.0f);
                else
                    glNormal3f(v_NormalsBuffer[v_IndexBuffer[j].NormalIndex-1].x,
                               v_NormalsBuffer[v_IndexBuffer[j].NormalIndex-1].y,
                               v_NormalsBuffer[v_IndexBuffer[j].NormalIndex-1].z);
                //////////
                if(v_IndexBuffer[j].TexIndex!=0){
                    glTexCoord2f(v_TexCoords[v_IndexBuffer[j].TexIndex-1].u,
                                 v_TexCoords[v_IndexBuffer[j].TexIndex-1].v);
                }
                //////////
                glVertex3f(v_VertexBuffer[v_IndexBuffer[j].VertexIndex-1].x,
                           v_VertexBuffer[v_IndexBuffer[j].VertexIndex-1].y,
                           v_VertexBuffer[v_IndexBuffer[j].VertexIndex-1].z);

            }
            glEnd();
        }

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0f,1.0f,1.0f);
};
int  Text::RegenTextureCoord(){
    unsigned int Copy=m_Value;
    for(unsigned int i=0;i<m_nbDigit;i++){
        switch(Copy%10){
            case 0 : v_TexCoords[v_IndexBuffer[(3-i)*6].TexIndex-1].u=0.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6].TexIndex-1].v=0.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+1].TexIndex-1].u=0.2f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+1].TexIndex-1].v=0.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+2].TexIndex-1].u=0.2f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+2].TexIndex-1].v=0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+3].TexIndex-1].u=0.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+3].TexIndex-1].v=0.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+4].TexIndex-1].u=0.2f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+4].TexIndex-1].v=0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+5].TexIndex-1].u=0.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+5].TexIndex-1].v=0.5f ;
                     break;
            case 1 : v_TexCoords[v_IndexBuffer[(3-i)*6].TexIndex-1].u=0.2f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6].TexIndex-1].v=0.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+1].TexIndex-1].u=0.4f;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+1].TexIndex-1].v=0.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+2].TexIndex-1].u=0.4f;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+2].TexIndex-1].v=0.5f;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+3].TexIndex-1].u=0.2f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+3].TexIndex-1].v=0.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+4].TexIndex-1].u=0.4f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+4].TexIndex-1].v=0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+5].TexIndex-1].u=0.2f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+5].TexIndex-1].v=0.5f ;
                     break;
            case 2 : v_TexCoords[v_IndexBuffer[(3-i)*6].TexIndex-1].u= 0.4f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6].TexIndex-1].v= 0.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+1].TexIndex-1].u=0.6f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+1].TexIndex-1].v=0.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+2].TexIndex-1].u=0.6f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+2].TexIndex-1].v=0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+3].TexIndex-1].u=0.4f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+3].TexIndex-1].v=0.0f;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+4].TexIndex-1].u=0.6f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+4].TexIndex-1].v=0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+5].TexIndex-1].u=0.4f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+5].TexIndex-1].v=0.5f ;
                     break;
            case 3 : v_TexCoords[v_IndexBuffer[(3-i)*6].TexIndex-1].u= 0.6f;
                     v_TexCoords[v_IndexBuffer[(3-i)*6].TexIndex-1].v= 0.0f;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+1].TexIndex-1].u= 0.8f;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+1].TexIndex-1].v=0.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+2].TexIndex-1].u=0.8f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+2].TexIndex-1].v=0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+3].TexIndex-1].u=0.6f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+3].TexIndex-1].v=0.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+4].TexIndex-1].u=0.8f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+4].TexIndex-1].v=0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+5].TexIndex-1].u=0.6f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+5].TexIndex-1].v=0.5f ;
                     break;
            case 4 : v_TexCoords[v_IndexBuffer[(3-i)*6].TexIndex-1].u=0.8f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6].TexIndex-1].v= 0.0f;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+1].TexIndex-1].u=1.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+1].TexIndex-1].v=0.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+2].TexIndex-1].u=1.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+2].TexIndex-1].v=0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+3].TexIndex-1].u=0.8f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+3].TexIndex-1].v=0.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+4].TexIndex-1].u=1.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+4].TexIndex-1].v=0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+5].TexIndex-1].u=0.8f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+5].TexIndex-1].v=0.5f ;
                     break;
            case 5 : v_TexCoords[v_IndexBuffer[(3-i)*6].TexIndex-1].u=0.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6].TexIndex-1].v=0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+1].TexIndex-1].u=0.2f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+1].TexIndex-1].v=0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+2].TexIndex-1].u=0.2f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+2].TexIndex-1].v=1.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+3].TexIndex-1].u=0.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+3].TexIndex-1].v=0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+4].TexIndex-1].u=0.2f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+4].TexIndex-1].v=1.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+5].TexIndex-1].u=0.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+5].TexIndex-1].v=1.0f ;
                     break;
            case 6 : v_TexCoords[v_IndexBuffer[(3-i)*6].TexIndex-1].u=0.2f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6].TexIndex-1].v=0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+1].TexIndex-1].u=0.4f;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+1].TexIndex-1].v=0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+2].TexIndex-1].u=0.4f;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+2].TexIndex-1].v=1.0f;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+3].TexIndex-1].u=0.2f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+3].TexIndex-1].v=0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+4].TexIndex-1].u=0.4f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+4].TexIndex-1].v=1.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+5].TexIndex-1].u=0.2f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+5].TexIndex-1].v=1.0f ;
                     break;
            case 7 : v_TexCoords[v_IndexBuffer[(3-i)*6].TexIndex-1].u= 0.4f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6].TexIndex-1].v= 0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+1].TexIndex-1].u=0.6f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+1].TexIndex-1].v=0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+2].TexIndex-1].u=0.6f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+2].TexIndex-1].v=1.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+3].TexIndex-1].u=0.4f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+3].TexIndex-1].v=0.5f;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+4].TexIndex-1].u=0.6f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+4].TexIndex-1].v=1.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+5].TexIndex-1].u=0.4f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+5].TexIndex-1].v=1.0f ;
                     break;
            case 8 : v_TexCoords[v_IndexBuffer[(3-i)*6].TexIndex-1].u= 0.6f;
                     v_TexCoords[v_IndexBuffer[(3-i)*6].TexIndex-1].v= 0.5f;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+1].TexIndex-1].u= 0.8f;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+1].TexIndex-1].v=0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+2].TexIndex-1].u=0.8f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+2].TexIndex-1].v=1.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+3].TexIndex-1].u=0.6f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+3].TexIndex-1].v=0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+4].TexIndex-1].u=0.8f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+4].TexIndex-1].v=1.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+5].TexIndex-1].u=0.6f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+5].TexIndex-1].v=1.0f ;
                     break;
            case 9 : v_TexCoords[v_IndexBuffer[(3-i)*6].TexIndex-1].u=0.8f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6].TexIndex-1].v= 0.5f;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+1].TexIndex-1].u=1.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+1].TexIndex-1].v=0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+2].TexIndex-1].u=1.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+2].TexIndex-1].v=1.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+3].TexIndex-1].u=0.8f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+3].TexIndex-1].v=0.5f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+4].TexIndex-1].u=1.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+4].TexIndex-1].v=1.0f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+5].TexIndex-1].u=0.8f ;
                     v_TexCoords[v_IndexBuffer[(3-i)*6+5].TexIndex-1].v=1.0f ;
                     break;
        }
        Copy/=10;
    }
};
int Text::GenerateMesh(){
    v_VertexBuffer=(Vertex3d*)malloc(16*sizeof(Vertex3d)) ;
    m_nbVertices=16 ;
    v_IndexBuffer=(Index*)malloc(24 *sizeof(Index))  ;
    m_Faces=8 ;
    v_NormalsBuffer=(Vertex3d*)malloc( sizeof(Vertex3d))  ;
    m_nbNormals=1;
    v_TexCoords=(Vertex2d*)malloc(16*sizeof(Vertex2d)) ;
    m_nbTexCoords=16 ;
    m_Material=(Material*)malloc(sizeof(Material));
    ///////////////////////
    m_Material->DiffuseColor={0.0f,0.0f,0.0f};
    m_Material->mtlName=NULL ;
    m_Material->TextureId=0 ;
    m_Material->TextureMap=(Image*)malloc(sizeof(Image));
    if(lodepng_decode32_file(&(m_Material->TextureMap->Pixels),
                          &(m_Material->TextureMap->Width),
                          &(m_Material->TextureMap->Height),
                          "Data//numbers.png")!=0)
        printf("Error Loading image file\n");
    ///////////////////////
    glGenTextures(1, &(m_Material->TextureId)); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, m_Material->TextureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGBA,                       //Format OpenGL uses for image
				 m_Material->TextureMap->Width, m_Material->TextureMap->Height,  //Width and height
				 0,                            //The border of the image
				 GL_RGBA, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 m_Material->TextureMap->Pixels);               //The actual pixel data

    ///////////////////////
    v_NormalsBuffer[0]={0.0f,0.0f,1.0f} ;
    ///////////////////////
    v_VertexBuffer[0]= {0.0f,3.0f,0.0f};v_VertexBuffer[1]= {1.8f,3.0f,0.0f} ;v_VertexBuffer[2]={1.8f,-3.0f,0.0f} ;v_VertexBuffer[3]= {0.0f,-3.0f,0.0f} ;
    v_VertexBuffer[4]= {1.8f,3.0f,0.0f};v_VertexBuffer[5]= {3.1f,3.0f,0.0f};v_VertexBuffer[6]={3.1f,-3.0f,0.0f};v_VertexBuffer[7]= {1.6f,-3.0f,0.0f} ;
    v_VertexBuffer[8]= {3.2f,3.0f,0.0f};v_VertexBuffer[9]= {4.7f,3.0f,0.0f};v_VertexBuffer[10]={4.7f,-3.0f,0.0f};v_VertexBuffer[11]={3.2f,-3.0f,0.0f};
    v_VertexBuffer[12]={4.9f,3.0f,0.0f};v_VertexBuffer[13]={6.4f,3.0f,0.0f};v_VertexBuffer[14]={6.4f,-3.0f,0.0f};v_VertexBuffer[15]={4.9f,-3.0f,0.0f};
    ///////////////////////
    v_IndexBuffer[0].NormalIndex=1;v_IndexBuffer[0].VertexIndex=1;v_IndexBuffer[0].TexIndex=1;
    v_IndexBuffer[1].NormalIndex=1;v_IndexBuffer[1].VertexIndex=2;v_IndexBuffer[1].TexIndex=2;
    v_IndexBuffer[2].NormalIndex=1;v_IndexBuffer[2].VertexIndex=3;v_IndexBuffer[2].TexIndex=3;

    v_IndexBuffer[3].NormalIndex=1;v_IndexBuffer[3].VertexIndex=1;v_IndexBuffer[3].TexIndex=1;
    v_IndexBuffer[4].NormalIndex=1;v_IndexBuffer[4].VertexIndex=3;v_IndexBuffer[4].TexIndex=3;
    v_IndexBuffer[5].NormalIndex=1;v_IndexBuffer[5].VertexIndex=4;v_IndexBuffer[5].TexIndex=4;

    v_IndexBuffer[6].NormalIndex=1;v_IndexBuffer[6].VertexIndex=5;v_IndexBuffer[6].TexIndex=5;
    v_IndexBuffer[7].NormalIndex=1;v_IndexBuffer[7].VertexIndex=6;v_IndexBuffer[7].TexIndex=6;
    v_IndexBuffer[8].NormalIndex=1;v_IndexBuffer[8].VertexIndex=7;v_IndexBuffer[8].TexIndex=7;

    v_IndexBuffer[9].NormalIndex=1;v_IndexBuffer[9].VertexIndex=5;v_IndexBuffer[9].TexIndex=5;
    v_IndexBuffer[10].NormalIndex=1;v_IndexBuffer[10].VertexIndex=7;v_IndexBuffer[10].TexIndex=7;
    v_IndexBuffer[11].NormalIndex=1;v_IndexBuffer[11].VertexIndex=8;v_IndexBuffer[11].TexIndex=8;

    v_IndexBuffer[12].NormalIndex=1;v_IndexBuffer[12].VertexIndex=9;v_IndexBuffer[12].TexIndex=9;
    v_IndexBuffer[13].NormalIndex=1;v_IndexBuffer[13].VertexIndex=10;v_IndexBuffer[13].TexIndex=10;
    v_IndexBuffer[14].NormalIndex=1;v_IndexBuffer[14].VertexIndex=11;v_IndexBuffer[14].TexIndex=11;

    v_IndexBuffer[15].NormalIndex=1;v_IndexBuffer[15].VertexIndex=9;v_IndexBuffer[15].TexIndex=9;
    v_IndexBuffer[16].NormalIndex=1;v_IndexBuffer[16].VertexIndex=11;v_IndexBuffer[16].TexIndex=11;
    v_IndexBuffer[17].NormalIndex=1;v_IndexBuffer[17].VertexIndex=12;v_IndexBuffer[17].TexIndex=12;

    v_IndexBuffer[18].NormalIndex=1;v_IndexBuffer[18].VertexIndex=13;v_IndexBuffer[18].TexIndex=13;
    v_IndexBuffer[19].NormalIndex=1;v_IndexBuffer[19].VertexIndex=14;v_IndexBuffer[19].TexIndex=14;
    v_IndexBuffer[20].NormalIndex=1;v_IndexBuffer[20].VertexIndex=15;v_IndexBuffer[20].TexIndex=15;

    v_IndexBuffer[21].NormalIndex=1;v_IndexBuffer[21].VertexIndex=13;v_IndexBuffer[21].TexIndex=13;
    v_IndexBuffer[22].NormalIndex=1;v_IndexBuffer[22].VertexIndex=15;v_IndexBuffer[22].TexIndex=15;
    v_IndexBuffer[23].NormalIndex=1;v_IndexBuffer[23].VertexIndex=16;v_IndexBuffer[23].TexIndex=16;
    ///////////////////////
    this->RegenTextureCoord();
    return 1;
};
void Text::UpdateMtx(){
    Drawable::UpdateMtx();
    m_TransMtx[0]*=m_Scale;
    m_TransMtx[5]*=m_Scale;
    m_TransMtx[10]*=m_Scale;
};
