/*
 * File: basketball.h
 * Contributors:
 *   - Sophie Jackson
 *   - Nathaniel Atwood
 *
 * Most Recent Update:
 *   Added getPosition returning a point for color changing functionality
 *
 * Date of Most Recent Update:
 *   12/3/2024
 *
 * Description:
 *   Header file for each Basketball object. Tracks the position, and color of a basketball.
 *   Designed to be used in The Best Developers Education Application.
 */
#ifndef BASKETBALL_H
#define BASKETBALL_H

#include <QObject>
#include <QColor>

class Basketball : public QObject {
    Q_OBJECT
    // --------------------------------- Begin Basketball Fields ----------------------------------- //
private:
    int xPosition;      // x coordinate
    int yPosition;      // y coordinate
    QColor ballColor;   // color of the basketball
    // ---------------------------------- End Basketball Fields ------------------------------------ //

    // ---------------------- Begin Basketball Constructors and Destructors ------------------------ //
public:
    explicit Basketball(QObject *parent);
    explicit Basketball(int x, int y, QColor newColor);    // constructor for testing: manually input parameters
    Basketball(const Basketball & other);                                   // copy constructor
    // ----------------------- End Basketball Constructors and Destructors ------------------------- //

    // --------------------------------- Begin Basketball Methods ---------------------------------- //
public:
    int getX();                 // returns x position
    int getY();                 // returns y position
    QPoint getPosition() const; // returns position as a point
    QColor getColor() const;    // returns color of basketball
    void setPosition(int x, int y); //sets the x ,and y position of a basketball
    // ---------------------------------- End Basketball Methods ----------------------------------- //

    // --------------------------------- Begin Basketball Signals ---------------------------------- //
signals:
    // ---------------------------------- End Basketball Signals ----------------------------------- //

    // ---------------------------------- Begin Basketball Slots ----------------------------------- //
public slots:
    // ----------------------------------- End Basketball Slots ------------------------------------ //
};

#endif // BASKETBALL_H
