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
	int i; //计数器
	point p;
	edge ed;
	Filename = QFileDialog::getOpenFileName(this, QStringLiteral("打开文件"), "", "*.txt");
	QFile infile(Filename);
	if (!infile.open(QIODevice::ReadOnly | QIODevice::Text)) { QMessageBox::warning(this, QStringLiteral("打开文件"), QStringLiteral("文件未打开"));
	return;
	}
	QByteArray arr = infile.readLine();
	QStringList list = QString(arr).split(QRegExp("\\s+|,+ ")); //正则表达式--空格或逗号为分割符的文件
	know_point_num = list.at(0).toInt();
	unknow_point_num = list.at(1).toInt();
	observe_num = list.at(2).toInt();
	//清空列表
	list.clear();
	arr = infile.readLine();
	list = QString(arr).split(QRegExp("\\s+|,+ "));
	for (i = 0; i < list.size(); i++)
	{
		//判断是否为未知点
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
	//清空列表
	list.clear();
	arr = infile.readLine();
	list = QString(arr).split(QRegExp("\\s+|,+ "));
	for (i = 0; i < list.size(); i++)
	{
		//？？？？？必须用[]修改，不能用.at()修改，不知为何
		points[unknow_point_num].height = list.at(0).toDouble();
	}
	list.clear();
	//分行读取
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
	//设置表头
	ui.tableWidget->setHorizontalHeaderLabels(QStringList() << QStringLiteral("起点点号") << QStringLiteral("终点点号") << QStringLiteral("观测高差") << QStringLiteral("水准路线高差") << QStringLiteral("已知点高差"));
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
	QMessageBox::information(this, QStringLiteral("帮助文档"), "123456789123498795\n451321319797984566132165");
}

void balancing_programm::calculate()
{


}