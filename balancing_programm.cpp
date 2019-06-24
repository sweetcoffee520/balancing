#include "balancing_programm.h"
#include <QFile>
#include <QFiledialog>
#include <QTextstream>
#include <cmath>
#include <QMessagebox>
#include "Matrix.h"
balancing_programm::balancing_programm(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.action_open, &QAction::triggered, this, &balancing_programm::readfile);
	connect(ui.action_save, &QAction::triggered, this, &balancing_programm::savefile);
	connect(ui.action_close, &QAction::triggered, this, &balancing_programm::pro_close);
	connect(ui.actioncod_adjust, &QAction::triggered, this, &balancing_programm::codi_adjust);
	connect(ui.actionird_adjust, &QAction::triggered, this, &balancing_programm::ird_adjust);
	connect(ui.actionori_data, &QAction::triggered, this, &balancing_programm::ori_data);
	connect(ui.actionleve_network, &QAction::triggered, this, &balancing_programm::level_network);
	connect(ui.actionresult, &QAction::triggered, this, &balancing_programm::result);
	connect(ui.actionhelp, &QAction::triggered, this, &balancing_programm::help);
	connect(ui.action_calculate, &QPushButton::clicked , this, &balancing_programm::calculate);

}
 
void balancing_programm::readfile()
{
	int i; //������
	point p;
	edge ed;
	Filename = QFileDialog::getOpenFileName(this, QStringLiteral("���ļ�"), "", "*.txt");
	QFile infile(Filename);
	if (!infile.open(QIODevice::ReadOnly | QIODevice::Text)) { QMessageBox::warning(this, QStringLiteral("���ļ�"), QStringLiteral("�ļ�δ��"));
	return;
	}
	QByteArray arr = infile.readLine();
	QStringList list = QString(arr).split(QRegExp("\\s+|,+ ")); //������ʽ--�ո�򶺺�Ϊ�ָ�����ļ�
	know_point_num = list.at(0).toInt();
	unknow_point_num = list.at(1).toInt();
	observe_num = list.at(2).toInt();
	//����б�
	list.clear();
	arr = infile.readLine();
	list = QString(arr).split(QRegExp("\\s+|,+ "));
	for (i = 0; i < list.size(); i++)
	{
		//�ж��Ƿ�Ϊδ֪��
		if (i < unknow_point_num)
		{
			p.iskonwn = 0;
			p.id = list.at(i);
			points.append(p);
		}
		else
		{
			p.iskonwn = 1;
			p.id = list.at(i);
			points.append(p);
		}
	}
	//����б�
	list.clear();
	arr = infile.readLine();
	list = QString(arr).split(QRegExp("\\s+|,+ "));
	for (i = 0; i < list.size(); i++)
	{
		//����������������[]�޸ģ�������.at()�޸ģ���֪Ϊ��
		points[unknow_point_num].height = list.at(0).toDouble();
	}
	list.clear();
	//���ж�ȡ
	while (!infile.atEnd())
	{
		QByteArray arr = infile.readLine();
		list = QString(arr).split(QRegExp("\\s+|,+ "));
		ed.id = list.at(0).toInt();
		ed.beginpoint = list.at(1);
		ed.endpoint = list.at(2);
		ed.observe_intercept = list.at(3).toDouble();
		ed.route_length = list.at(4).toDouble();
		edges.append(ed);
		list.clear();
	}
	
	infile.close();
}

void balancing_programm::savefile()
{


}

void balancing_programm::pro_close()
{
	this->close();
}
void balancing_programm::codi_adjust()
{

}

void balancing_programm::ird_adjust()
{

}

void balancing_programm::ori_data()
{
	int i,j;
	ui.tableWidget->clear();
	ui.tableWidget->setColumnCount(5);
	ui.tableWidget->setRowCount(know_point_num+unknow_point_num);
	//���ñ�ͷ
	ui.tableWidget->setHorizontalHeaderLabels(QStringList() << QStringLiteral("�����") << QStringLiteral("�յ���") << QStringLiteral("�۲�߲�") << QStringLiteral("ˮ׼·�߸߲�") << QStringLiteral("��֪��߲�"));
	QStringList list;
	for (i = 0; i < edges.size(); i++)
	{
		list << edges.at(i).beginpoint << edges.at(i).endpoint << QString::number(edges.at(i).observe_intercept) << QString::number(edges.at(i).route_length);
		int col = 0;
		ui.tableWidget->setItem(i, col++, new QTableWidgetItem(list.at(0)));
		ui.tableWidget->setItem(i, col++, new QTableWidgetItem(list.at(1)));
		ui.tableWidget->setItem(i, col++, new QTableWidgetItem(list.at(2)));
		ui.tableWidget->setItem(i, col++, new QTableWidgetItem(list.at(3)));
		list.clear();
	}
}

void balancing_programm::level_network()
{

}

void balancing_programm::result()
{


}

void balancing_programm::help()
{
	QMessageBox::information(this, QStringLiteral("�����ĵ�"), "123456789123498795\n451321319797984566132165");
}

void balancing_programm::calculate()
{


}