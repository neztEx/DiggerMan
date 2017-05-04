#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <vector>

using namespace std;
class BaseObject; //forward declaration

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir)
    : GameWorld(assetDir)
    {
    }
    
    virtual int init();
    
    virtual int move();
    
    virtual void cleanUp();
    
    void insertObject(BaseObject *o);
    int getSizeVector();
    BaseObject* getObject(int i);
    
private:
    vector<BaseObject*> gameObjects;
    
};

#endif // STUDENTWORLD_H_
