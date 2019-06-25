#include "balancing_programm.h"
#include <QFile>
#include <QFiledialog>
#include <QTextstream>
#include <cmath>
#include <QMessagebox>
#include <QLabel>
#include "Matrix.h"

int know_point_num;
//δ֪�����
int unknow_point_num;
//�۲�ֵ����
int observe_num;
//��֪��߳�
QList <edge> edges;
QList <point> points;

Matrix v, L(observe_num, 1),DXX;
//�����
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
	int i; //������
	point p;
	edge ed;
	Filename = QFileDialog::getOpenFileName(this, QStringLiteral("���ļ�"), "", "*.txt");
	QFile infile(Filename);
	if (!infile.open(QIODevice::ReadOnly | QIODevice::Text)) { QMessageBox::warning(this, QStringLiteral("����"), QStringLiteral("�ļ�δ��"));
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
		//����������������[]�޸ģ�������.at()�޸ģ���֪Ϊ��;�ƺ�.at()��ֻ��
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
	QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("�ļ���ȡ��ɣ�������ʾԭʼ������ʾ�ļ�����"));
}

void balancing_programm::savefile()
{
	int i;
	QString ss;
	QString saveFilename;
	saveFilename = QFileDialog::getSaveFileName(this, QStringLiteral("�����ļ�"), "", ("*.txt"));
	QFile outfile(saveFilename);
	QTextStream out(&outfile);
	if (!outfile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QMessageBox::warning(this, QStringLiteral("����"), QStringLiteral("�ļ�δ��"));
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
	QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("�˹���δ�������"));
}

void balancing_programm::ird_adjust()
{
	if (Filename == "")
	{
		QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("���ȶ�ȡ�ļ�"));
		return;
	}
	Matrix temp(observe_num,1);
	int i;
	Matrix B(observe_num, unknow_point_num), l(observe_num, 1), x,P(observe_num,observe_num),NBB,W;
	get_B_l(B, l);
	//����Ȩ��
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
	ui.tableWidget->setHorizontalHeaderLabels(QStringList() << QStringLiteral("�����") << QStringLiteral("�յ���") << QStringLiteral("�۲�߲�") << QStringLiteral("������߲�"));
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
	QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("�������"));
}

void balancing_programm::ori_data()
{
	if (Filename == "")
	{
		QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("���ȶ�ȡ�ļ�"));
		return;
	}
	int i,j;
	ui.tableWidget->clear();
	ui.tableWidget->setColumnCount(4);
	ui.tableWidget->setRowCount(observe_num);
	//���ñ�ͷ
	ui.tableWidget->setHorizontalHeaderLabels(QStringList() << QStringLiteral("�����") << QStringLiteral("�յ���") << QStringLiteral("�۲�߲�") << QStringLiteral("�۲����"));
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
		QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("���ȶ�ȡ�ļ�"));
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
	ui.tableWidget->setHorizontalHeaderLabels(QStringList() << QStringLiteral("������") << QStringLiteral("������߲�") << QStringLiteral("�����"));
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
	QMessageBox::information(this, QStringLiteral("�����ĵ�"), QStringLiteral("�˳�����Qt������\n�ó��������ļ����д򿪣����棬�ر����ֹ��ܣ�\nƽ���������ƽ��ͼ��ƽ�\n��ʾ������ʾԭʼ���ݺ�ˮ׼����\nע�⣺������ļ����ļ����ݲ�����ʾ����Ҫ��ʾ�������ʾ���µ���ʾԭʼ���ݣ�\n���������������ļ�����ƽ������µ�����ƽ�����֮���������ʾƽ���Ľ����Ȼ���������ļ��������ļ���ʽ�ͱ���ڵĸ�ʽ��ͬ��"));
}



void get_B_l(Matrix & B, Matrix & l)
{
	int i, j;
	//�����
	int pointnum_begin;
	//�յ���
	int pointnum_end;
	double temp;
	//����߳�
	for (i = 0; i < edges.size(); i++)
	{
		//�ж�����Ƿ�Ϊ��֪��
		if (edges.at(i).beginpoint.mid(0, 1) != "P")
		{
			//�յ���(δ֪����)
			pointnum_end = edges.at(i).endpoint.mid(1).toInt();
			//�ҵ�����Ӧ����֪��
			for (j = unknow_point_num; j < (unknow_point_num + know_point_num); j++)
			{
				if (points.at(j).id == edges.at(i).beginpoint)
				{
					//����߳�
					if (points[pointnum_end - 1].height == 0)
						points[pointnum_end - 1].height = points.at(j).height + edges.at(i).observe_intercept;
				}
			}
		}
		//�յ��Ƿ�Ϊ��֪��
		else if (edges.at(i).endpoint.mid(0, 1) != "P")
		{
			//����ţ�δ֪��)
			pointnum_begin = edges.at(i).beginpoint.mid(1).toInt();
			// �ҵ��յ���Ӧ����֪��
			for (j = unknow_point_num; j < (unknow_point_num + know_point_num); j++)
			{
				if (points.at(j).id == edges.at(i).endpoint)
				{
					//����߳�
					if (points[pointnum_begin- 1].height == 0)
						points[pointnum_begin - 1].height = points.at(j).height - edges.at(i).observe_intercept;
				}
			}
		}
		else
		{
			//�����
			pointnum_begin = edges.at(i).beginpoint.mid(1).toInt();
			//�յ���(δ֪����)
			pointnum_end = edges.at(i).endpoint.mid(1).toInt();
			if (points[pointnum_end - 1].height == 0)
				points[pointnum_end - 1].height = points[pointnum_begin - 1].height + edges.at(i).observe_intercept;
		}
	}
	//����B����;���
	for (i = 0; i < observe_num; i++)
	{
		//�ж�����Ƿ�Ϊ��ָ�㣬����ǣ���lΪ��
		if (edges.at(i).beginpoint.mid(0, 1) != "P")
		{
			//�����
			pointnum_begin = edges.at(i).beginpoint.mid(1).toInt();
			//�յ���(δ֪����)
			pointnum_end = edges.at(i).endpoint.mid(1).toInt();
			B.set(i, pointnum_end - 1, 1);
		}
		//�ж��յ��Ƿ�Ϊ��֪��,����ǣ���lΪ��
		else if (edges.at(i).endpoint.mid(0, 1) != "P")
		{

			//�յ����
			pointnum_end = edges.at(i).endpoint.mid(1).toInt();
			//������(δ֪����)
			pointnum_begin = edges.at(i).beginpoint.mid(1).toInt();
			B.set(i, pointnum_begin - 1, -1);
		}
		else
		{
			//�����
			pointnum_begin = edges.at(i).beginpoint.mid(1).toInt();
			//�յ���
			pointnum_end = edges.at(i).endpoint.mid(1).toInt();
			B.set(i, pointnum_begin - 1, -1);
			B.set(i, pointnum_end - 1, 1);
			//����l���󣬹۲�ֵ��ȥ��ֵ
			temp = edges.at(i).observe_intercept - (points.at(pointnum_end - 1).height - points.at(pointnum_begin - 1).height);
			l.set(i, 0, temp);
		}
	}
}
