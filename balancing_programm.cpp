#include "balancing_programm.h"
#include <QFile>
#include <QFiledialog>
#include <QTextstream>
#include <cmath>
#include <QMessagebox>
#include <QLabel>
#include "Matrix.h"

int know_point_num;
//未知点个数
int unknow_point_num;
//观测值个数
int observe_num;
//已知点高程
QList <edge> edges;
QList <point> points;

Matrix v, L(observe_num, 1),DXX;
//中误差
double o;

void get_B_l(Matrix &B,Matrix &L);
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
	connect(ui.action_result, &QAction::triggered, this, &balancing_programm::showresult);
	connect(ui.actionhelp, &QAction::triggered, this, &balancing_programm::help);
}
 
void balancing_programm::readfile()
{
	int i; //计数器
	point p;
	edge ed;
	Filename = QFileDialog::getOpenFileName(this, QStringLiteral("打开文件"), "", "*.txt");
	QFile infile(Filename);
	if (!infile.open(QIODevice::ReadOnly | QIODevice::Text)) { QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("文件未打开"));
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
		//？？？？？必须用[]修改，不能用.at()修改，不知为何;似乎.at()是只读
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
	QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("文件读取完成，请点击显示原始数据显示文件数据"));
}

void balancing_programm::savefile()
{
	int i;
	QString ss;
	QString saveFilename;
	saveFilename = QFileDialog::getSaveFileName(this, QStringLiteral("保存文件"), "", ("*.txt"));
	QFile outfile(saveFilename);
	QTextStream out(&outfile);
	if (!outfile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("文件未打开"));
		return;
	}
	for (i = 0; i < observe_num; i++)
	{
		QString  ss = edges.at(i).beginpoint + "  " + edges.at(i).endpoint + "  " + QString::number(edges.at(i).observe_intercept) + "  " + ui.tableWidget->item(i, 3)->text();
		out << ss << endl;
	}
	outfile.close();
}

void balancing_programm::pro_close()
{
	this->close();
}
void balancing_programm::codi_adjust()
{
	QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("此功能未开发完成"));
}

void balancing_programm::ird_adjust()
{
	if (Filename == "")
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请先读取文件"));
		return;
	}
	Matrix temp(observe_num,1);
	int i;
	Matrix B(observe_num, unknow_point_num), l(observe_num, 1), x,P(observe_num,observe_num),NBB,W;
	get_B_l(B, l);
	//计算权阵
	for (i = 0; i < observe_num; i++)
	{
		temp.set(i, 0, edges.at(i).observe_intercept);
		P.set(i, i, 1/edges.at(i).observe_intercept);
	}
	NBB = B.Trans()*P*B;
	W = B.Trans()*P*l;
	x = NBB.Inverse()*W;
	v = B * x - l;
	L = temp + v;
	o = sqrt((v.Trans()*P*v).get(0,0)/(observe_num-unknow_point_num));
	DXX = o*o*P.Inverse();
	ui.tableWidget->clear();
	QStringList list;
	ui.tableWidget->setColumnCount(4);
	ui.tableWidget->setRowCount(observe_num);
	ui.tableWidget->setHorizontalHeaderLabels(QStringList() << QStringLiteral("起点点号") << QStringLiteral("终点点号") << QStringLiteral("观测高差") << QStringLiteral("改正后高差"));
	for (i = 0; i < observe_num; i++)
	{
		list << edges.at(i).beginpoint << edges.at(i).endpoint << QString::number(edges.at(i).observe_intercept) << QString::number(L.get(i, 0));
		int col = 0;
		ui.tableWidget->setItem(i, col++, new QTableWidgetItem(list.at(0)));
		ui.tableWidget->setItem(i, col++, new QTableWidgetItem(list.at(1)));
		ui.tableWidget->setItem(i, col++, new QTableWidgetItem(list.at(2)));
		ui.tableWidget->setItem(i, col++, new QTableWidgetItem(list.at(3)));
		list.clear();
	}
	QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("计算完成"));
}

void balancing_programm::ori_data()
{
	if (Filename == "")
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请先读取文件"));
		return;
	}
	int i,j;
	ui.tableWidget->clear();
	ui.tableWidget->setColumnCount(4);
	ui.tableWidget->setRowCount(observe_num);
	//设置表头
	ui.tableWidget->setHorizontalHeaderLabels(QStringList() << QStringLiteral("起点点号") << QStringLiteral("终点点号") << QStringLiteral("观测高差") << QStringLiteral("观测距离"));
	QStringList list;
	for (i = 0; i < observe_num; i++)
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
	if (Filename == "")
	{
		QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请先读取文件"));
		return;
	}
	ui.tableWidget->clear();
	ui.tableWidget->setColumnCount(1);
	ui.tableWidget->setRowCount(1);
	QLabel *label = new QLabel();
	label->setPixmap(QPixmap(":/Images/level_network.png"));
	label->setAlignment(Qt::AlignHCenter);
	ui.tableWidget->setCellWidget(0, 0, label);
	ui.tableWidget->resizeColumnToContents(0);
	ui.tableWidget->resizeRowToContents(0);
}

void balancing_programm::showresult()
{
	int i;
	ui.tableWidget->clear();
	QStringList list;
	ui.tableWidget->setColumnCount(3);
	ui.tableWidget->setRowCount(observe_num);
	ui.tableWidget->setHorizontalHeaderLabels(QStringList() << QStringLiteral("改正数") << QStringLiteral("改正后高差") << QStringLiteral("中误差"));
	for (i = 0; i < observe_num; i++)
	{
		list << QString::number(v.get(i, 0)) << QString::number(L.get(i, 0)) << QString::number(DXX.get(i,i));
		int col = 0;
		ui.tableWidget->setItem(i, col++, new QTableWidgetItem(list.at(0)));
		ui.tableWidget->setItem(i, col++, new QTableWidgetItem(list.at(1)));
		ui.tableWidget->setItem(i, col++, new QTableWidgetItem(list.at(2)));
		list.clear();
	}
}

void balancing_programm::help()
{
	QMessageBox::information(this, QStringLiteral("帮助文档"), QStringLiteral("此程序由Qt开发：\n该程序界面的文件栏有打开，保存，关闭三种功能；\n平差方法有条件平差和间接平差；\n显示中有显示原始数据和水准网；\n注意：点击打开文件后，文件内容不会显示，如要显示，点击显示栏下的显示原始数据；\n具体操作：点击打开文件后点击平差方法栏下的两种平差方法，之后会立即显示平差后的结果。然后点击保存文件。保存文件格式和表格内的格式相同；"));
}



void get_B_l(Matrix & B, Matrix & l)
{
	int i, j;
	//起点点号
	int pointnum_begin;
	//终点点号
	int pointnum_end;
	double temp;
	//估算高程
	for (i = 0; i < edges.size(); i++)
	{
		//判断起点是否为已知点
		if (edges.at(i).beginpoint.mid(0, 1) != "P")
		{
			//终点点号(未知点点号)
			pointnum_end = edges.at(i).endpoint.mid(1).toInt();
			//找到起点对应的已知点
			for (j = unknow_point_num; j < (unknow_point_num + know_point_num); j++)
			{
				if (points.at(j).id == edges.at(i).beginpoint)
				{
					//估算高程
					if (points[pointnum_end - 1].height == 0)
						points[pointnum_end - 1].height = points.at(j).height + edges.at(i).observe_intercept;
				}
			}
		}
		//终点是否为已知点
		else if (edges.at(i).endpoint.mid(0, 1) != "P")
		{
			//起点点号（未知点)
			pointnum_begin = edges.at(i).beginpoint.mid(1).toInt();
			// 找到终点点对应的已知点
			for (j = unknow_point_num; j < (unknow_point_num + know_point_num); j++)
			{
				if (points.at(j).id == edges.at(i).endpoint)
				{
					//估算高程
					if (points[pointnum_begin- 1].height == 0)
						points[pointnum_begin - 1].height = points.at(j).height - edges.at(i).observe_intercept;
				}
			}
		}
		else
		{
			//起点点号
			pointnum_begin = edges.at(i).beginpoint.mid(1).toInt();
			//终点点号(未知点点号)
			pointnum_end = edges.at(i).endpoint.mid(1).toInt();
			if (points[pointnum_end - 1].height == 0)
				points[pointnum_end - 1].height = points[pointnum_begin - 1].height + edges.at(i).observe_intercept;
		}
	}
	//计算B矩阵和矩阵
	for (i = 0; i < observe_num; i++)
	{
		//判断起点是否为已指点，如果是，则l为零
		if (edges.at(i).beginpoint.mid(0, 1) != "P")
		{
			//起点点号
			pointnum_begin = edges.at(i).beginpoint.mid(1).toInt();
			//终点点号(未知点点号)
			pointnum_end = edges.at(i).endpoint.mid(1).toInt();
			B.set(i, pointnum_end - 1, 1);
		}
		//判断终点是否为已知点,如果是，则l为零
		else if (edges.at(i).endpoint.mid(0, 1) != "P")
		{

			//终点点点号
			pointnum_end = edges.at(i).endpoint.mid(1).toInt();
			//起点点点号(未知点点号)
			pointnum_begin = edges.at(i).beginpoint.mid(1).toInt();
			B.set(i, pointnum_begin - 1, -1);
		}
		else
		{
			//起点点号
			pointnum_begin = edges.at(i).beginpoint.mid(1).toInt();
			//终点点号
			pointnum_end = edges.at(i).endpoint.mid(1).toInt();
			B.set(i, pointnum_begin - 1, -1);
			B.set(i, pointnum_end - 1, 1);
			//计算l矩阵，观测值减去估值
			temp = edges.at(i).observe_intercept - (points.at(pointnum_end - 1).height - points.at(pointnum_begin - 1).height);
			l.set(i, 0, temp);
		}
	}
}
