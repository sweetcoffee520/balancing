#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_balancing_programm.h"
#include <QList>

//前置声明
class edge;
class point;
class balancing_programm : public QMainWindow
{
	Q_OBJECT

public:
	balancing_programm(QWidget *parent = Q_NULLPTR);
private slots:
	//计算
	void calculate();
	//读文件
	void readfile();
	//写文件
	void savefile();
	//关闭程序
	void pro_close();
	//帮助
	void help();
	//条件平差
	void codi_adjust();
	//间接平差
	void ird_adjust();
	//原始数据
	void ori_data();
	//水准网
	void level_network();
	//结果
	void result();

private:
	QString Filename;
	//已知点个数
	int know_point_num;
	//未知点个数
	int unknow_point_num;
	//观测值个数
	int observe_num;
	//已知点高程
	QList <double> know_point_altitude;
	QList <edge> edges;
	QList <point> points;
	Ui::balancing_programmClass ui;
};

//边类
class edge
{
public:
	//初始化
	edge():id(0), observe_intercept(0), route_length(0), beginpoint("0"), endpoint("1")
	{

	}
	//点号
	int id;
	//高差
	double observe_intercept;
	//路线长度
	double route_length;
	//起始点
	QString beginpoint;
	//终点
	QString endpoint;
};
//点类
class point
{
public:
	//初始化
	point():id("p0"),iskonwn(0),height(0)
	{

	}
	//是否已知
	bool iskonwn;
	//高程
	double height;
	//点号
	QString id;
};
