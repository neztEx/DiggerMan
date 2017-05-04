#include "Actor.h"
#include "StudentWorld.h"
//#include "GameWorld.h"

#include <iostream>

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
//testing github commit functions

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


void DiggerMan::setWorld(StudentWorld * gw)
{
    m_sw = gw; //this is to access the StudentWorld object
}

StudentWorld * DiggerMan::getWorld()
{
    return m_sw;
}


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




/*
 
	void Boulder::doSomething() {
 
 if (isVisible() == false) { //if boulder is dead we do nothing
 return;
 }
 if (stableState == true) {
 for (int i = 0; i < 4; i++) {
 if (StudentWorld.gameMap[getX() + i][getY() - 1]->isVisible() == true) //checks to see if the dirt under the rock is visible
 return;
 else {
 stableState = false;
 waitingState = true;
 }
 }
 }
 if (waitingState == true) {
 tickCounter++;
 if (tickCounter == 30) {
 waitingState = false;
 fallingState = true;
 return;
 }
 }
 if (fallingState == true) {
 moveTo(getX(), getY() - 1);
 }
 
 //sam will finish this code later today!
	}*/

void Squirt::doSomething()
{
    if (getTravel() > 0)
    {
        setVisible(true);
        switch (getDirection())
        {
            case up:
                moveTo(getX(), getY() + 1);
                break;
            case down:
                moveTo(getX(), getY() - 1);
                break;
            case right:
                moveTo(getX() + 1, getY());
                break;
            case left:
                moveTo(getX() - 1, getY());
                break;
        }
        reduceTravel();
    }
    else
    {
        setVisible(false);
    }
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

void BaseObject::doSomething()
{
}
