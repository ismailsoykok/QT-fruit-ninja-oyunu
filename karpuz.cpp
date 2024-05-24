#include "karpuz.h"
#include <QTimer>
//İSMAİL SOYKÖK 22100011007
karpuz::karpuz(QWidget *parent):QPushButton(parent)
{
    tiklandimi=false;
    connect(this,SIGNAL(clicked()),this,SLOT(tikla()));




}

void karpuz::tikla()
{

    tiklandimi = !tiklandimi; //tıklanınca değişkeni true yapıyor

    if (tiklandimi) {

        disconnect(this, SIGNAL(clicked()), this, SLOT(tikla()));


        setIcon(QIcon(":/new/prefix1/images/2.png")); //kesik karpuz resmi koyuyoruz
        setIconSize(QSize(50, 50));


        QTimer::singleShot(2000, this, &karpuz::sil);// belli bi süre sonra butonu siliyoruz


    }

}
void karpuz::sil()
{
    setGeometry(x(),y(),0,0);//boyutunu 0 yapma

}

