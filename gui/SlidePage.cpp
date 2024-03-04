/*
* @Author: Qianhua Liu
* @Date: 2024-03-04
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/

#include "gui/SlidePage.h"

namespace localminmax::gui {
SlideLayer::SlideLayer(QWidget *parent) 
    : QWidget(parent)
{
    m_background = new QWidget(this);
    m_background->resize(parent->size());
    m_background->setStyleSheet("background-color:#5a000000");
    m_background->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_background->show();
}

SlideLayer::~SlideLayer()
{
    delete m_background;
}
void SlideLayer::setEnabled(bool enabled)
{
    m_enabled = enabled;
}

void SlideLayer::mousePressEvent(QMouseEvent *event)
{
    m_pressed = m_enabled;
}

void SlideLayer::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_enabled && m_pressed) {
        emit clicked();
        m_pressed = false;
    }
}
void SlideLayer::resizeEvent(QResizeEvent *event)
{
    m_background->resize(this->parentWidget()->size());
}

void SlidePage::slideIn()
{
    if(m_cur_ani != nullptr){
        m_cur_ani->stop();
        m_cur_ani->deleteLater();
        m_cur_ani = nullptr;
    }
    m_on_shown = true;
    m_slide_layer->raise();
    m_slide_layer->setEnabled(true);
    this->raise();
    m_slide_layer->show();
    QParallelAnimationGroup* in_group = new QParallelAnimationGroup(this);
    QPropertyAnimation* slide_in_ani = new QPropertyAnimation(this, "pos", this);
    slide_in_ani->setStartValue(this->pos());
    slide_in_ani->setEndValue(QPoint(0, 0));
    slide_in_ani->setDuration(1000);
    slide_in_ani->setEasingCurve(QEasingCurve::InOutExpo);
    QPropertyAnimation* fade_in_ani = new QPropertyAnimation(m_opacity, "opacity", this);
    fade_in_ani->setStartValue(m_opacity->opacity());
    //> note: DO NOT CHANGE 0.99 TO 1!!!!!
    //>       Will cause unexpected position shift (maybe qt's bug)
    fade_in_ani->setEndValue(0.99);
    fade_in_ani->setDuration(750);
    QSequentialAnimationGroup *rotate = new QSequentialAnimationGroup(this);
    rotate->addPause(250);
    in_group->addAnimation(slide_in_ani);
    in_group->addAnimation(fade_in_ani);
    in_group->addAnimation(rotate);
    connect(in_group, &QParallelAnimationGroup::finished, this, [=](){
        this->m_cur_ani = nullptr;
    });
    in_group->start();
    m_cur_ani = in_group;
}

void SlidePage::slideOut()
{
    if(m_cur_ani != nullptr){
        m_cur_ani->stop();
        m_cur_ani->deleteLater();
        m_cur_ani = nullptr;
    }
    m_on_shown = false;
    m_slide_layer->setEnabled(false);
    QParallelAnimationGroup* out_group = new QParallelAnimationGroup(this);
    QPropertyAnimation* slide_out_ani = new QPropertyAnimation(this, "pos", this);
    slide_out_ani->setStartValue(this->pos());
    slide_out_ani->setEndValue(QPoint(-this->width() - 30, 0));
    slide_out_ani->setDuration(1000);
    slide_out_ani->setEasingCurve(QEasingCurve::InOutExpo);
    QPropertyAnimation* fade_out_ani = new QPropertyAnimation(m_opacity, "opacity", this);
    fade_out_ani->setStartValue(m_opacity->opacity());
    fade_out_ani->setEndValue(0);
    fade_out_ani->setDuration(750);
    out_group->addAnimation(slide_out_ani);
    out_group->addAnimation(fade_out_ani);
    connect(this, &SlidePage::sizeChange, slide_out_ani, [=](){
        slide_out_ani->setEndValue(QPoint(-this->width() - 30, 0));
    });
    out_group->start();
    m_cur_ani = out_group;
}

SlidePage::SlidePage(int radius, QString name, QWidget *parent)
    : QWidget(parent), m_corner_radius(radius), m_page_name(name)
{
    this->resize(parent->width() * 0.4 <= PREFER_WIDTH ? 
                 PREFER_WIDTH : parent->width() * 0.4, parent->height());
    this->move(QPoint(-this->width() - 30, 0));
    m_name_label = new QLabel(m_page_name, this);
    m_text_font.setStyleStrategy(QFont::PreferAntialias);
    m_name_label->setFont(m_text_font);

    m_opacity = new QGraphicsOpacityEffect(this);
    m_opacity->setOpacity(0);
    m_name_label->setGraphicsEffect(m_opacity);

    QString style = "background-color:white;border-radius:" + 
                    QString::asprintf("%d", m_corner_radius) + "px";
    m_backgroud = new QWidget(this);
    m_backgroud->lower();
    m_backgroud->resize(this->size());
    m_backgroud->setStyleSheet(style);
    m_backgroud->show();

    // intialize layout
    QVBoxLayout* main_layout = new QVBoxLayout(this);
    main_layout->setContentsMargins(20, 40, 20, 20);
    QWidget* title_bar = new QWidget(this);
    QHBoxLayout* title_layout = new QHBoxLayout(title_bar);
    title_layout->setAlignment(Qt::AlignLeft);
    title_bar->setLayout(title_layout);
    title_layout->addWidget(m_name_label);
    main_layout->addWidget(title_bar);
    main_layout->setAlignment(Qt::AlignTop);
    this->setLayout(main_layout);

    m_slide_layer = new SlideLayer(this->parentWidget());
    m_slide_layer->resize(this->parentWidget()->size());
    m_slide_layer->setGraphicsEffect(m_opacity);
    m_slide_layer->setMouseTracking(true);
    connect(m_slide_layer, &SlideLayer::clicked, this, [=](){
        slideOut();
        setFocus();
    });
    
    // set shadow 
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(30);
    shadow->setColor(QColor(0, 0, 0));
    shadow->setOffset(0, 0);
    this->setGraphicsEffect(shadow);
    // set policies
    this->setFocusPolicy(Qt::ClickFocus);
    this->setMouseTracking(true);
    m_backgroud->setMouseTracking(true);
    m_slide_layer->setMouseTracking(true);
}

void SlidePage::setRadius(int radius)
{
    m_corner_radius = radius;
    QString style;
    style = "background-color:white;border-radius:" + 
            QString::asprintf("%d", m_corner_radius) + "px";
    this->setStyleSheet(style);
}

void SlidePage::setName(QString name)
{
    m_page_name = name;
    m_name_label->setText(m_page_name);
}

void SlidePage::addContent(QWidget* widget)
{
    widget->setParent(this);
}

void SlidePage::addContents(QVector<QWidget*> widgets)
{
}

void SlidePage::removeContents(QVector<QWidget*> widgets)
{
}

void SlidePage::updateContents(){
}

void SlidePage::scrollToTop(){
}

void SlidePage::resizeEvent(QResizeEvent *event)
{
    
}

} // localminmax::gui
