#include "Actor.h"
#include "StudentWorld.h"
#include <algorithm>
#include <cmath>
#include <time.h>
#include <memory>
//#include "GameWorld.h"
#include <queue>

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

void BaseObject::GetAnnoyed(int x)
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

// function returns if the distance between objects is <=3
// if it is then it sends the name of the object
BaseObject::name BaseObject::HittingSomething2(int x, int y)
{
	//change this for a nice code!!! to go thru the vector
	for (int i = 0; i < getWorld()->getSizeVector(); i++)
	{
		//if (getWorld()->getObject(i)->ObjectInMap(x, y))
		if (Radious(x, y, getWorld()->getObject(i)->getX(), getWorld()->getObject(i)->getY()) <= 3.0)
		{
			//cout << "x1: " << x << " y1: " << y << " x2: "<<getWorld()->getObject(i)->getX() << " y2: " << getWorld()->getObject(i)->getY() << endl;
			//cout << "Radius::: "<<Radious(x, y, getWorld()->getObject(i)->getX(), getWorld()->getObject(i)->getY()) << endl;
			return getWorld()->getObject(i)->getName();

		}
	}
	return none;

}

int BaseObject::IndexOfObjectWithinRadius(int x, int y)
{
	//change this for a nice code!!! to go thru the vector
	for (int i = 0; i < getWorld()->getSizeVector(); i++)
	{
		//if (getWorld()->getObject(i)->ObjectInMap(x, y))
		if (Radious(x, y, getWorld()->getObject(i)->getX(), getWorld()->getObject(i)->getY()) <= 3.0)
		{
			/*cout << "x1: " << x << " y1: " << y << " x2: " << getWorld()->getObject(i)->getX() << " y2: " << getWorld()->getObject(i)->getY() << endl;
			cout << "Radius::: " << Radious(x, y, getWorld()->getObject(i)->getX(), getWorld()->getObject(i)->getY()) << endl;*/
			if (getWorld()->getObject(i)->getName()!= getName())
				return i;

		}
	}
	return -1;

}




// function that return the radious distance from two objects
// taking as a parameters the x and y coordinates from both objects
double BaseObject::Radious(int x1, int y1, int x2, int y2)
{
	return sqrt((pow(abs((x1 - x2)), 2.0)) + (pow(abs((y1 - y2)), 2.0)));
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

double BaseObject::RadiusFromPlayer()
{
	return sqrt((pow(abs((getX() - getWorld()->getPlayer()->getX())), 2.0)) + (pow(abs((getY() - getWorld()->getPlayer()->getY())), 2.0)));
}

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
				//cout << "x: " << getX() << "y:  " << getY() << endl;
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
				setState(dead);
                break;
            case 90:// if press 'Z'
				if (getSonarKit() > 0) // if diggerman has sonarkits
				{
					//cout << "launching sonar kit" << endl;
					discoverObjects();
					decreaseSonarKit();
				}
				
				break;
            case 122:// if press 'z'
				if (getSonarKit() > 0) // if diggerman has sonarkits
				{
				//	cout << "launching sonar kit" << endl;
					discoverObjects();
					decreaseSonarKit();
				}
				
				break;
        }
    }
}


//Function that checks if Diggerman is allowed to move in the
//next position. If it can returns true, if it is out of the
//oilfield limits then it returns false.
bool DiggerMan::AllowMove(int x, int y, Direction Dir)
{
	if ((x >= 0) && (x <= 60) && (y >= 0) && (y <= 60))
	{
		if (HittingSomething2(x, y) == boulder)
			return false;

		/*
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
				//if (HittingSomething((x+3), (y + i)) == boulder)
				if (HittingSomething2((x + 3), (y + i)) == boulder)
					return false;
			} return true;
			break;
		case up:
			for (int i = 0; i < 4; i++)
			{
				//if (HittingSomething((x+i), (y + 3)) == boulder)
				if (HittingSomething2((x + i), (y + 3)) == boulder)
					return false;
			} return true;
			break;
		case down:
			for (int i = 0; i < 4; i++)
			{
				//if (HittingSomething((x+i), (y)) == boulder)
				if (HittingSomething2((x + i), (y)) == boulder)
					return false;
			} return true;
			break;
		}*/

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
				//	cout << "found OBJECT IN RADAR" << endl;
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

void DiggerMan::decreaseHealth(int x)
{
	health=health - x;
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

void DiggerMan::GetAnnoyed(int x)
{
	decreaseHealth(x);
	if (getHealth() <= 0)
	{
		getWorld()->playSound(SOUND_PLAYER_GIVE_UP);
		setState(dead);
	}

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

          if (getWorld()->dirtAlive(getX(),getY() - 1) == false && getWorld()->dirtAlive(getX()+1,getY() - 1) == false &&  getWorld()->dirtAlive(getX()+2,getY() - 1) == false && getWorld()->dirtAlive(getX()+3,getY() - 1) == false)
            {
				moveTo(getX(), getY() - 1);
				if(HittingPlayer(getX(), getY()) == 0)
				 {
					  getWorld()->getPlayer()->setState(dead);
				 }
				
                //int i = IndexOfObjectWithinRadius(getX(), getY());
                else if (IndexOfObjectWithinRadius(getX(), getY()) >= 0)
                {
					int i = IndexOfObjectWithinRadius(getX(), getY());
					//cout << "object found it by boulder " << i << endl;
					//setVisible(false);
					//setState(dead);
					switch (getWorld()->getObject(i)->getName())
                    {
                        case regProt:
                            getWorld()->getObject(i)->GetAnnoyed(50);
                            setVisible(false);
                            setState(dead);
                            break;
                        case hardProt:
                            getWorld()->getObject(i)->GetAnnoyed(50);
                            setVisible(false);
                            setState(dead);
                            break;
                    }
                }
				//switch (HittingSomething((getX()), getY()))
				//{
				//case regProt:
				//	//getWorld()->getObject(i)->GetAnnoyed(50);
				//	cout << "protester!!!" << endl;
				//	setVisible(false);
				//	setState(dead);
				//	break;
				//
				//
				//}

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
		int i = IndexOfObjectWithinRadius(x, y);
		if (i >=0)
		{ 
			switch (getWorld()->getObject(i)->getName())
			{
			case boulder:
				return false;
					break;
			case regProt:
				getWorld()->getObject(i)->GetAnnoyed(2);
				return false;
					break;
			case hardProt:
				getWorld()->getObject(i)->GetAnnoyed(2);
				return false;
				break;

			}
		//return false;
		}
			switch (getDirection())
			{
			case left:

				for (int i = 0; i < 4; i++)
				{
					if (getWorld()->dirtAlive(x, (y + i)))
						return false;
				} return true;
				break;
			case right:
				for (int i = 0; i < 4; i++)
				{
					if  (getWorld()->dirtAlive((x + 3), (y + i)))
						return false;
				} return true;
				break;
			case up:
				for (int i = 0; i < 4; i++)
				{
					if (getWorld()->dirtAlive((x + i), (y + 3)))
						return false;
				} return true;
				break;
			case down:
				for (int i = 0; i < 4; i++)
				{
					if (getWorld()->dirtAlive((x + i), (y)))
						return false;
				} return true;
				break;
			}
		
		
	}
		return false;
    
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
		//if (HittingPlayer(getX(), getY()) == 0) //its touching the object
		if (RadiusFromPlayer() <= 3.0) // its touching the object
		{
			setVisible(false);
			setState(dead);
			getWorld()->getPlayer()->addSquirtGun();
			//cout << "object picked up by diggerman!!!!" << endl;
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


//*************************************************************************************
//************* SONAR KIT FUNCTIONS ***************************************************
//*************************************************************************************

void SonarKit::doSomething()
{
	if (getTickCounter() <= getmaxT()) //if the number of ticks is still less than the max ticks for this level
	{
		addCounter();
		//if (HittingPlayer(getX(), getY()) == 0) //its touching the object
		if (RadiusFromPlayer() <= 3.0) // its touching the object
		{
			setVisible(false);
			setState(dead);
			getWorld()->getPlayer()->addSonarKit();
		//	cout << "object picked up by diggerman!!!!" << endl;
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


//*************************************************************************************
//************* BARREL    FUNCTIONS ***************************************************
//*************************************************************************************
void Barrel::doSomething()
{
	if (getmaxT() > 0) //this means that the sonar kit was activated near this object
	{
		setVisible(true);
		if (getTickCounter() <= getmaxT()) //if the number of ticks is still less than the max ticks for this level
		{
			addCounter();
			//if (HittingPlayer(getX(), getY()) == 0) //its touching the object
			if (RadiusFromPlayer() <= 3)
			{
				setState(dead);
				setVisible(false);
				//getWorld()->getPlayer()->addSonarKit();
				//cout << "object picked up by diggerman!!!!" << endl;
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
	// if (RadiusFromPlayer() == 4.0) // its on the edge
	{
		setVisible(true);
	}
	// if (HittingPlayer(getX(), getY()) == 0) // its touching the object
	else if (RadiusFromPlayer() <= 3)
	{
		setState(dead);
		setVisible(false);
		//getWorld()->getPlayer()->addSonarKit();
		//cout << "object picked up by diggerman!!!!" << endl;
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


//*************************************************************************************
//************* HIDDEN GOODIE FUNCTIONS ***********************************************
//*************************************************************************************


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


//*************************************************************************************
//************* GOLD NUGGET FUNCTIONS *************************************************
//*************************************************************************************


void GoldNugget::doSomething()
{
	if (getCounterByProt() == 0)
	{
		if (getmaxT() > 0) //this means that the sonar kit was activated near this object
		{
			setVisible(true);
			
		}

		//else if (HittingPlayer(getX(), getY()) == 1) //its on the edge
		if (RadiusFromPlayer() == 4.0) // its on the edge
		{
			setVisible(true);
		}
		//else if ((HittingPlayer(getX(), getY()) == 0) && (getPickable() == true)) // its touching the object
		else	if ((RadiusFromPlayer() <= 3) && (getPickable() == true))
		{
			setState(dead);
			setVisible(false);
			//getWorld()->getPlayer()->addSonarKit();
		//	cout << "object picked up by diggerman!!!!" << endl;
			getWorld()->playSound(SOUND_GOT_GOODIE);
			getWorld()->increaseScore(10);
			getWorld()->getPlayer()->AddGoldNum();

		}

		else
		{
			if (getPickable() == false) //protester can pick gold
			{
				int i = IndexOfObjectWithinRadius(getX(), getY());
				if (i >= 0)
				{
					switch (getWorld()->getObject(i)->getName())
					{
					case regProt:
						getWorld()->getObject(i)->GetAnnoyed(100);
						setVisible(false);
						setState(dead);
						break;
					case hardProt:
						getWorld()->getObject(i)->GetAnnoyed(100);
						int calc = 100 - getWorld()->getLevel() * 10;
						setCounterByProt(max(50, calc));
						break;

					}
				}
			}
		}
	}
	else // it was picked up by the hardprotester
	{
		decreaseCounterByProt();
		if (getCounterByProt() == 0) //has reached the end of ticks
		{
			setVisible(false);
			setState(dead);
		}
	}
}

void GoldNugget::initialize(StudentWorld * m_gw)
{
	setWorld(m_gw);
	setCounterByProt(0);
}

int GoldNugget::getCounterByProt()
{
	return counterByProt;
}

void GoldNugget::decreaseCounterByProt()
{
	counterByProt--;
}

void GoldNugget::setCounterByProt(int x)
{
	counterByProt = x;
}


//**********************************************************************
//********** PROTESTER FUNCTIONS *******************************
//**********************************************************************

bool Protester::AllowMove(int x, int y, Direction dir)
{

	if ((x >= 0) && (x <= 60) && (y >= 0) && (y <= 60))
	{
		int i = IndexOfObjectWithinRadius(x, y);
		if (i >= 0)
		{
			switch (getWorld()->getObject(i)->getName())
			{
			case boulder:
				return false;
				break;

			}
			//return false;
		}
			switch (dir)
			{
			case left:
				//cout << "LEFT" << endl;
				for (int i = 0; i < 4; i++)
				{
					if (getWorld()->dirtAlive(x, (y + i)))
						return false;
				} return true;
				break;
			case right:
				for (int i = 0; i < 4; i++)
				{
					if (getWorld()->dirtAlive((x + 3), (y + i)))
						return false;
				} return true;
				break;
			case up:
				for (int i = 0; i < 4; i++)
				{
					if (getWorld()->dirtAlive((x + i), (y + 3)))
						return false;
				} return true;
				break;
			case down:
				for (int i = 0; i < 4; i++)
				{
					if (getWorld()->dirtAlive((x + i), (y)))
						return false;
				} return true;
				break;
			}
		
	}
	
	return false;
}

void Protester::decreaseHealth(int x)
{
	health = health - x;
}

int Protester::getHealth()
{
	return health;
}

void Protester::setHealth(int x)
{
	health = x;
}

void Protester::setProtesterState(Protesterstate x)
{
	p_state = x;
}

Protester::Protesterstate Protester::getProt_State()
{
	return p_state;
}

int Protester::calculateSquarestoMove()
{
    srand(time(NULL));
    int random = rand() % 52+8;
//	cout << "random number:: " << random << endl;
    return random;
}

void Protester::resetSquarestoMove()
{
	squareToMoveinDir = 0;
}

int Protester::getSquaresToMove()
{
	return squareToMoveinDir;
}

void Protester::setSquarestoMove()
{
	squareToMoveinDir = calculateSquarestoMove();
}

void Protester::decreaseSquaresToMove()
{
	squareToMoveinDir--;
}

void Protester::resetCounterTicks()
{
	counterTicksRest = ticksToWait;
}

void Protester::decreaseCounterTicks()
{
	counterTicksRest--;
}

int Protester::getCounterTicks()
{
	return counterTicksRest;
}

int Protester::getCounterNoRestTicks()
{
	return counterNoRestTicks;
}

void Protester::decreaseCounterNoRest()
{
	counterNoRestTicks--;
}

void Protester::resetCounterNoRest()
{
	counterNoRestTicks = 15;
}


Protester::Direction Protester::PlayerPosition(int x, int y)
{
	if (((x - ((getWorld()->getPlayer()->getX() + 3))) == 1) || ((x - ((getWorld()->getPlayer()->getX() + 3))) == 0))
		return left;
	else if ((((x + 3) - (getWorld()->getPlayer()->getX())) == -1)|| (((x + 3) - (getWorld()->getPlayer()->getX())) == -0))
		return right;
	else if (((y - ((getWorld()->getPlayer()->getY() + 3))) == 1)|| ((y - ((getWorld()->getPlayer()->getY() + 3))) == 0))
		return down;
	else if ((((y + 3) - (getWorld()->getPlayer()->getY())) == -1)|| (((y + 3) - (getWorld()->getPlayer()->getY())) == 0))
		return up;
    
    return left;

}

Protester::Direction Protester::getNewDirection()
{
	bool moveApproved = false;
	srand(time(NULL));
	while (!moveApproved)
	{
		int random = rand() % 4 + 1;
		//cout << "random number:: " << random << endl;
		switch (random)
		{
		case 1:    //left
			//cout << "left" << endl;
			if (AllowMove((getX() - 1), getY(), left))
			{
			  //  cout << "left" << endl;
				moveApproved = true;
				return left;
			}
			break;
		case 2:	//right
			//cout << "right" << endl;
			if (AllowMove((getX() + 1), getY(), right))
			{
			//	cout << "right" << endl;
				moveApproved = true;
				return right;
			}
			break;
		case 3:   //up
			
			//cout << "up" << endl;
			if (AllowMove(getX(), (getY()+1),up))
			{
				//cout << "up" << endl;
				moveApproved = true;
				return up;
			}
			break;
		case 4:  //down
			//cout << "down" << endl;
			if (AllowMove(getX(), (getY() - 1),down))
			{
			//	cout << "down" << endl;
				moveApproved = true;
				return down;
			}
			break;

		}
	}
	return GraphObject::none;
}

bool Protester::FollowPlayer()
{
	
	//check if the player is on the same X positions
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
		if ((getX() + i) == ((getWorld()->getPlayer()->getX() + j)))
		{
			//its in one of the X coord of the protester!
			if (RadiusFromPlayer() > 4.0) //its far from 4 units
			{
				if ((abs(getY() - getWorld()->getPlayer()->getY())) < squareToMoveinDir) // if the protester can reach the player with his squares to move
				{
					//it is above or below???
					if (getY() > getWorld()->getPlayer()->getY())
					{
						// it is below!!
						if (CheckIfPathIsEmpty(getX(), (getWorld()->getPlayer()->getY() + 4), getX(), getY()))
						{
						//	cout << "below path clear!!" << endl;
							setDirection(down);
							moveTo(getX(), (getY() - 1));
							return true;
						}
					}
					else  //it is up
					{
						if (CheckIfPathIsEmpty(getX(), (getY() + 4), getX(), getWorld()->getPlayer()->getY()))
						{
						//	cout << "up path clear!!" << endl;
							setDirection(up);
							moveTo(getX(), (getY() + 1));
							return true;
						}
					}
				}
			}

		}
		}
	}
	//check for Ys
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j < 4; j++)
		{

			if ((getY() + i) == ((getWorld()->getPlayer()->getY()) + j))
			{
				//its in one of the X coord of the protester!
				if (RadiusFromPlayer() > 4.0) //its far from 4 units
				{
					if ((abs(getX() - getWorld()->getPlayer()->getX())) < squareToMoveinDir)
					{
						//it is right or left???
						if (getX() > getWorld()->getPlayer()->getX())
						{
							// it is on the left!!
							if (CheckIfPathIsEmpty((getWorld()->getPlayer()->getX() + 4), getY(), getX(), getY()))
							{
							//	cout << "left path clear!!" << endl;
								setDirection(left);
								moveTo((getX()-1), getY());
								return true;
							}
						}
						else  //it is at right
						{
							if (CheckIfPathIsEmpty((getX() + 4), getY(), getWorld()->getPlayer()->getX(), getY()))
							{
							//	cout << "right path clear!!" << endl;
								setDirection(right);
								moveTo((getX() + 1), getY());
								return true;
							}
						}
					}
				}
			}
		}
	}
	
	return false;
}

//the second set of x.y has to be the greatest
bool Protester::CheckIfPathIsEmpty(int x1, int y1, int x2, int y2)
{
	if (x1 == x2)
	{
		//its on a vertical sight
		for (int i = y1; i < y2; i++)
		{
			if (HittingSomething2(x1, i) == boulder)
				return false;

			for (int j = 0; j < 4; j++)
			{
				if (getWorld()->dirtAlive(((x1)+j), i))
					return false;
			}
		}
		return true;

	}
	else if (y1 == y2)
	{
		//its on a horizontal sight
		for (int i = x1; i < x2; i++)
		{
			if (HittingSomething2(i, y1) == boulder)
				return false;

			for (int j = 0; j < 4; j++)
			{
				if (getWorld()->dirtAlive(i, ((y1)+j)))
					return false;
			}
		}
		return true;
	}
	//cout << "wrong coordenates!!!" << endl;
	return false;
}

int Protester::getPerpMovements()
{
	return perpendicularMovements;
}

void Protester::decreasePerpMovements()
{
	perpendicularMovements--;
}

void Protester::setPerpMovements()
{
	perpendicularMovements=0;
}

void Protester::ActivatePerpMovement()
{
	perpendicularMovements=200;
}

void Protester::setTicksToWait(int x)
{
	ticksToWait = x;
}

void Protester::setCounterNoRestTicks(int x)
{
	counterNoRestTicks = x;
}

void Protester::setCounterTicksRest(int x)
{
	counterTicksRest = x;
}

void Protester::bfs(int x, int y){
    struct node;
    typedef shared_ptr<node> upNode;
    struct node{
        int xco;
        int yco;
        upNode up = nullptr;
        upNode right = nullptr;
        upNode left = nullptr;
        upNode down = nullptr;
        bool visited = false;
        bool path = false;
    };
    queue<upNode> q; //travel
    //vector<node*> visited; //nodes visited
    
    upNode head(new node); //initializes the first node position of protester
    
    head->xco = getX();
    head->yco = getY();
    q.push(head);
    
    upNode guess(new node);

    while(!q.empty()){
        guess = q.front();
        q.pop();
        //visited.push_back(guess);
        
        if (guess == nullptr)
            continue;
        if (guess->xco == x && guess->yco == y){ //once destination is found return;
            q.pop();
            break;
        }
//        if(getWorld()->dirtAlive(guess->xco, guess->yco+1) == true && find(visited.begin(), visited.end(), guess->up) != visited.end() == false){
//        if(getWorld()->dirtAlive(guess->xco, (guess->yco)+1) == false && guess->path == false){
            if(AllowMove(guess->xco, guess->yco+1, up) == true && guess->path == false){ //up
            upNode newGuess(new node);
            newGuess->xco = guess->xco;
            newGuess->yco = guess->yco + 1;
            guess->path = true;
            guess->up = newGuess;
            q.push(newGuess);
            //cout << "up node" << endl;
        }
//        if(getWorld()->dirtAlive(guess->xco+1, guess->yco) == false && guess->path == false){
        if(AllowMove(guess->xco+1, guess->yco, right) == true && guess->path == false){ //right
            upNode newGuess(new node);
            newGuess->xco = guess->xco+1;
            newGuess->yco = guess->yco;
            guess->path = true;
            guess->right = newGuess;
            q.push(newGuess);
            //cout << "right node" << endl;
        }
//        if(getWorld()->dirtAlive(guess->xco-1, guess->yco) == false && guess->path == false){
        if(AllowMove(guess->xco-1, guess->yco, left) == true && guess->path == false){ //left

            upNode newGuess(new node);
            newGuess->xco = guess->xco-1;
            newGuess->yco = guess->yco;
            guess->path = true;
            guess->left = newGuess;
            q.push(newGuess);
            //cout << "left node" << endl;
        }
//        if(getWorld()->dirtAlive(guess->xco, guess->yco-1) == false && guess->path == false){
        if(AllowMove(guess->xco, guess->yco-1, down) == true && guess->path == false){ //down

            upNode newGuess(new node);
            newGuess->xco = guess->xco;
            newGuess->yco = guess->yco-1;
            guess->path = true;
            guess->down = newGuess;
            q.push(newGuess);
            //cout << "down node" << endl;
        }
    }
    
    deque<upNode> correctPath;
    head->visited = true;
    correctPath.push_back(head);
    
    while(head->xco != x || head->yco != y)
    {
        if(head->up != nullptr && head->up->visited == false){
            head->up->visited = true;
            head = head->up;
            correctPath.push_back(head);
        }
        else if(head->right != nullptr && head->right->visited == false){
                head->right->visited = true;
                head = head->right;
                correctPath.push_back(head);
            }
        else if(head->left != nullptr && head->left->visited == false){
                head->left->visited = true;
                head = head->left;
                correctPath.push_back(head);
            }
        else if(head->down != nullptr && head->left->visited == false){
                head->down->visited = true;
                head = head->down;
                correctPath.push_back(head);
            }
        else correctPath.pop_back();
        
    }
    int resultX = correctPath[1]->xco;
    int resultY = correctPath[1]->yco;

    moveTo(resultX, resultY);
   // cout << "protester move" << endl;

}

/* old reg protester functions

//**********************************************************************
//********** REGULAR PROTESTER FUNCTIONS *******************************
//**********************************************************************

void RegProtester::doSomething()
{
switch (getProt_State())
{
case moving:
//cout << "its on moving state" << endl;
if (getCounterNoRestTicks() == 0)  //hasnt yell at the diggerman
{
if (getPerpMovements() > 0)
decreasePerpMovements();
//if ((HittingPlayer(getX(), getY()) == 1)|| (HittingPlayer(getX(), getY()) == 0)) //diggerman is on the edge or touching the protester
if (RadiusFromPlayer() <= 4)
{
//getWorld()->playSound(SOUND_PROTESTER_YELL);
////cout << "annoying diggerman" << endl;
//resetCounterNoRest(); //starts the counternorestTicks to 15
switch (PlayerPosition(getX(), getY())) //find to where the player is facing
{
case up:
cout << "its is coming from up" << endl;
if (getDirection() == up) // if the protester is facing up
{
getWorld()->playSound(SOUND_PROTESTER_YELL);
resetCounterNoRest();
}
break;
case down:
cout << "its is coming from down" << endl;
if (getDirection() == down) // if the protester is facing down
{
getWorld()->playSound(SOUND_PROTESTER_YELL);
resetCounterNoRest();
}
break;
case left:
cout << "its is coming from left" << endl;
if (getDirection() == left) // if the protester is facing left
{
getWorld()->playSound(SOUND_PROTESTER_YELL);
resetCounterNoRest();
}
break;
case right:
cout << "its is coming from right" << endl;
if (getDirection() == right) // if the protester is facing right
{
getWorld()->playSound(SOUND_PROTESTER_YELL);
resetCounterNoRest();
}
break;
}

//ANNOY THE DIGGERMAN
}

else
{
if (FollowPlayer())// if its watching the player
{
cout << "success" << endl;
//resetSquarestoMove();
setSquarestoMove(); //set squarestomove to zero
}
else
{
if (getSquaresToMove() > 0)  // there is still N chances to move
{
decreaseSquaresToMove();
switch (getDirection())
{
case up:
if (AllowMove(getX(), (getY() + 1),up))
moveTo(getX(), getY() + 1);
else  // its either in fron of a boulder or on an intersection
{
//check perpendicular movement
if (getPerpMovements() == 0) //perpendicular movement is allowed
{
if (AllowMove(getX() - 1, getY(), left))
if (AllowMove(getX() + 1, getY(), right)) //both available
{
srand(time(NULL));
int random = rand() % 2 + 1;
switch (random)
{
case 1: //left
setDirection(left);
moveTo(getX() - 1, getY());
ActivatePerpMovement();
break;
case 2: // to the right
setDirection(right);
moveTo(getX() + 1, getY());
ActivatePerpMovement();
break;
}

}
else // only left is available
{
setDirection(left);
moveTo(getX() - 1, getY());
ActivatePerpMovement();
}
else if (AllowMove(getX() + 1, getY(), right))
{
//only right available
setDirection(right);
moveTo(getX() + 1, getY());
ActivatePerpMovement();
}
else  //neither left nor right is available
{
resetSquarestoMove();
}
}
else
resetSquarestoMove(); //set squares to move to zero
}
break;
case down:
if (AllowMove(getX(), getY() - 1, down))
moveTo(getX(), getY() - 1);
else  // its either in fron of a boulder or on an intersection
{
//check perpendicular movement
if (getPerpMovements() == 0) //perpendicular movement is allowed
{
if (AllowMove(getX() - 1, getY(), left))
if (AllowMove(getX() + 1, getY(), right)) //both available
{
srand(time(NULL));
int random = rand() % 2 + 1;
switch (random)
{
case 1: //left
setDirection(left);
moveTo(getX() - 1, getY());
ActivatePerpMovement();
break;
case 2: // to the right
setDirection(right);
moveTo(getX() + 1, getY());
ActivatePerpMovement();
break;
}

}
else // only left is available
{
setDirection(left);
moveTo(getX() - 1, getY());
ActivatePerpMovement();
}
else if (AllowMove(getX() + 1, getY(), right))
{
//only right available
setDirection(right);
moveTo(getX() + 1, getY());
ActivatePerpMovement();
}
else  //neither left nor right is available
{
resetSquarestoMove();
}
}
else
resetSquarestoMove(); //set squares to move to zero
}

break;
case right:
if (AllowMove(getX() + 1, getY(), right))
moveTo(getX() + 1, getY());
else  // its either in fron of a boulder or on an intersection
{
//check perpendicular movement
if (getPerpMovements() == 0) //perpendicular movement is allowed
{
if (AllowMove(getX(), getY()-1, down))
if (AllowMove(getX(), getY()+1, up)) //both available
{
srand(time(NULL));
int random = rand() % 2 + 1;
switch (random)
{
case 1: //down
setDirection(down);
moveTo(getX(), getY()-1);
ActivatePerpMovement();
break;
case 2: // up
setDirection(up);
moveTo(getX(), getY()+1);
ActivatePerpMovement();
break;
}

}
else //only down
{
setDirection(down);
moveTo(getX() , getY()-1);
ActivatePerpMovement();
}
else if (AllowMove(getX(), getY()+1, up))
{
//only up available
setDirection(up);
moveTo(getX(), getY()+1);
ActivatePerpMovement();
}
else  //neither left nor right is available
{
resetSquarestoMove();
}
}
else
resetSquarestoMove(); //set squares to move to zero
}

break;
case left:
if (AllowMove(getX() - 1, getY(), left))
moveTo(getX() - 1, getY());
break;
}

}
else  //squarestoMove has reach 0
{
setSquarestoMove(); //reset the squarest to move
setDirection(getNewDirection());
}
}
}

}
else   // the counter is greater than 0
decreaseCounterNoRest();

setProtesterState(rest);
break;

case rest:
//cout << "Ticks Resting::" << getCounterTicks()<< endl;

decreaseCounterTicks();
if (getCounterTicks() == 0)
{
resetCounterTicks();
setProtesterState(moving);
}
break;

case leaveOil:
break;

}

}

bool RegProtester::AllowMove(int x, int y, Direction dir)
{

if ((x >= 0) && (x <= 60) && (y >= 0) && (y <= 60))
{
int i = IndexOfObjectWithinRadius(x, y);
if (i >= 0)
{
switch (getWorld()->getObject(i)->getName())
{
case boulder:
return false;
break;

}
//return false;
}
switch (dir)
{
case left:
cout << "LEFT" << endl;
for (int i = 0; i < 4; i++)
{
if (getWorld()->dirtAlive(x, (y + i)))
return false;
} return true;
break;
case right:
for (int i = 0; i < 4; i++)
{
if (getWorld()->dirtAlive((x + 3), (y + i)))
return false;
} return true;
break;
case up:
for (int i = 0; i < 4; i++)
{
if (getWorld()->dirtAlive((x + i), (y + 3)))
return false;
} return true;
break;
case down:
for (int i = 0; i < 4; i++)
{
if (getWorld()->dirtAlive((x + i), (y)))
return false;
} return true;
break;
}

}

return false;
}

void RegProtester::Initialize(StudentWorld * m_gw)
{
setWorld(m_gw);
health = 5;
//squareToMoveinDir = calculateSquarestoMove();
setSquarestoMove();
int calc = 3 - getWorld()->getLevel() / 4;
ticksToWait = max (0, calc);
//cout << "ticstowait  is equal to!!!" << ticksToWait << endl;
resetCounterTicks();
counterNoRestTicks = 0;
setPerpMovements();

}

void RegProtester::decreaseHealth(int x)
{
health = health - x;
}

int RegProtester::getHealth()
{
return health;
}

void RegProtester::setProtesterState(Protesterstate x)
{
p_state = x;
}

RegProtester::Protesterstate RegProtester::getProt_State()
{
return p_state;
}

int RegProtester::calculateSquarestoMove()
{
srand(time(NULL));
int random = rand() % 52+8;
cout << "random number:: " << random << endl;
return random;
}

void RegProtester::resetSquarestoMove()
{
squareToMoveinDir = 0;
}

int RegProtester::getSquaresToMove()
{
return squareToMoveinDir;
}

void RegProtester::setSquarestoMove()
{
squareToMoveinDir = calculateSquarestoMove();
}

void RegProtester::decreaseSquaresToMove()
{
squareToMoveinDir--;
}

void RegProtester::resetCounterTicks()
{
counterTicksRest = ticksToWait;
}

void RegProtester::decreaseCounterTicks()
{
counterTicksRest--;
}

int RegProtester::getCounterTicks()
{
return counterTicksRest;
}

int RegProtester::getCounterNoRestTicks()
{
return counterNoRestTicks;
}

void RegProtester::decreaseCounterNoRest()
{
counterNoRestTicks--;
}

void RegProtester::resetCounterNoRest()
{
counterNoRestTicks = 15;
}

void RegProtester::GetAnnoyed(int x)
{
if (x == 2) //hitted by squirt
{
getWorld()->increaseScore(100);
setProtesterState(rest);
int calc = 100 - getWorld()->getLevel() * 10;
counterTicksRest = max(50, calc);

}
else if (x==50) // by a boulder
getWorld()->increaseScore(500);
else if (x == 100) //by a gold nugget
{
getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
getWorld()->increaseScore(100);
setVisible(false);
setState(dead); //CHANGE FOR STATE LEAVE OIL
}

decreaseHealth(x);
if (getHealth() <= 0 && getState()==alive)
{
setVisible(false);
setState(dead); //CHANGE FOR STATE LEAVE OIL
getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
counterTicksRest = 0;
}
else
getWorld()->playSound(SOUND_PROTESTER_ANNOYED);

}

RegProtester::Direction RegProtester::PlayerPosition(int x, int y)
{
if (((x - ((getWorld()->getPlayer()->getX() + 3))) == 1) || ((x - ((getWorld()->getPlayer()->getX() + 3))) == 0))
return left;
else if ((((x + 3) - (getWorld()->getPlayer()->getX())) == -1)|| (((x + 3) - (getWorld()->getPlayer()->getX())) == -0))
return right;
else if (((y - ((getWorld()->getPlayer()->getY() + 3))) == 1)|| ((y - ((getWorld()->getPlayer()->getY() + 3))) == 0))
return down;
else if ((((y + 3) - (getWorld()->getPlayer()->getY())) == -1)|| (((y + 3) - (getWorld()->getPlayer()->getY())) == 0))
return up;

return left;

}

RegProtester::Direction RegProtester::getNewDirection()
{
bool moveApproved = false;
srand(time(NULL));
while (!moveApproved)
{
int random = rand() % 4 + 1;
cout << "random number:: " << random << endl;
switch (random)
{
case 1:    //left
cout << "left" << endl;
if (AllowMove((getX() - 1), getY(), left))
{
cout << "left" << endl;
moveApproved = true;
return left;
}
break;
case 2:	//right
//cout << "right" << endl;
if (AllowMove((getX() + 1), getY(), right))
{
cout << "right" << endl;
moveApproved = true;
return right;
}
break;
case 3:   //up

//cout << "up" << endl;
if (AllowMove(getX(), (getY()+1),up))
{
cout << "up" << endl;
moveApproved = true;
return up;
}
break;
case 4:  //down
//cout << "down" << endl;
if (AllowMove(getX(), (getY() - 1),down))
{
cout << "down" << endl;
moveApproved = true;
return down;
}
break;

}
}
return GraphObject::none;
}

bool RegProtester::FollowPlayer()
{

//check if the player is on the same X positions
for (int i = 0; i < 4; i++)
{
for (int j = 0; j < 4; j++)
{
if ((getX() + i) == ((getWorld()->getPlayer()->getX() + j)))
{
//its in one of the X coord of the protester!
if (RadiusFromPlayer() > 4.0) //its far from 4 units
{
if ((abs(getY() - getWorld()->getPlayer()->getY())) < squareToMoveinDir) // if the protester can reach the player with his squares to move
{
//it is above or below???
if (getY() > getWorld()->getPlayer()->getY())
{
// it is below!!
if (CheckIfPathIsEmpty(getX(), (getWorld()->getPlayer()->getY() + 4), getX(), getY()))
{
cout << "below path clear!!" << endl;
setDirection(down);
moveTo(getX(), (getY() - 1));
return true;
}
}
else  //it is up
{
if (CheckIfPathIsEmpty(getX(), (getY() + 4), getX(), getWorld()->getPlayer()->getY()))
{
cout << "up path clear!!" << endl;
setDirection(up);
moveTo(getX(), (getY() + 1));
return true;
}
}
}
}

}
}
}
//check for Ys
for (int i = 0; i<4; i++)
{
for (int j = 0; j < 4; j++)
{

if ((getY() + i) == ((getWorld()->getPlayer()->getY()) + j))
{
//its in one of the X coord of the protester!
if (RadiusFromPlayer() > 4.0) //its far from 4 units
{
if ((abs(getX() - getWorld()->getPlayer()->getX())) < squareToMoveinDir)
{
//it is right or left???
if (getX() > getWorld()->getPlayer()->getX())
{
// it is on the left!!
if (CheckIfPathIsEmpty((getWorld()->getPlayer()->getX() + 4), getY(), getX(), getY()))
{
cout << "left path clear!!" << endl;
setDirection(left);
moveTo((getX()-1), getY());
return true;
}
}
else  //it is at right
{
if (CheckIfPathIsEmpty((getX() + 4), getY(), getWorld()->getPlayer()->getX(), getY()))
{
cout << "right path clear!!" << endl;
setDirection(right);
moveTo((getX() + 1), getY());
return true;
}
}
}
}
}
}
}

return false;
}

//the second set of x.y has to be the greatest
bool RegProtester::CheckIfPathIsEmpty(int x1, int y1, int x2, int y2)
{
if (x1 == x2)
{
//its on a vertical sight
for (int i = y1; i < y2; i++)
{
if (HittingSomething2(x1, i) == boulder)
return false;

for (int j = 0; j < 4; j++)
{
if (getWorld()->dirtAlive(((x1)+j), i))
return false;
}
}
return true;

}
else if (y1 == y2)
{
//its on a horizontal sight
for (int i = x1; i < x2; i++)
{
if (HittingSomething2(i, y1) == boulder)
return false;

for (int j = 0; j < 4; j++)
{
if (getWorld()->dirtAlive(i, ((y1)+j)))
return false;
}
}
return true;
}
cout << "wrong coordenates!!!" << endl;
return false;
}

int RegProtester::getPerpMovements()
{
return perpendicularMovements;
}

void RegProtester::decreasePerpMovements()
{
perpendicularMovements--;
}

void RegProtester::setPerpMovements()
{
perpendicularMovements=0;
}

void RegProtester::ActivatePerpMovement()
{
perpendicularMovements=200;
}


*/

// ******************************************
// ****** REGULAR PROTESTER FUNCTIONS *******
// ******************************************

void RegProtester::doSomething()
{
	
	switch (getProt_State())
	{
	case moving:
		//cout << "its on moving state" << endl;
		if (getCounterNoRestTicks() == 0)  //hasnt yell at the diggerman
		{
			if (getPerpMovements() > 0)
				decreasePerpMovements();
			//if ((HittingPlayer(getX(), getY()) == 1)|| (HittingPlayer(getX(), getY()) == 0)) //diggerman is on the edge or touching the protester
			if (RadiusFromPlayer() <= 4)
			{
				//getWorld()->playSound(SOUND_PROTESTER_YELL);
				////cout << "annoying diggerman" << endl;
				//resetCounterNoRest(); //starts the counternorestTicks to 15
				switch (PlayerPosition(getX(), getY())) //find to where the player is facing
				{
				case up:
					//cout << "its is coming from up" << endl;
					if (getDirection() == up) // if the protester is facing up
					{
						getWorld()->playSound(SOUND_PROTESTER_YELL);
						getWorld()->getPlayer()->GetAnnoyed(2);
						resetCounterNoRest();
					}
					break;
				case down:
					//cout << "its is coming from down" << endl;
					if (getDirection() == down) // if the protester is facing down
					{
						getWorld()->playSound(SOUND_PROTESTER_YELL);
						getWorld()->getPlayer()->GetAnnoyed(2);
						resetCounterNoRest();
					}
					break;
				case left:
				//	cout << "its is coming from left" << endl;
					if (getDirection() == left) // if the protester is facing left
					{
						getWorld()->playSound(SOUND_PROTESTER_YELL);
						getWorld()->getPlayer()->GetAnnoyed(2);
						resetCounterNoRest();
					}
					break;
				case right:
				//	cout << "its is coming from right" << endl;
					if (getDirection() == right) // if the protester is facing right
					{
						getWorld()->playSound(SOUND_PROTESTER_YELL);
						getWorld()->getPlayer()->GetAnnoyed(2);
						resetCounterNoRest();
					}
					break;
				}

				//ANNOY THE DIGGERMAN
			}

			else
			{
				if (FollowPlayer())// if its watching the player
				{
				//	cout << "success" << endl;
					//resetSquarestoMove();
					setSquarestoMove(); //set squarestomove to zero
				}
				else
				{
					if (getSquaresToMove() > 0)  // there is still N chances to move
					{
						decreaseSquaresToMove();
						switch (getDirection())
						{
						case up:
							if (AllowMove(getX(), (getY() + 1), up))
								moveTo(getX(), getY() + 1);
							else  // its either in fron of a boulder or on an intersection
							{
								//check perpendicular movement
								if (getPerpMovements() == 0) //perpendicular movement is allowed
								{
									if (AllowMove(getX() - 1, getY(), left))
										if (AllowMove(getX() + 1, getY(), right)) //both available
										{
											srand(time(NULL));
											int random = rand() % 2 + 1;
											switch (random)
											{
											case 1: //left
												setDirection(left);
												moveTo(getX() - 1, getY());
												ActivatePerpMovement();
												break;
											case 2: // to the right
												setDirection(right);
												moveTo(getX() + 1, getY());
												ActivatePerpMovement();
												break;
											}

										}
										else // only left is available
										{
											setDirection(left);
											moveTo(getX() - 1, getY());
											ActivatePerpMovement();
										}
									else if (AllowMove(getX() + 1, getY(), right))
									{
										//only right available
										setDirection(right);
										moveTo(getX() + 1, getY());
										ActivatePerpMovement();
									}
									else  //neither left nor right is available
									{
										resetSquarestoMove();
									}
								}
								else
									resetSquarestoMove(); //set squares to move to zero
							}
							break;
						case down:
							if (AllowMove(getX(), getY() - 1, down))
								moveTo(getX(), getY() - 1);
							else  // its either in fron of a boulder or on an intersection
							{
								//check perpendicular movement
								if (getPerpMovements() == 0) //perpendicular movement is allowed
								{
									if (AllowMove(getX() - 1, getY(), left))
										if (AllowMove(getX() + 1, getY(), right)) //both available
										{
											srand(time(NULL));
											int random = rand() % 2 + 1;
											switch (random)
											{
											case 1: //left
												setDirection(left);
												moveTo(getX() - 1, getY());
												ActivatePerpMovement();
												break;
											case 2: // to the right
												setDirection(right);
												moveTo(getX() + 1, getY());
												ActivatePerpMovement();
												break;
											}

										}
										else // only left is available
										{
											setDirection(left);
											moveTo(getX() - 1, getY());
											ActivatePerpMovement();
										}
									else if (AllowMove(getX() + 1, getY(), right))
									{
										//only right available
										setDirection(right);
										moveTo(getX() + 1, getY());
										ActivatePerpMovement();
									}
									else  //neither left nor right is available
									{
										resetSquarestoMove();
									}
								}
								else
									resetSquarestoMove(); //set squares to move to zero
							}

							break;
						case right:
							if (AllowMove(getX() + 1, getY(), right))
								moveTo(getX() + 1, getY());
							else  // its either in fron of a boulder or on an intersection
							{
								//check perpendicular movement
								if (getPerpMovements() == 0) //perpendicular movement is allowed
								{
									if (AllowMove(getX(), getY() - 1, down))
										if (AllowMove(getX(), getY() + 1, up)) //both available
										{
											srand(time(NULL));
											int random = rand() % 2 + 1;
											switch (random)
											{
											case 1: //down
												setDirection(down);
												moveTo(getX(), getY() - 1);
												ActivatePerpMovement();
												break;
											case 2: // up
												setDirection(up);
												moveTo(getX(), getY() + 1);
												ActivatePerpMovement();
												break;
											}

										}
										else //only down
										{
											setDirection(down);
											moveTo(getX(), getY() - 1);
											ActivatePerpMovement();
										}
									else if (AllowMove(getX(), getY() + 1, up))
									{
										//only up available
										setDirection(up);
										moveTo(getX(), getY() + 1);
										ActivatePerpMovement();
									}
									else  //neither left nor right is available
									{
										resetSquarestoMove();
									}
								}
								else
									resetSquarestoMove(); //set squares to move to zero
							}

							break;
						case left:
							if (AllowMove(getX() - 1, getY(), left))
								moveTo(getX() - 1, getY());
							break;
						}

					}
					else  //squarestoMove has reach 0
					{
						setSquarestoMove(); //reset the squarest to move
						setDirection(getNewDirection());
					}
				}
			}

		}
		else   // the counter is greater than 0
			decreaseCounterNoRest();

		setProtesterState(Protester::rest);
		break;

	case rest:
		//cout << "Ticks Resting::" << getCounterTicks()<< endl;

		decreaseCounterTicks();
		if (getCounterTicks() == 0)
		{
			resetCounterTicks();
			setProtesterState(Protester::moving);
		}
		break;


	case leaveOil:
		//bfs(60, 60);
		setState(dead);
		setVisible(false);
		break;

	}
}

void RegProtester::Initialize(StudentWorld * m_gw)
{
	setWorld(m_gw);
	setHealth(5);
	//squareToMoveinDir = calculateSquarestoMove();
	setSquarestoMove();
	int calc = 3 - getWorld()->getLevel() / 4;
	setTicksToWait(max(0, calc));
	//cout << "ticstowait  is equal to!!!" << ticksToWait << endl;
	resetCounterTicks();
	setCounterNoRestTicks(0);
	setPerpMovements();
}

void RegProtester::GetAnnoyed(int x)
{
	if (getProt_State() != Protester::leaveOil)
	{
		if (x == 2) //hitted by squirt
		{
			getWorld()->increaseScore(100);
			setProtesterState(Protester::rest);
			int calc = 100 - getWorld()->getLevel() * 10;
			setCounterTicksRest(max(50, calc));

		}
		else if (x == 50) // by a boulder
			getWorld()->increaseScore(500);
		else if (x == 100) //by a gold nugget
		{
			getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
			getWorld()->increaseScore(100);
			setProtesterState(Protester::leaveOil); //CHANGE FOR STATE LEAVE OIL
		}

		decreaseHealth(x);
		if (getHealth() <= 0 && getState() == alive && getProt_State() != Protester::leaveOil)
		{
			//setVisible(false);
			//setState(dead); //CHANGE FOR STATE LEAVE OIL
			setProtesterState(Protester::leaveOil);
			getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
			setCounterTicksRest(0);
		}
		else
			getWorld()->playSound(SOUND_PROTESTER_ANNOYED);
	}
}

// ******************************************
// ****** HARD PROTESTER FUNCTIONS *******
// ******************************************

void HardProtester::doSomething()
{
	if (getCountStaring() == 0) //if its not staring at gold
	{

		switch (getProt_State())
		{
		case moving:
			//cout << "its on moving state" << endl;
			if (getCounterNoRestTicks() == 0)  //hasnt yell at the diggerman
			{
				if (getPerpMovements() > 0)
					decreasePerpMovements();
				//if ((HittingPlayer(getX(), getY()) == 1)|| (HittingPlayer(getX(), getY()) == 0)) //diggerman is on the edge or touching the protester
				if (RadiusFromPlayer() <= 4)
				{
					//getWorld()->playSound(SOUND_PROTESTER_YELL);
					////cout << "annoying diggerman" << endl;
					//resetCounterNoRest(); //starts the counternorestTicks to 15
					switch (PlayerPosition(getX(), getY())) //find to where the player is facing
					{
					case up:
					//	cout << "its is coming from up" << endl;
						if (getDirection() == up) // if the protester is facing up
						{
							getWorld()->playSound(SOUND_PROTESTER_YELL);
							resetCounterNoRest();
						}
						break;
					case down:
					//	cout << "its is coming from down" << endl;
						if (getDirection() == down) // if the protester is facing down
						{
							getWorld()->playSound(SOUND_PROTESTER_YELL);
							resetCounterNoRest();
						}
						break;
					case left:
					//	cout << "its is coming from left" << endl;
						if (getDirection() == left) // if the protester is facing left
						{
							getWorld()->playSound(SOUND_PROTESTER_YELL);
							resetCounterNoRest();
						}
						break;
					case right:
					//	cout << "its is coming from right" << endl;
						if (getDirection() == right) // if the protester is facing right
						{
							getWorld()->playSound(SOUND_PROTESTER_YELL);
							resetCounterNoRest();
						}
						break;
					}

					//ANNOY THE DIGGERMAN
				}

				else
				{
					if (FollowPlayer())// if its watching the player
					{
						//cout << "success" << endl;
						//resetSquarestoMove();
						setSquarestoMove(); //set squarestomove to zero
					}
					else
					{
						if (getSquaresToMove() > 0)  // there is still N chances to move
						{
							decreaseSquaresToMove();
							switch (getDirection())
							{
							case up:
								if (AllowMove(getX(), (getY() + 1), up))
									moveTo(getX(), getY() + 1);
								else  // its either in fron of a boulder or on an intersection
								{
									//check perpendicular movement
									if (getPerpMovements() == 0) //perpendicular movement is allowed
									{
										if (AllowMove(getX() - 1, getY(), left))
											if (AllowMove(getX() + 1, getY(), right)) //both available
											{
												srand(time(NULL));
												int random = rand() % 2 + 1;
												switch (random)
												{
												case 1: //left
													setDirection(left);
													moveTo(getX() - 1, getY());
													ActivatePerpMovement();
													break;
												case 2: // to the right
													setDirection(right);
													moveTo(getX() + 1, getY());
													ActivatePerpMovement();
													break;
												}

											}
											else // only left is available
											{
												setDirection(left);
												moveTo(getX() - 1, getY());
												ActivatePerpMovement();
											}
										else if (AllowMove(getX() + 1, getY(), right))
										{
											//only right available
											setDirection(right);
											moveTo(getX() + 1, getY());
											ActivatePerpMovement();
										}
										else  //neither left nor right is available
										{
											resetSquarestoMove();
										}
									}
									else
										resetSquarestoMove(); //set squares to move to zero
								}
								break;
							case down:
								if (AllowMove(getX(), getY() - 1, down))
									moveTo(getX(), getY() - 1);
								else  // its either in fron of a boulder or on an intersection
								{
									//check perpendicular movement
									if (getPerpMovements() == 0) //perpendicular movement is allowed
									{
										if (AllowMove(getX() - 1, getY(), left))
											if (AllowMove(getX() + 1, getY(), right)) //both available
											{
												srand(time(NULL));
												int random = rand() % 2 + 1;
												switch (random)
												{
												case 1: //left
													setDirection(left);
													moveTo(getX() - 1, getY());
													ActivatePerpMovement();
													break;
												case 2: // to the right
													setDirection(right);
													moveTo(getX() + 1, getY());
													ActivatePerpMovement();
													break;
												}

											}
											else // only left is available
											{
												setDirection(left);
												moveTo(getX() - 1, getY());
												ActivatePerpMovement();
											}
										else if (AllowMove(getX() + 1, getY(), right))
										{
											//only right available
											setDirection(right);
											moveTo(getX() + 1, getY());
											ActivatePerpMovement();
										}
										else  //neither left nor right is available
										{
											resetSquarestoMove();
										}
									}
									else
										resetSquarestoMove(); //set squares to move to zero
								}

								break;
							case right:
								if (AllowMove(getX() + 1, getY(), right))
									moveTo(getX() + 1, getY());
								else  // its either in fron of a boulder or on an intersection
								{
									//check perpendicular movement
									if (getPerpMovements() == 0) //perpendicular movement is allowed
									{
										if (AllowMove(getX(), getY() - 1, down))
											if (AllowMove(getX(), getY() + 1, up)) //both available
											{
												srand(time(NULL));
												int random = rand() % 2 + 1;
												switch (random)
												{
												case 1: //down
													setDirection(down);
													moveTo(getX(), getY() - 1);
													ActivatePerpMovement();
													break;
												case 2: // up
													setDirection(up);
													moveTo(getX(), getY() + 1);
													ActivatePerpMovement();
													break;
												}

											}
											else //only down
											{
												setDirection(down);
												moveTo(getX(), getY() - 1);
												ActivatePerpMovement();
											}
										else if (AllowMove(getX(), getY() + 1, up))
										{
											//only up available
											setDirection(up);
											moveTo(getX(), getY() + 1);
											ActivatePerpMovement();
										}
										else  //neither left nor right is available
										{
											resetSquarestoMove();
										}
									}
									else
										resetSquarestoMove(); //set squares to move to zero
								}

								break;
							case left:
								if (AllowMove(getX() - 1, getY(), left))
									moveTo(getX() - 1, getY());
								break;
							}

						}
						else  //squarestoMove has reach 0
						{
							setSquarestoMove(); //reset the squarest to move
							setDirection(getNewDirection());
						}
					}
				}

			}
			else   // the counter is greater than 0
				decreaseCounterNoRest();

			setProtesterState(Protester::rest);
			break;

		case rest:
			//cout << "Ticks Resting::" << getCounterTicks()<< endl;

			decreaseCounterTicks();
			if (getCounterTicks() == 0)
			{
				resetCounterTicks();
				setProtesterState(Protester::moving);
			}
			break;

		case leaveOil:
			//bfs(60, 60);
			break;

		}
	}
	else  //it is looking at gold
	{
		decreaseStaring();
	}
    
    
}

void HardProtester::Initialize(StudentWorld * m_gw)
{
	setWorld(m_gw);
	setHealth(20);
	setSquarestoMove();
	int calc = 3 - getWorld()->getLevel() / 4;
	setTicksToWait(max(0, calc));
	resetCounterTicks();
	setCounterNoRestTicks(0);
	setPerpMovements();
	setCountStaring(0);
}

void HardProtester::GetAnnoyed(int x)
{
	if (getProt_State() != Protester::leaveOil)
	{
		if (x == 2) //hitted by squirt
		{
			getWorld()->increaseScore(250);
			setProtesterState(Protester::rest);
			int calc = 100 - getWorld()->getLevel() * 10;
			setCounterTicksRest(max(50, calc));
			decreaseHealth(x);
			if (getHealth() > 0)
				getWorld()->playSound(SOUND_PROTESTER_ANNOYED);

		}
		else if (x == 50) // by a boulder
		{
			getWorld()->increaseScore(500);
			decreaseHealth(x);
		}
		else if (x == 100) //by a gold nugget
		{
			getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
			getWorld()->increaseScore(50);
			activateStare(); //its going to start to look at the gold
		}

		//decreaseHealth(x);
		if (getHealth() <= 0 && getState() == alive)
		{
			//setVisible(false);
			//setState(dead); //CHANGE FOR STATE LEAVE OIL
			setProtesterState(Protester::leaveOil);
			getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
			setCounterTicksRest(0);
		}
	}

}

void HardProtester::activateStare()
{
	int calc = 100 - getWorld()->getLevel() * 100;
	setCountStaring(max(50, calc));
}

void HardProtester::decreaseStaring()
{
	countStaring--;
}

void HardProtester::setCountStaring(int x)
{
	countStaring = x;
}

int HardProtester::getCountStaring()
{
	return countStaring ;
}
