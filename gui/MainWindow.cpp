/*
* @Author: Qianhua Liu
* @Date: 2024-03-04
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/

#include "gui/MainWindow.h"

#include <QtGui/QPainterPath>
#include <QtGui/QRegion>
#include <QtCore/QTimer>

#include "forms/ui_MainWindow.h"

namespace localminmax::gui {

MainWindow::MainWindow(QWidget* parent) 
    : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    m_ui->centralwidget->setMouseTracking(true);
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=](){
        init();
    });
    timer->setSingleShot(true);
    timer->start(10);

    connect(m_ui->adjSizeBtn, &QPushButton::clicked, this, [=](){controlWindowScale();});
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::init()
{
    QPainterPath path;
    path.addRoundedRect(m_ui->mainWidget->rect(), m_corner_radius - 1, m_corner_radius - 1);

    QRegion mask(path.toFillPolygon().toPolygon());
    m_ui->mainWidget->setMask(mask);

    QString main_style;
    m_ui->mainWidget->setObjectName("mainWidget");
    main_style = "QWidget#mainWidget{background-color:" + m_mian_back_ground.name() + 
                 QString::asprintf(";border-radius:%dpx", m_corner_radius) + "}";
    
    m_ui->mainWidget->setStyleSheet(main_style);
    m_window_shadow = new QGraphicsDropShadowEffect(this);
    m_window_shadow->setBlurRadius(30);
    m_window_shadow->setColor(QColor(0, 0, 0));
    m_window_shadow->setOffset(0, 0);
    m_ui->mainWidget->setGraphicsEffect(m_window_shadow);
    
    // create border
    m_border = new QWidget(this);
    m_border->move(m_ui->mainWidget->pos() - QPoint(1, 1));
    m_border->resize(m_ui->mainWidget->size() + QSize(2, 2));
    QString border_style;
    border_style = "background-color:#00FFFFFF;border:1.5px solid #686868; border-radius:" + 
                   QString::asprintf("%d", m_corner_radius) + "px";
    m_border->setStyleSheet(border_style);
    m_border->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_border->show();

    // TODO: create about page

    // create display area
    QFont title_font = QFont("Corbel Light", 24);
    QFontMetrics title_fm(title_font);
    m_canvas_title = new QLineEdit(this);
    m_canvas_title->setFont(title_font);
    m_canvas_title->setText("START");
    m_canvas_title->setMaxLength(20);
    m_canvas_title->setReadOnly(true);
    m_canvas_title->setMinimumHeight(title_fm.height());
    m_canvas_title->setMaximumWidth(title_fm.size(Qt::TextSingleLine, "START").width() + 10);
    m_canvas_title->setStyleSheet("background-color:#00000000;border-style:none;border-width:0px;margin-left:1px;");
    connect(m_canvas_title, &QLineEdit::textEdited, m_canvas_title, [=](QString text){
        m_canvas_title->setMaximumWidth(title_fm.size(Qt::TextSingleLine, text).width());
    });

    QFont desc_font = QFont("Corbel Light", 12);
    QFontMetrics desc_fm(desc_font);
    m_canvas_desc = new QLineEdit(this);
    m_canvas_desc->setFont(desc_font);
    m_canvas_desc->setText("Add your first canvas to start");
    m_canvas_desc->setMaxLength(128);
    m_canvas_desc->setReadOnly(true);
    m_canvas_desc->setMinimumHeight(desc_fm.lineSpacing());
    m_canvas_desc->setStyleSheet("background-color:#00000000;border-style:none;border-width:0px;");

    // create title
    QWidget* title_inner_widget = new QWidget(this);
    title_inner_widget->setFixedHeight(m_canvas_title->height());
    QHBoxLayout* inner_layout = new QHBoxLayout(title_inner_widget);
    title_inner_widget->setLayout(inner_layout);
    inner_layout->setContentsMargins(0, 0, 0, 0);
    inner_layout->setSpacing(10);
    inner_layout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    inner_layout->addWidget(m_canvas_title);

    QWidget* title_widget = new QWidget(this);
    title_widget->setMaximumHeight(m_canvas_title->height() + m_canvas_desc->height());
    QVBoxLayout* outer_layout = new QVBoxLayout(title_widget);
    title_widget->setLayout(outer_layout);
    outer_layout->setContentsMargins(0, 0, 0, 0);
    outer_layout->setSpacing(0);
    outer_layout->addWidget(title_inner_widget);
    outer_layout->addWidget(m_canvas_desc);

    // create default page
    
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    m_mouse_pressed = false;
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    if(event->globalPosition().y() < 2)
        controlWindowScale();
#else
    if(event->globalPos().y() < 2)
        controlWindowScale();
#endif
}

void MainWindow::resizeEvent(QResizeEvent *event)
{

}

void MainWindow::controlWindowScale()
{

}

} // localminmax::gui
