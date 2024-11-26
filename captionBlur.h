#pragma once

#include <Windows.h>
#include <QtWidgets/QWidget>
#include <QMovie>
#include <QSize>
#include <QList>
#include <QResource>
#include <QPainter>
#include <QCloseEvent>
#include <QApplication>
#include <QSettings>
#include <QDesktopWidget>

#include <QGraphicsBlurEffect>
#include <QDebug>
#include <QPainterPath>
#include <QMovie>

#include <vector>
#include <QDir>
#include "ui_captionBlur.h"
#include "WindowCompositionAttribute.h"


class captionBlur : public QWidget
{
	Q_OBJECT

public:
	captionBlur(char **argv, QWidget*parent = Q_NULLPTR);
	int Width;
	int Height;

	bool padHolding = false; //检测按键长按
	

private:
	Ui_captionBlur ui;

	QSettings* Setting;  //for geometry loading

	float startX;                              
	float startY;

	HWND hwnd;
	HMODULE huser;
	pfnSetWindowCompositionAttribute setWindowCompositionAttribute;

	QColor acryBackground;	//用来控制背景颜色

	bool blurring;                  //处于模糊状态

	int padding;                    //边距
	bool moveEnable;                //可移动
	bool resizeEnable;              //可拉伸
	QWidget* widget;                //无边框窗体

	bool pressed;                   //鼠标按下
	bool pressedLeft;               //鼠标按下左侧
	bool pressedRight;              //鼠标按下右侧
	bool pressedTop;                //鼠标按下上侧
	bool pressedBottom;             //鼠标按下下侧
	bool pressedLeftTop;            //鼠标按下左上侧
	bool pressedRightTop;           //鼠标按下右上侧
	bool pressedLeftBottom;         //鼠标按下左下侧
	bool pressedRightBottom;        //鼠标按下右下侧

	int rectX, rectY, rectW, rectH; //窗体坐标+宽高
	QPoint lastPos;                 //鼠标按下处坐标

	QRect rectLeft;                 //左侧区域
	QRect rectRight;                //右侧区域
	QRect rectTop;                  //上侧区域
	QRect rectBottom;               //下侧区域
	QRect rectLeftTop;              //左上侧区域
	QRect rectRightTop;             //右上侧区域
	QRect rectLeftBottom;           //左下侧区域
	QRect rectRightBottom;          //右下侧区域
signals:

private slots:
	void initConnect();
	void initVariables();
	void doAero();
	void disableAero();
	void setWidget(QWidget* widget);
	
protected:
	void closeEvent(QCloseEvent* event);
	void mouseDoubleClickEvent(QMouseEvent* event);

	void paintEvent(QPaintEvent* event);
	bool eventFilter(QObject* watched, QEvent* event);

	bool initConfig();
	bool readConfig();
	bool saveConfig();
};




