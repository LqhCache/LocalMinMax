/*
* @author: Qianhua Liu
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

    connect(m_ui->adjSizeBtn, &QPushButton::clicked, this, [=]() {
        controlWindowScale();
    });
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
    m_default_settings_page = new SlidePage(m_corner_radius, "ABOUT", m_ui->mainWidget);
    GuiTextInputItem* version = new GuiTextInputItem("version", m_default_settings_page);
    version->setValue("1.3-beta");
    version->setEnabled(false);
    GuiTextInputItem* m_update_date = new GuiTextInputItem("last-upd", m_default_settings_page);
    m_update_date->setValue("2024/03/06 23:00");
    m_update_date->setEnabled(false);
    GuiTextInputItem* author = new GuiTextInputItem("author", m_default_settings_page);
    author->setValue("Qianhua | Made with love");
    author->setEnabled(false);
    GuiTextInputItem* license = new GuiTextInputItem("license", m_default_settings_page);
    license->setValue("MIT License");
    license->setEnabled(false);
    GuiTextInputItem* GitHub = new GuiTextInputItem("git", m_default_settings_page);
    GitHub->setValue("github.com/Qianhua");
    GitHub->setEnabled(false);
    m_default_settings_page->addContent(GitHub);
    m_default_settings_page->addContent(license);
    m_default_settings_page->addContent(author);
    m_default_settings_page->addContent(m_update_date);
    m_default_settings_page->addContent(version);
    m_cur_settings_page = m_default_settings_page;
    m_default_settings_page->show();
    m_page_list.push_back(m_default_settings_page);

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

    m_settings_icon = new GuiIcon("/home/liuqianhua/workspace/LocalMinMax/gui/forms/icons/settings.svg", "settings", 5, this);
    m_settings_icon->setMinimumHeight(m_canvas_title->height() * 0.7);
    m_settings_icon->setMaximumWidth(m_canvas_title->height() * 0.7);
    connect(m_settings_icon, &GuiIcon::clicked, this, [=]() {
        QPropertyAnimation* rotate = new QPropertyAnimation(m_settings_icon, "rotationAngle", this);
        rotate->setDuration(750);
        rotate->setStartValue(0);
        rotate->setEndValue(90);
        rotate->setEasingCurve(QEasingCurve::InOutExpo);
        rotate->start();
        m_cur_settings_page->slideIn();
    });
    m_layers_icon = new GuiIcon("/home/liuqianhua/workspace/LocalMinMax/gui/forms/icons/layers.svg", "layers", 5, this);
    m_layers_icon->setMinimumHeight(m_canvas_title->height() * 0.7);
    m_layers_icon->setMaximumWidth(m_canvas_title->height() * 0.7);

    // create title
    QWidget* title_inner_widget = new QWidget(this);
    title_inner_widget->setFixedHeight(m_canvas_title->height());
    QHBoxLayout* inner_layout = new QHBoxLayout(title_inner_widget);
    title_inner_widget->setLayout(inner_layout);
    inner_layout->setContentsMargins(0, 0, 0, 0);
    inner_layout->setSpacing(10);
    inner_layout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    inner_layout->addWidget(m_canvas_title);
    inner_layout->addWidget(m_settings_icon);
    inner_layout->addWidget(m_layers_icon);

    QWidget* title_widget = new QWidget(this);
    title_widget->setMaximumHeight(m_canvas_title->height() + m_canvas_desc->height());
    QVBoxLayout* outer_layout = new QVBoxLayout(title_widget);
    title_widget->setLayout(outer_layout);
    outer_layout->setContentsMargins(0, 0, 0, 0);
    outer_layout->setSpacing(0);
    outer_layout->addWidget(title_inner_widget);
    outer_layout->addWidget(m_canvas_desc);

    // create default page
    m_default_page = new QWidget(m_ui->mainWidget);
    m_default_page->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    GuiBigIconButton* createNew = new GuiBigIconButton("/home/liuqianhua/workspace/LocalMinMax/gui/forms/icons/create.png", "Create new", 10, this);
    createNew->setScale(0.9);
    GuiBigIconButton* openFile = new GuiBigIconButton("/home/liuqianhua/workspace/LocalMinMax/gui/forms/icons/open.png", "Open from file", 10, this);
    connect(openFile, &GuiBigIconButton::clicked, this, [=](){
        // QString inputPath = QFileDialog::getOpenFileName(this, tr("Open map"), " ",  tr("Map File(*.map)"));
        // if(!inputPath.isEmpty()){
        //     MyCanvas *newCanvas = loadCanvas(inputPath);
        //     if(newCanvas != nullptr){
        //         canvasList.push_back(newCanvas);
        //         GuiSelectionItem *newLayer = new GuiSelectionItem(newCanvas->name(), newCanvas->description(), m_layers_page);
        //         m_layer_select->addItem(newLayer);
        //         m_layer_select->SetSelection(newLayer);
        //         m_page_list.push_back(newCanvas->settingPage());
        //         connect(newLayer, &GuiSelectionItem::selected, this, [=](){selectCanvas(newCanvas);});
        //         selectCanvas(newCanvas);
        //         connect(newCanvas, &MyCanvas::nameChanged, this, [=](QString text){
        //             canvasTitle->setText(text);
        //             canvasTitle->setMaximumWidth(QFontMetrics(QFont("Corbel Light", 24)).size(Qt::TextSingleLine, canvasTitle->text()).width() + 10);
        //             newLayer->setTitle(text);
        //         });
        //         connect(newCanvas, &MyCanvas::descChanged, this, [=](QString text){this->canvasDesc->setText(text);newLayer->setDescription(text);});
        //         connect(newCanvas, &MyCanvas::setDel, this, [=](MyCanvas *c){m_cur_settings_page->slideOut();deleteCanvas(c);m_layer_select->RemoveItem(newLayer);});
        //         m_create_new_page->slideOut();
        //     }
        // }
    });
    QHBoxLayout *m_default_pageLayout = new QHBoxLayout(m_default_page);
    m_default_page->setLayout(m_default_pageLayout);
    m_default_pageLayout->setContentsMargins(50, 30, 50, 80);
    m_default_pageLayout->setSpacing(20);
    m_default_pageLayout->addWidget(createNew);
    m_default_pageLayout->addWidget(openFile);

    /* create layers page */
    // for add new page
    GuiTextInputItem *rename = new GuiTextInputItem("Name:",m_create_new_page);
    // rename->setValue("Layer_" + QString::asprintf("%d", canvasList.size()));
    rename->setValue("Layer_" + QString::asprintf("%d", 2));
    GuiTextInputItem *redescribe = new GuiTextInputItem("Detail:",m_create_new_page);
    redescribe->setValue("No description");

    m_layers_page = new SlidePage(m_corner_radius, "LAYERS", m_ui->mainWidget);
    m_layers_page->stackUnder(m_create_new_page);
    connect(m_layers_icon, &GuiIcon::clicked, m_layers_page, &SlidePage::slideIn);
    m_layer_select = new GuiSingleSelectGroup("Layers", m_layers_page);
    connect(m_layer_select, &GuiSingleSelectGroup::itemChange, m_layers_page, [=](){m_layers_page->updateContents();});
    GuiTextButton *openFileBtn = new GuiTextButton("Open file", m_layers_page);
    connect(openFileBtn, &GuiTextButton::clicked, this, [=]() {
        // QString inputPath = QFileDialog::getOpenFileName(this, tr("Open map"), " ",  tr("Map File(*.map)"));
        // if(!inputPath.isEmpty()){
        //     MyCanvas *newCanvas = loadCanvas(inputPath);
        //     if(newCanvas != nullptr){
        //         canvasList.push_back(newCanvas);
        //         GuiSelectionItem *newLayer = new GuiSelectionItem(newCanvas->name(), newCanvas->description(), m_layers_page);
        //         m_layer_select->addItem(newLayer);
        //         m_layer_select->SetSelection(newLayer);
        //         m_page_list.push_back(newCanvas->settingPage());
        //         connect(newLayer, &GuiSelectionItem::selected, this, [=](){selectCanvas(newCanvas);});
        //         selectCanvas(newCanvas);
        //         connect(newCanvas, &MyCanvas::nameChanged, this, [=](QString text){
        //             canvasTitle->setText(text);
        //             canvasTitle->setMaximumWidth(QFontMetrics(QFont("Corbel Light", 24)).size(Qt::TextSingleLine, canvasTitle->text()).width() + 10);
        //             newLayer->setTitle(text);
        //         });
        //         connect(newCanvas, &MyCanvas::descChanged, this, [=](QString text){this->canvasDesc->setText(text);newLayer->setDescription(text);});
        //         connect(newCanvas, &MyCanvas::setDel, this, [=](MyCanvas *c){m_cur_settings_page->slideOut();deleteCanvas(c);m_layer_select->RemoveItem(newLayer);});
        //         m_create_new_page->slideOut();
        //     }
        // }
    });
    GuiTextButton *addNewBtn = new GuiTextButton("Create new", m_layers_page);
    m_layers_page->addContent(addNewBtn);
    m_layers_page->addContent(openFileBtn);
    m_layers_page->addContent(m_layer_select);
    // connect(addNewBtn, &GuiTextButton::clicked, this, [=](){rename->setValue("Layer_" + QString::asprintf("%d", canvasList.size()));redescribe->setValue("No description");m_create_new_page->slideIn();});
    connect(addNewBtn, &GuiTextButton::clicked, this, [=](){rename->setValue("Layer_" + QString::asprintf("%d", 2));redescribe->setValue("No description");m_create_new_page->slideIn();});
    m_layers_page->show();
    m_page_list.push_back(m_layers_page);

    /* create add new slide page */
    m_create_new_page = new SlidePage(m_corner_radius, "CREATE CANVAS", m_ui->mainWidget);
    QLineEdit *canvasName = new QLineEdit(this);
    canvasName->setMaximumHeight(20);
    QLineEdit *canvasDesc = new QLineEdit(this);
    canvasDesc->setMaximumHeight(20);

    QWidget *whiteSpace = new QWidget(m_create_new_page);
    whiteSpace->setFixedHeight(30);
    GuiSingleSelectGroup *structureSel = new GuiSingleSelectGroup("Structure",m_create_new_page);
    GuiSelectionItem *item_1 = new GuiSelectionItem("AL", "Use adjacent list for canvas", m_create_new_page);
    GuiSelectionItem *item_2 = new GuiSelectionItem("AML", "Use multiple adjacent list for canvas", m_create_new_page);
    structureSel->addItem(item_1);
    structureSel->addItem(item_2);
    GuiSingleSelectGroup *dirSel = new GuiSingleSelectGroup("Mode", m_create_new_page);
    GuiSelectionItem *item_3 = new GuiSelectionItem("DG", "Directed graph", m_create_new_page);
    GuiSelectionItem *item_4 = new GuiSelectionItem("UDG", "Undirected graph", m_create_new_page);
    dirSel->addItem(item_3);
    dirSel->addItem(item_4);
    GuiTextButton *submit = new GuiTextButton("Create!", m_create_new_page);
    connect(submit, &GuiTextButton::clicked, this, [=](){
        // MyCanvas *newCanvas = new MyCanvas(m_corner_radius,
        //                                    rename->value(),
        //                                    redescribe->value(),
        //                                    structureSel->value() == 0 ? MyCanvas::AL : MyCanvas::AML,
        //                                    dirSel->value() == 0 ? MyCanvas::DG : MyCanvas::UDG, ui->mainWidget);
        // canvasList.push_back(newCanvas);
        // GuiSelectionItem *newLayer = new GuiSelectionItem(newCanvas->name(), newCanvas->description(), layersPage);
        // m_layer_select->addItem(newLayer);
        // m_layer_select->SetSelection(newLayer);
        // m_page_list.push_back(newCanvas->settingPage());
        // connect(newLayer, &GuiSelectionItem::selected, this, [=](){selectCanvas(newCanvas);});
        // selectCanvas(newCanvas);
        // connect(newCanvas, &MyCanvas::nameChanged, this, [=](QString text){
        //     canvasTitle->setText(text);
        //     canvasTitle->setMaximumWidth(QFontMetrics(QFont("Corbel Light", 24)).size(Qt::TextSingleLine, canvasTitle->text()).width() + 10);
        //     newLayer->setTitle(text);
        // });
        // connect(newCanvas, &MyCanvas::descChanged, this, [=](QString text){this->canvasDesc->setText(text);newLayer->setDescription(text);});
        // connect(newCanvas, &MyCanvas::setDel, this, [=](MyCanvas *c){m_cur_settings_page->slideOut();deleteCanvas(c);m_layer_select->RemoveItem(newLayer);});
        // m_create_new_page->slideOut();
    });
    m_create_new_page->addContent(submit);
    m_create_new_page->addContent(dirSel);
    m_create_new_page->addContent(structureSel);
    m_create_new_page->addContent(whiteSpace);
    m_create_new_page->addContent(redescribe);
    m_create_new_page->addContent(rename);
    // connect(createNew, &GuiBigIconButton::clicked, m_create_new_page, [=](){rename->setValue("Layer_" + QString::asprintf("%d", canvasList.size()));redescribe->setValue("No description");m_create_new_page->slideIn();});
    connect(createNew, &GuiBigIconButton::clicked, m_create_new_page, [=](){rename->setValue("Layer_" + QString::asprintf("%d", 2));redescribe->setValue("No description");m_create_new_page->slideIn();});
    m_create_new_page->show();
    m_page_list.push_back(m_create_new_page);

    m_ui->displayLayout->addWidget(title_widget);
    m_ui->displayLayout->addWidget(m_default_page);
    m_ui->displayLayout->setAlignment(Qt::AlignTop);
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
