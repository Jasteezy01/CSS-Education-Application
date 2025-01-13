/*
 * File: court.h
 * Contributors:
 *   - Sophie Jackson
 *   - Nathaniel Atwood
 *   - Charles Wolfgramm
 *
 * Most Recent Update:
 *   Added slot to allow drawing to begin when user clicks start button.
 *
 * Date of Most Recent Update:
 *   12/2/2024
 *
 * Description:
 *   Header file for each FlexOption object. Tracks the values of each FlexOption.
 *   Designed to be used in The Best Developers Education Application.
 */
#ifndef COURT_H
#define COURT_H

#include "flexboxmodel.h"
#include "flexoption.h"
#include <QGraphicsView>
#include <Box2D/Box2D.h>
#include <QColor>
#include <QVector>
#include <QTimer>
#include <QPainter>

class Court : public QWidget {
    Q_OBJECT
    // ------------------------------------ Begin Court Fields ------------------------------------- //
private:
    b2World world;                                          // Box2D World Object
    QVector<b2Body*> bodyVector;                            // Vector of Body ID's in World
    QVector<b2Body*> hoopCollisionVector;
    QVector<FlexOption> flexOptVector;                      // Vector of flexOptions
    QVector<QImage> imagesVector;                           // Vectors of QImages for painting
    QImage hoopImage;                                       // Image to draw hoop
    QImage BallImage;                                       // Image to draw a ball
    FlexboxModel* gameModel;                                // Holds info for updating court
    float courtWidth = 811.0f / 20.0f;                      // Converts from screen to Box2d
    float courtHeight = 511.0f / 20.0f;                     // Conversts from screne to Box2d
    bool gravityState = false;                              // Determines the state of gravity
    QTimer* updateTimer;                                    // Timer for updating world
    // ------------------------------------- End Court Fields -------------------------------------- //

    // ------------------------- Begin Court Constructors and Destructors -------------------------- //
public:
    Court(QWidget *parent = nullptr);                       // Default Constructor
    Court(FlexboxModel &model, QWidget *parent = nullptr);            // Constructor with Model
    // -------------------------- End Court Constructors and Destructors --------------------------- //

    // ------------------------------------ Begin Court Methods ------------------------------------ //
public:
    void paintEvent(QPaintEvent *);                         // Method QT looks for update frame
    void stepSimulation();                                  // Steps widget and box2D once

    void addHoops();

private:
    void addStaticBodies();                                 // Defines Court Boundaries in World
    void addDynamicBody(int posX, int posY);                // Defines ONE dynamic body in World
    void clearStaticBodies();
    void clearDynamicBodies();

    // ------------------------------------- End Court Methods ------------------------------------- //

    // ------------------------------------ Begin Court Signals ------------------------------------ //
signals:
    void collisonHappned();
    void JamesLookAtThis(QString data);
    void displayWin();
    // ------------------------------------- End Court Signals ------------------------------------- //

    // ------------------------------------- Begin Court Slots ------------------------------------- //
public slots:
    void SetGravityState(bool);
    void startSimulation();        // Starts movement on court
    void stopSimulation();         // Stops movement on court
    void jamesInputReceived();
    void centerBasketball();
    void stopCourt();
    void redrawStuff();

    // -------------------------------------- End Court Slots -------------------------------------- //
};

#endif // COURT_H
