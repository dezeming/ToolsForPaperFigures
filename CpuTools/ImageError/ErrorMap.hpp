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

#ifndef __ErrorMap_hpp__
#define __ErrorMap_hpp__

#include <opencv2/opencv.hpp>

namespace cputools {

	struct errorMapConfig {
		errorMapConfig(float minVal = 0.0f, float maxVal = 1.0f, float power = 1.0f, bool useMask = false, int maskChannel = 0) :
			minVal(minVal),
			maxVal(maxVal),
			power(power),
			useMask(useMask),
			maskChannel(maskChannel)
		{

		}

		float minVal, maxVal;
		float power;
		int maskChannel;
		bool useMask;
	};

	/** make ErrorMap
	* intputImage1 and intputImage2 must be CV_8U or CV_32F
	* maskImage is not necessary
	*/
	bool makeErrorMap(
		const cv::Mat& intputImage1,
		const cv::Mat& intputImage2,
		const cv::Mat& maskImage,
		cv::Mat& errorMap,
		const errorMapConfig& errorconfig);

	bool makeErrorMap(
		const std::string inputFileName1,
		const std::string inputFileName2,
		const std::string maskFileName,
		const std::string errorMapName,
		const errorMapConfig& errorconfig);


	bool makeErrorMapForFloatMat(
		const std::string inputFileName1,
		const std::string inputFileName2,
		const std::string maskFileName,
		const std::string errorMapName,
		const errorMapConfig& errorconfig);


}





#endif





