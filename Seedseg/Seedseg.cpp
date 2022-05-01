#include "Seedseg.h"
#include"althorighm.h"

inline cv::Mat QImage2cvMat(const QImage& image)
{
    switch (image.format())
    {
        // 8-bit, 4 channel
    case QImage::Format_ARGB32:
        break;
    case QImage::Format_ARGB32_Premultiplied:
    {
        cv::Mat mat(image.height(), image.width(),CV_8UC4, (void*)image.constBits(),image.bytesPerLine());
        return mat.clone();
    }

    // 8-bit, 3 channel
    case QImage::Format_RGB32:
    {
        cv::Mat mat(image.height(), image.width(),CV_8UC4,(void*)image.constBits(),image.bytesPerLine());
        // drop the all-white alpha channel
        cv::cvtColor(mat, mat, cv::COLOR_BGRA2BGR);
        return mat.clone();
    }
    case QImage::Format_RGB888:
    {
        QImage swapped = image.rgbSwapped();
        cv::Mat mat(swapped.height(), swapped.width(), CV_8UC3,(void*)image.constBits(),image.bytesPerLine());
        return mat.clone();
    }

    // 8-bit, 1 channel   
    case QImage::Format_Indexed8:
    {
        cv::Mat mat(image.height(), image.width(),CV_8UC1,(void*)image.constBits(),image.bytesPerLine());
        return mat.clone();
    }

    // wrong
    default:
        //qDebug() << "ERROR: QImage could not be converted to Mat.";
        break;
    }
    return cv::Mat();
}

inline QImage cvMat2QImage(const cv::Mat& mat)
{
    switch (mat.type())
    {
        // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image(mat.data,mat.cols, mat.rows,static_cast<int>(mat.step), QImage::Format_ARGB32);
        return image;
    }

    // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image(mat.data, mat.cols, mat.rows,static_cast<int>(mat.step),QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    // 8-bit, 1 channel
    case CV_8UC1:
    {
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        QImage image(mat.data,mat.cols, mat.rows,static_cast<int>(mat.step),QImage::Format_Grayscale8);
#else
        static QVector<QRgb>  sColorTable;

        // only create our color table the first time
        if (sColorTable.isEmpty())
        {
            sColorTable.resize(256);

            for (int i = 0; i < 256; ++i)
            {
                sColorTable[i] = qRgb(i, i, i);
            }
        }

        QImage image(mat.data,mat.cols, mat.rows,static_cast<int>(mat.step),QImage::Format_Indexed8);
        image.setColorTable(sColorTable);
#endif
        return image;
    }
    // wrong 
    default:
        //qDebug() << "ERROR: Mat could not be converted to QImage.";
        break;
    }
    return QImage();
}


Seedseg::Seedseg(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->resize(QSize(1080,780));
    init();
}

void Seedseg::init()
{
    //添加信号与槽函数
    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(open()));
    connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(save()));
    connect(ui.comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboxSelect(int)));
    connect(ui.comboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(onCombox_2Select(int)));
    connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(calcu()));
    connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(classify()));
}

void Seedseg::open()
{
    QSettings setting("./Setting.ini", QSettings::IniFormat);          //为了能记住上次打开的路径
    QString lastPath = setting.value("LastFilePath").toString();
    QString filename = QFileDialog::getOpenFileName(this,
        QString::fromLocal8Bit("读入图像路径"), lastPath, QString::fromLocal8Bit("Images(*.jpg *.png *.bmp)"));
    if (filename.isEmpty())
    {
        return;
    }
    else
    {
        QImage* img = new QImage();
        if (!(img->load(filename))) //加载图像
        {
            QMessageBox::warning(this, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("打开图像错误！"));
		}
        QString str = QString::fromLocal8Bit("打开路径： ") + filename;
		ui.txtout->append(str);
		open_path = filename.toStdString();
        imgSrc = QImage2cvMat(*img);
        //原图尺寸较大，进行缩放：
		ui.imgshow->setPixmap(QPixmap::fromImage(*img));
        ui.imgshow->setScaledContents(true);
	}
}

void Seedseg::save()
{

    QSettings setting("./Setting.ini", QSettings::IniFormat);          //为了能记住上次打开的路径
    QString lastPath = setting.value("LastFilePath").toString();
    QString filename = QFileDialog::getSaveFileName(this,
        QString::fromLocal8Bit("读入图像路径"), lastPath, QString::fromLocal8Bit("Images(*.jpg *.png *.bmp)"));
    if (filename.isEmpty())
    {
        return;
    }
    else
    {
        if (!filename.isNull()) //加载图像
        {
            QString str = QString::fromLocal8Bit("保存路径： ") + filename;
            ui.txtout->append(str);
            save_path = filename.toStdString();
            QImage img = ui.imgshow->pixmap()->toImage();     // 读取图像
            img.save(filename);                          // 保存图像
        }
    }
}

void Seedseg::onComboxSelect(int)
{
    if (imgSrc.empty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("打开图像错误！"));
        return;
    }
    Mat img_mask, img_seg;
    seg.get_segmask(imgSrc, img_mask);
    seg_flag = true;

    QImage im = cvMat2QImage(imgSrc);
    QImage*img_small = &im;
    ui.label_3->setPixmap(QPixmap::fromImage(*img_small));
    ui.label_3->setScaledContents(true);
    //获取combobox当前内容
    QString text = ui.comboBox->currentText();
    
    if (text == QString::fromLocal8Bit("灰度化"))
    {
        QImage img_ = cvMat2QImage(seg.image_gray);
        imShow = &img_;
        ui.imgshow->setPixmap(QPixmap::fromImage(*imShow));
        ui.imgshow->setScaledContents(true);
    }
    else if (text == QString::fromLocal8Bit("二值化"))
    {
        QImage img_ = cvMat2QImage(seg.image_bw);
        imShow = &img_;
        ui.imgshow->setPixmap(QPixmap::fromImage(*imShow));
        ui.imgshow->setScaledContents(true);
    }
    else if (text == QString::fromLocal8Bit("闭运算"))
    {
        QImage img_ = cvMat2QImage(seg.image_close);
        imShow = &img_;
        ui.imgshow->setPixmap(QPixmap::fromImage(*imShow));
        ui.imgshow->setScaledContents(true);
    }
    else if (text == QString::fromLocal8Bit("种子分割"))
    {
        seg.get_seg(img_mask);
        QImage img_ = cvMat2QImage(seg.image_seg);
        imShow = &img_;
        ui.imgshow->setPixmap(QPixmap::fromImage(*imShow));
        ui.imgshow->setScaledContents(true);
    }
    
}

void Seedseg::onCombox_2Select(int)
{
    if (imgSrc.empty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("Error"), QString::fromLocal8Bit("打开图像错误！"));
        return;
    }
    if (seg_flag != true)
    {
        Mat img_mask, img_seg;
        seg.get_segmask(imgSrc, img_mask);
        seg.get_seg(img_mask);
    }
    seed_flag = true;

    QImage im = cvMat2QImage(imgSrc);
    QImage* img_small = &im;
    ui.label_3->setPixmap(QPixmap::fromImage(*img_small));
    ui.label_3->setScaledContents(true);
    //获取combobox当前内容
    QString text = ui.comboBox_2->currentText();
    seg.get_seed(seg.image_close);
    
    Mat img_show = seg.image_bw.clone();
    if (img_show.channels() == 1)
    {
        cvtColor(img_show, img_show, COLOR_GRAY2BGR);
    }

    if (text == QString::fromLocal8Bit("外轮廓"))
    {
        drawContours(img_show, seg.Contours, -1, Scalar(0, 255, 0), 3);
        QImage img_ = cvMat2QImage(img_show);
        imShow = &img_;
        ui.imgshow->setPixmap(QPixmap::fromImage(*imShow));
        ui.imgshow->setScaledContents(true);
    }
    else if (text == QString::fromLocal8Bit("外接矩形"))
    {
        for (int i = 0; i < seg.Boundrects.size(); ++i)
        {
            rectangle(img_show, seg.Boundrects[i], Scalar(0, 255, 0),3);
        }
        QImage img_ = cvMat2QImage(img_show);
        imShow = &img_;
        ui.imgshow->setPixmap(QPixmap::fromImage(*imShow));
        ui.imgshow->setScaledContents(true);
    }
    else if (text == QString::fromLocal8Bit("凸包"))
    {
        drawContours(img_show, seg.Hulls, -1, Scalar(0, 255, 0),3);
        QImage img_ = cvMat2QImage(img_show);
        imShow = &img_;
        ui.imgshow->setPixmap(QPixmap::fromImage(*imShow));
        ui.imgshow->setScaledContents(true);
    }
    /*else if (text == QString::fromLocal8Bit("种子下端"))
    {
        seg.get_Classify();
        for (int i = 0; i < seg.Cons_down.size(); ++i)
        {
            if (seg.Cons_down[i].size() > 0)
            {
                drawContours(img_show, seg.Cons_down, i, Scalar(0, 255, 0), 3);
            }
        }
        
        QImage img_ = cvMat2QImage(img_show);
        imShow = &img_;
        ui.imgshow->setPixmap(QPixmap::fromImage(*imShow));
        ui.imgshow->setScaledContents(true);
    }*/
}

void Seedseg::calcu()
{
    QImage im = cvMat2QImage(imgSrc);
    QImage* img_small = &im;
    ui.label_3->setPixmap(QPixmap::fromImage(*img_small));
    ui.label_3->setScaledContents(true);
    if (seed_flag != true)
    {
        Mat img_mask, img_seg;
        seg.get_segmask(imgSrc, img_mask);
        seg.get_seg(img_mask);
        seg.get_seed(img_mask);
        seg.get_Classify();
    }
    QString str;
    Mat img = seg.image_seg.clone();
    for (int i = 0; i < seg.lens_1.size(); ++i)
    {
        str = QString::number(i)+"   " +
            QString::fromLocal8Bit("Grain Width: ") + QString::number(seg.lens_1[i]) +
            QString::fromLocal8Bit("  Crease Depth: ") + QString::number(seg.lens_2[i]) +
            QString::fromLocal8Bit("  Crease Area: ") + QString::number(seg.lens_3[i]);
        ui.txtout->append(str);
        putText(img, to_string(i), seg.Rects[i].center, FONT_HERSHEY_SCRIPT_COMPLEX, 2,Scalar(0,0,255),1);
    }
    QImage img_ = cvMat2QImage(img);
    imShow = &img_;
    ui.imgshow->setPixmap(QPixmap::fromImage(*imShow));
    ui.imgshow->setScaledContents(true);
}

void Seedseg::classify()
{
    QImage im = cvMat2QImage(imgSrc);
    QImage* img_small = &im;
    ui.label_3->setPixmap(QPixmap::fromImage(*img_small));
    ui.label_3->setScaledContents(true);
    if (seed_flag != true)
    {
        Mat img_mask, img_seg;
        seg.get_segmask(imgSrc, img_mask);
        seg.get_seg(img_mask);
        seg.get_seed(img_mask);
        seg.get_Classify();
    }
    QString str;
    Mat img(seg.image_seg.size(),CV_8UC3,Scalar::all(0));
    Scalar color_[3]{ Scalar(123,12,234),Scalar(55,200,20),Scalar(65,30,200) };
    for (int i = 0; i < seg.lens_1.size(); ++i)
    {
        if (seg.lens_3[i] < 100)
        {
            drawContours(img, seg.Contours, i, color_[0], -1);
            str = QString::number(i) + "   " +
                QString::fromLocal8Bit("Grain Width: ") + QString::number(seg.lens_1[i]) +
                QString::fromLocal8Bit("  Crease Depth: ") + QString::number(seg.lens_2[i]) +
                QString::fromLocal8Bit("  Crease Area: ") + QString::number(seg.lens_3[i]) +
                QString::fromLocal8Bit("   第 ") + QString::number(1) + QString::fromLocal8Bit(" 类")+
                QString::fromLocal8Bit("   底部凹陷面积 < 100 ");
        }
        else if (seg.lens_3[i] <= 200) {
            drawContours(img, seg.Contours, i, color_[1], -1);
            str = QString::number(i) + "   " +
                QString::fromLocal8Bit("Grain Width: ") + QString::number(seg.lens_1[i]) +
                QString::fromLocal8Bit("  Crease Depth: ") + QString::number(seg.lens_2[i]) +
                QString::fromLocal8Bit("  Crease Area: ") + QString::number(seg.lens_3[i]) +
                QString::fromLocal8Bit("   第 ") + QString::number(2) + QString::fromLocal8Bit(" 类")+
                QString::fromLocal8Bit("   100 < 底部凹陷面积 200 ");
        }
        else
        {
            drawContours(img, seg.Contours, i, color_[2], -1);
            str = QString::number(i) + "   " +
                QString::fromLocal8Bit("Grain Width: ") + QString::number(seg.lens_1[i]) +
                QString::fromLocal8Bit("  Crease Depth: ") + QString::number(seg.lens_2[i]) +
                QString::fromLocal8Bit("  Crease Area: ") + QString::number(seg.lens_3[i]) +
                QString::fromLocal8Bit("   第 ") + QString::number(3) + QString::fromLocal8Bit(" 类") +
                QString::fromLocal8Bit("   200 < 底部凹陷面积 300 ");
        }
        ui.txtout->append(str);
        putText(img, to_string(i), seg.Rects[i].center, FONT_HERSHEY_SCRIPT_COMPLEX, 2, Scalar(0, 0, 255), 1);
    }
    Mat img_;
    addWeighted(seg.image_src, 0.6, img, 0.4,0, img_);
    QImage img_show = cvMat2QImage(img_);
    imShow = &img_show;
    ui.imgshow->setPixmap(QPixmap::fromImage(*imShow));
    ui.imgshow->setScaledContents(true);
}

