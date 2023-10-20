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


#include "CpuTools/Common/cpu_Common.hpp"

#include "CpuTools/ImageEdit/ImageClip.hpp"
#include "CpuTools/ImageEdit/ImageCircleAreas.hpp"
#include "CpuTools/ImageError/ErrorMap.hpp"

void testCode_Dez_1() {

	//COUT_RED("hahahaha") << std::endl;
	//COUT_GREEN("hahahaha") << std::endl;
	//COUT_YELLOW("hahahaha") << std::endl;
	//COUT_BLUE("hahahaha") << std::endl;

	cputools::ClipConfig cc(300, 300,250, 250);
	cputools::ImageClip("./TestImages/Background1.png", "./TestImages/output.png", cc);

	int cent[2] = {400,200};
	unsigned char color[3] = {0,255,0};
	cputools::CircleRoundConfig crc(cent, 290, color, 15);
	cputools::Image_CircleAreas_usingRound("./TestImages/Background1.png", "./TestImages/output2.png", crc);

	int offset[4] = {300,100,100,200};
	cputools::CircleRectConfig crc2(offset, color, 15);
	cputools::Image_CircleAreas_usingRectangle("./TestImages/Background1.png", "./TestImages/output3.png", crc2);
	cputools::Image_CircleWholeImage("./TestImages/Background1.png", "./TestImages/output4.png", crc2);

	cputools::Image_Clip_and_CircleWholeImage("./TestImages/Background1.png", "./TestImages/output5.png", cc, crc2);


	cputools::errorMapConfig emc(0.0f, 1.0f, 1.0f, false, 3);
	cputools::makeErrorMapForFloatMat(
		"./TestImages/Feimos_test_ColorBar_Img1.png",
		"./TestImages/Feimos_test_ColorBar_Img2.png",
		"./TestImages/Feimos_test_ColorBar_mask.png", 
		"./TestImages/Feimos_test_ColorBar_error.png", emc);

}




















