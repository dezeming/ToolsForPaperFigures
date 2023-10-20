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

#include "ErrorMap.hpp"
#include "CpuTools/Utility/cvMat.hpp"

#include <cmath>

namespace cputools {

	bool makeErrorMap(
		const cv::Mat& intputImage1, 
		const cv::Mat& intputImage2, 
		const cv::Mat& maskImage, 
		cv::Mat& errorMap,
		const errorMapConfig& errorconfig) {

		if (errorconfig.minVal >= errorconfig.maxVal) {
			Print_CPU_Error("Illegal maximumand minimum setting");
			return false;
		}

		if (
			!isCvMatHasData(intputImage1) || 
			!isCvMatHasData(intputImage2)) {
			Error_EmptyMat();
			return false;
		}

		bool flag = isMatHasSameSize(intputImage1, intputImage2);
		if (!flag) {
			Error_InconsistentImageSizes();
			return false;
		}

		flag = isMatHasSameWH(intputImage1, intputImage2, maskImage);
		if (!flag && errorconfig.useMask) {
			Error_InconsistentImageSizes();
			return false;
		}

		if (!isMatHasSameType(intputImage1, intputImage2)) {
			Error_InconsistentImageTypes();
			return false;
		}

		if (maskImage.channels() <= errorconfig.maskChannel && errorconfig.useMask) {
			Print_CPU_Error("Mask's channel count does not meet the requirement");
			return false;
		}
		if (!isCvMatTypeEquals8U(maskImage) && !isCvMatTypeEquals32F(maskImage) && errorconfig.useMask) {
			Print_CPU_Error("Illegal maskImage type");
			return false;
		}

		bool isUcharMat = false, isFloatMat = false;
		if (isCvMatTypeEquals8U(intputImage1)) {
			isUcharMat = true;
		}
		if (isCvMatTypeEquals32F(intputImage1)) {
			isFloatMat = true;
		}
		if (!isUcharMat && !isFloatMat) {
			Print_CPU_Error("Illegal Mat type");
			return false;
		}

		errorMap = createUcharCvMat(intputImage1.cols, intputImage1.rows, 4);

		cv::Mat colorbar = cv::imread("./PresetFiles/ColorBar2.png", cv::IMREAD_UNCHANGED);
		if (!isCvMatHasData(colorbar)) {
			Print_CPU_Error("ColorBar not loaded correctly");
			return false;
		}

		float invSection = 1.0f / (errorconfig.maxVal - errorconfig.minVal);

		int width = intputImage1.cols, height = intputImage1.rows, channels = intputImage1.channels();
		
		int calChannel = 0;
		if (channels >= 3) calChannel = 3;
		else calChannel = channels;

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				int offset = (i + j * width);
				float errVal = 0.0f;

				float maskVal;
				if (isCvMatTypeEquals8U(maskImage) && errorconfig.useMask) {
					maskVal = ((unsigned char*)(maskImage.data))[offset * maskImage.channels() + errorconfig.maskChannel];
				}
				else if (isCvMatTypeEquals32F(maskImage) && errorconfig.useMask) {
					maskVal = ((float*)(maskImage.data))[offset * maskImage.channels() + errorconfig.maskChannel];
				}
				else {
					if (errorconfig.useMask) {
						Print_CPU_Error("Fatal error, illegal mask type");
						return false;
					}
					maskVal = 1.f;
				}

				if (maskVal > 0.f || !errorconfig.useMask) {

					float dif = 0.0f;

					if (isUcharMat)
						for (int l = 0; l < calChannel; l++)
							dif += pow(
								abs(((unsigned char*)(intputImage1.data))[offset * channels + l]
								- ((unsigned char*)(intputImage2.data))[offset * channels + l])
								, errorconfig.power);
					else if (isFloatMat) {
						for (int l = 0; l < calChannel; l++)
							dif += pow(
								abs(((float*)(intputImage1.data))[offset * channels + l]
								- ((float*)(intputImage2.data))[offset * channels + l])
								, errorconfig.power);
					}
					else {
						Print_CPU_Error("Fatal error, illegal image type");
						return false;
					}

					if (dif < errorconfig.minVal) dif = errorconfig.minVal;
					if (dif > errorconfig.maxVal) dif = errorconfig.maxVal;
					float rate = (dif - errorconfig.minVal) * invSection;
					int offset2 = colorbar.cols * rate;
					if (offset2 >= colorbar.cols) offset2 = (colorbar.cols - 1);

					for (int l = 0; l < 3; l++)
						((unsigned char*)errorMap.data)[offset * 4 + l]
							= ((unsigned char*)colorbar.data)[(offset2 * colorbar.channels() + l)];
					((unsigned char*)errorMap.data)[offset * 4 + 3] = 255;

				}
				else {
					int offset2 = 0;
					for (int l = 0; l < 3; l++)
						((unsigned char*)errorMap.data)[offset * 4 + l]
							= ((unsigned char*)colorbar.data)[(offset2 * colorbar.channels() + l)];
					((unsigned char*)errorMap.data)[offset * 4 + 3] = 255;
				}
			}
		}

		return true;
	}


	bool makeErrorMap(
		const std::string inputFileName1,
		const std::string inputFileName2,
		const std::string maskFileName,
		const std::string errorMapName,
		const errorMapConfig& errorconfig) {

		cv::Mat srcImage1 = cv::imread(inputFileName1, cv::IMREAD_UNCHANGED);
		cv::Mat srcImage2 = cv::imread(inputFileName2, cv::IMREAD_UNCHANGED);
		cv::Mat mask;
		
		if (errorconfig.useMask)
			mask = cv::imread(maskFileName, cv::IMREAD_UNCHANGED);

		cv::Mat errorMap; 

		bool flag = makeErrorMap(
			srcImage1,
			srcImage2,
			mask,
			errorMap,
			errorconfig);
		if (flag) {
			flag = cv::imwrite(errorMapName, errorMap);
			if (!flag)
				Error_ImageWriteError();
		}
			
		return flag;
	}

	bool makeErrorMapForFloatMat(
		const std::string inputFileName1,
		const std::string inputFileName2,
		const std::string maskFileName,
		const std::string errorMapName,
		const errorMapConfig& errorconfig) {

		cv::Mat srcImage1 = cv::imread(inputFileName1, cv::IMREAD_UNCHANGED), srcImage1_float;
		cv::Mat srcImage2 = cv::imread(inputFileName2, cv::IMREAD_UNCHANGED), srcImage2_float;
		cv::Mat mask;

		if (errorconfig.useMask)
			mask = cv::imread(maskFileName, cv::IMREAD_UNCHANGED);

		bool flag_convert = UcharCvMat2FloatCvMat(srcImage1, srcImage1_float);
		flag_convert = flag_convert && UcharCvMat2FloatCvMat(srcImage2, srcImage2_float);
		if (!flag_convert) {
			Error_ImageConvertError();
			return false;
		}

		cv::Mat errorMap;

		bool flag = makeErrorMap(
			srcImage1_float,
			srcImage2_float,
			mask,
			errorMap,
			errorconfig);
		if (flag) {
			flag = cv::imwrite(errorMapName, errorMap);
			if (!flag)
				Error_ImageWriteError();
		}

		return flag;
	}



}











