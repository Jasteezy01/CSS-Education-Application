/*
 * File: mainwindow.cpp
 * Contributors:
 *   - Sophie Jackson
 *   - Nathaniel Atwood
 *   - Charles Wolfgramm
 *   - Jadon Olson
 *
 * Most Recent Update:
 *      Updated to use web engine and current level for positions.
 *
 * Date of Most Recent Update:
 *   12/7/2024
 *
 * Description:
 *   .cpp file for MainWindow. Handles UI of the Web Dev Educational game.
 *   Designed to be used in The Best Developers Education Application.
 */

#include "mainwindow.h"
#include "court.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(FlexboxModel &model, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->levelDisplay->show();

    gameModel = &model;
    QVBoxLayout* layout = new QVBoxLayout();
    Court* crt = new Court(model, this);
    layout->addWidget(crt); // Replace `Court` with your actual widget class
    ui->levelDisplay->setLayout(layout);

    // connect flex options
    connect(ui->option1, &FlexOption::clicked, this, &MainWindow::moveOption);
    connect(ui->option2, &FlexOption::clicked, this, &MainWindow::moveOption);
    connect(ui->option3, &FlexOption::clicked, this, &MainWindow::moveOption);

    // connect menu items
    // connect(ui->actionSave_Game, &QAction::triggered, this, &MainWindow::SaveGame); // Connects saving in the menu to save functionality
    // connect(ui->actionLoad_Game, &QAction::triggered, this, &MainWindow::LoadGame); // Connects loading in the menu to load functionality
    // connect(ui->actionNew_Game, &QAction::triggered, this, &MainWindow::NewGame); // Connects new game in the menu to new game functionality

    // connect buttons
    //connect(ui->addBasketBallBtn, &QAbstractButton::clicked, this, &MainWindow::addBasketBall);
    //connect(ui->setGravityCheck, &QCheckBox::toggled, crt, &Court::SetGravityState);
    //connect(this, &MainWindow::startButtonPressed, crt , &Court::startSimulation);
    //connect(this, &MainWindow::updateOptionLabel, ui->option1 , &FlexOption::updateOptionText);
    //connect(this, &MainWindow::centerBasketball, &model, &FlexboxModel::centerBasketball);
    //connect(this, &MainWindow::centerOption, crt, &Court::centerBasketball);
    setOptionLabels(); // sets the text of one option/ calls emit to change the text of each option.
    connect(&model, &FlexboxModel::displayGUIWin, this, &MainWindow::nextLevel); // TODO: this should NOT be connected  to this button: should be a separate check
    connect(&model, &FlexboxModel::finalTurnComplete, this, &MainWindow::finalTurnComplete);


    //When a solution is reached start simulation (MainWindow ->Model ->James -> Court - > MainWindow)

    connect(this, &MainWindow::sendInputVector, &model, &FlexboxModel::checkSolution);
    //Button clicked event is handled in void MainWindow::on_checkSolution_clicked() method

    //connection signifying if input received is correct
    connect(&model, &FlexboxModel::sendAnswerFlag, this, &MainWindow::updateGameLabel);
    //If input is incorrect, reset court
    //connect(&model, &FlexboxModel::resetCourt, crt, &Court::resetLevelState);

    //resets the court for next level
    connect(this, &MainWindow::resetCourt,&model, &FlexboxModel::setCourtForNextLevel);
    connect(&model, &FlexboxModel::resetOptionLayout, this, &MainWindow::clearPlanningBoard);
    //Send options to model for james to process

    //Set options depending on level

}



void MainWindow::updateGameLabel(bool state)
{
    if(state)
    {
        ui->gameStatusLabel->setText("CORRECT ENTRY!");
    }
    else
    {
        ui->gameStatusLabel->setText("INCORRECT ENTRY!");
    }

}

void MainWindow::setOptionLabels() {
    QVector<FlexOption*> modelOptions = gameModel->getFlexOptions();
    ui->option1->updateOptionText(modelOptions[0]->getOptionText());
    ui->option1->setText(modelOptions[0]->getOptionText());
    qDebug() << "set option 1 text to " << modelOptions[0]->getOptionText();

    ui->option2->updateOptionText(modelOptions[1]->getOptionText());
    ui->option2->setText(modelOptions[1]->getOptionText());
    qDebug() << "set option 2 text to " << modelOptions[1]->getOptionText();

    ui->option3->updateOptionText(modelOptions[2]->getOptionText());
    ui->option3->setText(modelOptions[2]->getOptionText());
    qDebug() << "set option 3 text to " << modelOptions[2]->getOptionText();

    // Set Level Description
    ui->levelDescriptionLabel->setText(gameModel->getLevelDescription());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::finalTurnComplete(){
    levelCompleteScreen = new CongratulationsWindow(true, this); // create a new congratulations window with the final level
    levelCompleteScreen->show();
    update();
}

void MainWindow::nextLevel() {
    levelCompleteScreen = new CongratulationsWindow(false, this);
    levelCompleteScreen->show();
    connect(levelCompleteScreen, &CongratulationsWindow::moveToNextLevel, this, &MainWindow::nextLevelClicked);
    update();
}

void MainWindow::nextLevelClicked(){
    qDebug() << "hiding";
    levelCompleteScreen->hide(); // called when next level is clicked from the congratulations screen: returns to game
    emit resetCourt();
}

void MainWindow::addBasketBall(){
    qDebug() << "added a nonexistant ball :)";

}
void MainWindow::addHoop(){

}
void MainWindow::addOption(){

}
void MainWindow::removeBasketBall(){

}
void MainWindow::removeHoop(){

}
void MainWindow::removeOption(){

}

void MainWindow::clearPlanningBoard()
{

    selectedOptions.clear();

    for (int i = 0; i < ui->inputLayout->count(); i++) {
        qDebug() << "In concatenate loop";
        QLayoutItem *item = ui->inputLayout->itemAt(i); // Get the layout item
        if (item->widget()) { // Ensure the item has a widget
            FlexOption *option = qobject_cast<FlexOption*>(item->widget()); // Cast to FlexOption
            if (option) { // Ensure the cast was successful
                ui->inputLayout->removeWidget(option);
                option->hide();
                ui->optionsLayout->addWidget(option);
                option->show();
                option->setCurrentLayout(1);
            }
        }
    }

    setOptionLabels();
}

void MainWindow::moveOption(int currentLayout, FlexOption* optionClicked){
    currentOption = optionClicked;
    if(currentLayout == 1){
        ui->optionsLayout->removeWidget(currentOption);
        currentOption->hide();
        ui->inputLayout->addWidget(currentOption);
        currentOption->show();
        currentOption->setCurrentLayout(2);
        //Extract code from moved option and put into webengine
    }
    else{
        ui->inputLayout->removeWidget(currentOption);
        currentOption->hide();
        ui->optionsLayout->addWidget(currentOption);
        currentOption->show();
        currentOption->setCurrentLayout(1);
        //Undo code that was added to webengine
    }
}


void MainWindow::on_checkSolution_clicked()
{
    //qDebug() << "Within checkSolution";
    //FlexOption currentOptionActual = *currentOption;
    //qDebug() << "Current Option: " << currentOptionActual.getOptionText();

    selectedOptions.clear();

    for (int i = 0; i < ui->inputLayout->count(); i++) {
        qDebug() << "In concatenate loop";
        QLayoutItem *item = ui->inputLayout->itemAt(i); // Get the layout item
        if (item->widget()) { // Ensure the item has a widget
            FlexOption *option = qobject_cast<FlexOption*>(item->widget()); // Cast to FlexOption
            if (option) { // Ensure the cast was successful
                selectedOptions.append(option);
            }
        }
    }

    emit sendInputVector(selectedOptions);
}
