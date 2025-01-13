/*
 * File: flexboxmodel.h
 * Contributors:
 *   - Nathaniel Atwood
 *
 * Most Recent Update:
 *   Created File Based on UML document
 *
 * Date of Most Recent Update:
 *   11/20/2024
 *
 * Description:
 *   Header file for the Flexbox Model. This model will keep track of the state of the game
 *   including the web rendering, and Box2D graphics.
 */
#ifndef FLEXBOXMODEL_H
#define FLEXBOXMODEL_H

#include "flexboxlevel.h"
#include <QObject>

class FlexboxModel : public QObject
{
    Q_OBJECT
    // -------------------------------- Begin Flexbox Model Fields --------------------------------- //
private:
    QVector<FlexboxLevel> levels;                          // Holds Levels Collection for Game.
    int currentLevel;                                      // Tracks current level user is at
    // --------------------------------- End Flexbox Model Fields ---------------------------------- //

    // --------------------- Begin Flexbox Model Constructors and Destructors ---------------------- //
public:
    explicit FlexboxModel(QObject *parent = nullptr);      // Default Constructor
    FlexboxModel(int levelNumber);                         // Constructs model at specific level
    ~FlexboxModel();                                       // Destructs
    // ---------------------- End Flexbox Model Constructors and Destructors ----------------------- //

    // -------------------------------- Begin Flexbox Model Methods -------------------------------- //
public:
    enum ColorOptions {green, blue, red, orange, magenta};
    void changeLevel();                                    // Changes level in model and view
    QMap<ColorOptions, QPoint> getHoopPositions();         // Gets positions of hoops
    QMap<ColorOptions, QPoint> getBallPositions();         // Gets positions of balls


    // --------------------------------- End Flexbox Model Methods --------------------------------- //

    // -------------------------------- Begin Flexbox Model Signals -------------------------------- //
signals:
    void endGame();                                        // Signal End (without crashing)
    void addElement();                                     // Adds Element to Preview Widget
    void changeElement();                                  // Changes Element in Preview Widget
    // --------------------------------- End Flexbox Model Signals --------------------------------- //

    // --------------------------------- Begin Flexbox Model Slots --------------------------------- //
public slots:
    void startGame();                                      // Starts game in model and view
    void styleOptionMoved();                               // Updates preview with style options
    void levelCleared();                                   // Advances level in model and view
    // ---------------------------------- End Flexbox Model Slots ---------------------------------- //
};

#endif // FLEXBOXMODEL_H
