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
	double RadiusFromPlayer();
    virtual void doSomething();
	virtual bool AllowMove(int x, int y);
	virtual void Initialize();
	virtual void activateSonar();
	virtual void GetAnnoyed(int x);
	void setState(state d);
	state getState();
	void setName(name n);
	name getName();
	void setSpace(); //fill the x_space and y_space arrays
	bool ObjectInMap(int x, int y);// checks if the map is in the x,y coord provided
    //virtual void updateTickCounter();
	name HittingSomething(int x, int y); //Send coord x,y and check if there is another object in the oilfield

	BaseObject::name HittingSomething2(int x, int y);

	int IndexOfObjectWithinRadius(int x, int y);

	double Radious(int x1, int y1, int x2, int y2);

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
	bool AllocateSquirt();
    bool AllowMove(int x, int y, Direction dir);
	void Initialize(StudentWorld *m_gw);
	void addSquirtGun();
	void decraseSquirtGun();
	int getSquirtNum(); 
	void addSonarKit();
	void decreaseSonarKit();
	int getSonarKit();
	int getGoldNum();
	void AddGoldNum();
	void decreaseGoldNum();
	void discoverObjects(); //for sonarkit
	void decreaseHealth(int x);
	void increaseHealth();
	int getHealth();
	void ResetHealth();
	void GetAnnoyed(int x);
	
private:
	int squirt_num;
	int sonarkit_num;
	int health;
	int Gold_num;
};

 //beggining comment for protester
//*****************************************
//****  PROTESTER CLASS  ******************
//*****************************************

class Protester : public BaseObject
{
public:
enum Protesterstate { rest, leaveOil, moving};
Protester(int imageID, int startX, int startY, Direction dir = left, double size = 1.0, unsigned int depth = 0)
: BaseObject(imageID, startX, startY, dir, size, depth)
{
setVisible(true);
//setName(regProt);
setProtesterState(moving);
setSpace();
}

//void doSomething();
bool AllowMove(int x, int y, Direction dir);
//void Initialize(StudentWorld *m_gw);
void decreaseHealth(int x);
int getHealth();
void setHealth(int x);
void setProtesterState(Protesterstate x);
Protesterstate getProt_State();
int calculateSquarestoMove(); //returns a value between 8 and 60
void resetSquarestoMove();
int getSquaresToMove();
void setSquarestoMove();
void decreaseSquaresToMove();
Direction getNewDirection();
void resetCounterTicks();
void decreaseCounterTicks();
int getCounterTicks();
int getCounterNoRestTicks();
void decreaseCounterNoRest();
void resetCounterNoRest();
//void GetAnnoyed(int x);
Direction PlayerPosition(int x, int y);
bool FollowPlayer();
bool CheckIfPathIsEmpty(int x1, int y1, int x2, int y2);
int getPerpMovements();
void decreasePerpMovements();
void setPerpMovements();
void ActivatePerpMovement();
void setTicksToWait(int x);
void setCounterNoRestTicks(int x);
void setCounterTicksRest(int x);
void bfs(int x, int y);

private:
int health;
Protesterstate p_state;
int squareToMoveinDir;
int ticksToWait;
int counterTicksRest;
int counterNoRestTicks;
int perpendicularMovements;
};





 //end comment for protester



//****************************
//****	REGULAR PROTESTER CLASS  ******************
//****************************

class RegProtester : public Protester
{
public:
	enum Protesterstate { rest, leaveOil, moving};
	RegProtester()
		: Protester(IMID_PROTESTER, 60, 60, left, 1.0, 0)
	{
		setName(regProt);
	}

	void doSomething();
	void Initialize(StudentWorld *m_gw);
	void GetAnnoyed(int x);

};


//**************************************************
//****	HARDCORE PROTESTER CLASS  ******************
//**************************************************

class HardProtester : public Protester
{
public:
	enum Protesterstate { rest, leaveOil, moving };
	HardProtester()
		: Protester(IMID_HARD_CORE_PROTESTER, 60, 60, left, 1.0, 0)
	{
		setName(hardProt);
	}

	void doSomething();
	void Initialize(StudentWorld *m_gw);
	void GetAnnoyed(int x);
	void activateStare();
	void decreaseStaring();
	void setCountStaring(int x);

	int getCountStaring();

private:
	int countStaring;
	

};





//old regular protester
/*  


//****************************
//****	REGULAR PROTESTER CLASS  ******************
//****************************

class RegProtester : public BaseObject
{
public:
enum Protesterstate { rest, leaveOil, moving};
RegProtester()
: BaseObject(IMID_PROTESTER, 60, 60, left, 1.0, 0)
{
setVisible(true);
setName(regProt);
setProtesterState(moving);
setSpace();
}

void doSomething();
bool AllowMove(int x, int y, Direction dir);
void Initialize(StudentWorld *m_gw);
//void addSquirtGun();
//void decraseSquirtGun();
//int getSquirtNum();
//void addSonarKit();
//void decreaseSonarKit();
//int getSonarKit();
//int getGoldNum();
//void AddGoldNum();
//void decreaseGoldNum();
//void discoverObjects(); //for sonarkit
void decreaseHealth(int x);
//void increaseHealth();
int getHealth();
//void ResetHealth();
void setProtesterState(Protesterstate x);
Protesterstate getProt_State();
int calculateSquarestoMove(); //returns a value between 8 and 60
void resetSquarestoMove();
int getSquaresToMove();
void setSquarestoMove();
void decreaseSquaresToMove();
Direction getNewDirection();
void resetCounterTicks();
void decreaseCounterTicks();
int getCounterTicks();
int getCounterNoRestTicks();
void decreaseCounterNoRest();
void resetCounterNoRest();
void GetAnnoyed(int x);
Direction PlayerPosition(int x, int y);
bool FollowPlayer();
bool CheckIfPathIsEmpty(int x1, int y1, int x2, int y2);
int getPerpMovements();
void decreasePerpMovements();
void setPerpMovements();
void ActivatePerpMovement();

private:
int health;
Protesterstate p_state;
int squareToMoveinDir;
int ticksToWait;
int counterTicksRest;
int counterNoRestTicks;
int perpendicularMovements;
};


*/

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
		setPickable(true);
		//setName(waterPool);
	}
	void activateSonar();
	bool getPickable();
	void setPickable(bool x);
private:
	bool pickableforDig;
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
	int getCounterByProt();
	void decreaseCounterByProt();
	void setCounterByProt(int x);

private:
	int counterByProt;
};


// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
