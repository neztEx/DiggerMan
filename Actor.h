#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
//#include "GameWorld.h"g
#include "StudentWorld.h"

//testing

class StudentWorld;  //forward declaration



class BaseObject : public GraphObject
{
public:
    BaseObject(int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0)
    : GraphObject(imageID, startX, startY, dir, size, depth)
    {}
    virtual void doSomething();
};



//****************************
//**** DIRT CLASS  *******************
//****************************

class Dirt: public GraphObject
{
public:
    Dirt(int x, int y)
    : GraphObject(IMID_DIRT, x, y, right, .25, 3)
    {
        setVisible(true);
        
    }
    
    
    
    /*Direction dir = right, double size = 1.0, unsigned int depth = 0)
     : m_imageID(imageID), m_visible(false), m_x(startX), m_y(startY),
     m_destX(startX), m_destY(startY), m_brightness(1.0),
     m_animationNumber(0), m_direction(dir), m_size(size), m_depth(depth)
     */
    
    
    
};


//****************************
//**** DIGGERMAN CLASS  ******************
//****************************

class DiggerMan : public GraphObject
{
public:
    DiggerMan()
    : GraphObject(IMID_PLAYER, 30, 60, right, 1.0, 0)
    {
        setVisible(true);
        
        
    }
    
    void doSomething();
    void setWorld(StudentWorld *gw);
    StudentWorld *getWorld();
    bool AllowMove(int x, int y);
    
    /*Direction dir = right, double size = 1.0, unsigned int depth = 0)
     : m_imageID(imageID), m_visible(false), m_x(startX), m_y(startY),
     m_destX(startX), m_destY(startY), m_brightness(1.0),
     m_animationNumber(0), m_direction(dir), m_size(size), m_depth(depth)
     */
    
private:
    StudentWorld *m_sw;
    
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
        travel = 4;
        
    }
    
    void doSomething();
    int getTravel();
    void reduceTravel();
    void stopTravel();
    
    /*void setWorld(GameWorld*gw);
     GameWorld *getWorld();
     bool AllowMove(int x, int y);*/
    
    /*Direction dir = right, double size = 1.0, unsigned int depth = 0)
     : m_imageID(imageID), m_visible(false), m_x(startX), m_y(startY),
     m_destX(startX), m_destY(startY), m_brightness(1.0),
     m_animationNumber(0), m_direction(dir), m_size(size), m_depth(depth)
     */
    
private:
    GameWorld *m_sw;
    int travel; //distance to travel
    
};


//****************************
//**** BOULDER CLASS  ******************
//****************************


class Boulder : public GraphObject {
    
public:
    Boulder(int x, int y) : GraphObject(IMID_BOULDER, x, y, down, 1.0, 1) {
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
