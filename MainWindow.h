#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "karpuz.h"
#include <QMouseEvent>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int basarili = 0;
    int basarisiz = 0;
    int i=0;
    int frekans;
    int geriSayimSure = 30;
    double oran = 0;
    int bombasay = 0;

    void sayac();
    void geriSayimGuncelle();
     void bombaTiklandi();
    public slots:
    void zorluk();
    void karpuzekle();
    void bombaolustur();
    void karpuzdusme();

private:
    QTimer *zamanlayici=new QTimer(this);
    QTimer *zamanlayici2=new QTimer(this);
    void on_action1_arkaplan_triggered();
    void on_action2_arkaplan_triggered();
    void on_arkaplan3_triggered();


    Ui::MainWindow *ui;
    QList<karpuz*> buttonlar;
    QList<QPushButton*> bombalar;


};
#endif // MAINWINDOW_H
