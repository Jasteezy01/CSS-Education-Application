/*
 * File: basketballhoop.h
 * Contributors:
 *   - Sophie Jackson
 *   - Nathaniel Atwood
 *
 * Most Recent Update:
 *   Comments
 *
 * Date of Most Recent Update:
 *   12/2/2024
 *
 * Description:
 *   Header file for each BasketballHoop object. Tracks the position, and color of hoop.
 *   Designed to be used in The Best Developers Education Application.
 */
#ifndef BASKETBALLHOOP_H
#define BASKETBALLHOOP_H

#include <QObject>
#include <QColor>
#include "flexboxmodel.h"

class BasketballHoop : public QObject
{
    Q_OBJECT
    // ------------------------------- Begin Basketball Hoop Fields -------------------------------- //
private:
    int xPosition;      // x coordinate
    int yPosition;      // y coordinate
    QColor hoopColor;   // color of hoop
    // -------------------------------- End Basketball Hoop Fields --------------------------------- //

    // -------------------- Begin Basketball Hoop Constructors and Destructors --------------------- //
public:
    explicit BasketballHoop(QObject *parent = nullptr);
    BasketballHoop(int x, int y, QColor color);      // Creates new baskeball hoop with specified colors and position
    BasketballHoop(const BasketballHoop & other);    // Copy constructor
    // --------------------- End Basketball Hoop Constructors and Destructors ---------------------- //

    // ------------------------------- Begin Basketball Hoop Methods ------------------------------- //
public:
    QPoint getPosition() const;     // returns basketball's position as a QPoint
    QColor getColor() const;        // returns basketball's color as a QColor
    void setPosition(int x, int y); //sets the x ,and y position of a basketball hoop
    // -------------------------------- End Basketball Hoop Methods -------------------------------- //

    // ------------------------------- Begin Basketball Hoop Signals ------------------------------- //
signals:
    // -------------------------------- End Basketball Hoop Signals -------------------------------- //

    // -------------------------------- Begin Basketball Hoop Slots -------------------------------- //
public slots:
    // --------------------------------- End Basketball Hoop Slots --------------------------------- //
};

#endif // BASKETBALLHOOP_H
