/*
 * File: congratulationswindow.h
 * Contributors:
 *   - Sophie Jackson
 *
 * Most Recent Update:
 *   Code cleanup
 *
 * Date of Most Recent Update:
 *   12/11/2024
 *
 * Description:
 *   Handles displaying a level complete screen inbetween levels.
 *   This class outlines the custom behavior for this congratulations window
 *   widget.
 *   Designed to be used in The Best Developers Education Application.
 */

#ifndef CONGRATULATIONSWINDOW_H
#define CONGRATULATIONSWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QRandomGenerator>
#include <QVBoxLayout>

class BasketballWidget;

class CongratulationsWindow : public QWidget {
    Q_OBJECT
    // ------------------------------------ Begin CongratulationsWindow Fields ------------------------------------- //
private:
    QTimer* basketballDrawingTimer; // timer to handle drawing individual basketballs in win animation
    QVector<BasketballWidget*> basketballImageVector; // vector of basketball widgets to display for animation
    QRandomGenerator* randomNum; // random number generator for randomizing drawings
    int basketballIterations; // tracks the number of times a "basketball arc" has been drawn
    QVBoxLayout* layout; // layout for the congratulations window
    bool buttonsDrawn; // true if buttons have been added in final window; false otherwise
    int maxIterations; // sets a maximum number of "basketball arcs"
    int currentBasketball; // tracks the current basketball in a given vector
    bool isFinalLevel; // tracks if this is the final level complete screen
    // ------------------------------------- End CongratulationsWindow Fields -------------------------------------- //

    // -------------------------- Begin CongratulationsWindow Constructors and Destructors ------------------------- //
public:
    CongratulationsWindow(bool finalLevel, QWidget *parent = nullptr);
    ~CongratulationsWindow();
    // --------------------------- End CongratulationsWindow Constructors and Destructors -------------------------- //

    // ------------------------------------ Begin CongratulationsWindow Methods ------------------------------------ //
private:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void drawButtons(); // adds buttons to the widget
    // ------------------------------------- End CongratulationsWindow Methods ------------------------------------- //

    // ------------------------------- Begin CongratulationsWindow Signals and Slots ------------------------------- //
public slots:
    void drawBasketball();
    void nextLevelClicked();
signals:
    void moveToNextLevel();
    // -------------------------------- End CongratulationsWindow Signals and Slots -------------------------------- //
};

#endif // CONGRATULATIONSWINDOW_H

/*
 * Custom class for BasketballWidget: each widget contains an outlined basketball image drawn
 */
class BasketballWidget: public QWidget{
    Q_OBJECT
public:
    // Constructor: sets size and background to be transparent
    BasketballWidget(QWidget *parent) : QWidget(parent){
        this->setFixedSize(155, 155);
        this->setStyleSheet("background-color: rgba(0,0,0,0)");
    }
    // Custom paint event: sets widget display to be basketballs
    void paintEvent(QPaintEvent *){
        // draw basketball
        QPainter painter(this);
        painter.translate(0, height());
        painter.scale(1, -1);
        QImage basketball = QImage(":/basketball.png").scaled(150, 150, Qt::KeepAspectRatio).transformed(QTransform().rotate(180.0));
        painter.drawImage(0, 0, basketball);

        // draw outline
        QPen pen;
        pen.setColor(outlineColor);
        pen.setWidth(5);
        painter.setPen(pen);
        painter.drawEllipse(0,0,150,150);
    }
    // setter for the color of the basketball's outline
    void setColor(int color){
        QVector<QColor> colorVec = {Qt::red, Qt::blue, Qt::white, Qt::black, Qt::green, Qt::gray, Qt::cyan, Qt::yellow, Qt::magenta};
        outlineColor = colorVec[color];
    }
private:
    QColor outlineColor; // outline color of the basketball
};
