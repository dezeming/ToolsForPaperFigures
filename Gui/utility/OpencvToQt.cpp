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

#include "opencvtoqt.hpp"



OpenCVtoQt::OpenCVtoQt() { }

//void LabelDisplayMat::LabeltoMat(QLabel *label, cv::Mat &mat)
//{
//    cv::Mat Rgb;
//    QImage Img;
//    if (mat.channels() == 3)//RGB Img
//    {
//        cv::cvtColor(mat, Rgb, cv::COLOR_BGR2RGB);
//        Img = QImage((const uchar*)(Rgb.data), Rgb.cols, Rgb.rows, Rgb.cols * Rgb.channels(), QImage::Format_RGB888);
//    }
//    else//Gray Img
//    {
//        Img = QImage((const uchar*)(mat.data), mat.cols, mat.rows, mat.cols*mat.channels(), QImage::Format_Indexed8);
//    }
//    label->setPixmap(QPixmap::fromImage(Img));
//}


void OpenCVtoQt::LabeltoMat(QLabel *label, cv::Mat &mat) { }

QImage OpenCVtoQt::cvMatToQImage(const cv::Mat &inMat)
{
	switch (inMat.type())
	{
	// 8-bit, 4 channel
	case CV_8UC4:
	{
		QImage image(inMat.data,
			inMat.cols, inMat.rows,
			//Step: Number of bytes of the first row element in the matrix
			//Step[0]: Number of bytes of the first row element in the matrix
			//Step[1]: The number of bytes of an element in a matrix
			//Step 1(0): How many channels are there in a row of the matrix
			//Step1(1): How many channels does an element have (channel())
			static_cast<int>(inMat.step),
			QImage::Format_ARGB32);

		return image;
	}

	// 8-bit, 3 channel
	case CV_8UC3:
	{
		QImage image(inMat.data,
			inMat.cols, inMat.rows,
			static_cast<int>(inMat.step),
			QImage::Format_RGB888);

		return image.rgbSwapped();
	}

	// 8-bit, 1 channel
	case CV_8UC1:
	{
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
		QImage image(inMat.data,
			inMat.cols, inMat.rows,
			static_cast<int>(inMat.step),
			//Format_Alpha8 and Format_Grayscale8 were added in Qt 5.5
			QImage::Format_Grayscale8);
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

			QImage image(inMat.data,
				inMat.cols, inMat.rows,
				static_cast<int>(inMat.step),
				QImage::Format_Indexed8);

			image.setColorTable(sColorTable);
#endif

		return image;
	}

	default:
		std::cout << "OpenCVtoQt::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type() << std::endl;
		break;
	}

	return QImage();
}


QPixmap OpenCVtoQt::cvMatToQPixmap(const cv::Mat &inMat)
{
	return QPixmap::fromImage(cvMatToQImage(inMat));
}


cv::Mat OpenCVtoQt::QImageToCvMat(const QImage &inImage, bool inCloneImageData)
{
	switch (inImage.format())
	{
		// 8-bit, 4 channel
	case QImage::Format_ARGB32:
	case QImage::Format_ARGB32_Premultiplied:
	{
		cv::Mat  mat(inImage.height(), inImage.width(),
			CV_8UC4,
			const_cast<uchar*>(inImage.bits()),
			static_cast<size_t>(inImage.bytesPerLine())
		);

		return (inCloneImageData ? mat.clone() : mat);
	}

	// 8-bit, 3 channel
	case QImage::Format_RGB32:
	case QImage::Format_RGB888:
	{
		if (!inCloneImageData)
		{
			std::cout << "OpenCVtoQt::QImageToCvMat() - Conversion requires cloning because we use a temporary QImage" << std::endl;
		}

		QImage   swapped = inImage;

		if (inImage.format() == QImage::Format_RGB32)
		{
			swapped = swapped.convertToFormat(QImage::Format_RGB888);
		}

		swapped = swapped.rgbSwapped();

		return cv::Mat(swapped.height(), swapped.width(),
			CV_8UC3,
			const_cast<uchar*>(swapped.bits()),
			static_cast<size_t>(swapped.bytesPerLine())
		).clone();
	}

	// 8-bit, 1 channel
	case QImage::Format_Indexed8:
	{
		cv::Mat  mat(inImage.height(), inImage.width(),
			CV_8UC1,
			const_cast<uchar*>(inImage.bits()),
			static_cast<size_t>(inImage.bytesPerLine())
		);

		return (inCloneImageData ? mat.clone() : mat);
	}

	default:
		std::cout << "OpenCVtoQt::QImageToCvMat() - QImage format not handled in switch:" << inImage.format() << std::endl;
		break;
	}

	return cv::Mat();
}

cv::Mat OpenCVtoQt::QPixmapToCvMat(const QPixmap &inPixmap, bool inCloneImageData)
{
	return QImageToCvMat(inPixmap.toImage(), inCloneImageData);
}


OpenCVtoQt::~OpenCVtoQt() { };





