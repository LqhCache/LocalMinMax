/*
* @Author: Qianhua Liu
* @Date: 2024-03-04
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/

#include "gui/GuiWidgets.h"

namespace localminmax::gui {

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

} // localminmax::gui
