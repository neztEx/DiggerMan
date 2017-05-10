#include "StudentWorld.h"
#include <string>
#include <random>

using namespace std;
//const int DIRT_HEIGHT = 60;

//-------CUSTOM FUNCTIONS---------
//void createDirt(); //fills screen with dirt
bool digging(DiggerMan *z);
void createGameObjects();
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
    
    int count = 0;
    for (int i = 0; i <= count; i++) {
        Boulder *bl = new Boulder(distr(eng), distr(eng));
        bl->setWorld(this);
        insertObject(bl);
    }
}

