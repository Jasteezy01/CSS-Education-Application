/*
 * File: webgenius.cpp
 * Contributors:
 *   - Nathaniel Atwood
 *
 * Most Recent Update:
 *      Updated for incredulous debugging.
 *
 * Date of Most Recent Update:
 *   12/7/2024
 *
 * Description:
 *   Implementation file for the WebGenius class. This is a facade class for using the QT web
 *   engine. It provides funcitonality for getting the positions of objects on a page that have
 *   been arranged with flexbox styling text.
 *   Designed to be used in The Best Developers Education Application.
 */
#include "webgenius.h"
#include <QDebug>
#include <QWebEnginePage>
#include <QVector>
#include <QPoint>

WebGenius::WebGenius(QObject *parent) : QObject(parent) {
    connect(&webView, &QWebEngineView::loadFinished, this, &WebGenius::onHtmlLoaded);
    connect(webView.page(), &QWebEnginePage::loadFinished, this, [this]() {
        // JavaScript to get the positions of "basketball" and "basketball_hoop" elements
        QString js = R"(
            (function() {
                let basketballs = [];
                let hoops = [];

                // Get all basketball elements
                document.querySelectorAll('.basketball').forEach(el => {
                    let rect = el.getBoundingClientRect();
                    basketballs.push({
                        x: rect.left + rect.width / 2,
                        y: rect.top + rect.height / 2
                    });
                });

                // Get all basketball_hoop elements
                document.querySelectorAll('.basketball_hoop').forEach(el => {
                    let rect = el.getBoundingClientRect();
                    hoops.push({
                        x: rect.left + rect.width / 2,
                        y: rect.top + rect.height / 2
                    });
                });

                // Return as a combined object
                return { basketballs, hoops };
            })();
        )";

        webView.page()->runJavaScript(js, [this](const QVariant &result) {
            onJavaScriptResult(result);
        });
    });
}

void WebGenius::analyzeHtml(const QString &htmlContent) {
    webView.setHtml(htmlContent);
}

void WebGenius::onHtmlLoaded(bool success) {
    if (!success) {
        qWarning() << "Failed to load HTML content.";
        emit analysisComplete();
        return;
    }
}

void WebGenius::onJavaScriptResult(const QVariant &result) {
    basketballRenderedPositons.clear();
    basketballHoopRenderedPositons.clear();

    if (result.canConvert<QVariantMap>()) {
        QVariantMap map = result.toMap();

        // Process basketball positions
        QVariantList basketballs = map["basketballs"].toList();
        for (const QVariant &item : basketballs) {
            QVariantMap pos = item.toMap();
            QPoint center(pos["x"].toInt(), pos["y"].toInt());
            basketballRenderedPositons.append(center);
        }

        // Process basketball hoop positions
        QVariantList hoops = map["hoops"].toList();
        for (const QVariant &item : hoops) {
            QVariantMap pos = item.toMap();
            QPoint center(pos["x"].toInt(), pos["y"].toInt());
            basketballHoopRenderedPositons.append(center);
        }
    }

    qDebug() << "This is James! I have analyzed your html!";
    emit analysisComplete();
}

QVector<QPoint> WebGenius::getBasketballCenters() const {
    return basketballRenderedPositons;
}

QVector<QPoint> WebGenius::getBasketballHoopCenters() const {
    return basketballHoopRenderedPositons;
}
