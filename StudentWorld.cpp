#include "StudentWorld.h"
#include <string>
#include <random>
#include "Actor.h"
#include <algorithm>

using namespace std;
//const int DIRT_HEIGHT = 60;

//declaration of player
//DiggerMan *player = new DiggerMan();


GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp


int StudentWorld::init()
{
    //DIRT - creating the data structure for the dirt object w/ mineshaft
    createDirt();
	DiggerMan *player = new DiggerMan();
	setPlayer(player);
    getPlayer()->setWorld(this);
    createGameObjects();
    
    return GWSTATUS_CONTINUE_GAME;
}
int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    decLives();
	//fillObjectCoord(player);
    getPlayer()->doSomething();
    if (digging(getPlayer()))
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
	o->setWorld(this);
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
   // cout << "returning dirt location " << gameMap[x][y]->isVisible() << endl;
    
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
	WaterPool *w1 = new WaterPool(6, 10);
	w1->initialize(this);
	insertObject(w1);
}




//Function that fills the 2D array used to detect t
// the position occupied by the objects in the map
// The function calls the vector were all the objects are
// stored. Then based in the location of the objects, fills
// the 2d array assigning the positions that each object
// is occupying in the map the number that each object has in
// the vector. 

/*
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
				//cout << "GETS IN FILLING!!!!!!" << endl;
				//cout << xcoord + x << "  " << ycoord + y << "   " << i << endl;
				*(ObjectCoord[xcoord + x][ycoord + y]) = getObject(i)->getName();
			}
		}
	}
	//lastly add the diggerman to the grid
	xcoord = z->getX();
	ycoord = z->getY();
	//int sizevec = getSizeVector();
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			//cout << xcoord + x << "  " << ycoord + y << "   " << sizevec << endl;
			*(ObjectCoord[xcoord + x][ycoord + y]) = BaseObject::diggerman; // the diggerman will have the last number in the grid
		}
	}
}
*/

//This function updates the vector checking the state
// of each object in it. If the states is equal to 'dead'
// then it will swap the the object with the one in the 
// last position of the vector, then it deletes the last
// one. 
void StudentWorld::UpdateVector()
{
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
	//cout << "size of the vector is:: " << getSizeVector() << endl; 

}

DiggerMan * StudentWorld::getPlayer()
{
	return m_player;
}

void StudentWorld::setPlayer(DiggerMan * z)
{
	m_player = z;
}


/* Function that returns false if the oildfield
// has any object in the map. Using the 2d array that
// saves the location of all the objects in the map
// returns true if there is nothing there


bool StudentWorld::isMapEmpty(int x, int y)
{
	if (ObjectCoord[x][y] == nullptr)
		return true;

	return false;
}


// Function that returns which object is placed in
// the (x,y) position.  
BaseObject::name * StudentWorld::objectInMap(int x, int y)
{
	//if (*(ObjectCoord[x][y]) == getSizeVector()) //Diggerman is always stored  with the integer equals to the size of the objectsvector
	//	return nullptr; //its the diggerman!!!
	//else
	//{
	//	cout << "OBJECT TO BE SEARCHED IN POSITION:: " << &(ObjectCoord[x][y]) << endl;
	//	return getObject(*(ObjectCoord[x][y])); //return the object in that x,y position using the getobject function

	//}
	return (ObjectCoord[x][y]);
}

*/
