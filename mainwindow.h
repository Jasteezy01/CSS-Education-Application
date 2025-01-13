/*
 * File: mainwindow.h
 * Contributors:
 *   - Sophie Jackson
 *   - Nathaniel Atwood
 *
 * Most Recent Update:
 *   Comments updated
 *
 * Date of Most Recent Update:
 *   12/2/2024
 *
 * Description:
 *   Header file for the MainWindow class. Handles user input and output to and through the GUI.
 *   Designed to be used in The Best Developers Education Application.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "flexoption.h"
#include "flexboxmodel.h"
#include "court.h"
#include "congratulationswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    // -------------------------------- Begin Main Window Fields ----------------------------------- //
private:
    Ui::MainWindow *ui;
    FlexOption* currentOption;                  // Tracks current FlexOption selected
    QVector<FlexOption*> selectedOptions;       // Vector of selected options
    Court* court;                                // Court being drawn
    FlexboxModel* gameModel;
    CongratulationsWindow* levelCompleteScreen;
    // --------------------------------- End Main Window Fields ------------------------------------ //

    // --------------------- Begin Main Window Constructors and Destructors ------------------------ //
public:
    MainWindow(FlexboxModel &model, QWidget *parent = nullptr);     // Constructor
    ~MainWindow();                             // Destructor
    // ---------------------- End Main Window Constructors and Destructors ------------------------- //

    // -------------------------------- Begin Main Window Methods ---------------------------------- //
public:
    void setOptionLabels();
    // --------------------------------- End Main Window Methods ----------------------------------- //

    // -------------------------------- Begin Main Window Signals ---------------------------------- //
signals:
    void startGame();                          // Sent when game starts
    void loadGame();                           // Sent when load game is selection
    void styleOptionMoved();                   // Sent when FlexOption object is moved by user
    void updateOptionLabel(QString opt);
    void centerBasketball();
    void startButtonPressed();
    void centerOption();
    void resetCourt();
    void sendInputVector(QVector<FlexOption*>);
    // --------------------------------- End Main Window Signals ----------------------------------- //

    // --------------------------------- Begin Main Window Slots ----------------------------------- //
public slots:
    void addBasketBall();                      // Handles GUI functionality for adding a basketball
    void addHoop();                            // Handles GUI functionality for adding a hoop
    void addOption();                          // Handles GUI functionality for adding a style option
    void removeBasketBall();                   // Handles GUI functionality for removing a basketball
    void removeHoop();                         // Handles GUI functionality for removing a hoop
    void removeOption();                       // Handles GUI functionality for removing a style option
    void moveOption(int currentLayout,         // Handles GUI display for moving Style Options
    FlexOption* optionClicked);
    void nextLevel(); // for testing congratulations window
    void nextLevelClicked(); // dismisses congratulations window
    void updateGameLabel(bool);
    void clearPlanningBoard();
    void finalTurnComplete();                  // Received from flexboxmodel to signal end of game
    // ---------------------------------- End Main Window Slots ------------------------------------ //
private slots:
    void on_checkSolution_clicked();
};
#endif // MAINWINDOW_H
