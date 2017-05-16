#include "Actor.h"
#include "StudentWorld.h"
#include <algorithm>
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



void BaseObject::setWorld(StudentWorld * gw)
{
	m_sw = gw; //this is to access the StudentWorld object
}

StudentWorld * BaseObject::getWorld()
{
	return m_sw;
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


				break;
			}
            case KEY_PRESS_TAB:
                break;
            case KEY_PRESS_ESCAPE:
                break;
            case 90:   // if press 'Z'
                break;
            case 122: // if press 'z'
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
    
}

bool DiggerMan::HitPlayer(int x, int y)
{
	//if radious is from the edges:
	//if ((getX()-3)
	
	return false;
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

void WaterPool::doSomething()
{
	if ( getTickCounter()<= T) //if the number of ticks is still less than the max ticks for this level
	{
		addCounter();
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
	T = max(100, 300 - 10 * 1); //subs 1 for the current level: getWorld()->getCurrentLevel();

}

void WaterPool::addCounter()
{
	tickCounter++;
}

int WaterPool::getTickCounter()
{
	return tickCounter;
}


