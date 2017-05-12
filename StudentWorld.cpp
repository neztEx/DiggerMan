#include "StudentWorld.h"
#include <string>
#include <random>
#include "Actor.h"
#include <algorithm>

using namespace std;
//const int DIRT_HEIGHT = 60;

//-------CUSTOM FUNCTIONS---------
//void createDirt(); //fills screen with dirt
//bool digging(DiggerMan *z);
//void createGameObjects();
//--------------------------------

//Dirt *gameMap = new gameMap;
DiggerMan *player = new DiggerMan();
//Boulder *bl = new Boulder(20,50);
//Dirt *gameMap[VIEW_WIDTH][DIRT_HEIGHT];
GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp


int StudentWorld::init()
{
    //DIRT - creating the data structure for the dirt object w/ mineshaft
    createDirt();
    player->setWorld(this);
    createGameObjects();
   // bl->setWorld(this);
    //Boulder *bl = new Boulder(20,20);
    //insertObject(bl);
    
    return GWSTATUS_CONTINUE_GAME;
}
int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    decLives();
    player->doSomething();
    if (digging(player))
    {
        playSound(SOUND_DIG);
    }
    for (int i = 0; i < getSizeVector(); i++)
    {
        //cout << "vector doSomething" << endl;
        getObject(i)->doSomething();
    }
	UpdateVector();
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    
}

//-------CUSTOM FUNCTIONS---------
void StudentWorld::insertObject(BaseObject * o)
{
    gameObjects.push_back(o);
}

int StudentWorld::getSizeVector()
{
    return gameObjects.size();
}

BaseObject* StudentWorld::getObject(int i)
{
    
    return gameObjects.at(i);
}

bool StudentWorld::dirtAlive(int x,int y)
{
    cout << "returning dirt location " << gameMap[x][y]->isVisible() << endl;
    
    return gameMap[x][y]->isVisible();
}
void StudentWorld::createDirt() {
    //using 2d array for coordinate system and init with a for loop
    for (int x = 0; x<VIEW_WIDTH; x++) {
        for (int y = 0; y<DIRT_HEIGHT; y++) {
            gameMap[x][y] = new Dirt(x, y);
        }
    }
    //MINESHAFT
    for (int x = 30; x <= 33; x++) {
        for (int y = 4; y <= 59; y++) {
            gameMap[x][y]->setVisible(false);
        }
    }
};

// Function that checks all the positions
// that the diggerman is occupying and
// if is in the same position than one
// dirt object it sets the visibility of the
// dirt to false. Returns true when it changes
// at least one dirt's visibility from true to false
bool StudentWorld::digging(DiggerMan *z)
{
    bool dig = false;
    for(int x=0;x<4;x++)
        for (int y = 0; y < 4; y++)
        {
            if ((z->getY() + y) < DIRT_HEIGHT)
            {
                if (gameMap[z->getX() + x][z->getY() + y]->isVisible())
                {
                    dig = true;
                    gameMap[z->getX() + x][z->getY() + y]->setVisible(false);
                    
                    //for testing
                    //cout << "x cord: " << z->getX() + x << " Y cord: " << z->getY() + y << endl;
                    
                }
            }
        }
    return dig;
}

void StudentWorld::createGameObjects() {
    random_device rd; //obtain a random number from hardware
    mt19937 eng(rd()); //seed the generator
    uniform_int_distribution<> distr(0, 59); //define the range
    
    int count = 2;
    for (int i = 0; i <= count; i++) {
        Boulder *bl = new Boulder(distr(eng), distr(eng));
        bl->setWorld(this);
        insertObject(bl);
    }
}




//Function that fills the 2D array used to detect t
// the position occupied by the objects in the map
// The function calls the vector were all the objects are
// stored. Then based in the location of the objects, fills
// the 2d array assigning the positions that each object
// is occupying in the map the number that each object has in
// the vector. 
void StudentWorld::fillObjectCoord(DiggerMan *z)
{
	//first clean the grid
	for (int x = 0; x < VIEW_WIDTH; x++) {
		for (int y = 0; y < VIEW_HEIGHT; y++) {
			ObjectCoord[x][y] = nullptr;
		}
	}
	// then load the grid with the position of the objects in the map
	int xcoord, ycoord;
	for (int i = 0; i < getSizeVector(); i++)
	{

		xcoord = getObject(i)->getX();
		ycoord = getObject(i)->getY();
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				*ObjectCoord[xcoord + x][ycoord + y] = i;
			}
		}
	}
	//lastly add the diggerman to the grid
	xcoord = z->getX();
	ycoord = z->getY();
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			*ObjectCoord[xcoord + x][ycoord + y] = getSizeVector(); // the diggerman will have the last number in the grid
		}
	}
}


//This function updates the vector checking the state
// of each object in it. If the states is equal to 'dead'
// then it will swap the the object with the one in the 
// last position of the vector, then it deletes the last
// one. 
void StudentWorld::UpdateVector()
{
	
	cout << "FIRST SIZE:::" << getSizeVector() << endl;
	bool swaped;
	int deleteitems = 0;
	for (int i = 0; i < getSizeVector(); i++)
	{
		if ((deleteitems + i) >= getSizeVector()) //we reach the end of the vector
			break;	
		swaped = false;
		if (getObject(i)->getState() == BaseObject::dead ) //check the first element in the vector
		{
			deleteitems++; //increase the elements to be deleted
			if ((deleteitems + i) == getSizeVector()) //we reach the end of the vector
				break;
			else
			{
				while (!swaped)
				{
					if (getObject(getSizeVector() - deleteitems)->getState() == BaseObject::alive) //check if the last one is alive 
					{
						iter_swap(gameObjects.begin() + i, gameObjects.begin() + (getSizeVector() - deleteitems));
						swaped = true;
					}
					else
					{
						if (deleteitems == getSizeVector())
							break; //all the items has the state of dead
						deleteitems++; //encounter a new dead object
					}
				}
			}
		}
	}
	// for loop that deletes the items 
	for (int i = 0; i < deleteitems; i++)
	{
		gameObjects.pop_back();
	}
	
	//for testing 
	cout << "size of the vector is:: " << getSizeVector() << endl; 

}

