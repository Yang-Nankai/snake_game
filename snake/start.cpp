#include "start.h"
#include "ui_start.h"
#include <QIcon>
#include <QPalette>
#include <QPixmap>
#include <QMessageBox>
#include <QRect>

extern bool isRun;
start::start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::start)
{
    setWindowFlags(Qt::CustomizeWindowHint|Qt::SplashScreen | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
    ui->setupUi(this);


}

start::~start()
{
    delete ui;
}


void start::on_start_pushButton_clicked()
{
    this->close();
    isRun = true;
    delete this;
    return;
}

void start::on_quit_pushButton_clicked()
{

    exit(0);
    delete this;
    return;
}





