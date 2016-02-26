#ifndef PFE_UFO_H_
#define PFE_UFO_H_
class UFO :public Enemy {
public :
    UFO();
    UFO(Vertex3d Pos);
    UFO(Vertex3d Pos, Vertex3d Dir, Vertex3d Up);
    int LoadFromFile();
    void Update(float dt);
};
#endif // PFE_UFO_H_
