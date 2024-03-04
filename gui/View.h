/*
* @Author: Qianhua Liu
* @Date: 2024-03-02
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_GUI_VIEW_H
#define LOCALMINMAX_GUI_VIEW_H

#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsEllipseItem>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QGraphicsPathItem>
#include <QtWidgets/QLabel>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>
#include <QtGui/QResizeEvent>
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtCore/QQueue>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QVector>
#include <QtCore/QTimeLine>
#include <QtCore/QEasingCurve>
#include <QtCore/QtMath>

namespace localminmax::gui {
class ViewLog : public QLabel {
    Q_OBJECT
public:
    ViewLog(const QString& log, const QWidget* parent = nullptr);

private:
    void resizeEvent(QResizeEvent* event);

    QFont m_log_font = QFont("Corbel", 12);
    QString m_log_test;
};

class GraphicsView;
class GraphicsVertexView;
class GraphicsLineView;

} // localminmax::gui

#endif // LOCALMINMAX_GUI_VIEW_H