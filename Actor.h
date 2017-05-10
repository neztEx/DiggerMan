#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
//#include "GameWorld.h"g
#include "StudentWorld.h"

class StudentWorld;  //forward declaration

//********************************************************************
//**************** BASEOBJECT CLASS (Base class) *********************
//********************************************************************

class BaseObject : public GraphObject
{
public:
    enum state{alive, dead};
    
    BaseObject(int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0)
    : GraphObject(imageID, startX, startY, dir, size, depth)
    {}
	void setWorld(StudentWorld *gw);
	StudentWorld *getWorld();
    virtual void doSomething();
	virtual bool AllowMove(int x, int y);
    //virtual void updateTickCounter();

private:
	StudentWorld *m_sw;
    //int tickCounter = 0;

};



//****************************
//**** DIRT CLASS  *******************
//****************************

class Dirt: public BaseObject
{
public:
    Dirt(int x, int y)
    : BaseObject(IMID_DIRT, x, y, right, .25, 3)
    {
        setVisible(true);
    }
};


//****************************
//**** DIGGERMAN CLASS  ******************
//****************************

class DiggerMan : public BaseObject
{
public:
    DiggerMan()
    : BaseObject(IMID_PLAYER, 30, 60, right, 1.0, 0)
    {
        setVisible(true);
    }
    
    void doSomething();
    bool AllowMove(int x, int y);
};



//****************************
//**** SQUIRT CLASS  ******************
//****************************

class Squirt : public BaseObject
{
public:
    Squirt(int x, int y, Direction dir)
    : BaseObject(IMID_WATER_SPURT, x, y, dir, 1.0, 1)
    {
        setVisible(false);
        

		if (AllowMove(getX(), getY())) //check if when Diggerman throws a squirt, its within
			travel = 4;					// the limits of the oilfield. If its not then the travel
		else                           // is set to 0. 
			travel = 0;
        
    }
    
    void doSomething();
	bool AllowMove(int x, int y);
    int getTravel();
    void reduceTravel();
    void stopTravel();
   
private:
    int travel; //distance to travel
    
};


//****************************
//**** BOULDER CLASS  ******************
//****************************


class Boulder : public BaseObject{
    
public:
    enum state{};
    
    Boulder(int x, int y)
    : BaseObject(IMID_BOULDER, x, y, down, 1.0, 1)
    {
        setVisible(true);
    }
    void doSomething();
    
private:
    bool stableState = true;
    bool waitingState = false;
    bool fallingState = false;
    int tickCounter = 0;
    
};

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
