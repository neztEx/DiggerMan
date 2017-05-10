#include "Actor.h"
#include "StudentWorld.h"
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
                    if (AllowMove(getX() - 1, getY()))
                        moveTo(getX() - 1, getY());
                }
                else
                    setDirection(left);
                break;
                
            case KEY_PRESS_RIGHT:
                if (getDirection() == right)
                {
                    if (AllowMove(getX() + 1, getY()))
                        moveTo(getX() + 1, getY());
                }
                else
                    setDirection(right);
                break;
                
            case KEY_PRESS_UP:
                if (getDirection() == up)
                {
                    if (AllowMove(getX(), getY() + 1))
                        moveTo(getX(), getY() + 1);
                }
                else
                    setDirection(up);
                break;
                
            case KEY_PRESS_DOWN:
                if (getDirection() == down)
                {
                    if (AllowMove(getX(), getY() - 1))
                        moveTo(getX(), getY() - 1);
                }
                else
                    setDirection(down);
                break;
            case KEY_PRESS_SPACE:
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
                cout << "never gets here" << endl;
                getWorld()->insertObject(new Squirt(xS, yS, getDirection()));
				getWorld()->playSound(SOUND_PLAYER_SQUIRT);
		
                
                break;
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
bool DiggerMan::AllowMove(int x, int y)
{
    if ((x >= 0) && (x <= 60) && (y >= 0) && (y <= 60))
        return true;
    else
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
        cout << "stable" << endl;
        cout << "returns getWorld function: " << getWorld()->dirtAlive(getX(),getY() - 1) << endl;

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
        cout << "waiting" << endl;

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
            cout << "animate" << endl;
            return;
        }
        else
        {
            cout << "falling state is false" << endl;
            fallingState = false;
            stableState = true;
            tickCounter = 0;
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
        setVisible(true);
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
    }
}

bool Squirt::AllowMove(int x, int y)
{
	if ((x >= 0) && (x <= 60) && (y >= 0) && (y <= 60))
		return true;
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
