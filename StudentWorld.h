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
    void addNewObjects();
	void UpdateVector();
	DiggerMan* getPlayer();
	void setPlayer( DiggerMan *z);
    void setlevel();
	void setTotalBarrels(int B);
	int GetTotalBarrels();
	void DecreaseBarrels();
	void ResetBarrels();
	void SetDisplayText();
    bool ecludianDistance(int x, int y);
    void setTickCounter();
    int getTickCounter();
    void resetTickCounter();
  


    

private:
    Dirt *gameMap[VIEW_WIDTH][DIRT_HEIGHT];
    vector<BaseObject*> gameObjects;
	int MaxBarrels; //max barrels per level
	DiggerMan *m_player;
    int current_level_number = 0;
    int tickCounter;
	
};

#endif // STUDENTWORLD_H_
