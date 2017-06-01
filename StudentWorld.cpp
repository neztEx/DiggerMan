#include "StudentWorld.h"
#include <string>
#include <cstdlib>
#include "Actor.h"
#include <algorithm>
#include <time.h>
#include <sstream>
#include <random>
//#include <windows.h>


using namespace std;
//const int DIRT_HEIGHT = 60;

//declaration of player
//DiggerMan *player = new DiggerMan();
string intToString(int x);
string twoDigits(int x);
string threeDigits(int x);
string sixDigits(int x);
string formatString(int level, int lives, int health,  int squirts, int gold, int sonar, int barrelsLeft, int score);


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
	ResetBarrels();
    createGameObjects();
    
    
    return GWSTATUS_CONTINUE_GAME;
}
int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
   // decLives();
	SetDisplayText();
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
    addNewObjects();
	UpdateVector();
    if (getPlayer()->isVisible() == false){
        playSound(GWSTATUS_PLAYER_DIED);
        return GWSTATUS_PLAYER_DIED;
    }
    if(GetTotalBarrels() == 0){
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{

    for(int i = 0; i < gameObjects.size(); i++){
        delete gameObjects[i];
    }
    gameObjects.clear();
    for (int x = 0; x<VIEW_WIDTH; x++)
    {
        for (int y = 0; y<DIRT_HEIGHT; y++)
        {
            delete gameMap[x][y];
        }
    }
    delete getPlayer();
}
//--------------CUSTOM FUNCTIONS-------------------

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
void StudentWorld::setlevel(){
    current_level_number++;
}
void StudentWorld::setTotalBarrels(int B)
{
	MaxBarrels = B;
}
int StudentWorld::GetTotalBarrels()
{
	return MaxBarrels;
}
void StudentWorld::DecreaseBarrels()
{
	MaxBarrels--;
}
void StudentWorld::ResetBarrels()
{
	MaxBarrels = 0;
}
void StudentWorld::SetDisplayText()
{
	int levels = getLevel();
	int lives = getLives();
	int health = getPlayer()->getHealth();
	int squirts = getPlayer()->getSquirtNum();
	int gold = getPlayer()->getGoldNum();
	int sonar = getPlayer()->getSonarKit();
	int barrelsLeft = GetTotalBarrels();
	int score = getScore();
	string s = formatString(levels, lives, health, squirts, gold, sonar, barrelsLeft, score);
	setGameStatText(s);
}

void StudentWorld::createGameObjects() {
    int current_level_number = getLevel() + 100;
    
    int B = min(current_level_number / 2 + 2, 7); //boulders
    int G = max(5-current_level_number / 2, 2); //gold nuggets
    int L = min(2+current_level_number, 18); //barrels of oil
    
    
	setTotalBarrels(L);
    srand(time(NULL));

    for (int i = 0; i < B; i++) {
        int x = rand() % 60;
        int y = rand() % 36+20; //56-20=36, plus 20 to start the range at.
        //cout << y << endl;
        while(x == 30 || x == 31 || x == 32 || x == 33){
            x = rand() % 60;
        }
        Boulder *bl = new Boulder(x,y);
        bl->setWorld(this);
		//delete the line below
		cout << "boulder X: "<<bl->getX() << " y: " << bl->getY() << endl;
        for(int x1 = 0; x1<4;x1++){
            for(int y1 = 0; y1<4; y1++){
                gameMap[x+x1][y+y1]->setVisible(false);
            }
        }
        insertObject(bl);
    }
    for (int i = 0; i < G; i++) {
        int x = rand() % 60;
        int y = rand() % 56;
        while(x == 30 || x == 31 || x == 32 || x == 33){
            x = rand() % 60;
        }
        GoldNugget *gn1 = new GoldNugget(x,y);;
        gn1->initialize(this);
        insertObject(gn1);
    }
    for (int i = 0; i < L; i++) {
        int x = rand() % 60;
        int y = rand() % 56;
        while(x == 30 || x == 31 || x == 32 || x == 33){
            x = rand() % 60;
        }
        Barrel *bo1 = new Barrel(x,y);
        bo1->initialize(this);
        insertObject(bo1);
    }
	
	
	RegProtester *prot = new RegProtester;
	prot->Initialize(this);
	insertObject(prot);
	
	
	HardProtester *prot2 = new HardProtester;
	prot2->Initialize(this);
	insertObject(prot2);
	
	
	/*
	WaterPool *w1 = new WaterPool(6, 10);
	//WaterPool *w1 = new WaterPool(30, 10);
	w1->initialize(this);
	insertObject(w1);
	SonarKit *sk1 = new SonarKit(8, 30);
	sk1->initialize(this);
	insertObject(sk1);

*/

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

//functions to add new objects after certain amount of ticks have occured in the game
void StudentWorld::addNewObjects(){

    int current_level_number = getLevel();
    bool goodieAdded = false;
    int G = (current_level_number * 25 + 300);
    
    //windows code for time
    
     LARGE_INTEGER cicles;   
     QueryPerformanceCounter(&cicles);   
     srand (cicles.QuadPart);
    
  
    //////Mac code for time
    //timeval t1;
    //gettimeofday(&t1, NULL);
    //srand(t1.tv_usec * t1.tv_sec);
    //
    
    
    int random = rand() % G;

    if(random < 1){ //1 in G chance to add a new object to the game
       // cout << "goodie to be added!" << endl;
        while(goodieAdded != true){ //while the item hasnt been added continue to loop until a location can be found
            int random2 = rand() % 5;

            if(random2 < 1){ //to add sonar kit
                SonarKit *sk1 = new SonarKit(0, 60);
                sk1->initialize(this);
                insertObject(sk1);
                goodieAdded = true;
                return;
            }
            if(random2 < 4){ //to add water pool
                
                bool freeSpace = false;
                while(goodieAdded != true){
                    int xSet = 0;
                    int ySet = 0;
                    while(freeSpace != true)
                    {
                        int x = rand() % 60;
                        int y = rand() % 56;
                        
                        Boulder *temp = new Boulder(x, y);
                        bool result = find(gameObjects.begin(), gameObjects.end(), temp) != gameObjects.end();
                        delete temp;
                        
                        if(result == false)
                        {
                            
                            for(int x1 = 0; x1<4;x1++)
                            {
                                for(int y1 = 0; y1<4; y1++)
                                {
                                    if(gameMap[x+x1][y+y1]->isVisible()==true)
                                    {
                                        freeSpace = false;
                                        break;
                                    }
                                    else
                                    {
                                        freeSpace = true;
                                    }
                                }
                                if(freeSpace == false)
                                    break;
                            }
                            
                            if(freeSpace == true)
                            {
                                xSet = x;
                                ySet = y;
                            }
                        }
                    }
                    WaterPool *w1 = new WaterPool(xSet,ySet);
                    w1->initialize(this);
                    insertObject(w1);
                    goodieAdded = true;
                    return;
                }
            }
        }
    }
    return;
    
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

string intToString(int x)
{	
	stringstream s1;
	s1 << x;
	return s1.str();

}

string twoDigits(int x)
{
	string s2;
	if (x >= 10)
		s2 = intToString(x);
	else
		s2 = (" " + intToString(x));
	return s2;
}
string threeDigits(int x)
{
	string s2;
	int perc = x * 10;
	if (perc >= 100)
		s2 = intToString(perc);
	else
		s2 = (" " + intToString(perc));
	return s2+"%";
}

string sixDigits(int x)
{
	string s2,s3;
	s2 = intToString(x);
	if (s2.length() < 6)
	{
		int numZeros = 6 - s2.length();
		for (int i = 0; i < numZeros; i++)
		{
			if (s3.empty())
				s3 = "0";
			else
				s3 = s3 + "0";
		}
		return s3 + s2;
	}
		return s2;
}



string formatString(int level, int lives, int health, int squirts, int gold, int sonar, int barrelsLeft, int score)
{
	string s1;
	s1 = ("Lvl: " + twoDigits(level) + "  Lives: " + intToString(lives) + "  Hlth: " + threeDigits(health) + "  Wtr: " + twoDigits(squirts)
		+ "  Gld: " + twoDigits(gold) + "  Sonar: " + twoDigits(sonar) + "  Oil Left: " + twoDigits(barrelsLeft) + "  Scr: " + sixDigits(score));
	return s1;
}
