#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;


class Segment
{
public:
	vector<vector<Point>>Contours;//������
	vector<vector<Point>>Cons_down;
	vector<Rect>Boundrects;//�洢��Ӿ���
	vector<RotatedRect>Rects;//�洢��С��Ӿ���
	vector<vector<Point>>Hulls;//�洢͹��
	vector<Mat>Seeds;//�洢�ָ��ͼ��
	vector<Mat>Seeds_down;//�洢�ָ��ͼ��

	//���������������
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

	void get_seg(const Mat mask);//���ӷָ�

	void get_seed(const Mat mask);//�ָ�����Ӽ�������

	void get_Classify();//����

	
};

