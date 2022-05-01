#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;


class Segment
{
public:
	vector<vector<Point>>Contours;//外轮廓
	vector<vector<Point>>Cons_down;
	vector<Rect>Boundrects;//存储外接矩形
	vector<RotatedRect>Rects;//存储最小外接矩形
	vector<vector<Point>>Hulls;//存储凸包
	vector<Mat>Seeds;//存储分割后图像
	vector<Mat>Seeds_down;//存储分割后图像

	//求出种子三个特征
	vector<float>lens_1;//Grain width
	vector<float>lens_2;//Crease Depth
	vector<float>lens_3;//Grease Area

	Mat image_src;
	Mat image_gray;
	Mat image_bw;
	Mat image_close;
	Mat image_seg;
	Mat image_seg_1;

public:

	void get_segmask(const Mat src, Mat&mask);

	void get_seg(const Mat mask);//种子分割

	void get_seed(const Mat mask);//分割单个种子计算特征

	void get_Classify();//分类

	
};

