#pragma once
#include <QtWidgets/QMainWindow>
#include<QtGui>
#include<QtWidgets>
#include<QMainWindow>
#include "ui_Seedseg.h"
#include"althorighm.h"

class Seedseg : public QMainWindow
{
    Q_OBJECT

public:
    Seedseg(QWidget *parent = Q_NULLPTR);
    void init();
    
    Segment seg;

private:
    Ui::SeedsegClass ui;
    std::string open_path;
    std::string save_path;

    QImage* imShow;
    Mat imgSrc;
    
    bool seg_flag;
    bool seed_flag;

private slots:

    void open();
    void save();
    void onComboxSelect(int);
    void onCombox_2Select(int);
    void calcu();
    void classify();
};
