#include "Seedseg.h"
#include"althorighm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Seedseg w;
    w.show();
    return a.exec();
}




//Segment seg;
//
//int main()
//{
//	Mat im = imread("img//JZ11.jpg");
//
//	Mat gray;
//	if (!im.empty() && im.channels() == 3)
//	{
//		cvtColor(im, gray, COLOR_BGR2GRAY);
//	}
//	else if (!im.empty() && im.channels() == 1)
//	{
//		gray = im.clone();
//	}
//	else {
//		cout << "Í¼Ïñ¶ÁÈ¡´íÎó£¡" << endl;
//		return -1;
//	}
//
//	
//
//
//	
//	
//
//
//
//	waitKey(0);
//	return 0;
//}
