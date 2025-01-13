/*
 * File: flexboxlevel.cpp
 * Contributors:
 *   - Nathaniel Atwood
 *   - Sophie Jackson
 *   - Jadon Olson
 *
 * Most Recent Update:
 *      Updated to use web engine and current level for positions.
 *
 * Date of Most Recent Update:
 *   12/7/2024
 *
 * Description:
 *   Houses each level in its own class.
 *   Designed to be used in The Best Developers Education Application.
 */

#include "flexboxlevel.h"
#include "flexoption.h"

FlexboxLevel::FlexboxLevel() {
    // Constructor Implementation
}

FlexboxLevel:: FlexboxLevel(QVector<BasketballHoop*> hoops,
                            QVector<Basketball*> balls,
                            QVector<FlexOption*> options,
                            QVector<FlexOption*> solution,
                            QString levelHtmlPartOne,
                            QString levelHtmlPartThree,
                            QString levelDescription)   : hoops(hoops),
                                                          balls(balls),
                                                          flexOptions(options),
                                                          solutionVector(solution),
                                                          levelHtmlPartOne(levelHtmlPartOne),
                                                          levelHtmlPartThree(levelHtmlPartThree),
                                                          levelDescription(levelDescription) {

}

FlexboxLevel::~FlexboxLevel() {
    // Destructor implementation
}

void FlexboxLevel::moveBasketball() {
    //TODO: implement the moving of basketball
}

void FlexboxLevel::checkPosition() {
    //TODO: implement dis :)
}

QVector<BasketballHoop*> FlexboxLevel::getHoops() {
    return hoops;
}

QVector<Basketball*> FlexboxLevel::getBasketballs() {
    return balls;
}

QVector<FlexOption*> FlexboxLevel::getFlexOptions() {
    return flexOptions;
}

FlexboxLevel::FlexboxLevel(const FlexboxLevel& other) {
    //TODO: IMPLEMENT
}

QVector<FlexOption*> FlexboxLevel::getSolutions()
{
    return solutionVector;
}

// Returns a copy of the html
QString FlexboxLevel::getLevelHtmlPartOne() {
    return this ->levelHtmlPartOne;
}

// Returns a copy of the html
QString FlexboxLevel::getLevelHtmlPartThree() {
    return this ->levelHtmlPartThree;
}

void FlexboxLevel::updateBasketballs(QVector<QPoint> centers) {
    for (int i = 0; i < this->balls.count(); i++) {
        qDebug() << "Setting a ball to " << centers[i].x() << " and " << centers[i].y();
        this->balls[i]->setPosition(centers[i].x(), centers[i].y());
    }
}

void FlexboxLevel::updateBasketballHoops(QVector<QPoint> centers) {
    for (int i = 0; i < this->hoops.count(); i++) {
        qDebug() << "Setting a hoop to " << centers[i].x() << " and " << centers[i].y();
        this->hoops[i]->setPosition(centers[i].x(), centers[i].y());
    }
}

QString FlexboxLevel::getDescription() {
    return this->levelDescription;
}
