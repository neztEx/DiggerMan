#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
//#include "GameWorld.h"g
#include "StudentWorld.h"

class StudentWorld;  //forward declaration
//enum state;
//********************************************************************
//**************** BASEOBJECT CLASS (Base class) *********************
//********************************************************************

class BaseObject : public GraphObject
{
public:
   
	enum state { alive, dead };
	enum name {boulder, diggerman, barrelOil, squirt, goldNugget, sonarKit, waterPool, regProt, hardProt, none  };
	BaseObject(int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0)
		: GraphObject(imageID, startX, startY, dir, size, depth)
    {
		m_state = alive;
	}
	void setWorld(StudentWorld *gw);
	StudentWorld *getWorld();
	int HittingPlayer(int x, int y);
    virtual void doSomething();
	virtual bool AllowMove(int x, int y);
	virtual void Initialize();
	virtual void activateSonar();
	void setState(state d);
	state getState();
	void setName(name n);
	name getName();
	void setSpace(); //fill the x_space and y_space arrays
	bool ObjectInMap(int x, int y);// checks if the map is in the x,y coord provided
    //virtual void updateTickCounter();
	name HittingSomething(int x, int y); //Send coord x,y and check if there is another object in the oilfield

	int IndexOfObject(int x, int y);
	

private:
	StudentWorld *m_sw;
	state m_state;
	name m_name;
	int x_space[4]; //array to store the x_coordenates that the object is occupying
	int y_space[4]; //array to store the y_coordenates that the object is occupying
    

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
		setName(diggerman);
    }
    
    void doSomething();
    bool AllowMove(int x, int y, Direction dir);
	void Initialize(StudentWorld *m_gw);
	void addSquirtGun();
	void decraseSquirtGun();
	int getSquirtNum(); 
	void addSonarKit();
	void decreaseSonarKit();

	int getSonarKit();

	void discoverObjects(); //for sonarkit
	
private:
	int squirt_num;
	int sonarkit_num;
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
		setName(squirt);
		//travel = 4;

		//if (AllowMove(getX(), getY())) //check if when Diggerman throws a squirt, its within
		//	travel = 4;					// the limits of the oilfield. If its not then the travel
		//else                           // is set to 0. 
		//	travel = 0;
        
    }
    
    void doSomething();
	bool AllowMove(int x, int y);
    int getTravel();
    void reduceTravel();
    void stopTravel();
	void initialize(StudentWorld *m_gw);
   
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
		setName(boulder);
		setSpace();
    }
    void doSomething();
    
private:
    bool stableState = true;
    bool waitingState = false;
    bool fallingState = false;
    int tickCounter = 0;
    
};

//****************************
//**** GOODIE CLASS  ******************
//****************************

class Goodie : public BaseObject
{
public:
	Goodie(int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0)
		: BaseObject(imageID, startX, startY, dir, size, depth)
	{
		setVisible(true);
		//setName(waterPool);
	}

	void doSomething();
	//int HittingPlayer(int x, int y);
	void addCounter();
	int getTickCounter();
	void setmaxT(int max);
	int getmaxT();
	void resetCounter();

private:
	int tickCounter = 0;
	int T=0; //max ticks that object can be visible
};


//****************************
//**** HIDDEN GOODIE CLASS  ******************
//****************************

class HiddenGoodie : public Goodie
{
public:
	HiddenGoodie(int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0)
		: Goodie(imageID, startX, startY, dir, size, depth)
	{
		setVisible(false);
		//setName(waterPool);
	}
	void activateSonar();
};



//****************************
//**** WATER_POOL CLASS  ******************
//****************************

class WaterPool : public Goodie
{
public:
	WaterPool(int x, int y)
		: Goodie(IMID_WATER_POOL, x, y, right, 1.0, 2)
	{
		setVisible(true);
		setName(waterPool);
		setSpace();
	}

	void doSomething();
	void initialize(StudentWorld *m_gw);

};



//****************************
//**** SonarKit  ******************
//****************************

class SonarKit : public Goodie
{
public:
	SonarKit(int x, int y)
		: Goodie(IMID_SONAR, x, y, right, 1.0, 2)
	{
		setVisible(true);
		setName(sonarKit);
		setSpace();
	}

	void doSomething();
	void initialize(StudentWorld *m_gw);

};



//****************************
//**** BARREL CLASS  ******************
//****************************

class Barrel : public HiddenGoodie
{
public:
	Barrel(int x, int y)
		: HiddenGoodie(IMID_BARREL, x, y, right, 1.0, 2)
	{
		setName(barrelOil);
		setSpace();
	}

	void doSomething();
	void initialize(StudentWorld *m_gw);

};



//****************************
//**** GOLD NUGGET CLASS  ******************
//****************************

class GoldNugget : public HiddenGoodie
{
public:
	GoldNugget(int x, int y)
		: HiddenGoodie(IMID_GOLD, x, y, right, 1.0, 2)
	{
		setName(goldNugget);
		setSpace();
	}

	void doSomething();
	void initialize(StudentWorld *m_gw);

};


// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
