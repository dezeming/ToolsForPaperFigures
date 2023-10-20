/**
Copyright (C) <2023>  <Dezeming>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/*
code from: 
https://blog.csdn.net/weixin_45645281/article/details/108324747
*/

#ifndef OPENCVTOQT_H
#define OPENCVTOQT_H

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

#include <QLabel>
#include <QImage>
#include <QPixmap>

class OpenCVtoQt
{
public:
	OpenCVtoQt();

	/** Convert QLabel to cvMat
	* copy mode
	*/ 
	static void LabeltoMat(QLabel *label, cv::Mat &mat);

	/** Convert cvMat to QImage
	* Only supports CV_ 8UC4, CV_ 8UC3 and CV_ 8UC1.
	* copy mode
	*/
	static QImage cvMatToQImage(const cv::Mat &inMat);

	/** Convert cvMat to QPixmap
	* Only supports CV_ 8UC4, CV_ 8UC3 and CV_ 8UC1.
	* copy mode
	*/
	static QPixmap cvMatToQPixmap(const cv::Mat &inMat);

	/** Convert QImage to cvMat
	* copy mode
	*/
	static cv::Mat QImageToCvMat(const QImage &inImage, bool inCloneImageData = true);

	/** Convert QPixmap to cvMat
	* copy mode
	*/
	static cv::Mat QPixmapToCvMat(const QPixmap &inPixmap, bool inCloneImageData = true);


	~OpenCVtoQt();
};



#endif // OPENCVTOQT_H

