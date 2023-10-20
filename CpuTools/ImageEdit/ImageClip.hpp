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

#ifndef __ImageClip_h__
#define __ImageClip_h__

#include <opencv2/opencv.hpp>

namespace cputools {

/** Clip Configuration
* Configuration for clipping
*/
struct ClipConfig {
	ClipConfig(int idx[4], bool clamp = false, bool needoffset = true) {
		needClampped = clamp;
		isOffset = needoffset;
		index[0] = idx[0]; index[1] = idx[1]; index[2] = idx[2]; index[3] = idx[3];
	}

	ClipConfig(int idx0, int idx1, int idx2, int idx3, bool clamp = true, bool needoffset = true) {
		needClampped = clamp;
		isOffset = needoffset;
		index[0] = idx0; index[1] = idx1; index[2] = idx2; index[3] = idx3;
	}

	/* index[4] are the clip coordinates
	* index[0]: The starting point¡¯s horizontal coordinate for clipping
	* index[1]: The starting point¡¯s vertical coordinate for clipping
	* index[2] and index[3]: depend on the flag 'isOffset'
	*/
	int index[4];
	/* needClampped is a bool flag
	* true: when the coordinates exceed the range, clamp them to the boundary
	* false: when the coordinates exceed the range, stop the clipping and raise an error.
	*/
	bool needClampped;
	/* isOffset is a bool flag
	* true: clipping range: horizontal coordinates [index[0],index[0]+index[2]]; vertical coordinates [index[1],index[1]+index[3]]
	* false: clipping range: horizontal coordinates [index[0],index[2]]; vertical coordinates [index[1],index[3]]
	*/
	bool isOffset;
};


bool ImageClip(
	const cv::Mat& inputMat, 
	cv::Mat& outputMat, 
	const ClipConfig& clipCfg);

bool ImageClip(
	const std::string inputFileName, 
	const std::string outputFileName, 
	const ClipConfig& clipCfg);



}



#endif







