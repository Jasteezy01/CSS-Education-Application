/*
 * File: webgenius.h
 * Contributors:
 *   - Nathaniel Atwood
 *
 * Most Recent Update:
 *   Updated methods.
 *
 * Date of Most Recent Update:
 *   12/02/2024
 *
 * Description:
 *   Header file for the WebGenius STATIC class. This is a facade class for using the QT web
 *   engine. It provides funcitonality for getting the positions of objects on a page that have
 *   been arranged with flexbox styling text.
 *   Designed to be used in The Best Developers Education Application.
 */
#ifndef WEBGENIUS_H
#define WEBGENIUS_H

#include <QObject>
#include <QVector>
#include <QPoint>
#include <QString>
#include <QWebEngineView>

class WebGenius : public QObject {
    Q_OBJECT
    // --------------------------------- Begin Web Genius Fields ----------------------------------- //
private:
    QWebEngineView webView; // Web engine view to load and render the HTML
    QVector<QPoint> basketballRenderedPositons;
    QVector<QPoint> basketballHoopRenderedPositons;
    // ---------------------------------- End Web Genius Fields ------------------------------------ //

    // ------------------------ Begin Web Genius Constructors/Destructors -------------------------- //
public:
    explicit WebGenius(QObject *parent = nullptr);
    // ------------------------- End Web Genius Constructors/Destructors --------------------------- //

    // --------------------------------- Begin Web Genius Methods ---------------------------------- //
public:
    void analyzeHtml(const QString &htmlContent);          // Public method to start analyzing the HTML content
    QVector<QPoint> getBasketballCenters() const;          // Public getter for positions
    QVector<QPoint> getBasketballHoopCenters() const;       // Public getter for positions
    // ---------------------------------- End Web Genius Methods ----------------------------------- //

    // --------------------------------- Begin Web Genius Signals ---------------------------------- //
signals:
    void analysisComplete(); // Signal emitted when the analysis is complete
    // ---------------------------------- End Web Genius Signals ----------------------------------- //

    // ---------------------------------- Begin Web Genius Slots ----------------------------------- //
private slots:
    void onHtmlLoaded(bool success); // Slot triggered when the HTML content finishes loading
    void onJavaScriptResult(const QVariant &result); // Slot to process the results of JavaScript execution
    // ----------------------------------- End Web Genius Slots ------------------------------------ //
};

#endif // WEBGENIUS_H
