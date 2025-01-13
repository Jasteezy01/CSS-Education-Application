/*
 * File: flexoption.cpp
 * Contributors:
 *   - Jadon Olson
 *   - Sophie Jackson
 *   - Nathaniel Atwood
 *
 * Most Recent Update:
 *      Updated to use web engine and current level for positions.
 *
 * Date of Most Recent Update:
 *   12/7/2024
 *
 * Description:
 *   Implementation of the flexoption.h file.
 *   Designed to be used in The Best Developers Education Application.
 */

#include "flexoption.h"

FlexOption::FlexOption(QObject *parent) : QLabel{} {
    currentLayout = 1;
}

FlexOption::FlexOption(QString optionText, QObject *parent) : optionText(optionText) {
    currentLayout = 1;
}

FlexOption::FlexOption(const FlexOption &toCopy)
{
    currentLayout = toCopy.currentLayout;
    optionText = toCopy.optionText;
    optionId = toCopy.optionId;
}

void FlexOption::mousePressEvent(QMouseEvent* event) {
    emit clicked(currentLayout, this);
}

void FlexOption::setCurrentLayout(int newLayout){
    currentLayout = newLayout;
}

void FlexOption::updateOptionText(QString opt) {
    qDebug() << "Made it to updateOptionText" << opt;
    optionText = opt;
}

QString FlexOption::getOptionText() {
    return this->optionText;
}

// bool FlexOption::operator!= (FlexOption const& other)
// {
//     return optionText != other.optionText;
// }
