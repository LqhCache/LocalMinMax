/*
* @Author: Qianhua Liu
* @Date: 2024-03-04
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_GUI_SLIDEPAGE_H
#define LOCALMINMAX_GUI_SLIDEPAGE_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtGui/QPaintEvent>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QGraphicsOpacityEffect>
#include <QtWidgets/QGraphicsEffect>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QParallelAnimationGroup>
#include <QtCore/QSequentialAnimationGroup>

#include "common/Math.h"

namespace localminmax::gui {
constexpr int32_t PREFER_WIDTH = 350;

class SlideLayer : public QWidget{
    Q_OBJECT
signals:
    void clicked();

public:
    explicit SlideLayer(QWidget *parent = nullptr);
    ~SlideLayer();
    void setEnabled(bool enabled);

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

    bool m_pressed = false;
    bool m_enabled = true;
    QWidget* m_background;
};

class SlidePage : public QWidget {
    Q_OBJECT
signals:
    void sizeChange();

public slots:
    void slideIn();
    void slideOut();

public:
    SlidePage(int radius, QString name, QWidget *parent = nullptr);
    void setRadius(int radius);
    void setName(QString name);
    void addContent(QWidget* widget);
    void addContents(QVector<QWidget*> widgets);
    void removeContents(QVector<QWidget*> widgets);
    void updateContents();
    void scrollToTop();

private:
    void resizeEvent(QResizeEvent *event);

    int m_corner_radius;
    bool m_on_shown = false;
    QString m_page_name = nullptr;
    QLabel* m_name_label = nullptr;
    QWidget* m_backgroud = nullptr;
    SlideLayer* m_slide_layer = nullptr;
    QFont m_text_font = QFont("Corbel Light", 24);
    QParallelAnimationGroup* m_cur_ani = nullptr;
    QGraphicsOpacityEffect* m_opacity = nullptr;
};

} // localminmax::gui

#endif // LOCALMINMAX_GUI_SLIDEPAGE_H