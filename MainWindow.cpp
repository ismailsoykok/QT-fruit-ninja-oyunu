#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFile>
#include <QTimer>
#include <QLabel>
#include <QMessageBox>
//İSMAİL SOYKÖK 22100011007
/*
Arka plan değiştirme ve diğer label arka planlarını prefix 3'ün içine attım toolbardan arka plan değiştirme ve radiobuttonlarla zorluk seviyesi seçme ayarı koydum
oyna butonuna basana kadar oyun başlamıyor başladıktan sonra zorluk seviyesi yaptığım için en fazla kesilen karpuz sağlıklı bir kıyas olmayacaktı bu yüzden 30 saniye içinde karpuzların
yüzde kaçını kestiğine göre bir oran veriyor amaç en yüksek oranı sağlamak
skorlar.txt dosyasındaki en yüksek orandan daha yüksekse yeni rekor oluyor ve oynanan tüm skorlar dosyanın içine yazılıyor

 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label->raise();
    ui->label_2->raise();

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::zorluk);
    connect(ui->action1_arkaplan, &QAction::triggered, this, &MainWindow::on_action1_arkaplan_triggered);
    connect(ui->actionarkaplan2, &QAction::triggered, this, &MainWindow::on_action2_arkaplan_triggered);
    connect(ui->arkaplan3, &QAction::triggered, this, &MainWindow::on_arkaplan3_triggered);

}
MainWindow::~MainWindow()
{
    delete ui;

}
//BOMBAYA BASMA ÖZELLİĞİ EKLEDİM
void MainWindow::bombaolustur() {
    if(bombalar.length()<bombasay){ //zorluk seçimine göre bombasayısını belirleyip ona göre bomba oluşturuyoruz
        QPushButton *bomba = new QPushButton(this);
        int x = rand() % (800 - 200 + 1) + 200;
        int y = rand() % (300 - 100 + 1) + 100;;
        bomba->setGeometry(x, y, 70, 70);
        bomba->setIcon(QIcon(":/new/prefix3/images/bomba.png")); //butona bomba resmi koyma
        bomba->setIconSize(QSize(70, 70));
        bomba->setStyleSheet("background-color: rgba(255, 255, 255, 0);"); //arka planı şeffaf yapma
        bomba->show();
        connect(bomba, &QPushButton::clicked, this, &MainWindow::bombaTiklandi);
        bombalar.append(bomba);

        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, [=]() {
            if (!bomba) return;
            if (bomba->geometry().y() > 650) {
                bombalar.removeOne(bomba);
                delete bomba;
                timer->stop();

                return;
            }

            bomba->move(bomba->x(), bomba->y() + 5); // Yüksekliği artırarak bombanın düşmesini sağlar

        });
        timer->start(50); // Bombaların ne sıklıkla düşeceğini belirler
    }

}


void MainWindow::bombaTiklandi() {
    QPushButton *bomba = qobject_cast<QPushButton*>(sender()); // Tetikleyen öğeyi al

        bomba->setIcon(QIcon(":/new/prefix3/images/ates.png"));
        bomba->setStyleSheet("background-color: rgba(255, 255, 255, 0);");


        QTimer::singleShot(1500, [=]() {


                bomba->setGeometry(bomba->x(), bomba->y(), 0, 0);
                QMessageBox::warning(this, "YANDINIZ", "BOMBA PATLADI...");//bomba butonunu yok eder ve yandınız mesajı verir ardından uygulamayı kapatır
                close();


    }


);}





void MainWindow::on_action1_arkaplan_triggered()
{
    QString imagePath = ":/new/prefix3/images/depositphotos_67982979-stock-illustration-horizontally-seamless-game-background.jpg";
    QString styleSheet = "background-image: url(" + imagePath + ");";
    ui->label_3->setStyleSheet(styleSheet);
}
void MainWindow::on_action2_arkaplan_triggered()
{
    QString imagePath = ":/new/prefix3/images/fruit-ninja-6.jpg";
    QString styleSheet = "background-image: url(" + imagePath + ");";
    ui->label_3->setStyleSheet(styleSheet);
}
void MainWindow::on_arkaplan3_triggered(){

    QString imagePath = ":/new/prefix1/images/back.jpg";
    QString styleSheet = "background-image: url(" + imagePath + ");";
    ui->label_3->setStyleSheet(styleSheet);

    //action butonları ile arka planı değiştirme


}
void MainWindow::zorluk(){
    //pushbuttona basılınca 30 saniye süre sayması için timer ayarlıyoruz onun dışında fonksiyonu seçilen zorluğa göre belli aralıkla çağırıp karpuz üretiyoruz
    QMessageBox::information(this,"BİLGİLENDİRME","Bombalara basarsanız oyun biter, kesilen karpuzların kaçırılanlara oranına göre başarı durumu ölçülür."
                                                    " Zorluk seviyesi arttıkça düşen karpuz ve bomba sayısı artar."
                                                    " BOL ŞANS");
    geriSayimSure = 30;
    QTimer *geriSayimTimer = new QTimer(this);
    geriSayimTimer->setInterval(1000);
    connect(geriSayimTimer, &QTimer::timeout, this, &MainWindow::geriSayimGuncelle);
    geriSayimTimer->start();



    if(ui->easy->isChecked()){
        bombasay =1;
        QTimer *zamanlayici=new QTimer(this);
        zamanlayici->start(800);
        connect(zamanlayici, &QTimer::timeout, this, &MainWindow::karpuzekle);
        QTimer *zamanlayici2=new QTimer(this);
        zamanlayici2->start(1000);
        connect(zamanlayici2, &QTimer::timeout, this, &MainWindow::sayac);
        QTimer *zamanlayici3=new QTimer(this);
        zamanlayici3->start(1000);
        connect(zamanlayici3, &QTimer::timeout, this, &MainWindow::bombaolustur);
        QTimer *zamanlayici4=new QTimer(this);
        zamanlayici4->start(50);
        connect(zamanlayici4, &QTimer::timeout, this, &MainWindow::karpuzdusme);
        delete ui->groupBox;

    }
    else if(ui->medium->isChecked()){
        bombasay = 2;
        QTimer *zamanlayici=new QTimer(this);
        zamanlayici->start(600);
        connect(zamanlayici, &QTimer::timeout, this, &MainWindow::karpuzekle);
        QTimer *zamanlayici2=new QTimer(this);
        zamanlayici2->start(1000);
        connect(zamanlayici2, &QTimer::timeout, this, &MainWindow::sayac);
        QTimer *zamanlayici3=new QTimer(this);
        zamanlayici3->start(1000);
        connect(zamanlayici3, &QTimer::timeout, this, &MainWindow::bombaolustur);
        QTimer *zamanlayici4=new QTimer(this);
        zamanlayici4->start(50);
        connect(zamanlayici4, &QTimer::timeout, this, &MainWindow::karpuzdusme);
        delete ui->groupBox;
    }
    else if(ui->hard->isChecked()){
        bombasay = 3;
        QTimer *zamanlayici=new QTimer(this);
        zamanlayici->start(400);
        connect(zamanlayici, &QTimer::timeout, this, &MainWindow::karpuzekle);
        QTimer *zamanlayici2=new QTimer(this);
        zamanlayici2->start(1000);
        connect(zamanlayici2, &QTimer::timeout, this, &MainWindow::sayac);
        QTimer *zamanlayici3=new QTimer(this);
        zamanlayici3->start(1000);
        connect(zamanlayici3, &QTimer::timeout, this, &MainWindow::bombaolustur);
        QTimer *zamanlayici4=new QTimer(this);
        zamanlayici4->start(50);
        connect(zamanlayici4, &QTimer::timeout, this, &MainWindow::karpuzdusme);
        delete ui->groupBox;
    }
    else if(ui->imposible->isChecked()){
        bombasay = 4;
        QTimer *zamanlayici=new QTimer(this);
        zamanlayici->start(150);
        connect(zamanlayici, &QTimer::timeout, this, &MainWindow::karpuzekle);
        QTimer *zamanlayici2=new QTimer(this);
        zamanlayici2->start(1000);
        connect(zamanlayici2, &QTimer::timeout, this, &MainWindow::sayac);
        QTimer *zamanlayici3=new QTimer(this);
        zamanlayici3->start(1000);
        connect(zamanlayici3, &QTimer::timeout, this, &MainWindow::bombaolustur);
        QTimer *zamanlayici4=new QTimer(this);
        zamanlayici4->start(50);
        connect(zamanlayici4, &QTimer::timeout, this, &MainWindow::karpuzdusme);
        delete ui->groupBox;
    }
    else {

        QMessageBox::information(this,"Seçim hatası","ZORLUK SEVİYESİ SEÇİNİZ..");

    }
    ui->label_6->setVisible(false);




}

void MainWindow::geriSayimGuncelle()

{    if (geriSayimSure > 0) {
        geriSayimSure--;
        ui->geriSayimLabel->setText(QString::number(geriSayimSure));
    } else {
        disconnect(zamanlayici, &QTimer::timeout, this, &MainWindow::karpuzekle);
        disconnect(zamanlayici2, &QTimer::timeout, this, &MainWindow::sayac);
        // süre bitince kod dursun diye bağlantıları kesiyoruz

        ui->label->setText(QString::number(basarili));
        ui->label_2->setText(QString::number(basarisiz));
        double toplam = basarili + basarisiz;
        double oran = (toplam == 0) ? 0 : (static_cast<double>(basarili) / toplam);

        QFile file2("skorlar.txt");
        if (!file2.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QMessageBox::warning(this, "Hata", "skorlar.txt dosyası açılamadı!");
            return;
        }

        QTextStream dosya(&file2);
        double maxOran = 0.0;
        while (!dosya.atEnd()) {
            QString line = dosya.readLine();
            double gecicioran = line.toDouble();
            if (gecicioran > maxOran) {
                maxOran = gecicioran; //dosyadaki en büyük oranı buluyoruz ve karşılaştırıp ona göre mesaj yazdırıyoruz
            }
        }

        QString message;
        if (oran > maxOran) {
            message = "Başarılı: " + QString::number(basarili) +
                      "\nBaşarısız: " + QString::number(basarisiz) +
                      "\nOran: " + QString::number(oran) +
                      "\nEn yüksek oranı elde ettiniz!";
        } else {
            message = "Başarılı: " + QString::number(basarili) +
                      "\nBaşarısız: " + QString::number(basarisiz) +
                      "\nOran: " + QString::number(oran) +
                      "\nEn yüksek oranı geçemediniz.";
        }


        QMessageBox::information(nullptr, "SONUÇ", message);


        QTextStream giris(&file2);
        giris << "Oran: " << oran << "\n"; //oranı dosyaya atıyoruz

        file2.close();
        close();
    }
}

void MainWindow::karpuzekle(){

    QFile file(":/new/prefix2/konumlar.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        static QTextStream stream(&file);
        if (!stream.atEnd()) {
            QString deger = stream.readLine();
            QStringList values = deger.split(" ");
            if (values.size() >= 2) {
                int x = values[0].toInt();
                int y = values[1].toInt(); //dosyadan okunan x ve y konumlarını alıp rastgele konumda karpuz oluşturuyoruz
                karpuz *buton = new karpuz(this);
                buton->setGeometry(x, y, 70, 70);
                buton->setIcon(QIcon(":/new/prefix1/images/1.png")); //butona karpuz resmi koyma
                buton->setIconSize(QSize(50,50));
                buton->setStyleSheet("background-color: rgba(255, 255, 255, 0);"); //arka planı şeffaf yapma

                buton->show();
                buttonlar.append(buton);






            }
        } else {

            file.close();
        }
    }

}
void MainWindow::karpuzdusme(){



    for(int i=0;i<buttonlar.length();i++)
    {
        if(!buttonlar[i]->tiklandimi){
            buttonlar[i]->move(buttonlar[i]->x(), buttonlar[i]->y() + 5); //tıklanmayan butonlardan sayfanın altına düşenleri başarısız sayıp listeden atıyoruz
            if(buttonlar[i]->geometry().y()>650){
                buttonlar[i]->setGeometry(buttonlar[i]->x(), buttonlar[i]->y(), 0, 0);
                basarisiz+=1;
                buttonlar.removeAt(i);
            }

        }





    }
}
void MainWindow::sayac(){



    for(int i = 0;i<buttonlar.length();i++){

                if(buttonlar[i]->tiklandimi) { //tıklanan butonları basarili sayıyoruz ve listeden atıyoruz ayrıca karpuz sınıfının içindeki clicked ile bağlı tıkla fonksiyonu ilee butonun resmini kesik
                    basarili += 1;// karpuz yapıp butonu yok ediyoruz

                    buttonlar.removeAt(i);
                }


    }





    ui->label->setText(QString::number(basarili)); //labellara skoru yazdırma

    ui->label_2->setText(QString::number(basarisiz));

}




