#include "Actor.h"
#include "StudentWorld.h"
#include <algorithm>
#include <cmath>
//#include "GameWorld.h"

#include <iostream>

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
//testing github commit functions


//***********************************************************************************************
//************** BASE OBJECT FUNCTIONS ***********************************************************
//***********************************************************************************************


void BaseObject::doSomething()
{
}

bool BaseObject::AllowMove(int x, int y)
{
	return false;
}

void BaseObject::Initialize()
{
}

void BaseObject::activateSonar()
{
}

void BaseObject::setState(state d)
{
	m_state = d;
}

BaseObject::state BaseObject::getState()
{
	return m_state;
}

void BaseObject::setName(name n)
{
	m_name = n;
}

BaseObject::name BaseObject::getName()
{
	return m_name;
}

void BaseObject::setSpace()
{
	for (int i = 0; i < 4; i++)
	{
		x_space[i] = (getX() + i);
		y_space[i] = (getY() + i);
	}
}

bool BaseObject::ObjectInMap(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		if (x_space[i] == x)
		{
			for (int b = 0; b < 4; b++)
			{
				if (y_space[b] == y)
					return true;
			}
		}
	}
	return false;
}


//function that returns the name of the object encountered

BaseObject::name BaseObject::HittingSomething(int x, int y)
{
	
	//change this for a nice code!!! to go thru the vector
	for (int i = 0; i < getWorld()->getSizeVector(); i++)
	{
		if (getWorld()->getObject(i)->ObjectInMap(x, y))
			return getWorld()->getObject(i)->getName();
	}
	return none;

}

//function that returns the vector index of the object
// in that position, if there is nothing there returns -1
int BaseObject::IndexOfObject(int x, int y)
{

	//change this for a nice code!!! to go thru the vector
	for (int i = 0; i < getWorld()->getSizeVector(); i++)
	{
		if (getWorld()->getObject(i)->ObjectInMap(x, y))
			return i;
	}
	return -1;

}



void BaseObject::setWorld(StudentWorld * gw)
{
	m_sw = gw; //this is to access the StudentWorld object
}


StudentWorld * BaseObject::getWorld()
{
	return m_sw;
}


// Function that check if the Player is touching or in the edge of the objects
// returns 1 if its in the edge
// returns 0 if is touching the object
// returns 2 if is far of the object (no interaction)

int BaseObject::HittingPlayer(int x, int y)
{
	if (((x - ((getWorld()->getPlayer()->getX() + 3))) == 1) || (((x + 3) - (getWorld()->getPlayer()->getX())) == -1)) //its coming from left or right
	{
		if ((abs(y - (getWorld()->getPlayer()->getY()))) <= 4)
		{
			return 1;
		}
	}

	else if (((y - ((getWorld()->getPlayer()->getY() + 3))) == 1) || (((y + 3) - (getWorld()->getPlayer()->getY())) == -1)) //its coming from up or down
	{
		if ((abs(x - (getWorld()->getPlayer()->getX()))) <= 4)
		{

			return 1;
		}
	}
	if (((x - ((getWorld()->getPlayer()->getX() + 3))) == 0) || (((x + 3) - (getWorld()->getPlayer()->getX())) == 0)) //its coming from left or right
	{
		if ((abs(y - (getWorld()->getPlayer()->getY()))) <= 4)
		{
			return 0;
		}
	}

	else if (((y - ((getWorld()->getPlayer()->getY() + 3))) == 0) || (((y + 3) - (getWorld()->getPlayer()->getY())) == 0)) //its coming from up or down
	{
		if ((abs(x - (getWorld()->getPlayer()->getX()))) <= 4)
		{
			return 0;
		}
	}
	return 2;
}

//void BaseObject::updateTickCounter()(){
  //  tickCounter++;
//}

// *****************************
// ****** DIGGERMAN FUNCTIONS  ***************
// *****************************

void DiggerMan::doSomething()
{
    int ch;
    if ((getWorld()->getKey(ch) == true))
    {
        switch (ch)
        {
            case KEY_PRESS_LEFT:
                if (getDirection() == left)
                {
                    if (AllowMove(getX() - 1, getY(), left))
                        moveTo(getX() - 1, getY());
                }
                else
                    setDirection(left);
                break;
                
            case KEY_PRESS_RIGHT:
                if (getDirection() == right)
                {
                    if (AllowMove(getX() + 1, getY(), right))
                        moveTo(getX() + 1, getY());
                }
                else
                    setDirection(right);
                break;
                
            case KEY_PRESS_UP:
                if (getDirection() == up)
                {
                    if (AllowMove(getX(), getY() + 1, up))
                        moveTo(getX(), getY() + 1);
                }
                else
                    setDirection(up);
                break;
                
            case KEY_PRESS_DOWN:
                if (getDirection() == down)
                {
                    if (AllowMove(getX(), getY() - 1, down))
                        moveTo(getX(), getY() - 1);
                }
                else
                    setDirection(down);
                break;
            case KEY_PRESS_SPACE:
			{
				if (getSquirtNum() > 0) //if diggerman has bullets of water :p
				{

					int xS, yS;
					switch (getDirection())
					{
					case up:
						xS = getX();
						yS = getY() + 4;
						break;
					case down:
						xS = getX();
						yS = getY() - 4;
						break;
					case right:
						xS = getX() + 4;
						yS = getY();
						break;
					case left:
						xS = getX() - 4;
						yS = getY();
						break;
					}
					//cout << "never gets here" << endl;

					Squirt *s1 = new Squirt(xS, yS, getDirection());
					s1->initialize(getWorld());
					//cout << "INSIDE DIGGERMAN WITH SQUIRT" << s1->getWorld()->getSizeVector() << endl;
					getWorld()->insertObject(s1);
					getWorld()->playSound(SOUND_PLAYER_SQUIRT);
					decraseSquirtGun(); // decrease de bullets

				}
				break;
			
			}
            case KEY_PRESS_TAB:
				//add gold nugget to the map
				if (getGoldNum() > 0)
				{
					GoldNugget *gn1 = new GoldNugget(getX(), getY());;
					gn1->initialize(getWorld());
					gn1->setPickable(false);
					getWorld()->insertObject(gn1);
					decreaseGoldNum();
				}
                break;
            case KEY_PRESS_ESCAPE:
                break;
            case 90:// if press 'Z'
				if (getSonarKit() > 0) // if diggerman has sonarkits
				{
					cout << "launching sonar kit" << endl;
					discoverObjects();
					decreaseSonarKit();
				}
				
				break;
            case 122:// if press 'z'
				if (getSonarKit() > 0) // if diggerman has sonarkits
				{
					cout << "launching sonar kit" << endl;
					discoverObjects();
					decreaseSonarKit();
				}
				
				break;
        }
    }
}


//void DiggerMan::setWorld(StudentWorld * gw)
//{
//    m_sw = gw; //this is to access the StudentWorld object
//}
//
//StudentWorld * DiggerMan::getWorld()
//{
//    return m_sw;
//}


//Function that checks if Diggerman is allowed to move in the
//next position. If it can returns true, if it is out of the
//oilfield limits then it returns false.
bool DiggerMan::AllowMove(int x, int y, Direction Dir)
{
	if ((x >= 0) && (x <= 60) && (y >= 0) && (y <= 60))
	{
		switch (Dir)
		{
		case left:
			for (int i = 0; i < 4; i++)
			{
				if (HittingSomething(x, (y+i)) == boulder)
					return false;
			} return true;
			break;
		case right:
			for (int i = 0; i < 4; i++)
			{
				if (HittingSomething((x+3), (y + i)) == boulder)
					return false;
			} return true;
			break;
		case up:
			for (int i = 0; i < 4; i++)
			{
				if (HittingSomething((x+i), (y + 3)) == boulder)
					return false;
			} return true;
			break;
		case down:
			for (int i = 0; i < 4; i++)
			{
				if (HittingSomething((x+i), (y)) == boulder)
					return false;
			} return true;
			break;
		}

	}
		//return true;
    else
        return false;
    return true;
}


void DiggerMan::Initialize(StudentWorld * m_gw)
{
	setWorld(m_gw);
	squirt_num = 5;
	sonarkit_num = 1;
	health = 10;
	Gold_num = 0;
}

void DiggerMan::addSquirtGun()
{
	squirt_num = squirt_num + 5;
}

void DiggerMan::decraseSquirtGun()
{
	squirt_num--;
}

int DiggerMan::getSquirtNum()
{
	return squirt_num;
}

void DiggerMan::addSonarKit()
{
	sonarkit_num++;
}

void DiggerMan::decreaseSonarKit()
{ 
	sonarkit_num--;
}

int DiggerMan::getSonarKit()
{
	return sonarkit_num;
}

int DiggerMan::getGoldNum()
{
	return Gold_num;
}

void DiggerMan::AddGoldNum()
{
	Gold_num++;
}

void DiggerMan::decreaseGoldNum()
{
	Gold_num--;
}



// function that checks in a radious of 12 units
// from where its drooped (diggerman position) 
// if there is any hidden object around. If its find
// one, then it will activate the sonarkit timer in those
// objects
void DiggerMan::discoverObjects()
{
	int newX = (getX() - 12);
	int newY = (getY() - 12);
	for (int x = 0; x <= 28; x +=4)
	{
		for (int y = 0; y <= 28; y += 4)
		{
			if (( (x+ newX) >= 0) && ((x + newX) <= 60) && ((y+newY) >= 0) && ((y+newY) <= 60)) //if x and y are within the limits of the oilfield
			{
				//cout << "searching in positions " << (x + newX) << " " << (y + newY) << endl;
			
				if ((HittingSomething((x + newX), (y + newY)) == barrelOil) || (HittingSomething((x + newX), (y + newY)) == goldNugget))
				{
					cout << "found OBJECT IN RADAR" << endl;
					getWorld()->getObject(IndexOfObject((x + newX), (y + newY)))->activateSonar();
				}
				/*switch (HittingSomething((x + newX), (y + newY)
				{
				case waterPool:
					cout << "found a waterPool" << endl;
					break;
				case boulder:
					cout << "found boulder" << endl;
					break;
				case sonarKit:
					cout << "found sonarKit" << endl;
					break;
				case none:
					cout << "found none" << endl;
					break;
				}*/
					//else 
					//cout << "couldn't find something" << endl;
			}
		}

	}

}

void DiggerMan::decreaseHealth()
{
	health--;
}

void DiggerMan::increaseHealth()
{
	health++;
}

int DiggerMan::getHealth()
{
	return health;
}

void DiggerMan::ResetHealth()
{
	health = 10;
}






//*************************************************************************************************
//************ BOULDER FUNCTIONS  ******************************************************************
//*************************************************************************************************

 
void Boulder::doSomething()
{
    if (isVisible() == false) //if boulder is dead we do nothing
    {
        return;
    }
    if (stableState == true) {
       // cout << "stable" << endl;
      //  cout << "returns getWorld function: " << getWorld()->dirtAlive(getX(),getY() - 1) << endl;

            if (getWorld()->dirtAlive(getX(),getY() - 1) == false && getWorld()->dirtAlive(getX()+1,getY() - 1) == false &&  getWorld()->dirtAlive(getX()+2,getY() - 1) == false && getWorld()->dirtAlive(getX()+3,getY() - 1) == false)
            {
                stableState = false;
                waitingState = true;
                return;  //checks to see if the dirt under the rock is visible
            }
            else {
                return;
            }
    }
    if (waitingState == true) {
      //  cout << "waiting" << endl;

        tickCounter++;
        if (tickCounter == 30) {
            waitingState = false;
            fallingState = true;
            getWorld()->playSound(13);
            return;
        }
    }
    if (fallingState == true)
    {

        if(getWorld()->dirtAlive(getX(), getY()-1) == false)
        {
            moveTo(getX(), getY() - 1);
            if(HittingPlayer(getX(), getY()) == 0){
                getWorld()->getPlayer()->setVisible(false);
            }
            
		//	cout << "animate" << endl;
            return;
        }
        else
        {
          //  cout << "falling state is false" << endl;
            fallingState = false;
            stableState = true;
            tickCounter = 0;
			setVisible(false);
			setState(dead);
			
            return;
        }
        
    }
}


//*************************************************************************************************
//************ SQUIRT FUNCTIONS  ******************************************************************
//*************************************************************************************************

void Squirt::doSomething()
{
    if (getTravel() > 0)
    {
		//setVisible(true);
		//system("pause");
        switch (getDirection())
        {
            case up:
				if (AllowMove(getX(), getY() + 1))
					moveTo(getX(), getY() + 1);
				else
					stopTravel();
                break;
            case down:
				if (AllowMove(getX(), getY() - 1))
					moveTo(getX(), getY() - 1);
				else
					stopTravel();
                break;
            case right:
				if (AllowMove(getX()+1, getY()))
					moveTo(getX()+1, getY());
				else
					stopTravel();
                break;
            case left:
				if (AllowMove(getX()-1, getY()))
					moveTo(getX()-1, getY());
				else
					stopTravel();
                break;
        }
        reduceTravel();
    }
    else
    {
        setVisible(false);
		setState(dead);
    }
}

//function that checks if the squirt can moves to the x,y coord provided

bool Squirt::AllowMove(int x, int y)
{
	if ((x >= 0) && (x <= 60) && (y >= 0) && (y <= 60))
	{
		//based on the direction, checks if there is either dirt or a boulder in the x,y position
		//provided. if there are those, then squirt can move there therefore the functions returns false
		switch (getDirection())
		{
		case left:
			
			for (int i = 0; i < 4; i++)
			{
				if ((HittingSomething(x, (y + i)) == boulder) || (getWorld()->dirtAlive(x, (y + i))))
					return false;
			} return true;
			break;
		case right:
			for (int i = 0; i < 4; i++)
			{
				if ((HittingSomething((x+3), (y + i)) == boulder) || (getWorld()->dirtAlive((x+3), (y + i))))
					return false;
			} return true;
			break;
		case up:
			for (int i = 0; i < 4; i++)
			{
				if ((HittingSomething((x+i), (y + 3)) == boulder) || (getWorld()->dirtAlive((x+i), (y + 3))))
					return false;
			} return true;
			break;
		case down:
			for (int i = 0; i < 4; i++)
			{
				if ((HittingSomething((x+i), (y)) == boulder) || (getWorld()->dirtAlive((x+i), (y))))
					return false;
			} return true;
			break;
		}

	
	}
	else
		return false;
    return true;
}

int Squirt::getTravel()
{
    return travel;
}

void Squirt::reduceTravel()
{
    travel--;
}

void Squirt::stopTravel()
{
    travel = 0;
}

void Squirt::initialize(StudentWorld *m_gw)
{
	setWorld(m_gw);
	if (AllowMove(getX(), getY())) //check if when Diggerman throws a squirt, its within
	{
		travel = 4;  // the limits of the oilfield. If its not then the travel
		setVisible(true);
	}

	else                           // is set to 0. 
		travel = 0;
}


//*********************************************************************************************
//************************ Goodie Functions ***************************************************
//*********************************************************************************************


void Goodie::doSomething()
{
}


void Goodie::addCounter()
{
	tickCounter++;
}

int Goodie::getTickCounter()
{
	return tickCounter;
}

void Goodie::setmaxT(int max)
{
	T = max;
}

int Goodie::getmaxT()
{
	return T;
}

void Goodie::resetCounter()
{
	tickCounter = 0;
}




//********************************************************************************************
//*************************** WaterPool FUNCTIONS ********************************************
//********************************************************************************************

void WaterPool::doSomething()
{
	if ( getTickCounter()<= getmaxT()) //if the number of ticks is still less than the max ticks for this level
	{
		addCounter();
		if (HittingPlayer(getX(), getY()) == 0) //its touching the object
		{
			setVisible(false);
			setState(dead);
			getWorld()->getPlayer()->addSquirtGun();
			cout << "object picked up by diggerman!!!!" << endl;
			getWorld()->playSound(SOUND_GOT_GOODIE);
			getWorld()->increaseScore(100);
		}
	}
	else
	{
		setVisible(false);
		setState(dead);
	}
}


void WaterPool::initialize(StudentWorld * m_gw)
{
	setWorld(m_gw);
	setmaxT(max(100, 300 - 10 * 1)); //subs 1 for the current level: getWorld()->getCurrentLevel();

}

void SonarKit::doSomething()
{
	if (getTickCounter() <= getmaxT()) //if the number of ticks is still less than the max ticks for this level
	{
		addCounter();
		if (HittingPlayer(getX(), getY()) == 0) //its touching the object
		{
			setVisible(false);
			setState(dead);
			getWorld()->getPlayer()->addSonarKit();
			cout << "object picked up by diggerman!!!!" << endl;
			getWorld()->playSound(SOUND_GOT_GOODIE);
			getWorld()->increaseScore(75);
		}
	}
	else
	{
		setVisible(false);
		setState(dead);
	}
}

void SonarKit::initialize(StudentWorld * m_gw)
{
	setWorld(m_gw);
	setmaxT(max(100, 300 - 10 * 1));
}

void Barrel::doSomething()
{
	if (getmaxT() > 0) //this means that the sonar kit was activated near this object
	{
		setVisible(true);
		if (getTickCounter() <= getmaxT()) //if the number of ticks is still less than the max ticks for this level
		{
			addCounter();
			if (HittingPlayer(getX(), getY()) == 0) //its touching the object
			{
				setState(dead);
				setVisible(false);
				//getWorld()->getPlayer()->addSonarKit();
				cout << "object picked up by diggerman!!!!" << endl;
				getWorld()->playSound(SOUND_FOUND_OIL);
				getWorld()->increaseScore(1000);
				getWorld()->DecreaseBarrels();
			}
		}
		if (getTickCounter() == getmaxT())
		{
			resetCounter();
			setmaxT(0); //sonar is off
		}
	}

	else if (HittingPlayer(getX(), getY()) == 1) //its on the edge
	{
		setVisible(true);
	}
	else if (HittingPlayer(getX(), getY()) == 0) // its touching the object
	{
		setState(dead);
		setVisible(false);
		//getWorld()->getPlayer()->addSonarKit();
		cout << "object picked up by diggerman!!!!" << endl;
		getWorld()->playSound(SOUND_FOUND_OIL);
		getWorld()->increaseScore(1000);
		getWorld()->DecreaseBarrels();

	}
	/*else
		setVisible(false);*/
}

void Barrel::initialize(StudentWorld * m_gw)
{
	setWorld(m_gw);
	//setmaxT(max(100, 300 - 10 * 1));
}


void HiddenGoodie::activateSonar()
{
	setmaxT(50);
}

bool HiddenGoodie::getPickable()
{
	return pickableforDig;
}

void HiddenGoodie::setPickable(bool x)
{
	pickableforDig = x;
}

void GoldNugget::doSomething()
{
	if (getmaxT() > 0) //this means that the sonar kit was activated near this object
	{
		setVisible(true);
		if (getTickCounter() <= getmaxT()) //if the number of ticks is still less than the max ticks for this level
		{
			addCounter();
			if ((HittingPlayer(getX(), getY()) == 0)&& (getPickable()==true)) //its touching the object
			{
				setState(dead);
				setVisible(false);
				//getWorld()->getPlayer()->addSonarKit();
				cout << "object picked up by diggerman!!!!" << endl;
				getWorld()->playSound(SOUND_GOT_GOODIE);
				getWorld()->increaseScore(10);
				getWorld()->getPlayer()->AddGoldNum();
			}
		}
		if (getTickCounter() == getmaxT())
		{
			resetCounter();
			setmaxT(0); //sonar is off
		}
	}

	else if (HittingPlayer(getX(), getY()) == 1) //its on the edge
	{
		setVisible(true);
	}
	else if ((HittingPlayer(getX(), getY()) == 0) && (getPickable() == true)) // its touching the object
	{
		setState(dead);
		setVisible(false);
		//getWorld()->getPlayer()->addSonarKit();
		cout << "object picked up by diggerman!!!!" << endl;
		getWorld()->playSound(SOUND_GOT_GOODIE);
		getWorld()->increaseScore(10);
		getWorld()->getPlayer()->AddGoldNum();

	}
	/*else
	setVisible(false);*/
}

void GoldNugget::initialize(StudentWorld * m_gw)
{
	setWorld(m_gw);
}
