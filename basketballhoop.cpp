/*
 * File: baskeballhoop.cpp
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
 *   Header file for each FlexOption object. Tracks the values of each FlexOption.
 *   Designed to be used in The Best Developers Education Application.
 */

#include "basketballhoop.h"
#include <QPoint>

// -------------------- Begin Basketball Hoop Constructors and Destructors --------------------- //
BasketballHoop::BasketballHoop(QObject *parent) : QObject{parent} {}

BasketballHoop:: BasketballHoop(int x, int y, QColor color) {
    this->xPosition = x;
    this->yPosition = y;
    this->hoopColor = color;
}

BasketballHoop::BasketballHoop(const BasketballHoop & other){
    xPosition = other.xPosition;
    yPosition = other.yPosition;
    hoopColor = other.hoopColor;
}

// --------------------- End Basketball Hoop Constructors and Destructors ---------------------- //

// ------------------------------- Begin Basketball Hoop Methods ------------------------------- //
QColor BasketballHoop::getColor() const {
    return this->hoopColor;
}

QPoint BasketballHoop::getPosition() const {
    return QPoint(xPosition, yPosition);
}

void BasketballHoop::setPosition(int x, int y)
{
    xPosition = x;
    yPosition = y;
}
// -------------------------------- End Basketball Hoop Methods -------------------------------- //
