/*
 * File: flexboxmodel.h
 * Contributors:
 *   - Sophie Jackson
 *   - Nathaniel Atwood
 *
 * Most Recent Update:
 *   Updated getBasketballs for testing
 *
 * Date of Most Recent Update:
 *   12/3/2024
 *
 * Description:
 *   Header file for the Flexbox Model. This model will keep track of the state of the game
 *   including the web rendering, and Box2D graphics.
 */
#ifndef FLEXBOXMODEL_H
#define FLEXBOXMODEL_H

#include <QObject>
#include "webgenius.h"
#include "flexoption.h"

class FlexboxLevel;
class BasketballHoop;
class Basketball;

class FlexboxModel : public QObject {
    Q_OBJECT
    // -------------------------------- Begin Flexbox Model Fields --------------------------------- //
private:
    QVector<FlexboxLevel*> levels;                          // Holds Levels Collection for Game.
    int currentLevel;        // Tracks current level user is at
    QString input;
    WebGenius james;                                       // Handles web rendering
    // --------------------------------- End Flexbox Model Fields ---------------------------------- //

    // --------------------- Begin Flexbox Model Constructors and Destructors ---------------------- //
public:
    explicit FlexboxModel(QObject *parent = nullptr);      // Default Constructor
    FlexboxModel(int levelNumber);                         // Constructs model at specific level
    ~FlexboxModel();                                       // Destructs
    // ---------------------- End Flexbox Model Constructors and Destructors ----------------------- //

    // -------------------------------- Begin Flexbox Model Methods -------------------------------- //
public:
    void changeLevel();                                    // Changes level in model and view
    QVector<BasketballHoop*> getHoops();                   // Gets hoops
    QVector<Basketball*> getBasketballs();                  // Gets balls
    QVector<FlexOption*> getFlexOptions();
    QString getLevelHtmlPartOne();
    QString getLevelHtmlPartThree();
    void tellJamesToAnalyzeHtml(QString html);
    QString getLevelDescription();

private:
    void makeLevels();
    // --------------------------------- End Flexbox Model Methods --------------------------------- //

    // -------------------------------- Begin Flexbox Model Signals -------------------------------- //
signals:
    void endGame();                                        // Signal End (without crashing)
    void addElement();                                     // Adds Element to Preview Widget
    void changeElement();                                  // Changes Element in Preview Widget
    void sendAnswerFlag(bool);                             // Tells GUI gameState Label to change
    void resetCourtGravity();                                     //If solution is incorrect, reset court to start.
    void displayGUIWin();
    void updateCourt();
    void resetOptionLayout();
    void finalTurnComplete();                              // Tells GUI to draw the final congratulations screen
    // --------------------------------- End Flexbox Model Signals --------------------------------- //

    // --------------------------------- Begin Flexbox Model Slots --------------------------------- //
public slots:
    void startGame();                                      // Starts game in model and view
    void styleOptionMoved();                               // Updates preview with style options
    void updateFromJames();                                 // Updates the ball and hoops
    void checkSolution(QVector<FlexOption*> input);
    void displayWin();
    void setCourtForNextLevel();
    // ---------------------------------- End Flexbox Model Slots ---------------------------------- //
};

#endif // FLEXBOXMODEL_H
