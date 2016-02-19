#ifndef PFE_CUBE_H_
#define PFE_CUBE_H_
class CUBE :public Boss {
public :
    CUBE();
    ~CUBE();
    int LoadFormFile();
    int AddBehaviour(Behaviour Behav);
    //the new behaviour should be implemented in theis class as a method
private:

};
#endif // PFE_CUBE_H_
