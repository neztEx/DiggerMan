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
	getPlayer()->Initialize(this);
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
	if ((x >= VIEW_WIDTH) || (y >= DIRT_HEIGHT))
		return false;
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
	//WaterPool *w1 = new WaterPool(30, 10);
	w1->initialize(this);
	insertObject(w1);
	SonarKit *sk1 = new SonarKit(8, 30);
	sk1->initialize(this);
	insertObject(sk1);
	Barrel *bo1 = new Barrel(34, 45);
	bo1->initialize(this);
	insertObject(bo1);
	GoldNugget *gn1 = new GoldNugget (34, 35);
	gn1->initialize(this);
	insertObject(gn1);

	//Boulder *b4 = new Boulder(15, 40);
	//b4->setWorld(this);
	//insertObject(b4);
	//WaterPool *w2 = new WaterPool(34, 45);
	////WaterPool *w1 = new WaterPool(30, 10);
	//w2->initialize(this);
	//insertObject(w2);
	//SonarKit *sk2 = new SonarKit(3, 22);
	//sk2->initialize(this);
	//insertObject(sk2);
}


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
						deleteitems++;
						if ((deleteitems + i) >= getSizeVector())
							break; //all the items has the state of dead
					 //encounter a new dead object
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
	
	//cout << "size of the VEctor!!!" << getSizeVector() << endl;

}

DiggerMan * StudentWorld::getPlayer()
{
	return m_player;
}

void StudentWorld::setPlayer(DiggerMan * z)
{
	m_player = z;
}

