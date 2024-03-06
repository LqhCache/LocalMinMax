/*
* @Author: Qianhua Liu
* @Date: 2024-03-04
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_GUI_MAINWINDOW_H
#define LOCALMINMAX_GUI_MAINWINDOW_H

#include <memory>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QLineEdit>
#include <QtGui/QMouseEvent>
#include <QtCore/QVector>

#include "common/Math.h"
#include "gui/SlidePage.h"

QT_BEGIN_NAMESPACE
namespace Ui { 
class MainWindow; 
} // Ui
QT_END_NAMESPACE

namespace localminmax::gui {

enum class Position {
    AT_LEFT = 1, 
    AT_TOP = 2,  
    AT_RIGHT = 4, 
    AT_BOTTOM = 8,
    AT_TOP_LEFT = AT_LEFT | AT_TOP, 
    AT_TOP_RIGHT = AT_RIGHT | AT_TOP, 
    AT_BOTTOM_LEFT = AT_LEFT | AT_BOTTOM, 
    AT_BOTTOM_RIGHT = AT_RIGHT | AT_BOTTOM
};

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void init();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
    void controlWindowScale();

    int32_t m_corner_radius = 20;
    QWidget* m_border = nullptr;
    QWidget* m_default_page = nullptr;
    QGraphicsDropShadowEffect* m_window_shadow = nullptr;

    QLineEdit* m_canvas_title = nullptr;
    QLineEdit* m_canvas_desc = nullptr;
    GuiIcon* m_settings_icon = nullptr;
    GuiIcon* m_layers_icon = nullptr;
    QWidget* m_canvas_display = nullptr;

    QVector<SlidePage*> m_page_list;
    SlidePage* m_create_new_page = nullptr;
    SlidePage* m_default_settings_page = nullptr;
    SlidePage* m_cur_settings_page = nullptr;
    SlidePage* m_layers_page = nullptr;
    GuiSingleSelectGroup* m_layer_select = nullptr;

    bool m_maximized = false;
    bool m_mouse_pressed = false;
    Position m_mouse_state;

    QColor m_mian_back_ground = QColor(251, 251, 251);
    QPoint m_last_pos;
    QRect m_last_geometry;

private:
    Ui::MainWindow* m_ui;
};

} // localminmax::gui

#endif // LOCALMINMAX_GUI_MAINWINDOW_H