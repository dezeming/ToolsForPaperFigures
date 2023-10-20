cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

project(PaperDrawingTools)

set(CMAKE_BUILD_TYPE  "Release")

########################################################################
###################### Build ThirdParty Library ########################
########################################################################

set(QT_PATH "D:/DevTools/Qt/5.15.2/msvc2019_64" CACHE PATH "qt5 cmake dir")
set(CMAKE_PREFIX_PATH ${QT_PATH})
find_package(Qt5 COMPONENTS 
	Widgets 
	Gui 
	Core
REQUIRED)

#set(CMAKE_CXX_FLAGS "-mwindows")

# ------------------------------------------------------------------
# build OpenCV
# ------------------------------------------------------------------

set(OpenCV_DIR "D:/DevTools/OpenCV/opencv-4.8.0-VS2019-cuda12.1-Install/")
set(OpenCV_Libs_Release 
	${OpenCV_DIR}lib-Release/opencv_core480.lib
	${OpenCV_DIR}lib-Release/opencv_imgcodecs480.lib
	${OpenCV_DIR}lib-Release/opencv_imgproc480.lib
	
)
set(OpenCV_Bins_Release 
	${OpenCV_DIR}bin-Release/opencv_core480.dll
	${OpenCV_DIR}bin-Release/opencv_imgcodecs480.dll
	${OpenCV_DIR}bin-Release/opencv_imgproc480.dll
)

# ------------------------------------------------------------------
# build OpenMP
# ------------------------------------------------------------------

find_package(OpenMP REQUIRED)
if(OpenMP_FOUND)
	message(STATUS "found openmp") 
	set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS}, ${OPENMP_C_FLAGS})
   	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}, ${OPENMP_CXX_FLAGS})
else()
   	message(STATUS "openmp not found!")
endif()

# ------------------------------------------------------------------
# build openexr
# ------------------------------------------------------------------

set(openexr_dir "D:/DevTools/OpenEXR/")

set (OPENEXR_INCLUDE
  ${openexr_dir}/openexr/IlmBase/Imath
  ${openexr_dir}/openexr/IlmBase/Half
  ${openexr_dir}/openexr/IlmBase/Iex
  ${openexr_dir}/openexr/OpenEXR/IlmImf
  ${openexr_dir}/openexr/IlmBase/config
  ${openexr_dir}/openexr/OpenEXR/config
)

set (OPENEXR_LIBS 
	${openexr_dir}/VS2019-Install/lib-Release/Iex-2_5.lib
	${openexr_dir}/VS2019-Install/lib-Release/Half-2_5.lib
	${openexr_dir}/VS2019-Install/lib-Release/IexMath-2_5.lib
	${openexr_dir}/VS2019-Install/lib-Release/IlmThread-2_5.lib
	${openexr_dir}/VS2019-Install/lib-Release/IlmImf-2_5.lib
	${openexr_dir}/VS2019-Install/lib-Release/IlmImfUtil-2_5.lib
	${openexr_dir}/VS2019-Install/lib-Release/Imath-2_5.lib
	)

# ------------------------------------------------------------------
# build CUDA
# ------------------------------------------------------------------

find_package(CUDA REQUIRED)

set(CUDA_NVCC_FLAGS "-g -G")
# build option
set(GENCODE -gencode=arch=compute_35,code=sm_35)
set(GENCODE ${GENCODE} -gencode=arch=compute_30,code=sm_30)
set(GENCODE ${GENCODE} -gencode=arch=compute_20,code=sm_20)
set(GENCODE ${GENCODE} -gencode=arch=compute_10,code=sm_10)


########################################################################
######################### Feimos program setup ##########################
########################################################################

INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/GUI/
	${CMAKE_CURRENT_SOURCE_DIR}/CUDA/
	${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/
	${QT_INCLUDE_DIR}
	${OpenCV_DIR}/include/
	${CUDA_INCLUDE_DIRS}
)

# program output dir
set(publish_debug ${CMAKE_CURRENT_BINARY_DIR}/Debug) 
set(publish_release ${CMAKE_CURRENT_BINARY_DIR}/Release)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${publish_release})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${publish_debug})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${publish_release})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${publish_debug})

########################################################################
###################### Feimos CPU Applications #########################
########################################################################

set(CMAKE_BUILD_TYPE "Release")

# Common files
set(cpu_Common
	CpuTools/Common/cpu_Common.hpp
	CpuTools/Common/cpu_Common.cpp
)
# Make the Common_CUDA group
SOURCE_GROUP("Common" FILES ${cpu_Common})

# FileSystem files
set(FileSystem
)
# Make the FileSystem group
SOURCE_GROUP("FileSystem" FILES ${FileSystem})

# ImageEdit files
set(ImageEdit
	CpuTools/ImageEdit/ImageClip.hpp
	CpuTools/ImageEdit/ImageClip.cpp
	CpuTools/ImageEdit/ImageCircleAreas.hpp
	CpuTools/ImageEdit/ImageCircleAreas.cpp
	CpuTools/ImageEdit/ImageBorder.hpp
	CpuTools/ImageEdit/ImageBorder.cpp
)
# Make the ImageEdit group
SOURCE_GROUP("ImageEdit" FILES ${ImageEdit})

# ImageError files
set(ImageError
	CpuTools/ImageError/ErrorMap.hpp
	CpuTools/ImageError/ErrorMap.cpp
	CpuTools/ImageError/PSNR.hpp
	CpuTools/ImageError/PSNR.cpp
)
# Make the ImageError group
SOURCE_GROUP("ImageError" FILES ${ImageError})

# ImageMerge files
set(ImageMerge
)
# Make the ImageMerge group
SOURCE_GROUP("ImageMerge" FILES ${ImageMerge})

# Utility files
set(Utility
	CpuTools/Utility/timerRandom.hpp
	CpuTools/Utility/timerRandom.cpp
	CpuTools/Utility/cvMat.hpp
	CpuTools/Utility/cvMat.cpp
)
# Make the Utility group
SOURCE_GROUP("Utility" FILES ${Utility})

# Generate .lib for .dll files
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(CpuTools SHARED 
	${cpu_Common}
	${FileSystem}
	${ImageEdit}
	${ImageError}
	${ImageMerge}
	${Utility}
)

target_link_libraries(CpuTools 
	# OpenEXR Libs
	${OPENEXR_LIBS}
	# OpenCV Lib
	${OpenCV_Libs_Release}
)

########################################################################
###################### Feimos GPU Applications #########################
########################################################################

# Common files
set(cuda_Common
	CudaTools/Common/cuda_common.cuh
	CudaTools/Common/cuda_common.cu
)
# Make the cuda_Common group
SOURCE_GROUP("Common" FILES ${cuda_Common})

cuda_add_library(CudaTools SHARED 
	${cuda_Common}
)

########################################################################
###################### Feimos GUI Applications #########################
########################################################################

# set Qt moc rcc uic
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# utility files
set(utility
	Gui/utility/qdoubleslider.hpp
	Gui/utility/qdoubleslider.cpp
	Gui/utility/Status.hpp
	Gui/utility/Status.cpp
	Gui/Utility/OpencvToQt.hpp
	Gui/Utility/OpencvToQt.cpp
)
# Make the utility group
SOURCE_GROUP("utility" FILES ${utility})

# dataPresent files
set(dataPresent
	Gui/dataPresent/DataTreeWidget.hpp
	Gui/dataPresent/DataTreeWidget.cpp
	Gui/dataPresent/MemoryRecord.cpp
	Gui/dataPresent/DataPresentDockWidget.hpp
	Gui/dataPresent/DataPresentDockWidget.cpp
)
# Make the dataPresent group
SOURCE_GROUP("dataPresent" FILES ${dataPresent})

# mainWidget files
set(mainWidget
	Gui/mainWidget/mainWindow.hpp
	Gui/mainWidget/mainWindow.cpp
	Gui/mainWidget/main.cpp
	Gui/mainWidget/testCode.cpp
	Gui/mainWidget/MainGraphicsView.hpp
	Gui/mainWidget/MainGraphicsView.cpp
	Gui/mainWidget/DisplayWidget.hpp
	Gui/mainWidget/DisplayWidget.cpp
)
# Make the mainWidget group
SOURCE_GROUP("mainWidget" FILES ${mainWidget})


# Create executable
add_executable(PaperDrawingTools
	WIN32
	${utility}
	${mainWidget}
	${dataPresent}
)

target_link_libraries(PaperDrawingTools 
	# Qt Libs
	Qt5::Widgets
	Qt5::Gui
	Qt5::Core
	# Own Lib
	CudaTools
	CpuTools
)

# set as startup item
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT PaperDrawingTools)

# Set to console mode to output content from the console
# https://developercommunity.visualstudio.com/t/cmake-set-subsystem-to-console/46678
set_target_properties(PaperDrawingTools PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE")
set_target_properties(PaperDrawingTools PROPERTIES COMPILE_DEFINITIONS_RELEASE "_CONSOLE")
# set_target_properties(PaperDrawingTools PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
# set_target_properties(PaperDrawingTools PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "_CONSOLE")
#set_target_properties(PaperDrawingTools PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
#set_target_properties(PaperDrawingTools PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")

########################################################################
######################## Copy Important Files ##########################
########################################################################
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

# Copy dll files
FILE(GLOB OpencvDll_R ${OpenCV_Bins_Release})
file(COPY ${OpencvDll_R} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Release)

# Copy icons 
FILE(GLOB icons ${CMAKE_CURRENT_SOURCE_DIR}/Icons/*.*)
file(COPY ${icons} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/Icons/)

# Copy PresetFiles 
FILE(GLOB icons ${CMAKE_CURRENT_SOURCE_DIR}/PresetFiles/*.*)
file(COPY ${icons} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/PresetFiles/)

#FILE(GLOB ImageProcessCorePreset_png ${CMAKE_CURRENT_SOURCE_DIR}/Source/ImageProcessCore/ImageProcessCorePreset/*.png)
#file(COPY ${ImageProcessCorePreset_png} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/ImageProcessCorePreset/)

#FILE(GLOB ImageProcessCorePreset_hdr ${CMAKE_CURRENT_SOURCE_DIR}/Source/ImageProcessCore/ImageProcessCorePreset/*.hdr)
#file(COPY ${ImageProcessCorePreset_hdr} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/ImageProcessCorePreset/)

#FILE(GLOB ImageProcessCorePreset_bat ${CMAKE_CURRENT_SOURCE_DIR}/Source/ImageProcessCore/ImageProcessCorePreset/*.bat)
#file(COPY ${ImageProcessCorePreset_bat} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/ImageProcessCorePreset/)

#FILE(GLOB ImageProcessCorePreset_exe ${CMAKE_CURRENT_SOURCE_DIR}/Source/ImageProcessCore/ImageProcessCorePreset/*.exe)
#file(COPY ${ImageProcessCorePreset_exe} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/ImageProcessCorePreset/)

#FILE(GLOB ImageProcessCorePreset_txt ${CMAKE_CURRENT_SOURCE_DIR}/Source/ImageProcessCore/ImageProcessCorePreset/*.txt)
#file(COPY ${ImageProcessCorePreset_txt} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/ImageProcessCorePreset/)

#FILE(GLOB ImageProcessCorePreset_jpg ${CMAKE_CURRENT_SOURCE_DIR}/Source/ImageProcessCore/ImageProcessCorePreset/*.jpg)
#file(COPY ${ImageProcessCorePreset_jpg} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/ImageProcessCorePreset/)






