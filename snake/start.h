#ifndef START_H
#define START_H

#include <QWidget>

namespace Ui {
class start;
}

class start : public QWidget
{
    Q_OBJECT

public:
    explicit start(QWidget *parent = nullptr);
    ~start();

private slots:

    void on_start_pushButton_clicked();
    void on_quit_pushButton_clicked();

private:
    Ui::start *ui;
};

#endif // START_H

