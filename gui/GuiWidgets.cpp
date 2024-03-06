/*
* @Author: Qianhua Liu
* @Date: 2024-03-04
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/

#include "gui/GuiWidgets.h"

namespace localminmax::gui {
const int32_t DEFAULT_MIDDLE_SPACING = 5;
const int32_t DEFAULT_BOTTOM_SPACING = 30;
const int32_t DEFAULT_MARGIN = 10;
const int32_t DEFAULT_SPACING = 10;

constexpr QColor DEFAULT_COLOR = QColor(0, 0, 0, 0);
constexpr QColor DEFAULT_HOVER_COLOR = QColor(241, 241, 241, 200);

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

    m_mouse_pressed = false;
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
//GuiSingleSelectGroup class implementation
//*********************************************************//
GuiSingleSelectGroup::GuiSingleSelectGroup(QString name, QWidget *parent) :
    QWidget(parent)
{
    QFont title_font = QFont("Corbel", 16);
    QFontMetrics fm(title_font);
    qreal height = fm.lineSpacing();
    m_group_name = new QLabel(this);
    m_group_name->setMinimumHeight(height);
    m_group_name->setFont(title_font);
    m_group_name->setText(name);

    QWidget* spacing_line = new QWidget(this);
    spacing_line->setFixedHeight(1);
    spacing_line->setStyleSheet("background-color:#0a000000");

    this->setFixedHeight(m_group_name->height() + DEFAULT_MIDDLE_SPACING + 1 + DEFAULT_BOTTOM_SPACING);

    m_main_layout = new QVBoxLayout(this);
    m_main_layout->setContentsMargins(10, 0, 10, DEFAULT_BOTTOM_SPACING);
    m_main_layout->setSpacing(DEFAULT_MIDDLE_SPACING);
    m_main_layout->addWidget(m_group_name);
    m_main_layout->addWidget(spacing_line);
}

qreal GuiSingleSelectGroup::value()
{
    return m_select_id;
}

void GuiSingleSelectGroup::addItem(GuiSelectionItem *item)
{
    selections.push_back(item);
    this->setFixedHeight(this->height() + DEFAULT_MIDDLE_SPACING + item->height());
    m_main_layout->addWidget(item);
    if(m_select_id == -1){
        item->select();
        m_select_id = 0;
    }
    connect(item, SIGNAL(selected(selectionItem*)), this, SLOT(changeSelection(selectionItem*)));
    emit itemChange();
}

void GuiSingleSelectGroup::removeItem(GuiSelectionItem *item)
{
    int id = selections.indexOf(item);
    if (id < 0) {
        return;
    }
    selections.erase(selections.begin() + id);
    m_main_layout->removeWidget(item);
    item->setParent(nullptr);
    item->deleteLater();
    this->setFixedHeight(this->height() - DEFAULT_MIDDLE_SPACING - item->height());
    if(selections.size() == 0)
        m_select_id = -1;
    else{
        m_select_id = id < selections.size() ? id : id - 1;
        selections[m_select_id]->select();
    }
    emit selectedItemChange(m_select_id);
    emit itemChange();
}

void GuiSingleSelectGroup::setSelection(GuiSelectionItem *item)
{
    int id = selections.indexOf(item);
    selections[id]->select();
}

void GuiSingleSelectGroup::changeSelection(GuiSelectionItem *item)
{
    int id = selections.indexOf(item);
    for(int i = 0; i < selections.size(); i++){
        if(i == id) continue;
        selections[i]->deselect();
    }
    m_select_id = id;
    emit selectedItemChange(id);
}

//*********************************************************//
//GuiHorizontalValueAdjuster class implementation
//*********************************************************//
GuiHorizontalValueAdjuster::GuiHorizontalValueAdjuster(
    QString name, qreal min, qreal max, qreal step, QWidget *parent)
    : QWidget(parent), m_cur_value(min), m_min_value(min), m_max_value(max), m_step_value(step)
{
    QFont title_font = QFont("Corbel", 16);
    QFontMetrics fm(title_font);
    qreal height = fm.lineSpacing();
    m_title = new QLabel(this);
    m_title->setMinimumHeight(height);
    m_title->setFont(title_font);
    m_title->setText(name);

    QWidget* spacing_line = new QWidget(this);
    spacing_line->setFixedHeight(1);
    spacing_line->setStyleSheet("background-color:#0a000000");

    slider = new QSlider(Qt::Horizontal, this);
    slider->setMinimum(0);
    slider->setMaximum((max - min) / step + 1);
    slider->setPageStep(1);
    QString groove_style = "QSlider::groove:horizontal{height:6px; border-radius:3px;} ";
    QString slider_style = "QSlider::handle:horizontal{width:12px; margin-bottom:-3px; margin-top:-3px; background:#c2c2c2; border-radius:6px;} ";
    QString slider_h_style = "QSlider::handle:horizontal:hover{width:12px; margin-bottom:-3px; margin-top:-3px; background:#3a8fb7; border-radius:6px;} ";
    QString slider_p_style = "QSlider::handle:horizontal:pressed{width:12px; margin-bottom:-3px; margin-top:-3px; background:#005fb8; border-radius:6px;} ";
    QString sub_style = "QSlider::sub-page:horizontal{background:#0078D4; border-radius:3px} ";
    QString add_style = "QSlider::add-page:horizontal{background:#1a000000; border-radius:3px} ";
    slider->setStyleSheet(groove_style + slider_style + slider_h_style + slider_p_style + sub_style + add_style);


    QFont value_font = QFont("Corbel", 13);
    fm = QFontMetrics(title_font);
    height = fm.lineSpacing();
    m_value_label = new QLabel(this);
    m_value_label->setMinimumHeight(height);
    m_value_label->setFont(value_font);
    m_value_label->setText(QString::asprintf("%g", min));
    m_value_label->setMinimumWidth(30);
    m_value_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_value_label->setStyleSheet("margin-bottom:5px");

    QWidget *content = new QWidget(this);
    content->setMinimumHeight(m_value_label->height() < slider->height() ? 
                              m_value_label->height() : slider->height());
    QHBoxLayout *content_layout = new QHBoxLayout(content);
    content_layout->setAlignment(Qt::AlignVCenter);
    content->setLayout(content_layout);
    content_layout->setContentsMargins(0, 0, 0, 0);
    content_layout->setSpacing(10);
    content_layout->addWidget(m_value_label);
    content_layout->addWidget(slider);

    this->setMinimumHeight(m_title->height() + 2 * DEFAULT_MIDDLE_SPACING + 1 + 
                           content->height() + DEFAULT_BOTTOM_SPACING);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);
    mainLayout->setContentsMargins(10, 0, 10, DEFAULT_BOTTOM_SPACING);
    mainLayout->setSpacing(DEFAULT_MIDDLE_SPACING);
    mainLayout->addWidget(m_title);
    mainLayout->addWidget(spacing_line);
    mainLayout->addWidget(content);

    connect(slider, &QSlider::valueChanged, this, [=](qreal value) {
        m_value_label->setText(QString::asprintf("%g", value * m_step_value + m_min_value));
        m_cur_value = value * m_step_value + m_min_value;
        emit valueChanged(m_cur_value);
    });
}

void GuiHorizontalValueAdjuster::setValue(qreal value)
{
    m_value_label->setText(QString::asprintf("%g", value));
    slider->setValue((value - m_min_value) / m_step_value);
    m_cur_value = value;
    emit valueChanged(value);
}

//*********************************************************//
//GuiHorizontalValueAdjuster class implementation
//*********************************************************//
GuiBigIconButton::GuiBigIconButton(const QString &iconPath, const QString &description, 
                                   int radius, QWidget *parent)
    : QWidget(parent), m_corner_radius(radius)
{
    m_icon_img = new QPixmap(iconPath);

    /* set icon label and text label */
    m_icon = new QLabel(this);
    m_icon->setPixmap(*m_icon_img);
    m_icon->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_icon->setAlignment(Qt::AlignCenter);

    QFont text_font = QFont("Corbel", 13);
    QFontMetrics fm(text_font);
    m_text = new QLabel(this);
    m_text->setFont(text_font);
    m_text->setText(description);
    m_text->setWordWrap(true);
    m_text->setMinimumHeight(fm.lineSpacing());
    m_text->setAlignment(Qt::AlignCenter);

    /* set indicator */
    m_indicator = new QWidget(this);
    m_indicator->resize(6, 6);
    m_indicator->move(this->width() - 3, this->height() - 21);
    m_indicator->setStyleSheet("border-radius:3px;background-color:#afafaf");

    /* set background */
    m_background_widget = new QWidget(this);
    m_background_widget->resize(this->size());
    m_radius_style = QString::asprintf("border-radius:%dpx;", m_corner_radius);
    m_background_widget->setStyleSheet(m_radius_style + "background-color:#04000000");
    m_background_widget->lower();
    m_background_widget->show();

    /* set layout */
    QVBoxLayout* layout = new QVBoxLayout(this);
    this->setLayout(layout);
    layout->setContentsMargins(15, 35, 15, 35);
    layout->setSpacing(15);
    layout->addWidget(m_icon);
    layout->addWidget(m_text);
    layout->setAlignment(Qt::AlignCenter);

    this->setMinimumHeight(200);
}

void GuiBigIconButton::setSelectable(bool selectable)
{
    m_selectable = selectable;
}

void GuiBigIconButton::resizeEvent(QResizeEvent *event)
{
    m_background_widget->setFixedSize(this->size());
    if(m_on_selected){
        m_indicator->resize(this->width() * 0.1, 6);
        m_indicator->move(this->width() * 0.45, this->height() - 21);
    }
    else{
        m_indicator->resize(this->width() * 0.1, 6);
        m_indicator->move(this->width() * 0.45, this->height() - 21);
    }
}

void GuiBigIconButton::enterEvent(QEnterEvent *event)
{
    m_background_widget->setStyleSheet(m_corner_radius + "background-color:#0a0078D4");
    QPropertyAnimation* longer = new QPropertyAnimation(m_indicator, "geometry", this);
    longer->setStartValue(m_indicator->geometry());
    longer->setEndValue(QRectF(this->width() * 0.2, this->height() - 21, this->width() * 0.6, 6));
    longer->setDuration(150);
    longer->setEasingCurve(QEasingCurve::OutBack);
    longer->start();

    m_indicator->setStyleSheet("border-radius:3px;background-color:#0078d4");
}

void GuiBigIconButton::leaveEvent(QEvent *event)
{
    m_background_widget->setStyleSheet(m_radius_style + "background-color:#04000000");
    QPropertyAnimation *shorter = new QPropertyAnimation(m_indicator, "geometry", this);
    shorter->setStartValue(m_indicator->geometry());
    if(!m_on_selected) {
        shorter->setEndValue(QRectF(this->width() * 0.45, this->height() - 21, this->width() * 0.1, 6));
    }else {
        shorter->setEndValue(QRectF(this->width() * 0.3, this->height() - 21, this->width() * 0.4, 6));
    }
    shorter->setDuration(250);
    shorter->setEasingCurve(QEasingCurve::OutBack);
    shorter->start();

    if(!m_on_selected) {
        m_indicator->setStyleSheet("border-radius:3px;background-color:#afafaf");
    }
    m_mouse_pressed = false;
}

void GuiBigIconButton::mousePressEvent(QMouseEvent *event)
{
    m_background_widget->setStyleSheet(m_radius_style + "background-color:#1a0078D4");
    QPropertyAnimation *shorter = new QPropertyAnimation(m_indicator, "geometry", this);
    shorter->setStartValue(m_indicator->geometry());
    shorter->setEndValue(QRectF(this->width() * 0.4, this->height() - 21, this->width() * 0.2, 6));
    shorter->setDuration(100);
    shorter->setEasingCurve(QEasingCurve::OutBack);
    shorter->start();

    m_mouse_pressed = true;
}

void GuiBigIconButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_mouse_pressed){
        m_background_widget->setStyleSheet(m_radius_style + "background-color:#0a0078D4");
        QPropertyAnimation *longer = new QPropertyAnimation(m_indicator, "geometry", this);
        longer->setStartValue(m_indicator->geometry());
        longer->setEndValue(QRectF(this->width() * 0.2, this->height() - 21, this->width() * 0.6, 6));
        longer->setDuration(150);
        longer->setEasingCurve(QEasingCurve::OutBack);
        longer->start();

        m_mouse_pressed = false;
        emit clicked();
        if (m_selectable){ 
            emit selected();
            m_mouse_pressed = true;
        }
    }
}

void GuiBigIconButton::setScale(qreal scale)
{
    m_icon_img = new QPixmap(m_icon_img->scaled(m_icon_img->size() * scale, 
                             Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_icon->setPixmap(*m_icon_img);
}

//*********************************************************//
//GuiTextInputItem class implementation
//*********************************************************//
GuiTextInputItem::GuiTextInputItem(const QString &name, QWidget *parent)
    : QWidget(parent)
{
    QFont name_font = QFont("Corbel", 12);
    QFontMetrics fm(name_font);
    qreal height = fm.lineSpacing();
    m_item_name = new QLabel(this);
    m_item_name->setText(name);
    m_item_name->setFont(name_font);
    m_item_name->setFixedHeight(height);
    m_item_name->setStyleSheet("color:#1c1c1c");

    QFont text_font = QFont("Corbel", 12);
    fm = QFontMetrics(text_font);
    m_editor = new QLineEdit(this);
    m_editor->setText("");
    m_editor->setFixedHeight(fm.lineSpacing());
    m_editor->setStyleSheet("color:#5c5c5c;background-color:#00000000;border-style:none;");
    m_editor->setReadOnly(true);
    m_editor->setFont(text_font);

    m_background_widget = new QWidget(this);
    m_background_widget->setStyleSheet("background-color:#00000000;border-radius:5px;");
    m_background_widget->lower();
    m_background_widget->show();

    m_indicator = new QWidget(this);
    m_indicator->setFixedHeight(4);
    m_indicator->setStyleSheet("background-color:#0078d4;border-radius:2px");

    m_opac = new QGraphicsOpacityEffect(this);
    m_opac->setOpacity(0);
    m_indicator->setGraphicsEffect(m_opac);

    this->setFixedHeight(m_item_name->height() + 10);

    connect(m_editor, &QLineEdit::returnPressed, this, [=]() {
        leaveEditEffect();
        m_on_editing = false;
        m_editor->setReadOnly(true);
        m_cur_text = m_editor->text();
    });
    connect(m_editor, &QLineEdit::editingFinished, this, [=]() {
        leaveEditEffect();
        m_on_editing = false;
        m_editor->setReadOnly(true);
        m_cur_text = m_editor->text();
        QTimer *delay = new QTimer(this);
        connect(delay, &QTimer::timeout, this, [=](){
            m_mouse_pressed = false;
        });
        delay->setSingleShot(true);
        delay->start(10);
        m_mouse_pressed = false;
        emit textEdited(m_cur_text);
    });
}

void GuiTextInputItem::setValidator(QValidator* validator)
{
    m_editor->setValidator(validator);
}

void GuiTextInputItem::setEnabled(bool enabled)
{
    m_enabled = enabled;
}

void GuiTextInputItem::resizeEvent(QResizeEvent *event)
{
    m_item_name->move(DEFAULT_MARGIN, this->height() / 2 - m_item_name->height() / 2);
    m_item_name->setFixedWidth(this->width() * 0.3 - DEFAULT_MARGIN - DEFAULT_SPACING);
    int width = QFontMetrics(m_editor->font()).size(Qt::TextSingleLine, m_editor->text()).width() + 3;
    if(!m_on_editing){
        if(width > this->width() * 0.7 - DEFAULT_MARGIN) {
            m_editor->resize(this->width() * 0.7 - DEFAULT_MARGIN, m_editor->height());
        }else {
            m_editor->resize(width, m_editor->height());
        }
        m_editor->move(this->width() - DEFAULT_MARGIN - m_editor->width(), this->height() / 2 - m_editor->height() / 2);
        m_indicator->move(this->width() - DEFAULT_MARGIN, this->height() - 7);
    }
    else{
        m_editor->resize(this->width() * 0.7 - DEFAULT_MARGIN, m_editor->height());
        m_editor->move(this->width() * 0.3, this->height() / 2 - m_editor->height() / 2 - 2);
        m_indicator->move(this->width() * 0.3, this->height() - 7);
    }
    m_background_widget->setFixedSize(this->size());
}

void GuiTextInputItem::enterEditEffect()
{
    m_editor->setCursorPosition(m_editor->text().length());
    m_editor->setStyleSheet("color:#1c1c1c;background-color:#00000000;border-style:none;");
    QParallelAnimationGroup* group = new QParallelAnimationGroup(this);
    QPropertyAnimation* longer = new QPropertyAnimation(m_indicator, "geometry", this);
    longer->setStartValue(m_indicator->geometry());
    longer->setEndValue(QRectF(this->width() * 0.3, this->height() - 7, this->width() * 0.7 - DEFAULT_MARGIN, 4));
    longer->setDuration(500);
    longer->setEasingCurve(QEasingCurve::InOutExpo);
    QPropertyAnimation* fade = new QPropertyAnimation(m_opac, "opacity", this);
    fade->setStartValue(m_opac->opacity());
    fade->setEndValue(0.99);
    fade->setDuration(150);
    QPropertyAnimation* move = new QPropertyAnimation(m_editor, "geometry", this);
    move->setStartValue(m_editor->geometry());
    move->setEndValue(QRectF(this->width() * 0.3, this->height() / 2 - m_editor->height() / 2 - 2, 
                      this->width() * 0.7 - DEFAULT_MARGIN, m_editor->height()));
    move->setDuration(500);
    move->setEasingCurve(QEasingCurve::InOutExpo);
    group->addAnimation(longer);
    group->addAnimation(fade);
    group->addAnimation(move);
    group->start();
}

void GuiTextInputItem::leaveEditEffect()
{
    m_editor->setCursorPosition(0);
    m_editor->setStyleSheet("color:#5c5c5c;background-color:#00000000;border-style:none;");
    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
    QPropertyAnimation *shorter = new QPropertyAnimation(m_indicator, "geometry", this);
    shorter->setStartValue(m_indicator->geometry());
    shorter->setEndValue(QRectF(this->width() - DEFAULT_MARGIN - 4, this->height() - 7, 4, 4));
    shorter->setDuration(500);
    shorter->setEasingCurve(QEasingCurve::InOutExpo);
    QPropertyAnimation *fade = new QPropertyAnimation(m_opac, "opacity", this);
    fade->setStartValue(m_opac->opacity());
    fade->setEndValue(0.0);
    fade->setDuration(350);
    QPropertyAnimation *move = new QPropertyAnimation(m_editor, "geometry", this);
    move->setStartValue(m_editor->geometry());
    int width = QFontMetrics(m_editor->font()).size(Qt::TextSingleLine, m_editor->text()).width() + 3;
    if(width > this->width() * 0.7 - DEFAULT_MARGIN) {
        move->setEndValue(QRectF(this->width() * 0.3, this->height() / 2 - m_editor->height() / 2, 
                          this->width() * 0.7 - DEFAULT_MARGIN, m_editor->height()));
    }else {
        move->setEndValue(QRectF(this->width() - width - DEFAULT_MARGIN, this->height() / 2 - m_editor->height() / 2, 
                          width, m_editor->height()));
    }
    move->setDuration(500);
    move->setEasingCurve(QEasingCurve::InOutExpo);
    group->addAnimation(shorter);
    group->addAnimation(fade);
    group->addAnimation(move);
    group->start();
}

void GuiTextInputItem::enterEvent(QEnterEvent *event)
{
    m_background_widget->setStyleSheet("border-radius:5px;background-color:#0a000000");
}

void GuiTextInputItem::leaveEvent(QEvent *event)
{
    m_background_widget->setStyleSheet("border-radius:5px;background-color:#00000000");
}

void GuiTextInputItem::mousePressEvent(QMouseEvent *event)
{
    m_background_widget->setStyleSheet("border-radius:5px;background-color:#1a000000");
    m_mouse_pressed = true;
}

void GuiTextInputItem::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_mouse_pressed){
        m_background_widget->setStyleSheet("border-radius:5px;background-color:#0a000000");
        if(m_on_editing) {
            leaveEditEffect();
            m_on_editing = false;
            m_cur_text = m_editor->text();
            m_editor->setReadOnly(true);
            emit textEdited(m_cur_text);
        }
        else{
            if(m_enabled) {
                enterEditEffect();
                m_editor->raise();
                m_on_editing = true;
                m_editor->setReadOnly(false);
                m_editor->setText(m_cur_text + "");
                m_editor->setFocus();
            }
        }
        m_mouse_pressed = false;
    }
}

void GuiTextInputItem::setValue(const QString &text)
{
    m_editor->setText(text);
    m_editor->setCursorPosition(0);
    m_cur_text = text;
    int width = QFontMetrics(m_editor->font()).size(Qt::TextSingleLine, m_editor->text()).width() + 3;
    if(!m_on_editing){
        if(width > this->width() * 0.7 - DEFAULT_MARGIN) {
            m_editor->resize(this->width() * 0.7 - DEFAULT_MARGIN, m_editor->height());
        }else {
            m_editor->resize(width, m_editor->height());
        }
        m_editor->move(this->width() - DEFAULT_MARGIN - m_editor->width(), this->height() / 2 - m_editor->height() / 2);
    }
    else{
        m_editor->resize(this->width() * 0.7 - DEFAULT_MARGIN, m_editor->height());
        m_editor->move(this->width() * 0.3, this->height() / 2 - m_editor->height() / 2 - 2);
    }
}

//*********************************************************//
//GuiTextButton class implementation
//*********************************************************//
GuiTextButton::GuiTextButton(QString text, QWidget *parent, qreal ratio)
    : QWidget(parent)
{
    QFont text_font = QFont("Corbel", 10);
    QFontMetrics fm(text_font);
    qreal height = fm.lineSpacing();
    m_btn_text = new QLabel(this);
    m_btn_text->setText(text);
    m_btn_text->setFont(text_font);
    m_btn_text->setFixedHeight(height);
    m_btn_text->setFixedWidth(fm.size(Qt::TextSingleLine, text).width() + 2);
    m_btn_text->setStyleSheet("color:#1c1c1c");
    m_btn_text->setAlignment(Qt::AlignCenter);

    m_background_widget = new QWidget(this);
    m_background_widget->setStyleSheet("background-color:" + m_default_color + ";border-radius:5px;");

    this->setFixedHeight(m_btn_text->height() / ratio);
}

GuiTextButton::GuiTextButton(QString text, QString default_color, QString hover_color, 
                             QString pressed_color, QWidget *parent, qreal ratio)
    : QWidget(parent), m_default_color(default_color), m_hover_color(hover_color), m_pressed_color(pressed_color)
{
    QFont text_font = QFont("Corbel", 10);
    QFontMetrics fm(text_font);
    qreal height = fm.lineSpacing();
    m_btn_text = new QLabel(this);
    m_btn_text->setText(text);
    m_btn_text->setFont(text_font);
    m_btn_text->setFixedHeight(height);
    m_btn_text->setFixedWidth(fm.size(Qt::TextSingleLine, text).width() + 2);
    m_btn_text->setStyleSheet("color:#1c1c1c");
    m_btn_text->setAlignment(Qt::AlignCenter);

    m_background_widget = new QWidget(this);
    m_background_widget->setStyleSheet("background-color:" + m_default_color + ";border-radius:5px;");

    this->setFixedHeight(m_btn_text->height() / ratio);
}

void GuiTextButton::resizeEvent(QResizeEvent *event)
{
    m_background_widget->resize(this->size());
    m_btn_text->move(this->width() / 2 - m_btn_text->width() / 2, this->height() / 2 - m_btn_text->height() / 2);
}

void GuiTextButton::enterEvent(QEnterEvent *event)
{
    m_background_widget->setStyleSheet("background-color:" + m_hover_color + " ;border-radius:5px;");
}

void GuiTextButton::leaveEvent(QEvent *event)
{
    m_background_widget->setStyleSheet("background-color:" + m_default_color + ";border-radius:5px;");
    if(m_mouse_pressed){
        m_background_widget->setStyleSheet("background-color:" + m_pressed_color + ";border-radius:5px;");
        QPropertyAnimation* enlarge = new QPropertyAnimation(m_background_widget, "geometry", this);
        enlarge->setStartValue(m_background_widget->geometry());
        enlarge->setEndValue(QRect(0, 0, this->width(), this->height()));
        enlarge->setDuration(150);
        enlarge->setEasingCurve(QEasingCurve::OutBounce);
        enlarge->start();
        m_mouse_pressed = false;
    }
}

void GuiTextButton::mousePressEvent(QMouseEvent *event){
    m_background_widget->setStyleSheet("background-color:" + m_pressed_color + ";border-radius:5px;");
    QPropertyAnimation *shrink = new QPropertyAnimation(m_background_widget, "geometry", this);
    shrink->setStartValue(m_background_widget->geometry());
    shrink->setEndValue(QRect(0.05 * this->width(), 0.05 * this->height(), this->width() * 0.9, this->height() * 0.9));
    shrink->setDuration(100);
    shrink->setEasingCurve(QEasingCurve::OutBack);
    shrink->start();
    m_mouse_pressed = true;
    setFocus();
}

void GuiTextButton::mouseReleaseEvent(QMouseEvent *event){
    if(m_mouse_pressed){
        m_background_widget->setStyleSheet("background-color:" + m_hover_color + ";border-radius:5px;");
        QPropertyAnimation *enlarge = new QPropertyAnimation(m_background_widget, "geometry", this);
        enlarge->setStartValue(m_background_widget->geometry());
        enlarge->setEndValue(QRect(0, 0, this->width(), this->height()));
        enlarge->setDuration(150);
        enlarge->setEasingCurve(QEasingCurve::OutBounce);
        enlarge->start();
        m_mouse_pressed = false;
        emit clicked();
    }
}

} // localminmax::gui
