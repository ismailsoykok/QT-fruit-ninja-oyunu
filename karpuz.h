#ifndef KARPUZ_H
#define KARPUZ_H

#include <QPushButton>
#include <QWidget>
#define MAINWINDOW_H
class karpuz : public QPushButton
{
    Q_OBJECT
public:
    karpuz(QWidget *parent = nullptr);
    bool tiklandimi;
    void sil();


public slots:
    void tikla();

};

#endif // KARPUZ_H
