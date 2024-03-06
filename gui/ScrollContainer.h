/*
* @Author: Qianhua Liu
* @Date: 2024-03-04
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_GUI_SCROLLCONTAINER_H
#define LOCALMINMAX_GUI_SCROLLCONTAINER_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGraphicsOpacityEffect>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QParallelAnimationGroup>
#include <QtCore/QSequentialAnimationGroup>
#include <QtCore/QVector>
#include <QtCore/QTimer>
#include <QtCore/QtMath>

namespace localminmax::gui {
constexpr int32_t MAX_SPEED = 70;

class ScrollListContainer : public QWidget {
    Q_OBJECT
public:
    explicit ScrollListContainer(QWidget* parent = nullptr);
    void addWidget(QWidget* widget, bool set_animation = true);
    void removeWidget(QWidget* widget = nullptr);
    void updateHeight();
    void clear();

private:
    void paintEvent(QPaintEvent* event);

    int32_t m_spacing = 3;
    int32_t m_size = 0;
    QVector<QWidget*> m_widgets;
    QVector<int32_t> m_ys;
};

class ScrollIndicator : public QWidget {
    Q_OBJECT
signals:
    void scrollPage(int32_t);

private slots:
    void setHoverActive();

public:
    explicit ScrollIndicator(QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent* event);
    void enterEvent(QEnterEvent* event);
    void leaveEvent(QEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    QColor m_default_color = QColor(100, 100, 100, 130);
    QColor m_hover_color = QColor(70, 70, 70, 150);
    QColor m_press_color = QColor(50, 50, 50, 170);
    QColor m_cur_color;

    QTimer* m_hov_timer = nullptr;
    QTimer* m_ani_pause = nullptr;

    int32_t m_last_y;
    int32_t m_default_width = 2;
    int32_t m_default_width_at_focus = 9;
    int32_t m_margin = 3;

    bool m_pressed = false;
};

class ScrollArea : public QWidget {
    Q_OBJECT
private slots:
    void scrollContainer();
    void updateSpd();
    void scrollIndicator(int dp);

public:
    explicit ScrollArea(QWidget *parent = nullptr);
    void addWidget(QWidget* newWidget, bool setAnimation = true);
    void addWidgets(QVector<QWidget*> widgets);
    void removeWidget(QWidget* w  = nullptr);
    void scrollToTop();
    void updateHeight();
    void clear();

private:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void bounceBack();

    QTimer* m_get_cord;
    QTimer* m_refresh_view;

    ScrollListContainer* m_container;
    ScrollIndicator* m_indicator;

    QPropertyAnimation* m_bounce;

    bool m_pressed = false;
    bool m_scroll_down = true;
    bool m_out_of_edge = false;
    bool m_ignore_max_speed = false;

    int32_t m_start_y;
    int32_t m_last_y;
    int32_t m_before_out_of_edge_y;    //last y value before out of edge

    int32_t m_cur_speed = 0;
    int32_t m_move_stored = 0;
    int32_t m_damp = 1;
    int32_t m_next_move = 1;
};

} // localminmax::gui

#endif // LOCALMINMAX_GUI_SCROLLCONTAINER_H