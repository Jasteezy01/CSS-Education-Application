/*
 * File: flexoption.h
 * Contributors:
 *   - Sophie Jackson
 *   - Nathaniel Atwood
 *
 * Most Recent Update:
 *   Comments updated
 *
 * Date of Most Recent Update:
 *   12/3/2024
 *
 * Description:
 *   Header file for each FlexOption object. Tracks the values of each FlexOption.
 *   Designed to be used in The Best Developers Education Application.
 */
#ifndef FLEXOPTION_H
#define FLEXOPTION_H

#include <QObject>
#include <QtWidgets/qlabel.h>

class FlexOption : public QLabel {
    Q_OBJECT
    // -------------------------------- Begin Flex Option Fields ----------------------------------- //
private:
    int optionId;   // Unique id for the flex option
    void mousePressEvent(QMouseEvent* event) override; // overriden for movement functionality
    QString optionText;  // Text to be displayed for the flex option
public:
    int currentLayout; // int to track the current layout for placement in GUI

    // --------------------------------- End Flex Option Fields ------------------------------------ //

    // --------------------- Begin Flex Option Constructors and Destructors ------------------------ //
public:
    FlexOption(QObject *parent = nullptr);     // Constructor
    FlexOption(QString optionText, QObject *parent = nullptr);
    FlexOption(const FlexOption &toCopy);                //Copy Constructor
    //bool operator!= (FlexOption const& otherFlexOption);
    // ---------------------- End Flex Option Constructors and Destructors ------------------------- //

    // -------------------------------- Begin Flex Option Methods ---------------------------------- //
public:
    void setCurrentLayout(int newLayout); // sets the layout of the FlexOption
    QString getOptionText();
    void updateOptionText(QString opt);
    // --------------------------------- End Flex Option Methods ----------------------------------- //

    // -------------------------------- Begin Flex Option Signals ---------------------------------- //
signals:
    void clicked(int currentLayout, FlexOption* option); // sent when a FlexOption is clicked
    // --------------------------------- End Flex Option Signals ----------------------------------- //

    // --------------------------------- Begin Flex Option Slots ----------------------------------- //
public slots:
    // ---------------------------------- End Flex Option Slots ------------------------------------ //
};

#endif // FLEXOPTION_H
