/*
 * File: congratulationswindow.h
 * Contributors:
 *   - Sophie Jackson
 *
 * Most Recent Update:
 *   Code cleanup
 *
 *   Known bugs: need to get the actual level from the game model for displaying the final congrats message.
 *
 * Date of Most Recent Update:
 *   12/11/2024
 *
 * Description:
 *   Handles displaying a level complete screen inbetween levels.
 *   This class outlines the custom behavior for this congratulations window
 *   widget.
 *   Designed to be used in The Best Developers Education Application.
 *
 * Sources:
 *   https://kunalmaemo.blogspot.com/2010/11/animating-object-along-with-curve-in-qt.html
 *   Used to create a path for the basketballs to follow
 */

#include "congratulationswindow.h"
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QPropertyAnimation>
#include <QPainterPath>
#include <QRandomGenerator>
#include <QTimer>
#include <QTime>

CongratulationsWindow::CongratulationsWindow(bool finalLevel, QWidget *parent)
    : QWidget(parent){

    isFinalLevel = finalLevel;
    // basic setup
    this->setStyleSheet("background-color: rgba(0, 0, 0, 0.4)"); // mostly transparent: just an overlay. screen continues drawing behind this
    this->setFixedHeight(parent->height()); // full screen
    this->setFixedWidth(parent->width()); // full screen

    // set up layout
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // initialization
    basketballDrawingTimer = new QTimer();
    randomNum = new QRandomGenerator();
    maxIterations = 300;
    basketballIterations = 0;
    currentBasketball = 0;
    buttonsDrawn = false;

    // connections
    connect(basketballDrawingTimer, &QTimer::timeout, this, &CongratulationsWindow::drawBasketball);
    basketballDrawingTimer->start(100);
}

CongratulationsWindow::~CongratulationsWindow(){
    basketballDrawingTimer->stop();
    qDeleteAll(basketballImageVector);
    basketballImageVector.clear();
}

// ---------------------------------------------------------- overriden methods ----------------------------------------------------------
void CongratulationsWindow::paintEvent(QPaintEvent *){
    if(!isFinalLevel){
        basketballDrawingTimer->stop();
        if(buttonsDrawn)
            return;
        drawButtons();
    }
    else{
        QTimer::singleShot(10, this, [=](){
        drawButtons();});
    }
}

void CongratulationsWindow::mousePressEvent(QMouseEvent *event){
    if(isFinalLevel){
        basketballIterations = maxIterations;
        basketballDrawingTimer->stop();
        drawButtons();
    }
}

// ---------------------------------------------------------- helper methods ----------------------------------------------------------
void CongratulationsWindow::drawBasketball(){
    qDebug() << "calling draw basketball";
    // get randomly generated starting point
    int initialX = randomNum->bounded(0, width());
    int initialY = randomNum->bounded(0, height());

    // point the path will curve toward
    int startX = randomNum->bounded(0, initialX + 20);
    int startY = randomNum->bounded(0, initialY + 20);

    // point the path will end at: y value at height so it always goes to the bottom of the screen
    int endX = randomNum->bounded(0, width());

    int color = randomNum->bounded(0, 8); // colors vector generated in BasketballWidget class; 9 options

    // generate basketball vector along custom points
    QPainterPath path;
    path.moveTo(initialX, initialY);
    path.quadTo(startX, startY, endX, height());
    for(double i = 0 ; i < 1; i = i+0.1) {
        BasketballWidget* basketballWidget = new BasketballWidget(this);
        basketballWidget->hide(); // don't display: just generating basketballs to show later on a timer
        basketballWidget->setColor(color);
        basketballWidget->move(path.pointAtPercent(i).toPoint()); // update position to along the arc
        basketballImageVector.append(basketballWidget);
    }

    if(basketballIterations < maxIterations){
        if(currentBasketball < basketballImageVector.size()){
            basketballImageVector[currentBasketball]->show();
            currentBasketball++;
            basketballIterations++;
        }
    }
    else{
        if (!buttonsDrawn) {
            drawButtons();
        }
    }
}

void CongratulationsWindow::drawButtons(){
    if(buttonsDrawn)
        return;
    // set label text:
    QLabel* label = new QLabel();
    label->setAlignment(Qt::AlignCenter);
    if(isFinalLevel)
        label->setText("Way to go, you beat FLEXBALL! See you next season!");
    else{
        QRandomGenerator* textGen = new QRandomGenerator(QTime::currentTime().msec());
        QVector<QString> congratsMessages = {
            "Oh shoot! The ball went in!",
            "What a flex!",
            "You did it!",
            "Swish!",
            "Nothing but net!",
            "A buzzer beater!",
            "Let's add that shot to the highlight reel!",
            "Hall of fame, here you come!",
            "Another level, another win!"
        };
        label->setText(congratsMessages[textGen->bounded(8)]);
    }

    // set label font
    QFont font = label->font();
    font.setPointSize(50);
    label->setFont(font);

    if(!isFinalLevel){
        // set button font
        font.setBold(true);
        font.setPointSize(15);

        // button layout setup
        QWidget* buttonContainer = new QWidget(this);
        buttonContainer->setStyleSheet("background-color: rgba(0,0,0,1);");
        buttonContainer->setFixedHeight(50);
        QHBoxLayout* buttonLayout = new QHBoxLayout(buttonContainer);

    // add next level button if the game is not over
        QPushButton* nextLevel = new QPushButton("Next Level");
        nextLevel->setFont(font);
        nextLevel->setStyleSheet("background-color: rgba(255, 154, 71, 1); color:black");
        buttonLayout->addWidget(nextLevel);
        connect(nextLevel, &QPushButton::clicked, this, &CongratulationsWindow::nextLevelClicked);
        layout->addWidget(label);
        layout->addWidget(buttonContainer);
    }

    // add all elements to the larger widget
    if(isFinalLevel)
        layout->addWidget(label);

    // connections
    buttonsDrawn = true;

    // display widget
    this->setLayout(layout);
    this->update();
}

// ---------------------------------------------------------- slots ----------------------------------------------------------
void CongratulationsWindow::nextLevelClicked(){
    emit moveToNextLevel();
}
