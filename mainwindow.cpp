#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QMessageBox>
#include <mybutton.h>
#include <qtimer.h>

const int AMOUNT_OF_COLORS = 6;
int colors[AMOUNT_OF_COLORS][3] = {{240, 38, 180},
                   {255, 129, 228},
                   {255, 26, 114},
                   {204, 15, 122},
                   {255, 117, 161},
                   {255, 43, 216}};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Memory Blocks");
    QPixmap pixmap(":/new/img/img/text.png");
    ui->label->setPixmap(pixmap);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setColors(){
    int counterOfOuterLoop = (size*size/2)%AMOUNT_OF_COLORS==0?(size*size/2)/AMOUNT_OF_COLORS:(size*size/2)/AMOUNT_OF_COLORS+1;
    int initialisedBlocksCounter = 0;
    srand(time(NULL));
    for(int n = 0; n<counterOfOuterLoop; n++){
        for(int m =0; m<AMOUNT_OF_COLORS; m++){
            int i, j;
            do{
                i = rand()%size;
                j = rand()%size;
            } while(button[i][j]->isOccupied());
            QColor color(colors[m][0], colors[m][1], colors[m][2]);
            button[i][j]->setBgColor(color);
            button[i][j]->setOccupied(true);
            do{
                i = rand()%size;
                j = rand()%size;
            } while(button[i][j]->isOccupied());
            button[i][j]->setBgColor(color);
            button[i][j]->setOccupied(true);
            initialisedBlocksCounter+=2;
            if(initialisedBlocksCounter>=size*size)
                break;
        }
    }
}

void MainWindow::onBlockClicked(){
    MyButton* button = (MyButton*) sender();
    QString style = defaultStyle + "background-color: rgb("
                                 + QString::number(button->getBgColor().red()) + ","
                                 + QString::number(button->getBgColor().green()) + ","
                                 + QString::number(button->getBgColor().blue()) + ")";
    if(prev==nullptr && button->isActive()){
        prev = button;
        button->setStyleSheet(style);
        prev->setActive(false);
    } else {
        if(prev!=nullptr && prev->getBgColor() == button->getBgColor() && button->isActive()){
            button->setStyleSheet(style);
            button->setActive(false);
            prev = nullptr;
            pairCounter++;
            if(pairCounter==(size*size)/2){
                QMessageBox::StandardButton reply =QMessageBox::information(this, "You won", "Congratulations! You won the game!"
                                                                            "\nWould you like to start again?",
                                                                            QMessageBox::Yes|QMessageBox::No);
                if(reply==QMessageBox::Yes){
                    pairCounter = 0;
                    currentButton = nullptr;
                     ui->setupUi(this);
                     QPixmap pixmap(":/new/img/img/text.png");
                     ui->label->setPixmap(pixmap);
                } else {
                    QApplication::quit();
                }
            }
        } else if(prev!=nullptr && prev->getBgColor() != button->getBgColor() && button->isActive()){
            currentButton = button;
            button->setStyleSheet(style);
            QTimer::singleShot(200, this, SLOT(clearColors()));
        }
    }
}

void MainWindow::clearColors(){
    prev->setStyleSheet(defaultStyle);
    currentButton->setStyleSheet(defaultStyle);
    prev->setActive(true);
    prev = nullptr;
}

void MainWindow::on_btnStart_clicked()
{
    size = ui->lineEdit->text().toInt();
    button = new MyButton**[size];
    for(int i =0; i<size; i++){
        button[i] = new MyButton*[size];
    }
    QWidget *widget = new QWidget;
    QGridLayout *gridLayout = new QGridLayout;
    for(int i =0; i<size; i++){
        for(int j = 0; j<size; j++){
            button[i][j] = new MyButton;
            button[i][j]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            button[i][j]->setStyleSheet(defaultStyle);
            gridLayout->addWidget(button[i][j], i, j);
        }
    }
    setColors();
    for(int i =0; i<size; i++){
        for(int j = 0; j<size; j++){
            connect(button[i][j], SIGNAL(clicked()), this, SLOT(onBlockClicked()));
        }
    }
    for(int i =0; i<size; i++){
        for(int j = 0; j<size; j++){
           QString style = defaultStyle + "background-color: rgb("
                             + QString::number(button[i][j]->getBgColor().red()) + ","
                             + QString::number(button[i][j]->getBgColor().green()) + ","
                             + QString::number(button[i][j]->getBgColor().blue()) + ")";
            button[i][j]->setStyleSheet(style);
        }
    }
    widget->setLayout(gridLayout);
    setCentralWidget(widget);
    QTimer::singleShot(1000, this, SLOT(setDefaultStyle()));
}

void MainWindow::setDefaultStyle(){
    for(int i =0; i<size; i++){
        for(int j = 0; j<size; j++){
            button[i][j]->setStyleSheet(defaultStyle);
        }
    }
}
