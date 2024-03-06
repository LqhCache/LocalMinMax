/*
* @Author: Qianhua Liu
* @Date: 2024-03-04
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/

#include "gui/ScrollContainer.h"

namespace localminmax::gui {
ScrollArea::ScrollArea(QWidget *parent) : QWidget(parent)
{
    //initialize list container and timer
    m_container = new ScrollListContainer(this);
    m_container->move(0, 0);
    m_container->resize(this->width(), 3);
    m_get_cord = new QTimer;
    m_get_cord->setSingleShot(true);
    m_refresh_view = new QTimer;
    m_get_cord->setSingleShot(true);

    m_indicator = new ScrollIndicator(this);
    m_indicator->resize(m_indicator->width(), static_cast<int32_t>(static_cast<double>(this->height()) *
                        static_cast<double>(this->height()) / static_cast<double>(m_container->height())));
    m_indicator->move(this->width() - m_indicator->width() - 3, 0);

    this->setMouseTracking(true);
    m_container->setMouseTracking(true);
    m_indicator->setMouseTracking(true);

    m_bounce = new QPropertyAnimation(m_container, "pos");

    QObject::connect(m_get_cord, SIGNAL(timeout()), this, SLOT(updateSpd()));
    QObject::connect(m_refresh_view, SIGNAL(timeout()), this, SLOT(scrollContainer()));
    QObject::connect(m_indicator, SIGNAL(scrollPage(int)), this, SLOT(scrollIndicator(int)));
}

void ScrollArea::paintEvent(QPaintEvent *event)
{
    m_container->resize(this->width(), m_container->height());
    if (m_container->height() > this->height() && m_container->y() < this->height() - 
        m_container->height() && m_cur_speed == 0 && m_bounce->state() == QAbstractAnimation::Stopped) {
        m_container->move(m_container->x(), this->height() - m_container->height());
    }
    if (m_container->height() <= this->height()) {
        m_container->move(m_container->x(), 0);
        m_indicator->hide();
    }else {
        m_indicator->show();
    }
    m_indicator->resize(m_indicator->width(), static_cast<int32_t>(static_cast<double>(this->height()) *
                        static_cast<double>(this->height()) / static_cast<double>(m_container->height())));
    m_indicator->move(this->width() - m_indicator->width() - 3, -m_container->y() * this->height() / m_container->height());
}

void ScrollArea::mousePressEvent(QMouseEvent *event)
{
    if (m_container->height() > this->height()) {
        if (m_container->y() <= 0 && m_container->y() + m_container->height() >= this->height()) {
            m_pressed = true;
        }
        m_last_y = event->pos().y();
    }
    m_get_cord->stop();
    m_refresh_view->stop();
    m_cur_speed = 0;
    m_out_of_edge = false;
    m_move_stored = 0;
    m_next_move = 1;
}

void ScrollArea::mouseMoveEvent(QMouseEvent *event)
{
    setCursor(Qt::ArrowCursor);
    if(m_pressed){
        //start scroll
        if(!m_get_cord->isActive() && event->pos().y() - m_last_y != 0){
            //start 30ms timer
            m_get_cord->start(30);
            m_start_y = event->pos().y();
        }
        if(m_container->y() <= 0 && m_container->y() + m_container->height() >= this->height()) {
            m_container->move(m_container->x(), m_container->y() + event->pos().y() - m_last_y);
        }else {
            if(!m_out_of_edge){
                m_before_out_of_edge_y = event->pos().y();
                m_container->move(m_container->x(), m_container->y() + event->pos().y() - m_last_y);
                m_out_of_edge = true;
            }
            else{
                int pos = m_container->y() >= 0 ? 1 : -1;
                int dp = event->pos().y() - m_before_out_of_edge_y;
                if(dp == 0){
                    m_out_of_edge = false;
                    m_next_move = 1;
                    m_move_stored = 0;
                    if(m_container->y() >= 0) {
                        m_container->move(m_container->x(), 0);
                    }else {
                        m_container->move(m_container->x(), this->height() - m_container->height());
                    }
                }else if (dp / abs(dp) != pos) {
                    m_out_of_edge = false;
                    m_container->move(m_container->x(), this->y() + event->pos().y() - m_before_out_of_edge_y);
                    m_next_move = 1;
                    m_move_stored = 0;
                }else {
                    while(abs(m_move_stored) + m_next_move <= abs(event->pos().y() - m_before_out_of_edge_y)){
                        m_move_stored += m_next_move * pos;
                        m_container->move(m_container->x(), m_container->y() + pos);
                        m_next_move++;
                    }
                    while(m_next_move > 1 && abs(m_move_stored) > abs(event->pos().y() - m_before_out_of_edge_y)){
                        m_next_move--;
                        m_move_stored -= m_next_move * pos;
                        m_container->move(m_container->x(), m_container->y() - pos);
                    }
                    if(m_move_stored == 0){
                        m_before_out_of_edge_y = false;
                        if (m_container->y() >= 0) {
                            m_container->move(m_container->x(), 0);
                        }else {
                            m_container->move(m_container->x(), this->height() - m_container->height());
                        }
                        m_next_move = 1;
                        m_move_stored = 0;
                    }
                }
            }
        }
        m_last_y = event->pos().y();
    }
}

void ScrollArea::mouseReleaseEvent(QMouseEvent *event)
{
    //start scrolling
    if(m_container->y() > 0 || m_container->y() + m_container->height() < this->height()) {
        bounceBack();
    }else {
        m_refresh_view->start(30);
    }
    m_pressed = false;
}

void ScrollArea::bounceBack()
{
    m_refresh_view->stop();
    m_get_cord->stop();
    m_bounce->setDuration(500);
    m_bounce->setStartValue(m_container->pos());
    if(m_container->y() > 0) {
        m_bounce->setEndValue(QPoint(m_container->x(), 0));
    }else {
        m_bounce->setEndValue(QPoint(m_container->x(), this->height() - m_container->height()));
    }
    m_bounce->setEasingCurve(QEasingCurve::OutQuad);
    m_bounce->start();
}

void ScrollArea::scrollContainer()
{
    //scroll
    if(m_cur_speed > 0){
        if(m_cur_speed > MAX_SPEED && !m_ignore_max_speed) {
            m_cur_speed = MAX_SPEED;
        }else if(m_cur_speed <= MAX_SPEED) {
            m_ignore_max_speed = false;
        }
        int dp = m_scroll_down ? m_cur_speed : -m_cur_speed;
        m_container->move(m_container->x(), m_container->y() + dp);
    }
    else {
        return;
    }
    if(m_container->y() <= 0 && m_container->y() + m_container->height() >= this->height()){
        m_cur_speed -= m_damp;
        m_cur_speed = m_cur_speed < 0 ? 0 : m_cur_speed;
    }else {
        m_cur_speed /= 2;
    }
    if(m_cur_speed == 0 && (m_container->y() > 0 || m_container->y() + m_container->height() < this->height())) {
        bounceBack();
    }else {
        m_refresh_view->start(30);
    }
}

void ScrollArea::updateSpd() 
{
    int speed = m_last_y - m_start_y;
    m_scroll_down = speed >= 0;
    m_start_y = m_last_y;
    m_cur_speed = abs(m_cur_speed);
}

void ScrollArea::addWidget(QWidget* new_widget, bool set_animation)
{
    new_widget->setParent(m_container);
    m_container->addWidget(new_widget, set_animation);
}

void ScrollArea::addWidgets(QVector<QWidget*> widgets)
{
    for(const auto& widget : widgets) {
        addWidget(widget, false);
    }
}

void ScrollArea::removeWidget(QWidget *w)
{
    m_container->removeWidget(w);
}

void ScrollArea::scrollToTop()
{
    m_cur_speed = std::sqrt(8 * (- m_container->pos().y()) + 2) / 2;
    m_scroll_down = true;
    m_get_cord->stop();
    m_refresh_view->stop();
    m_out_of_edge = false;
    m_move_stored = 0;
    m_next_move = 1;
    m_ignore_max_speed = true;
    m_refresh_view->start(30);
}

void ScrollArea::updateHeight()
{
    m_container->updateHeight();
}

void ScrollArea::clear()
{
    m_container->clear();
}

void ScrollArea::scrollIndicator(int dp)
{
    int new_y = m_container->y() - dp * m_container->height() / this->height();
    if(new_y > 0) {
        new_y = 0;
    }else if(new_y < this->height() - m_container->height()) {
        new_y = this->height() - m_container->height();
    }
    m_container->move(m_container->x(), new_y);
    update();
}

void ScrollArea::wheelEvent(QWheelEvent* event)
{
    if(m_container->y() > 0 || m_container->y() + m_container->height() < this->height()) {
        return;
    }
    m_cur_speed += 5;
    bool newDirection = event->angleDelta().y() > 0;
    if(newDirection != m_scroll_down) {
        m_cur_speed = 5;
    }
    if(m_cur_speed > MAX_SPEED) {
        m_cur_speed = MAX_SPEED;
    }
    m_scroll_down = newDirection;
    if(!m_refresh_view->isActive()) {
        m_refresh_view->start(30);
    }
    update();
}

ScrollListContainer::ScrollListContainer(QWidget* parent) 
    : QWidget(parent) {}

void ScrollListContainer::paintEvent(QPaintEvent *event)
{
    for(int i = 0; i < m_widgets.size(); i++){
        m_widgets[i]->resize(this->width(), m_widgets[i]->height());
    }
}

void ScrollListContainer::addWidget(QWidget* widget, bool set_animation)
{
    //Add animation for all widgets current
    this->resize(this->width(), this->height() + widget->height() + m_spacing);
    m_widgets.push_back(widget);
    m_ys.push_back(0);
    ++ m_size;
    widget->resize(this->width(), widget->height());
    widget->show();

    if(set_animation) {
        QGraphicsOpacityEffect* widget_opac = new QGraphicsOpacityEffect(widget);
        widget_opac->setOpacity(0);
        widget->setGraphicsEffect(widget_opac);
        QParallelAnimationGroup* dp_group = new QParallelAnimationGroup;
        QSequentialAnimationGroup* new_widget_fade_in = new QSequentialAnimationGroup;
        for(int i = 0; i < m_size - 1; i++){
            m_ys[i] += widget->height() + m_spacing;
            QPropertyAnimation* move = new QPropertyAnimation(m_widgets[i], "pos");
            move->setDuration(750);
            move->setStartValue(m_widgets[i]->pos());
            move->setEndValue(QPoint(m_widgets[i]->x(), m_ys[i]));
            move->setEasingCurve(QEasingCurve::InOutQuart);
            dp_group->addAnimation(move);
        }
        new_widget_fade_in->addPause(300);
        QPropertyAnimation* fade = new QPropertyAnimation(widget_opac, "opacity", widget);
        fade->setDuration(300);
        fade->setStartValue(0.0);
        fade->setEndValue(0.99);
        new_widget_fade_in->addAnimation(fade);
        dp_group->addAnimation(new_widget_fade_in);
        dp_group->start();
        connect(dp_group, &QPropertyAnimation::stateChanged, [=]() {
            if(dp_group->state() == QAbstractAnimation::Stopped){
                if(widget_opac->opacity() != 0.99){
                    fade->start(QAbstractAnimation::DeleteWhenStopped);
                    connect(fade,&QPropertyAnimation::finished,[=](){widget_opac->deleteLater();});
                }else{
                    dp_group->deleteLater();
                    widget_opac->deleteLater();
                }
            }
        });
    }else{
        for(int i = 0; i < m_size - 1; i++){
            m_ys[i] += widget->height() + m_spacing;
            m_widgets[i]->move(QPoint(m_widgets[i]->pos().x(), m_ys[i]));
        }
    }
}

void ScrollListContainer::removeWidget(QWidget *widget)
{
    int32_t index;
    if(widget == nullptr) {
        index = m_size - 1;
        if(index != -1) {
            widget = m_widgets[index];
        }
    }else {
        index = m_widgets.indexOf(widget);
    }
    if(index == -1 || widget == nullptr){
        return;
    }
    this->resize(this->width(), this->height() - widget->height() - m_spacing);
    this->parentWidget()->update();
    widget->hide();
    widget->setParent(nullptr);
    QParallelAnimationGroup* dp_group = new QParallelAnimationGroup;
    for(int32_t i = index - 1; i >= 0; i--){
        m_ys[i] -= (widget->height() + m_spacing);
        QPropertyAnimation* move = new QPropertyAnimation(m_widgets[i], "pos");
        move->setDuration(750);
        move->setStartValue(m_widgets[i]->pos());
        move->setEndValue(QPoint(m_widgets[i]->x(), m_ys[i]));
        move->setEasingCurve(QEasingCurve::InOutQuart);
        dp_group->addAnimation(move);
    }
    dp_group->start(QAbstractAnimation::DeleteWhenStopped);
    m_widgets.remove(index);
    --m_size;
    m_ys.remove(index);
}

void ScrollListContainer::updateHeight()
{
    for(int i = m_size - 2; i >= 0; i--){
        m_ys[i] = m_ys[i + 1] + m_widgets[i + 1]->height() + m_spacing;
        m_widgets[i]->move(m_widgets[i]->pos().x(), m_ys[i]);
    }
    this->resize(this->width(), m_ys[0] + m_widgets[0]->height() + 3);
}

void ScrollListContainer::clear(){
    int32_t n = m_size;
    for(int i = 0; i < n; i ++) {
        removeWidget();
    }
}

ScrollIndicator::ScrollIndicator(QWidget *parent) : QWidget(parent)
{
    this->resize(m_default_width, 0);
    m_hov_timer = new QTimer(this);
    m_hov_timer->setSingleShot(true);
    m_ani_pause = new QTimer(this);
    m_ani_pause->setSingleShot(true);
    QObject::connect(m_hov_timer, SIGNAL(timeout()), this, SLOT(setHoverActive()));
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->m_cur_color = m_default_color; 

    this->setMouseTracking(true);
}

void ScrollIndicator::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_cur_color);
    painter.drawRect(this->rect());
}

void ScrollIndicator::enterEvent(QEnterEvent *event){
    if(!m_pressed){
        m_hov_timer->start(100);
        m_cur_color = m_hover_color;
        update();
    }
}

void ScrollIndicator::leaveEvent(QEvent *event){
    m_hov_timer->stop();
    m_cur_color = m_default_color;
    QPropertyAnimation* narrow = new QPropertyAnimation(this, "geometry");
    narrow->setDuration(300);
    narrow->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    narrow->setEndValue(QRect(this->parentWidget()->width() - m_margin - m_default_width, this->y(), m_default_width, this->height()));
    narrow->setEasingCurve(QEasingCurve::InOutQuad);
    narrow->start(QAbstractAnimation::DeleteWhenStopped);
    m_ani_pause->start(300);
    update();
}

void ScrollIndicator::mousePressEvent(QMouseEvent *event){
    m_cur_color = m_press_color;
    m_pressed = true;
    //>note: globalPos -> globalPosition here due to deprecation
    //>      may cause issues
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    m_last_y = event->globalPosition().y();
#else
    m_last_y = event->globalPos().y();
#endif
    update();
}

void ScrollIndicator::mouseMoveEvent(QMouseEvent *event){
    if(m_pressed && !m_ani_pause->isActive()){
        //>note: globalPos -> globalPosition here due to deprecation
        //>      may cause issues
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
        int dp = event->globalPosition().y() - m_last_y;
#else
        int dp = event->globalPos().y() - m_last_y;
#endif
        emit scrollPage(dp);
        //>note: globalPos -> globalPosition here due to deprecation
        //>      may cause issues
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
        m_last_y = event->globalPosition().y();
#else
        m_last_y = event->globalPos().y();
#endif
    }
}

void ScrollIndicator::mouseReleaseEvent(QMouseEvent *event){
    m_pressed = false;
    m_cur_color = m_hover_color;
    update();
}

void ScrollIndicator::setHoverActive(){
    QPropertyAnimation* widen = new QPropertyAnimation(this, "geometry");
    widen->setDuration(300);
    widen->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    widen->setEndValue(QRect(this->parentWidget()->width() - m_margin - m_default_width_at_focus, this->y(), m_default_width_at_focus, this->height()));
    widen->setEasingCurve(QEasingCurve::InOutQuad);
    widen->start(QAbstractAnimation::DeleteWhenStopped);
    m_ani_pause->start(300);
}

} // localminmax::gui
