/*
 * File: flexboxlevel.h
 * Contributors:
 *   - Sophie Jackson
 *   - Nathaniel Atwood
 *
 * Most Recent Update:
 *   Comments, added copy constructor
 *
 * Date of Most Recent Update:
 *   11/26/2024
 *
 * Description:
 *   Header file for each Flexbox Level object. Tracks if the user has passed the level or not.
 *   Designed to be used in The Best Developers Education Application.
 */
#ifndef FLEXBOXLEVEL_H
#define FLEXBOXLEVEL_H

#include "basketball.h"
#include "basketballhoop.h"
#include "flexoption.h"
#include "webgenius.h"
#include <QObject>
#include <QVector>

class FlexboxLevel : public QObject {
    Q_OBJECT
    // -------------------------------- Begin Flexbox Level Fields --------------------------------- //
private:
    QVector<BasketballHoop*> hoops;                         // Basketball Hoops in Level
    QVector<Basketball*> balls;                             // Basketballs in Level
    QVector<FlexOption*> flexOptions;                       // Flex Options in Level
    QVector<FlexOption*> solutionVector;                     // Level Solution to Check Against
    QString levelHtmlPartOne;
    QString levelHtmlPartThree;
    QString levelDescription;
    WebGenius james;                                       // Our BlackBox Web Renderer Facade
    // --------------------------------- End Flexbox Level Fields ---------------------------------- //

    // --------------------- Begin Flexbox Level Constructors and Destructors ---------------------- //
public:
    FlexboxLevel();                                        // Default Constructor
    FlexboxLevel(QVector<BasketballHoop*> hoops,
                 QVector<Basketball*> balls,
                 QVector<FlexOption*> flexOptions,
                 QVector<FlexOption*> solution,
                 QString levelHtmlPartOne,
                 QString levelHtmlPartThree,
                 QString levelDescription);
    ~FlexboxLevel();                                       // Destructor
    FlexboxLevel(const FlexboxLevel& other);               // Copy Constructor

    // ---------------------- End Flexbox Level Constructors and Destructors ----------------------- //

    // -------------------------------- Begin Flexbox Level Methods -------------------------------- //
public:
    void moveBasketball();                                 // Updates basketball postions
    void checkPosition();                                  // Checks positions against solution
    QVector<BasketballHoop*> getHoops();                    // Returns QVector of basketball hoops
    QVector<Basketball*> getBasketballs();                  // Returns QVector of basketballs
    QVector<FlexOption*> getFlexOptions();
    QString getLevelHtmlPartOne();
    QString getLevelHtmlPartThree();
    QVector<FlexOption*> getSolutions();
    void updateBasketballs(QVector<QPoint> centerPoints);
    void updateBasketballHoops(QVector<QPoint> centerPoints);
    QString getDescription();
    // --------------------------------- End Flexbox Level Methods --------------------------------- //

    // -------------------------------- Begin Flexbox Level Signals -------------------------------- //
signals:
    // --------------------------------- End Flexbox Level Signals --------------------------------- //

    // --------------------------------- Begin Flexbox Level Slots --------------------------------- //
public slots:
    // ---------------------------------- End Flexbox Level Slots ---------------------------------- //
};

#endif // FLEXBOXLEVEL_H
