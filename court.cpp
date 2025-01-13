/*
 * File: court.cpp
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
 *   Manages the custom widget in the flexbox game.
 *   Designed to be used in The Best Developers Education Application.
 */

#include "court.h"
#include "basketball.h"
#include "basketballhoop.h"
#include <QTimer>
#include <QPainterPath>

// ------------------------- Begin Court Constructors and Destructors -------------------------- //
Court::Court(QWidget *parent): QWidget(parent), world(b2Vec2(0.0f, 0.0f)) {}

Court::Court(FlexboxModel &model, QWidget *parent): QWidget(parent), world(b2Vec2(0.0f, 0.0f)), gameModel(&model) {
    // Draw border for development
    setAttribute(Qt::WA_StyledBackground, true);

    BallImage = QImage(":/basketball.png").scaled(50, 50, Qt::KeepAspectRatio).transformed(QTransform().rotate(180.0));
    hoopImage = QImage(":/hoop.png");
    // Define World
    addStaticBodies();
    for (Basketball* ball : gameModel->getBasketballs()) {
        addDynamicBody(ball->getPosition().x() /20,ball->getPosition().y()/20);
    }
    printf("Init world\n");

    // Connect web engine update from model
    connect(&model, &FlexboxModel::changeElement, this, &Court::jamesInputReceived);
    connect(this, &Court::displayWin, &model, &FlexboxModel::displayWin);
    connect(&model, &FlexboxModel::resetCourtGravity,this, &Court::stopCourt);
    connect(&model, &FlexboxModel::updateCourt, this, &Court::redrawStuff);

    // Create timer to run world
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &Court::stepSimulation);
}
// -------------------------- End Court Constructors and Destructors --------------------------- //

// ------------------------------------ Begin Court Methods ------------------------------------ //
void Court::paintEvent(QPaintEvent *) {
    //qDebug() << "paintEvent is being called";

    // Create a painter
    QPainter painter(this);
    painter.translate(0, height()); // Moves the origin to the bottom left corner.
    painter.scale(1, -1); // Inverts drawing to a "normal" perspective

    // Draw the Hoops
    for (const BasketballHoop* hoop : gameModel->getHoops()) {
        QPoint position = hoop->getPosition();
        int x = position.x();
        int y = position.y();
        painter.scale(1, -1);
        painter.drawImage(x - 50, -y - 25, hoopImage);
        painter.scale(1, -1);

        // draw border around hoops
        QPen newPen (Qt::black, 1);
        painter.setPen(newPen);
        painter.drawRect(x-50, y - 25 , 100,50);
    }

    // Draw the Basketballs
    QVector<Basketball*> basketballVector = gameModel->getBasketballs(); // used to retrieve colors

    // qDebug() << "Body count: "+ basketballVector.count();
    for (int i = 0; i < basketballVector.count(); i++) {
        b2Vec2 position = bodyVector[i]->GetPosition();
        Basketball* basketball = basketballVector[i]; // used to determine color needed to draw

        // Draw the one image               (Image offeset) TODO: Find scalable variable to take difference
        int x = static_cast<int>(position.x * 20)-25; // The static cast is a safer and cearer way to cast types.
        int y = static_cast<int>(position.y * 20)-25; // The static cast is a safer and cearer way to cast types.

        painter.drawImage(x, y , BallImage); // draw basketball

        // draw color on basketballs
        QPen pen (basketball->getColor(), 4);
        painter.setPen(pen);
        painter.drawEllipse(x, y, 50, 50);
    }

    // draw color on hoops last: appears like the balls go "through" the hoop
    for (const BasketballHoop* hoop : gameModel->getHoops()) {
        QPoint position = hoop->getPosition();
        int x = position.x();
        int y = position.y();
        // draw color on hoops
        QPen pen (hoop->getColor(), 4);
        painter.setPen(pen);
        painter.drawRect(x-39, y-23, 80, 2);
    }

    // Manage resources
    painter.end();
}

void Court::stepSimulation() {
    // Instruct the world to perform a single step of simulation.
    // It is generally best to keep the time step and iterations fixed.
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIteration = 6;
    int32 positionIteration = 2;
    world.Step(timeStep, velocityIteration, positionIteration);

    // Update widget
    update();
}

void Court::jamesInputReceived(){
    qDebug() << "James is done doin stuff...";
    clearDynamicBodies();
    for (Basketball* ball : gameModel->getBasketballs()) {
        addDynamicBody(ball->getPosition().x() /20 + 3.0f, (300-ball->getPosition().y())/20 + 3.0f);
        qDebug() <<"NEW X: " <<ball->getPosition().x() /20 + 3.0f<<"NEW Y: "<<ball->getPosition().y()/20 + 3.0f;
    }

    //enable gravity at this point
    QTimer::singleShot(1000, this, [=](){SetGravityState(true);});
    update();

    //display celebration screen
    emit displayWin();
    //reset court for next level
}


void Court::addHoops()
{
    for (const BasketballHoop* hoop : gameModel->getHoops()) {
        // Add left bound
        // determine position to be drawn
        QPoint pnt = hoop->getPosition();
        float pointX = (float) pnt.x() / 20 - 1.78;
        float pointY = -1.01 + (float) pnt.y() / 20;

        b2BodyDef hoopBodyDef;   // Creates Body definition
        hoopBodyDef.position.Set(pointX ,pointY); // Sets coords of body definitoon
        b2Body* hoopBody = world.CreateBody(&hoopBodyDef); // Creates a body based off of definition

        b2PolygonShape hoopShape; // Defines a "shape" in Box2d to reporesent hoop.

        hoopShape.SetAsBox(.2f, .13f); // Turns the "shape" to "box" to represent hoop.

        hoopBody->CreateFixture(&hoopShape, 0.0f); // Adds the hoop to the world
        hoopCollisionVector.append(hoopBody);

        // Add right bound
        pointX = (float) pnt.x() / 20 + 1.9;
        hoopBodyDef.position.Set(pointX, pointY);
        hoopBody = world.CreateBody(&hoopBodyDef);
        hoopBody->CreateFixture(&hoopShape, 0.0f);
        hoopCollisionVector.append(hoopBody);
    }
}

void Court::addStaticBodies() {
    b2BodyDef groundBodyDef;
    b2BodyDef leftBoundDef;
    b2BodyDef rightBoundDef;
    b2BodyDef ceilingBoundDef;
    //These determine position of each boundry within court widget
    // Get Screen to Box2D dimensions
    groundBodyDef.position.Set(courtWidth/2, 0.0f);
    leftBoundDef.position.Set(0.0f, courtHeight / 2);
    rightBoundDef.position.Set(courtWidth - 0.25f, courtHeight / 2);
    ceilingBoundDef.position.Set(courtWidth / 2, courtHeight - 0.25);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2Body* leftBoundBody = world.CreateBody(&leftBoundDef);
    b2Body* rightBoundBody = world.CreateBody(&rightBoundDef);
    b2Body* ceilingBoundBody = world.CreateBody(&ceilingBoundDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;
    b2PolygonShape leftBoundryBox;
    b2PolygonShape rightBoundryBox;
    b2PolygonShape ceilingBoundryBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(courtWidth / 2, 0.25f);
    leftBoundryBox.SetAsBox(0.25f, courtHeight / 2);
    rightBoundryBox.SetAsBox(0.25f, courtHeight / 2);
    ceilingBoundryBox.SetAsBox(courtWidth / 2, 0.25f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);
    leftBoundBody->CreateFixture(&leftBoundryBox,0.0f);
    rightBoundBody->CreateFixture(&rightBoundryBox, 0.0f);
    ceilingBoundBody->CreateFixture(&ceilingBoundryBox, 0.0f);

    // Add the hoops to the court
    addHoops();
}

void Court::SetGravityState(bool state)
{
    startSimulation();
    qDebug() << "IN GRAV METHOD";
    if(state)
    {
        qDebug() <<"Enabled Gravity";
        world.SetGravity(b2Vec2(0.0f,-9.8f));
    }
    else
    {
        qDebug() <<"Disabled Gravity";
        world.SetGravity(b2Vec2(0.0f,0.0f));
    }

    for(b2Body* body : bodyVector)
        body->SetAwake(true);

    update();
}

void Court::addDynamicBody(int posX, int posY) {
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    float x = (float) (courtWidth / 20) + posX;
    float y = (float) (courtWidth / 20) + posY;
    bodyDef.position.Set(x,y);
    qDebug() <<"Initial Ball position:" << x *20<<","<< y*20<<"|" ;
    b2Body* temp = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2CircleShape circle;
    circle.m_radius = 1.25f;

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;

    // Set the circle density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.9f;

    temp->CreateFixture(&fixtureDef);

    // Add the shape to the body.
    bodyVector.append(temp);
}

void Court::clearDynamicBodies() {
    for(b2Body* body: bodyVector)
    {
        world.DestroyBody(body);
    }
    this->bodyVector.clear();

}


void Court::centerBasketball() {
    b2Body* basketball = bodyVector.front();
    basketball->SetTransform(b2Vec2(20, 20), 0.0f);
}

void Court::startSimulation() {
    updateTimer->start(16); // ~60 FPS (1000ms / 60 ≈ 16ms)
}

void Court::stopSimulation() {
    updateTimer->stop();
}

void Court::clearStaticBodies()
{
        for(b2Body* body: hoopCollisionVector)
         {
             world.DestroyBody(body);
         }
        hoopCollisionVector.clear();
}

void Court::redrawStuff() {
    qDebug() << "made it to redrawStuff";

    clearDynamicBodies();
    clearStaticBodies();

    qDebug() << "redrawStuff hid the bodies";

    for (Basketball* ball : gameModel->getBasketballs()) {
        addDynamicBody(ball->getPosition().x() /20 + 3.0f, (300-ball->getPosition().y())/20 + 3.0f);
        qDebug() <<"NEW X: " <<ball->getPosition().x() /20 + 3.0f<<"NEW Y: "<<ball->getPosition().y()/20 + 3.0f;
    }

    for (BasketballHoop* hoop : gameModel->getHoops()) {
        addHoops();
        qDebug() <<"NEW X FOR HOOP: " <<hoop->getPosition().x() /20 + 3.0f<<"NEW Y FOR HOOP: "<<hoop->getPosition().y()/20 + 3.0f;
    }
    qDebug() << "redrawStuff added new bodies";

    update();
}

void Court::stopCourt() {
    stopSimulation();
}
// ------------------------------------- End Court Methods ------------------------------------- //
