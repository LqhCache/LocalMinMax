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

class GuiIcon : public QPushButton {
    Q_OBJECT
    Q_PROPERTY(qreal getRotationAngle READ getRotationAngle 
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
    QString m_icon_hint;
    QPixmap* m_icon_img = nullptr;

    /* for hover and click effects */
    QColor m_background_color;
};

class GuiSelectionItem : public QWidget {
    Q_OBJECT
signals:
    void selected(GuiSelectionItem* item);
    // void heightChange();
public:
    GuiSelectionItem(QString name, QString info = "", QWidget *parent = nullptr);
    void select();
    void deselect();
    void setTitle(QString title_text);
    void setDescription(QString desc_text);

private:
    void enterEvent(QEnterEvent* event);
    void leaveEvent(QEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent* event);

    QLabel* m_title = nullptr;
    QLabel* m_description = nullptr;
    QWidget* m_indicator = nullptr;
    QWidget* m_mainContent = nullptr;
    QWidget* m_bg_widget = nullptr;
    QGraphicsOpacityEffect* m_opac = nullptr;
    bool m_on_selected = false;
    bool m_mouse_pressed = false;
};

class GuiSingleSelectGroup : public QWidget{
    Q_OBJECT
signals:
    void selectedItemChange(int select_id);
    void itemChange();

private slots:
    void changeSelection(GuiSelectionItem *item);

public:
    GuiSingleSelectGroup(QString name = "", QWidget* parent = nullptr);
    void addItem(GuiSelectionItem* item);
    void removeItem(GuiSelectionItem* item);
    void setSelection(GuiSelectionItem* item);
    qreal value();

private:
    int32_t m_select_id = -1;
    QLabel* m_group_name = nullptr;
    QVBoxLayout* m_main_layout = nullptr;
    QVector<GuiSelectionItem*> selections;
};

class GuiHorizontalValueAdjuster : public QWidget{
    Q_OBJECT
signals:
    void valueChanged(qreal value);

public:
    GuiHorizontalValueAdjuster(QString name, qreal min, qreal max, qreal step, QWidget *parent = nullptr);
    void setValue(qreal value);
    qreal getValue();

private:
    qreal m_cur_value;
    qreal m_min_value;
    qreal m_max_value;
    qreal m_step_value;
    QLabel* m_title = nullptr;
    QLabel* m_value_label = nullptr;
    QWidget* m_edit_area = nullptr;
    GuiIcon* decrease_btn = nullptr;
    GuiIcon* increase_btn = nullptr;
    QSlider* slider = nullptr;
};

class GuiBigIconButton : public QWidget{
    Q_OBJECT
signals:
    void clicked();
    void selected();

public:
    GuiBigIconButton(const QString &iconPath, const QString &description, int radius, QWidget *parent = nullptr);
    void setSelectable(bool selectable = true);
    void setScale(qreal scale);

private:
    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

    int32_t m_corner_radius;

    bool m_selectable = false;
    bool m_mouse_pressed = false;
    bool m_on_selected = false;

    QString m_radius_style;

    QPixmap* m_icon_img = nullptr;
    QLabel* m_text = nullptr;
    QLabel* m_icon = nullptr;
    QWidget* m_background_widget = nullptr;
    QWidget* m_indicator = nullptr;
};

class GuiTextInputItem : public QWidget{
    Q_OBJECT
signals:
    void textEdited(QString text);

public:
    GuiTextInputItem(const QString &name, QWidget *parent = nullptr);
    QLineEdit* getLineEditor();
    QString getValue();

    void setValue(const QString& text);
    void setValidator(QValidator* validator);
    void setEnabled(bool enable = true);

private:
    void enterEditEffect();
    void leaveEditEffect();

    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

    bool m_mouse_pressed = false;
    bool m_on_editing = false;
    bool m_enabled = true;

    QString m_cur_text = "";
    QLabel* m_item_name = nullptr;
    QLineEdit* m_editor = nullptr;
    QWidget* m_background_widget = nullptr;
    QWidget* m_indicator = nullptr;
    QGraphicsOpacityEffect* m_opac = nullptr;
};

class GuiTextButton : public QWidget{
    Q_OBJECT
signals:
    void clicked();

public:
    GuiTextButton(QString text, QWidget* parent = nullptr, qreal ratio = 0.5);
    GuiTextButton(QString text, QString default_color, QString hover_color, QString pressed_color, 
                  QWidget *parent = nullptr, qreal ratio = 0.5);

private:
    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

    bool m_mouse_pressed;

    QString m_default_color = "#0a0078d4";
    QString m_hover_color = "#1a0078d4";
    QString m_pressed_color = "#2a0078d4";
 
    QLabel* m_btn_text = nullptr;
    QWidget* m_background_widget = nullptr;
};

} // localminmax::gui

#endif // LOCALMINMAX_GUI_GUIWIDGETS_H