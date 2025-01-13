/*
 * File: basketball.cpp
 * Contributors:
 *   - Sophie Jackson
 *   - Nathaniel Atwood
 *
 * Most Recent Update:
 *      Updated to use web engine and current level for positions.
 *
 * Date of Most Recent Update:
 *   12/7/2024
 *
 * Description:
 *   Implementation of the basketball.h file.
 *   Designed to be used in The Best Developers Education Application.
 */
#include "basketball.h"
#include "qpoint.h"

Basketball::Basketball(QObject *parent)
    : QObject{parent}
{}

Basketball::Basketball(int x, int y, QColor newColor) : xPosition(x), yPosition(y), ballColor(newColor)
{}

int Basketball::getX(){
    return xPosition;
}

int Basketball::getY(){
    return yPosition;
}

QPoint Basketball::getPosition() const{
    return QPoint(xPosition, yPosition);
}

QColor Basketball::getColor() const{
    return ballColor;
}

Basketball::Basketball(const Basketball &other){
    xPosition = other.xPosition;
    yPosition = other.yPosition;
    ballColor = other.ballColor;
}

void Basketball::setPosition(int x, int y)
{
    xPosition = x;
    yPosition = y;
}
