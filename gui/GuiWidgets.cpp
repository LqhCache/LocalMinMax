/*
* @Author: Qianhua Liu
* @Date: 2024-03-04
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/

#include "gui/GuiWidgets.h"

namespace localminmax::gui {

//*********************************************************//
//GuiIcon class implementation
//*********************************************************//

GuiIcon::GuiIcon(const QString& icon_path, QString hint, int r, QWidget *parent)
    : QPushButton(parent), m_radius(r), m_icon_hint(hint)
{
    QSvgRenderer renderer;
    renderer.load(icon_path);
    QSize size = renderer.defaultSize();
    m_icon_img = new QPixmap(size);
    m_icon_img->fill(Qt::transparent);
    QPainter painter(m_icon_img);
    painter.setRenderHints(QPainter::Antialiasing);
    renderer.render(&painter);

    m_widget_ratio = m_icon_img->height() / m_icon_img->width();
    m_background_color = DEFAULT_COLOR;
}

GuiIcon::GuiIcon(const QPixmap &icon, QString hint, int r, QWidget *parent)
    : QPushButton(parent), m_radius(r), m_icon_hint(hint)
{
    m_icon_img = new QPixmap(icon);

    m_widget_ratio = m_icon_img->height() / m_icon_img->width();
    m_background_color = DEFAULT_COLOR;

}

void GuiIcon::setRotationAngle(qreal angle)
{
    m_rotation = angle;
    update();
}

qreal GuiIcon::getRotationAngle() const 
{
    return m_rotation;
}

void GuiIcon::paintEvent(QPaintEvent* event)
{
    resize(height() / m_widget_ratio, height());

    QPainter bg_painter(this);
    bg_painter.setRenderHints(QPainter::Antialiasing);
    bg_painter.setPen(Qt::NoPen);
    bg_painter.setBrush(m_background_color);
    bg_painter.drawRoundedRect(this->rect(), m_radius, m_radius);

    QPainter pixmap_painter(this);
    pixmap_painter.setRenderHints(QPainter::Antialiasing);
    pixmap_painter.translate(width() / 2, height() / 2);
    pixmap_painter.rotate(m_rotation);
    pixmap_painter.translate(-width() / 2, -height() / 2);
    int w = m_icon_size_rate * width();
    int h = m_icon_size_rate * height();
    pixmap_painter.drawPixmap(width() / 2 - w / 2, height() / 2 - h / 2, w, h, *m_icon_img);

}

void GuiIcon::enterEvent(QEnterEvent *event)
{
    m_background_color = DEFAULT_HOVER_COLOR;
    update();
}

void GuiIcon::leaveEvent(QEvent* event)
{
    m_background_color = DEFAULT_COLOR;
    update();
}

void GuiIcon::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
    setFocus();
    m_icon_size_rate -= 0.1;
    update();
}

void GuiIcon::mouseReleaseEvent(QMouseEvent* event)
{
    m_icon_size_rate += 0.1;
    update();
}

//*********************************************************//
//GuiSelectionItem class implementation
//*********************************************************//

GuiSelectionItem::GuiSelectionItem(QString name, QString info, QWidget *parent)
    : QWidget(parent)
{
    /* set labels */
    QFont title_font = QFont("Corbel", 13);
    QFontMetrics fm(title_font);
    qreal height = fm.lineSpacing();
    m_title = new QLabel(this);
    m_title->setText(name);
    m_title->setFont(title_font);
    m_title->setMinimumHeight(height);
    m_title->setStyleSheet("color:#2c2c2c");
    m_title->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    QFont desc_font = QFont("Corbel Light", 11);
    fm = QFontMetrics(desc_font);
    height = fm.lineSpacing();
    m_description = new QLabel(this);
    m_description->setText(info);
    m_description->setFont(desc_font);
    m_description->setMinimumHeight(height);
    m_description->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_description->setStyleSheet("color:#707070");

    m_indicator = new QWidget(this);

    /* set minimum height and layout */
    setFixedHeight(m_title->height() + (info == "" ? 0 : m_description->height() + 5));
    m_indicator->resize(6, 0.4 * this->height());
    m_indicator->move(4, 0.3 * this->height());
    m_indicator->setStyleSheet("border-radius:3px;background-color:#0078D4");
    m_opac = new QGraphicsOpacityEffect(m_indicator);
    m_opac->setOpacity(0);
    m_indicator->setGraphicsEffect(m_opac);

    QVBoxLayout* content_layout = new QVBoxLayout(this);
    content_layout->setContentsMargins(20, 0, 0, 0);
    content_layout->setSpacing(2);
    this->setLayout(content_layout);
    content_layout->addWidget(m_title);
    if(info != "") {
        content_layout->addWidget(m_description);
    }
    content_layout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    /* set background widget */
    m_bg_widget = new QWidget(this);
    m_bg_widget->resize(this->size());
    m_bg_widget->setStyleSheet("border-radius:5px;background-color:#00000000");
    m_bg_widget->lower();
    m_bg_widget->show();

    this->setMouseTracking(true);
}

void GuiSelectionItem::enterEvent(QEnterEvent* event)
{
    m_bg_widget->setStyleSheet("border-radius:5px;background-color:#0a000000");
    QParallelAnimationGroup *enter = new QParallelAnimationGroup(this);
    QPropertyAnimation* longer = new QPropertyAnimation(m_indicator, "geometry", this);
    longer->setStartValue(m_indicator->geometry());
    longer->setEndValue(QRectF(4, 0.25 * this->height(), 6, this->height() * 0.5));
    longer->setDuration(150);
    longer->setEasingCurve(QEasingCurve::OutBack);
    QPropertyAnimation* fade_in = new QPropertyAnimation(m_opac, "opacity", this);
    fade_in->setStartValue(m_opac->opacity());
    fade_in->setEndValue(0.99);
    fade_in->setDuration(100);
    enter->addAnimation(longer);
    enter->addAnimation(fade_in);
    enter->start();
}

void GuiSelectionItem::leaveEvent(QEvent* event)
{
    m_bg_widget->setStyleSheet("border-radius:5px;background-color:#00000000");
    QParallelAnimationGroup *leave = new QParallelAnimationGroup(this);
    QPropertyAnimation *shorter = new QPropertyAnimation(m_indicator, "geometry", this);
    shorter->setStartValue(m_indicator->geometry());
    shorter->setEndValue(QRectF(4, 0.3 * this->height(), 6, this->height() * 0.4));
    shorter->setDuration(150);
    shorter->setEasingCurve(QEasingCurve::OutBack);
    QPropertyAnimation *fade_out = new QPropertyAnimation(m_opac, "opacity", this);
    fade_out->setStartValue(m_opac->opacity());
    fade_out->setEndValue(m_on_selected ? 0.99 : 0);
    fade_out->setDuration(100);
    leave->addAnimation(shorter);
    leave->addAnimation(fade_out);
    leave->start();

    m_mouse_pressed = !m_mouse_pressed;
}

void GuiSelectionItem::mousePressEvent(QMouseEvent* event)
{
    m_bg_widget->setStyleSheet("border-radius:5px;background-color:#1a000000");
    QPropertyAnimation *shorter = new QPropertyAnimation(m_indicator, "geometry", this);
    shorter->setStartValue(m_indicator->geometry());
    shorter->setEndValue(QRectF(4, 0.4 * this->height(), 6, this->height() * 0.2));
    shorter->setDuration(100);
    shorter->setEasingCurve(QEasingCurve::OutBack);
    shorter->start();

    m_mouse_pressed = true;
}

void GuiSelectionItem::mouseReleaseEvent(QMouseEvent* event)
{
    if(m_mouse_pressed){
        m_bg_widget->setStyleSheet("border-radius:5px;background-color:#0a000000");
        QPropertyAnimation *longer = new QPropertyAnimation(m_indicator, "geometry", this);
        longer->setStartValue(m_indicator->geometry());
        longer->setEndValue(QRectF(4, 0.25 * this->height(), 6, this->height() * 0.5));
        longer->setDuration(150);
        longer->setEasingCurve(QEasingCurve::OutBack);
        longer->start();

        if(!m_on_selected){
            m_on_selected = true;
            m_title->setStyleSheet("color:#005FB8");
            m_description->setStyleSheet("color:#3a8fb7");
            emit selected(this);
            setFocus();
        }
        m_mouse_pressed = false;
    }
}

void GuiSelectionItem::resizeEvent(QResizeEvent* event)
{
    m_bg_widget->resize(this->size());
}

void GuiSelectionItem::select()
{
    if(!m_on_selected){
        m_on_selected = true;
        m_title->setStyleSheet("color:#005FB8");
        m_description->setStyleSheet("color:#3a8fb7");
        m_indicator->setGeometry(4, 0.5 * this->height(), 6, 0);

        QParallelAnimationGroup *sel = new QParallelAnimationGroup(this);
        QPropertyAnimation *longer = new QPropertyAnimation(m_indicator, "geometry", this);
        longer->setStartValue(m_indicator->geometry());
        longer->setEndValue(QRectF(4, 0.3 * this->height(), 6, this->height() * 0.4));
        longer->setDuration(150);
        longer->setEasingCurve(QEasingCurve::OutBack);
        QPropertyAnimation *fade_in = new QPropertyAnimation(m_opac, "opacity", this);
        fade_in->setStartValue(m_opac->opacity());
        fade_in->setEndValue(0.99);
        fade_in->setDuration(100);
        sel->addAnimation(longer);
        sel->addAnimation(fade_in);
        sel->start();

        emit selected(this);
    }
}

void GuiSelectionItem::deselect()
{
    if(m_on_selected){
        m_on_selected = false;
        m_title->setStyleSheet("color:#2c2c2c");
        m_description->setStyleSheet("color:#707070");

        QPropertyAnimation *fade_out = new QPropertyAnimation(m_opac, "opacity", this);
        fade_out->setStartValue(m_opac->opacity());
        fade_out->setEndValue(0.0);
        fade_out->setDuration(100);
        fade_out->start();
    }
}

void GuiSelectionItem::setTitle(QString title_text)
{
    m_title->setText(title_text);
}

void GuiSelectionItem::setDescription(QString desc_text)
{
    m_description->setText(desc_text);
}

//*********************************************************//
//selectionItem class implementation
//*********************************************************//

} // localminmax::gui
