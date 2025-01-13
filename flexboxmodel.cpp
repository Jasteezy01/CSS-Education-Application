/*
 * File: flexboxmodel.cpp
 * Contributors:
 *   - Nathaniel Atwood
 *   - Sophie Jackson
 *
 * Most Recent Update:
 *      Updated to use web engine and current level for positions.
 *
 * Date of Most Recent Update:
 *   12/7/2024
 *
 * Description:
 *   Contains the Model for flexbox game.
 *   Designed to be used in The Best Developers Education Application.
 */
#include "flexboxmodel.h"
#include "flexboxlevel.h"
#include <QPoint>
#include <QMap>
#include <QTimer>
#include <QDebug>
#include <QtConcurrent/QtConcurrent>

FlexboxModel::FlexboxModel(QObject *parent) : QObject{parent}, input(""), currentLevel(4) {
    // Create Levels
    makeLevels();

    // Connect to the WebGenius analysisComplete signal
    connect(&james, &WebGenius::analysisComplete, this, &FlexboxModel::updateFromJames);
}

FlexboxModel::~FlexboxModel() {
    // Destructor implementation
}

void FlexboxModel::styleOptionMoved() {
    // Method implementation
}

void FlexboxModel::startGame() {
    // Method implementation
}

void FlexboxModel::checkSolution(QVector<FlexOption*> input)
{
    qDebug() << "Within checkSolution Slot, input: " << input;

    //WE'RE USING COPIES HERE
    QVector<FlexOption*> solution = levels[currentLevel]->getSolutions();
    qDebug() << "CURRENT SOLUTION: " << solution[0]->getOptionText();

    // Check Vector Sizes
    if (input.count() != solution.count()) {
        emit sendAnswerFlag(false);
        return;
    }

    //if input is correct!
    //throw options to james, and start simulation
    //if input is false :(
    //emit incorrect signal and reset court
    for(FlexOption* opt : input) {
        qDebug() << "IN FOR LOOP";

        // Check if input exists in solution
        bool winFlag = false;
        for (FlexOption* sol : solution) {
            if (opt->getOptionText() == sol->getOptionText()) {
                winFlag = true;
            }
        }

        // If input was not in solution
        if(!winFlag) {
            qDebug() << "Solution is Incorrect! :(";
            emit sendAnswerFlag(false);
            return;
        }
    }

    // Send stuff for james to proecess
    qDebug() << "Solution is correct! :)";
    emit sendAnswerFlag(true);


    //Concatenate Strings from Input Layout
    QString htmlPartTwo = "";
    for (FlexOption* opt : input) {
        htmlPartTwo.append(opt->getOptionText());
    }

    qDebug() << "This is part two: " << htmlPartTwo;

    // Concatenate full HTML
    QString inputHtml = "";
    inputHtml.append(getLevelHtmlPartOne());
    inputHtml.append(htmlPartTwo);
    inputHtml.append(getLevelHtmlPartThree());
    qDebug() << inputHtml;

    // Give James HTML to work on
    tellJamesToAnalyzeHtml(inputHtml);
}

void FlexboxModel::displayWin() {
    QTimer::singleShot(4000, this, [=](){emit displayGUIWin();});
}

void FlexboxModel::setCourtForNextLevel() {
    //Move onto next level
    if(currentLevel < this->levels.count() - 1) {
        currentLevel++;
        QVector<Basketball*> bucket;
        qDebug() <<"WE'RE IN LEVEL: " << currentLevel;

        //reset simulation of Court
        emit resetCourtGravity();
        emit resetOptionLayout();

        // Set balls
        bucket = levels[currentLevel]->getBasketballs();
        for(int i = 0; i < bucket.count(); i++) {
            bucket[i]->setPosition(50 + (i * 50), 0);
        }

    emit updateCourt();
    qDebug() << "After all that...";
    }
    else
    {
        emit finalTurnComplete();
    }
}

QVector<BasketballHoop*> FlexboxModel::getHoops() {
    return levels[currentLevel]->getHoops();
}

QVector<Basketball*> FlexboxModel::getBasketballs() {
    return levels[currentLevel]->getBasketballs();
}

QVector<FlexOption*> FlexboxModel::getFlexOptions() {
    return levels[currentLevel]->getFlexOptions();
}


QString FlexboxModel::getLevelHtmlPartOne(){
    return levels[currentLevel]->getLevelHtmlPartOne();
}

QString FlexboxModel::getLevelHtmlPartThree(){
    return levels[currentLevel]->getLevelHtmlPartThree();
}

void FlexboxModel::tellJamesToAnalyzeHtml(QString html) {
    james.analyzeHtml(html);
}

void FlexboxModel::updateFromJames() {
    qDebug()<< "#####################################################################################################";
    // Retrieve and log basketball center points once analysis is complete
    QVector<QPoint> pntVctr = james.getBasketballCenters();
    qDebug() << "Got the pntVctrBalls";
    for (const QPoint &point : pntVctr) {
        qDebug() << "Printing point from james: " << point;
    }

    QVector<QPoint> pntVctr2 = james.getBasketballHoopCenters();
    qDebug() << "Got the pntVctrHoops";
    for (const QPoint &point : pntVctr2) {
        qDebug() << "Printing point from james: " << point;
    }
    qDebug()<< "#####################################################################################################";

    // Update level balls
    levels[currentLevel]->updateBasketballs(james.getBasketballCenters());

    // Tell the court to update
    emit changeElement();
}

QString FlexboxModel::getLevelDescription() {
    return levels[currentLevel]->getDescription();
}

void FlexboxModel::makeLevels() {
    // ------------------------------------ Begin Level One ------------------------------------ //
    // Prep the level
    QVector<BasketballHoop*> basketballHoopsLevelOne;
    QVector<Basketball*> basketballsLevelOne;
    QVector<FlexOption*> levelOneSolution;

    // Add Basketball Hoops
    basketballHoopsLevelOne.append(new BasketballHoop(396, 145, QColor(255, 0, 0))); // Red

    // Add Basketballs
    basketballsLevelOne.append(new Basketball(100, 350, QColor(255, 0, 0))); // Red

    //Create solution for the level
    levelOneSolution.append(new FlexOption("justify-content: center;"));

    // Add level HTML
    QString levelOneHtmlPartOne = R"(
        <!DOCTYPE html>
        <html lang="en">
        <head>
          <meta charset="UTF-8">
          <meta name="viewport" content="width=811, height=511">
          <title>Red Boxes</title>
          <style>
            .container {
                height: 100vh;
                display: flex;
                flex-direction: row;
        )";

    // Insert Basketballs and Basketball Hoops between the <body> tags.
    QString levelOneHtmlPartThree = R"(
            }

            .basketball {
                width: 100px;
                height: 100px;
                background-color: red;
            }
          </style>
        </head>
        <body>
            <div class="container">
                <div class="basketball"></div>
            </div>
        </body>
        </html>
        )";

    QVector<FlexOption*> optionsLevelOne;
    optionsLevelOne.append(new FlexOption("justify-content: start;"));
    optionsLevelOne.append(new FlexOption("justify-content: center;"));
    optionsLevelOne.append(new FlexOption("justify-content: end;"));

    QString levelOneDescription = "This is level one. Select the correct justify-content settings to place the ball above the hoop";

    // Construct the level in the QVector
    FlexboxLevel* levelOne = new FlexboxLevel(basketballHoopsLevelOne, basketballsLevelOne, optionsLevelOne, levelOneSolution ,levelOneHtmlPartOne, levelOneHtmlPartThree, levelOneDescription);
    this->levels.append(levelOne);
    // ------------------------------------- End Level One ------------------------------------- //


    // ------------------------------------ Begin Level Two ------------------------------------ //
    // Prep the level
    QVector<BasketballHoop*> basketballHoopsLevelTwo;
    QVector<Basketball*> basketballsLevelTwo;
    QVector<FlexOption*> levelTwoSolution;

    // Add Basketball Hoops
    basketballHoopsLevelTwo.append(new BasketballHoop(270, 100, QColor(255, 0, 0))); // Red
    basketballHoopsLevelTwo.append(new BasketballHoop(570, 100, QColor(0, 255, 0))); // Blue

    // Add Basketballs
    basketballsLevelTwo.append(new Basketball(100, 350, QColor(255, 0, 0))); // Red
    basketballsLevelTwo.append(new Basketball(300, 350, QColor(0, 255, 0))); // Blue

    //Create solution to Level two;
    levelTwoSolution.append(new FlexOption("justify-content: space-around;"));

    // Add level HTML
    QString levelTwoHtmlPartOne = R"(
        <!DOCTYPE html>
        <html lang="en">
        <head>
          <meta charset="UTF-8">
          <meta name="viewport" content="width=811, height=511">
          <title>Red Boxes</title>
          <style>
            .container {
                height: 100vh;
                display: flex;
                flex-direction: row;
        )";

    // Insert Basketballs and Basketball Hoops between the <body> tags.
    QString levelTwoHtmlPartThree = R"(
            }

            .basketball {
                width: 100px;
                height: 100px;
                background-color: red;
            }

          </style>
        </head>
        <body>
            <div class="container">
                <div class="basketball"></div>
                <div class="basketball"></div>
            </div>
        </body>
        </html>
        )";

    QVector<FlexOption*> optionsLevelTwo;
    optionsLevelTwo.append(new FlexOption("justify-content: space-around;"));
    optionsLevelTwo.append(new FlexOption("justify-content: center;"));
    optionsLevelTwo.append(new FlexOption("justify-content: space-between;"));

    QString levelTwoDescription = "This is level two. Select the correct justify-content settings to place the ball above the hoop";

    // Construct the level in the QVector
    FlexboxLevel* levelTwo = new FlexboxLevel(basketballHoopsLevelTwo, basketballsLevelTwo, optionsLevelTwo, levelTwoSolution, levelTwoHtmlPartOne, levelTwoHtmlPartThree, levelTwoDescription);
    this->levels.append(levelTwo);
    // ------------------------------------- End Level Two ------------------------------------- //

    // ------------------------------------ Begin Level Three ------------------------------------ //
    // Prep the level
    QVector<BasketballHoop*> basketballHoopsLevelThree;
    QVector<Basketball*> basketballsLevelThree;
    QVector<FlexOption*> levelThreeSolution;

    // Add Basketball Hoops
    basketballHoopsLevelThree.append(new BasketballHoop(150, 200, QColor(255, 0, 0))); // Red
    basketballHoopsLevelThree.append(new BasketballHoop(250, 250, QColor(0, 255, 0))); // Blue
    basketballHoopsLevelThree.append(new BasketballHoop(350, 300, QColor(0, 0, 255))); // Blue

    // Add Basketballs
    basketballsLevelThree.append(new Basketball(100, 350, QColor(255, 0, 0))); // Red
    basketballsLevelThree.append(new Basketball(300, 350, QColor(0, 255, 0))); // Blue
    basketballsLevelThree.append(new Basketball(600, 350, QColor(0, 0, 255))); // Green

    //Create solution to Level Three;
    levelThreeSolution.append(new FlexOption("justify-content: start;"));

    // Add level HTML
    QString levelThreeHtmlPartOne = R"(
        <!DOCTYPE html>
        <html lang="en">
        <head>
          <meta charset="UTF-8">
          <meta name="viewport" content="width=811, height=511">
          <title>Red Boxes</title>
          <style>
            .container {
                height: 100vh;
                display: flex;
                flex-direction: row;
        )";

    // Insert Basketballs and Basketball Hoops between the <body> tags.
    QString levelThreeHtmlPartThree = R"(
            }

            .basketball {
                width: 100px;
                height: 100px;
                background-color: red;
            }

          </style>
        </head>
        <body>
            <div class="container">
                <div class="basketball"></div>
                <div class="basketball"></div>
                <div class="basketball"></div>
            </div>
        </body>
        </html>
        )";

    QVector<FlexOption*> optionsLevelThree;
    optionsLevelThree.append(new FlexOption("justify-content: space-around;"));
    optionsLevelThree.append(new FlexOption("justify-content: start;"));
    optionsLevelThree.append(new FlexOption("justify-content: space-between;"));

    QString levelThreeDescription = "This is level Three. Select the correct justify-content settings to place the ball above the hoop";

    // Construct the level in the QVector
    FlexboxLevel* levelThree = new FlexboxLevel(basketballHoopsLevelThree, basketballsLevelThree, optionsLevelThree, levelThreeSolution, levelThreeHtmlPartOne, levelThreeHtmlPartThree, levelThreeDescription);
    this->levels.append(levelThree);
    // ------------------------------------- End Level Three ------------------------------------- //

    // ------------------------------------ Begin Level Four ------------------------------------ //
    // Prep the level
    QVector<BasketballHoop*> basketballHoopsLevelFour;
    QVector<Basketball*> basketballsLevelFour;
    QVector<FlexOption*> levelFourSolution;

    // Add Basketball Hoops
    basketballHoopsLevelFour.append(new BasketballHoop(150, 300, QColor(255, 0, 0))); // Red
    basketballHoopsLevelFour.append(new BasketballHoop(150, 200, QColor(0, 255, 0))); // Green
    basketballHoopsLevelFour.append(new BasketballHoop(150, 100, QColor(0, 0, 255))); // Blue

    // Add Basketballs
    basketballsLevelFour.append(new Basketball(100, 350, QColor(255, 0, 0))); // Red
    basketballsLevelFour.append(new Basketball(200, 350, QColor(0, 255, 0))); // Green
    basketballsLevelFour.append(new Basketball(300, 350, QColor(0, 0, 255))); // Blue

    //Create solution for the level
    levelFourSolution.append(new FlexOption("flex-direction: column;"));
    levelFourSolution.append(new FlexOption("justify-content: start;"));

    // Add level HTML
    QString levelFourHtmlPartFour = R"(
        <!DOCTYPE html>
        <html lang="en">
        <head>
          <meta charset="UTF-8">
          <meta name="viewport" content="width=811, height=511">
          <title>Red Boxes</title>
          <style>
            .container {
                height: 100vh;
                display: flex;
        )";

    // Insert Basketballs and Basketball Hoops between the <body> tags.
    QString levelFourHtmlPartThree = R"(
            }

            .basketball {
                width: 100px;
                height: 100px;
                background-color: red;
            }
          </style>
        </head>
        <body>
            <div class="container">
                <div class="basketball"></div>
                <div class="basketball"></div>
                <div class="basketball"></div>
            </div>
        </body>
        </html>
        )";

    QVector<FlexOption*> optionsLevelFour;
    optionsLevelFour.append(new FlexOption("flex-direction: column;"));
    optionsLevelFour.append(new FlexOption("flex-direction: row;"));
    optionsLevelFour.append(new FlexOption("justify-content: start;"));

    QString levelFourDescription = "This is level Four. Select the correct justify-content settings to place the ball above the hoop. This level introduces a new FlexBox property called flex direction. This allow objects to be places on the screen vertically or horizontally.";

    // Construct the level in the QVector
    FlexboxLevel* levelFour = new FlexboxLevel(basketballHoopsLevelFour, basketballsLevelFour, optionsLevelFour, levelFourSolution ,levelFourHtmlPartFour, levelFourHtmlPartThree, levelFourDescription);
    this->levels.append(levelFour);
    // ------------------------------------- End Level Four ------------------------------------- //

    // ------------------------------------ Begin Level Five ------------------------------------ //
    // Prep the level
    QVector<BasketballHoop*> basketballHoopsLevelFive;
    QVector<Basketball*> basketballsLevelFive;
    QVector<FlexOption*> levelFiveSolution;

    // Add Basketball Hoops
    basketballHoopsLevelFive.append(new BasketballHoop(205, 300, QColor(255, 0, 0))); // Red
    basketballHoopsLevelFive.append(new BasketballHoop(410, 200, QColor(0, 255, 0))); // Green
    basketballHoopsLevelFive.append(new BasketballHoop(609, 100, QColor(0, 0, 255))); // Blue

    // Add Basketballs
    basketballsLevelFive.append(new Basketball(100, 50, QColor(255, 0, 0))); // Red
    basketballsLevelFive.append(new Basketball(200, 50, QColor(0, 255, 0))); // Green
    basketballsLevelFive.append(new Basketball(300, 50, QColor(0, 0, 255))); // Blue

    //Create solution for the level
    levelFiveSolution.append(new FlexOption("flex-direction: row;"));
    levelFiveSolution.append(new FlexOption("align-items: start;"));
    levelFiveSolution.append(new FlexOption("justify-content: space-around;"));


    // Add level HTML
    QString levelFiveHtmlPartOne = R"(
        <!DOCTYPE html>
        <html lang="en">
        <head>
          <meta charset="UTF-8">
          <meta name="viewport" content="width=811, height=511">
          <title>Red Boxes</title>
          <style>
            .container {
                height: 100vh;
                display: flex;
        )";

    // Insert Basketballs and Basketball Hoops between the <body> tags.
    QString levelFiveHtmlPartThree = R"(
            }

            .basketball {
                width: 100px;
                height: 100px;
                background-color: red;
            }
          </style>
        </head>
        <body>
            <div class="container">
                <div class="basketball"></div>
                <div class="basketball"></div>
                <div class="basketball"></div>
            </div>
        </body>
        </html>
        )";

    QVector<FlexOption*> optionsLevelFive;
    optionsLevelFive.append(new FlexOption("align-items: start;"));
    optionsLevelFive.append(new FlexOption("flex-direction: row;"));
    optionsLevelFive.append(new FlexOption("justify-content: space-around;"));

    QString levelFiveDescription = "This is level Five. Select the correct justify-content settings to place the ball above the hoop. This level introduces a new FlexBox property called flex direction. This allow objects to be places on the screen vertically or horizontally.";

    // Construct the level in the QVector
    FlexboxLevel* levelFive = new FlexboxLevel(basketballHoopsLevelFive, basketballsLevelFive, optionsLevelFive, levelFiveSolution ,levelFiveHtmlPartOne, levelFiveHtmlPartThree, levelFiveDescription);
    this->levels.append(levelFive);
    // ------------------------------------- End Level Five ------------------------------------- //
}
