#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_balancing_programm.h"
#include <QList>

//ǰ������
class edge;
class point;
class balancing_programm : public QMainWindow
{
	Q_OBJECT

public:
	balancing_programm(QWidget *parent = Q_NULLPTR);
private slots:
	//����
	void calculate();
	//���ļ�
	void readfile();
	//д�ļ�
	void savefile();
	//�رճ���
	void pro_close();
	//����
	void help();
	//����ƽ��
	void codi_adjust();
	//���ƽ��
	void ird_adjust();
	//ԭʼ����
	void ori_data();
	//ˮ׼��
	void level_network();
	//���
	void result();

private:
	QString Filename;
	//��֪�����
	int know_point_num;
	//δ֪�����
	int unknow_point_num;
	//�۲�ֵ����
	int observe_num;
	//��֪��߳�
	QList <double> know_point_altitude;
	QList <edge> edges;
	QList <point> points;
	Ui::balancing_programmClass ui;
};

//����
class edge
{
public:
	//��ʼ��
	edge():id(0), observe_intercept(0), route_length(0), beginpoint("0"), endpoint("1")
	{

	}
	//���
	int id;
	//�߲�
	double observe_intercept;
	//·�߳���
	double route_length;
	//��ʼ��
	QString beginpoint;
	//�յ�
	QString endpoint;
};
//����
class point
{
public:
	//��ʼ��
	point():id("p0"),iskonwn(0),height(0)
	{

	}
	//�Ƿ���֪
	bool iskonwn;
	//�߳�
	double height;
	//���
	QString id;
};
