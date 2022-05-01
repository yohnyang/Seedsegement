#include"althorighm.h"

void Segment::get_segmask(const Mat src, Mat&dst)
{
	if (src.empty()) 
	{
		cout << "图像读取错误！" << endl;
		return;
	}
	Mat img;
	resize(src, img, src.size() / 4);//原图尺寸太大，进行缩放
	Mat gray;
	if (img.channels() == 3)
	{
		cvtColor(img, gray, COLOR_BGR2GRAY);
		this->image_src = img.clone();
	}
	else if (img.channels() == 1)
	{
		gray = img.clone();
		cvtColor(gray, this->image_src, COLOR_GRAY2BGR);
	}
	
	Mat bw;
	threshold(gray, bw, -1, 255, THRESH_OTSU);//二值化
	//namedWindow("bw", WINDOW_NORMAL);
	//imshow("bw", bw);

	vector<Vec4i>hierachy;
	vector<vector<Point>>contours;
	findContours(bw, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());
	Mat bw0(bw.size(), CV_8UC1, Scalar(0));
	for (int i = 0; i < contours.size(); ++i)
	{
		int a = contourArea(contours[i]);
		//if (a < 150000 && a>20000)
		if (a < 12000 && a>4000)
		{
			drawContours(bw0, contours, i, Scalar(255), -1);
		}
	}
	//闭运算
	Mat bw_close;
	Mat ele = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	morphologyEx(bw0, bw_close, MORPH_CLOSE, ele);
	//namedWindow("close", WINDOW_NORMAL);
	//imshow("close", bw_close);
	this->image_src = img.clone();
	this->image_gray = gray.clone();
	this->image_bw = bw.clone();
	this->image_close = bw_close.clone();
	dst = bw_close.clone();
}

void Segment::get_seg(const Mat mask)
{
	Mat img_ = mask.clone();
	Mat img_s;
	cvtColor(img_, img_s, COLOR_GRAY2BGR);

	//Mat label, stats, cens;
	//connectedComponentsWithStats(img_, label, stats, cens, 8);
	//Point2f p;
	//for (int i = 1; i < cens.rows; ++i)
	//{
	//	p.x = cens.at<double>(i, 0);
	//	p.y = cens.at<double>(i, 1);
	//	
	//	//circle(img_s, p, 6, Scalar(0, 255, 0));
	//	putText(img_s, to_string(i), p, FONT_HERSHEY_COMPLEX, 6.0, Scalar(0, 255, 0),8);
	//	
	//}
	vector<Vec4i>hierachy;
	vector<vector<Point>>contours;
	findContours(img_, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());

	RNG rng;
	for (int i = 0; i < contours.size(); ++i)
	{
		Scalar color_ = Scalar(rng.uniform(0.0, 255.0), rng.uniform(0.0, 255.0), rng.uniform(0.0, 255.0));
		drawContours(img_s, contours, i, color_, -1);
	}
	addWeighted(this->image_src, 0.6, img_s, 0.4,0, this->image_seg);
	//this->image_seg = img_s.clone();
}

void Segment::get_seed(const Mat mask)
{
	Mat img_con = mask.clone();
	Mat img_hull = mask.clone();
	Mat img_ = mask.clone();
	//cvtColor(img_, img_, COLOR_GRAY2BGR);
	vector<Vec4i>hierachy_;
	vector<vector<Point>>contours_;
	findContours(mask, contours_, hierachy_, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());
	vector<Rect>boundrects(contours_.size());//存储外接矩形
	vector<RotatedRect>rects(contours_.size());//存储最小外接矩形
	vector<vector<Point>>hulls(contours_.size());//存储凸包
	vector<Mat>seeds(contours_.size());//存储分割后图像
	vector<Mat>seeds_down(contours_.size());//存储分割后图像1
	for (int i = 0; i < contours_.size(); ++i)
	{
		boundrects[i] = boundingRect(contours_[i]);
		seeds[i] = mask(Rect(boundrects[i].x - 20, boundrects[i].y - 20, boundrects[i].width + 40, boundrects[i].height + 40));
		//rectangle(img_, boundrects[i], Scalar(0, 255, 0));
		rects[i] = minAreaRect(contours_[i]);
		vector<Point2f> boxPts(4);
		rects[i].points(boxPts.data());
		//boundrects[i].points(boxPts.data());
		for (int j = 0; j < 4; j++)
		{
			//line(img_, boxPts[j], boxPts[(j + 1) % 4], Scalar(0, 255, 0), 2, 8);  //绘制最小外接矩形每条边
		}
		//计算凸包
		vector<int>hullmat;
		vector<Point>hull;
		convexHull(Mat(contours_[i]), hullmat, 1, 1);
		for (int k = 0; k < hullmat.size(); ++k)
		{
			hull.push_back(contours_[i][hullmat[k]]);
		}
		hulls[i] = (hull);
		drawContours(img_hull, hulls, i, Scalar(255), -1);
		//seeds_hulls[i] = img_hull(Rect(boundrects[i].x - 20, boundrects[i].y - 20, boundrects[i].width + 40, boundrects[i].height + 40));
		//cout << "1" << endl;
	}
	bitwise_xor(mask, img_hull, this->image_seg_1);
	Mat ele = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
	morphologyEx(this->image_seg_1, this->image_seg_1, MORPH_OPEN, ele);
	for (int i = 0; i < boundrects.size(); ++i)
	{
		seeds_down[i] = this->image_seg_1(Rect(boundrects[i].x - 20, boundrects[i].y - 20, boundrects[i].width + 40, boundrects[i].height + 40));
	}

	this->Contours.assign(contours_.begin(), contours_.end());
	this->Boundrects.assign(boundrects.begin(), boundrects.end());
	this->Rects.assign(rects.begin(), rects.end());
	this->Hulls.assign(hulls.begin(), hulls.end());
	this->Seeds.assign(seeds.begin(), seeds.end());
	this->Seeds_down.assign(seeds_down.begin(), seeds_down.end());
}

void Segment::get_Classify()
{
	int num = this->Seeds.size();
	vector<float>lens1(num);
	vector<float>lens2(num);
	vector<float>lens3(num);
	vector<vector<Point>>cons_down(num);
	vector<Mat>diff(num);
	for (int i = 0; i < num; i++)
	{
		lens1[i] = this->Boundrects[i].width;
		vector<Vec4i>hierachy;
		vector<vector<Point>>contours;
		findContours(this->Seeds_down[i], contours, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());
		int area_max = -1;;
		for (int j = 0; j < contours.size(); ++j)
		{
			Rect rect = boundingRect(contours[j]);
			int area = contourArea(contours[j]);
			if ( area> area_max)
			{
				area_max = area;
				lens2[i] = rect.height;
				lens3[i] = area;
				cons_down[i] = contours[j];
			}
		}
	}
	/*Mat bw(this->image_bw.size(), CV_8UC1, Scalar(0));
	drawContours(bw, cons_down, -1, Scalar(255), -1);*/
	this->lens_1.assign(lens1.begin(), lens1.end());
	this->lens_2.assign(lens2.begin(), lens2.end());
	this->lens_3.assign(lens3.begin(), lens3.end());
	this->Cons_down.assign(cons_down.begin(), cons_down.end());

}