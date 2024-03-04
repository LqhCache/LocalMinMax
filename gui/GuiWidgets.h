/*
* @Author: Qianhua Liu
* @Date: 2024-03-04
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_GUI_GUIWIDGETS_H
#define LOCALMINMAX_GUI_GUIWIDGETS_H

#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtCore/QRegularExpression>
#include <QtGui/QRegularExpressionValidator>
#include <QtWidgets/QSlider>
#include <QtCore/QString>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QResizeEvent>
#include <QtGui/QFocusEvent>
#include <QtWidgets/QGraphicsOpacityEffect>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtSvg/QtSvg>

namespace localminmax::gui {
constexpr QColor DEFAULT_COLOR = QColor(0, 0, 0, 0);
constexpr QColor DEFAULT_HOVER_COLOR = QColor(241, 241, 241, 200);

class GuiIcon : public QPushButton {
    Q_OBJECT
    Q_PROPERTY(qreal rotationAngle READ rotationAngle 
               WRITE setRotationAngle NOTIFY rotationAngleChanged)
signals:
    void rotationAngleChanged();

public:
    explicit GuiIcon(const QString& icon_path, QString hint = "", int r = 0, 
                     QWidget *parent = nullptr);
    explicit GuiIcon(const QPixmap &icon, QString hint = "", int r = 0, 
                     QWidget *parent = nullptr);

    void setRotationAngle(qreal angle = 0);

protected:
    void paintEvent(QPaintEvent* event);
    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

protected:
    qreal getRotationAngle() const;

private:
    int m_radius;
    qreal m_widget_ratio;
    qreal m_icon_size_rate = 0.8;
    qreal m_rotation = 0;
    QPixmap* m_icon_img;
    QString m_icon_hint;

    /* for hover and click effects */
    QColor m_background_color;
};

} // localminmax::gui

#endif // LOCALMINMAX_GUI_GUIWIDGETS_H