#include "captionBlur.h"
#include <QMetaType>
#include <QSysInfo> 

captionBlur::captionBlur(char **argv, QWidget *parent)
{
	ui.setupUi(this);
    //qDebug()<< QCoreApplication::applicationDirPath();
    
    
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);

	initVariables();
	initConnect();
    
    this->setWidget(this);
}

void captionBlur::initVariables()
{
	acryBackground = QColor(240, 240, 240, 150);

    blurring = false;

	padding = 8;
	moveEnable = true;
	resizeEnable = true;
	widget = NULL;

	pressed = false;
	pressedLeft = false;
	pressedRight = false;
	pressedTop = false;
	pressedBottom = false;
	pressedLeftTop = false;
	pressedRightTop = false;
	pressedLeftBottom = false;
	pressedRightBottom = false;

    
    initConfig();
    readConfig();
}



void captionBlur::initConnect()
{
    connect(ui.pb_start, &QPushButton::clicked, [=]() {
        this->doAero();
        this->blurring = true;
        });
    connect(ui.pb_close, &QPushButton::clicked,
        [=]() {
            delete Setting;
            Setting = nullptr;
            this->close();
        });
}

void captionBlur::doAero()
{
	acryBackground = QColor(10, 10, 10, 20);
	auto hwnd = HWND(winId());
	auto huser = GetModuleHandle("user32.dll");

	if (huser) {
		setWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(huser, "SetWindowCompositionAttribute");
		if (setWindowCompositionAttribute) {
			ACCENT_POLICY accent = { ACCENT_ENABLE_BLURBEHIND, 0, 0, 0 };
            accent.GradientColor = (128 << 24) | 0x000000; // 半透明黑色，Alpha = 128

			WINDOWCOMPOSITIONATTRIBDATA data;
			data.Attrib = WCA_ACCENT_POLICY;
			data.pvData = &accent;
			data.cbData = sizeof(accent);
			setWindowCompositionAttribute(hwnd, &data);
		}
	}
    ui.pb_close->setVisible(0);
    ui.pb_start->setVisible(0);
    ui.pb_close->setEnabled(0);
    ui.pb_start->setEnabled(0);
    this->update();
}

void captionBlur::disableAero()
{
	acryBackground = QColor(240, 240, 240, 150);
	auto hwnd = HWND(winId());
	auto huser = GetModuleHandle("user32.dll");

	if (huser) {
		setWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(huser, "SetWindowCompositionAttribute");
		if (setWindowCompositionAttribute) {
			ACCENT_POLICY accent = { ACCENT_DISABLED, 0, 0, 0 };
            
			WINDOWCOMPOSITIONATTRIBDATA data;
			data.Attrib = WCA_ACCENT_POLICY;
			data.pvData = &accent;
			data.cbData = sizeof(accent);
			setWindowCompositionAttribute(hwnd, &data);
		}
	}
    if (blurring == true) {
        ui.pb_close->setVisible(0);
        ui.pb_start->setVisible(0);
        ui.pb_close->setEnabled(0);
        ui.pb_start->setEnabled(0);
    }
    else {
        ui.pb_close->setEnabled(1);
        ui.pb_start->setEnabled(1);
        ui.pb_close->setVisible(1);
        ui.pb_start->setVisible(1);
        
    }
}

void captionBlur::closeEvent(QCloseEvent* event)
{
	event->accept();
}


void captionBlur::mouseDoubleClickEvent(QMouseEvent* event)
{

}

//void captionBlur::mousePressEvent(QMouseEvent* event) {
//	QWidget::mousePressEvent(event);
//	this->startX = event->x();
//	this->startY = event->y();
//}
//
//void captionBlur::mouseMoveEvent(QMouseEvent* event) {
//	QWidget::mouseMoveEvent(event);
//	float disX = event->x() - this->startX;
//	float disY = event->y() - this->startY;
//	this->move(this->x() + disX, this->y() + disY);
//}

void captionBlur::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QPen pen;
	pen.setColor(QColor(0, 0, 0, 20));  //前三个参数设定背景颜色的RGB值，最后一个参数设定颜色的透明度
	pen.setStyle(Qt::NoPen);
	pen.setWidth(1);
	painter.setPen(pen);
	painter.setBrush(acryBackground);
	
	painter.drawRect(this->rect());
}

void captionBlur::setWidget(QWidget* widget)
{
    if (this->widget == NULL) {
        this->widget = widget;
        //设置鼠标追踪为真
        this->widget->setMouseTracking(true);
        //绑定事件过滤器
        this->widget->installEventFilter(this);
        //设置悬停为真,必须设置这个,
       //当父窗体里边还有子窗体全部遮挡了识别不到MouseMove,需要识别HoverMove
        this->widget->setAttribute(Qt::WA_Hover, true);
    }
}

bool captionBlur::eventFilter(QObject* watched, QEvent* event)
{
    if (widget != NULL && watched == widget)
    {
        if (event->type() == QEvent::Resize)
        {
            //重新计算八个描点的区域
            int width = widget->width();
            int height = widget->height();

            //左侧描点区域
            rectLeft = QRect(0, padding, padding, height - padding * 2);
            //上侧描点区域
            rectTop = QRect(padding, 0, width - padding * 2, padding);
            //右侧描点区域
            rectRight = QRect(width - padding, padding, padding, height - padding * 2);
            //下侧描点区域
            rectBottom = QRect(padding, height - padding, width - padding * 2, padding);

            //左上角描点区域
            rectLeftTop = QRect(0, 0, padding, padding);
            //右上角描点区域
            rectRightTop = QRect(width - padding, 0, padding, padding);
            //左下角描点区域
            rectLeftBottom = QRect(0, height - padding, padding, padding);
            //右下角描点区域
            rectRightBottom = QRect(width - padding, height - padding, padding, padding);
        }
        else if (event->type() == QEvent::HoverMove)
        {
            //设置对应鼠标形状,这个必须放在这里而不是下面,因为可以在鼠标没有按下的时候识别
            QHoverEvent* hoverEvent = (QHoverEvent*)event;
            QPoint point = hoverEvent->pos();
            if (resizeEnable)
            {
                if (rectLeft.contains(point)) {
                    widget->setCursor(Qt::SizeHorCursor);
                }
                else if (rectRight.contains(point)) {
                    widget->setCursor(Qt::SizeHorCursor);
                }
                else if (rectTop.contains(point)) {
                    widget->setCursor(Qt::SizeVerCursor);
                }
                else if (rectBottom.contains(point)) {
                    widget->setCursor(Qt::SizeVerCursor);
                }
                else if (rectLeftTop.contains(point)) {
                    widget->setCursor(Qt::SizeFDiagCursor);
                }
                else if (rectRightTop.contains(point)) {
                    widget->setCursor(Qt::SizeBDiagCursor);
                }
                else if (rectLeftBottom.contains(point)) {
                    widget->setCursor(Qt::SizeBDiagCursor);
                }
                else if (rectRightBottom.contains(point)) {
                    widget->setCursor(Qt::SizeFDiagCursor);
                }
                else {
                    widget->setCursor(Qt::ArrowCursor);
                    if (blurring) {
                        disableAero();          //鼠标悬停查看字幕
                    }
                        
                }
            }

            //根据当前鼠标位置,计算XY轴移动了多少
            int offsetX = point.x() - lastPos.x();
            int offsetY = point.y() - lastPos.y();

            //根据按下处的位置判断是否是移动控件还是拉伸控件
            if (moveEnable)
            {
                if (pressed) {
                    widget->move(widget->x() + offsetX, widget->y() + offsetY);
                }
            }

            if (resizeEnable)
            {
                if (pressedLeft) {
                    int resizeW = widget->width() - offsetX;
                    if (widget->minimumWidth() <= resizeW) {
                        widget->setGeometry(widget->x() + offsetX, rectY, resizeW, rectH);
                    }
                }
                else if (pressedRight) {
                    widget->setGeometry(rectX, rectY, rectW + offsetX, rectH);
                }
                else if (pressedTop) {
                    int resizeH = widget->height() - offsetY;
                    if (widget->minimumHeight() <= resizeH) {
                        widget->setGeometry(rectX, widget->y() + offsetY, rectW, resizeH);
                    }
                }
                else if (pressedBottom) {
                    widget->setGeometry(rectX, rectY, rectW, rectH + offsetY);
                }
                else if (pressedLeftTop) {
                    int resizeW = widget->width() - offsetX;
                    int resizeH = widget->height() - offsetY;
                    if (widget->minimumWidth() <= resizeW) {
                        widget->setGeometry(widget->x() + offsetX, widget->y(), resizeW, resizeH);
                    }
                    if (widget->minimumHeight() <= resizeH) {
                        widget->setGeometry(widget->x(), widget->y() + offsetY, resizeW, resizeH);
                    }
                }
                else if (pressedRightTop) {
                    int resizeW = rectW + offsetX;
                    int resizeH = widget->height() - offsetY;
                    if (widget->minimumHeight() <= resizeH) {
                        widget->setGeometry(widget->x(), widget->y() + offsetY, resizeW, resizeH);
                    }
                }
                else if (pressedLeftBottom) {
                    int resizeW = widget->width() - offsetX;
                    int resizeH = rectH + offsetY;
                    if (widget->minimumWidth() <= resizeW) {
                        widget->setGeometry(widget->x() + offsetX, widget->y(), resizeW, resizeH);
                    }
                    if (widget->minimumHeight() <= resizeH) {
                        widget->setGeometry(widget->x(), widget->y(), resizeW, resizeH);
                    }
                }
                else if (pressedRightBottom) {
                    int resizeW = rectW + offsetX;
                    int resizeH = rectH + offsetY;
                    widget->setGeometry(widget->x(), widget->y(), resizeW, resizeH);
                    
                }
            }
        }
        else if (event->type() == QEvent::MouseButtonPress)
        {
            //记住当前控件坐标和宽高以及鼠标按下的坐标
            QMouseEvent* mouseEvent = (QMouseEvent*)event;
            rectX = widget->x();
            rectY = widget->y();
            rectW = widget->width();
            rectH = widget->height();
            lastPos = mouseEvent->pos();

            //判断按下的手柄的区域位置
            if (rectLeft.contains(lastPos)) {
                pressedLeft = true;
            }
            else if (rectRight.contains(lastPos)) {
                pressedRight = true;
            }
            else if (rectTop.contains(lastPos)) {
                pressedTop = true;
            }
            else if (rectBottom.contains(lastPos)) {
                pressedBottom = true;
            }
            else if (rectLeftTop.contains(lastPos)) {
                pressedLeftTop = true;
            }
            else if (rectRightTop.contains(lastPos)) {
                pressedRightTop = true;
            }
            else if (rectLeftBottom.contains(lastPos)) {
                pressedLeftBottom = true;
            }
            else if (rectRightBottom.contains(lastPos)) {
                pressedRightBottom = true;
            }
            else {
                pressed = true;
            }
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            //恢复所有
            pressed = false;
            pressedLeft = false;
            pressedRight = false;
            pressedTop = false;
            pressedBottom = false;
            pressedLeftTop = false;
            pressedRightTop = false;
            pressedLeftBottom = false;
            pressedRightBottom = false;
            widget->setCursor(Qt::ArrowCursor);
            saveConfig();
        }
        else if (event->type() == QEvent::HoverLeave && this->blurring == true){
            doAero();
        }
        else if (event->type() == QEvent::MouseButtonDblClick && this->blurring == true){
            disableAero();
            ui.pb_close->setEnabled(1);
            ui.pb_start->setEnabled(1);
            ui.pb_close->setVisible(1);
            ui.pb_start->setVisible(1);
            this->blurring = false;
            this->update();
        }
    }

    return QObject::eventFilter(watched, event);
}

bool captionBlur::initConfig()
{
    this->update();
    QString iniPath = QCoreApplication::applicationDirPath() + "/config.ini";
    Setting = new QSettings(iniPath, QSettings::IniFormat); 
    Setting->sync();
    return true;
}

bool captionBlur::readConfig()
{
    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    QRect rect0 = desktop->screenGeometry(0); 
    auto list = Setting->value("CB/Geometry").toList();
    //qDebug() << list;
    if (list.size() != 4) {
        this->setGeometry(abs((rect0.width() - 1000))/ 2, rect0.height() / 2, 1000, 100);
        saveConfig();
    }
    else {
        this->setGeometry(list[0].toInt(), list[1].toInt(), list[2].toInt(), list[3].toInt());
    }
    
    return true;
}

bool captionBlur::saveConfig()
{
    auto geo = this->geometry();
    //qDebug() << geo;
    QList<QVariant> pointlist;
    pointlist.append(geo.x());
    pointlist.append(geo.y());
    pointlist.append(geo.width());
    pointlist.append(geo.height());
    Setting->setValue("CB/Geometry", pointlist);
    return false;
}
