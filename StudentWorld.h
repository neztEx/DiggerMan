#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <vector>
const int DIRT_HEIGHT = 60;


using namespace std;
class BaseObject; //forward declaration
class Dirt; //foward declaration
class DiggerMan;


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir):GameWorld(assetDir){
    }
    
    virtual int init();
    
    virtual int move();
    
    virtual void cleanUp();
    
    //CUSTOM FUNCTIONS
    void insertObject(BaseObject *o);
    int getSizeVector();
    BaseObject* getObject(int i);
    void createDirt();
    bool dirtAlive(int x, int y);
    bool digging(DiggerMan *z);
    void createGameObjects();
	void fillObjectCoord(DiggerMan *z);
	void UpdateVector();

private:
    vector<BaseObject*> gameObjects;
    Dirt *gameMap[VIEW_WIDTH][DIRT_HEIGHT];
	int *ObjectCoord[VIEW_WIDTH][VIEW_HEIGHT]; //2d ARRAy that keeps track of the position of all the objects in the map
};

#endif // STUDENTWORLD_H_
