#How to setup OpenCV 2.4.9 for building modules

This is a short tutorial on how to set up OpenCV 2.4.9 with CMAKE on windows for building 64bit modules. We use these settings in the precompiled OpenCV libraries on the Ascend XYZ Algorithm Platform.


1. Download OpenCV from http://opencv.org/downloads.html http://sourceforge.net/projects/opencvlibrary/files/opencv-win/2.4.9/opencv-2.4.9.exe/download 
2. Download CMake from http://www.cmake.org/cmake/resources/software.html (I Use the win32 installer)
3. Run the downloaded exe with OpenCV (its a self contained packaged that just need to a path to extract, it will not do any changes to your system). I have min extracted at c:\dev\opencv-2.4.9
4. Install CMake and run it.
5. in the "Where is the source code" field you enter the path where you extracted opencv: c:\dev\opencv-2.4.9\opencv\sources
6. in the "where to build the binaries" field you enter the path where you extracted opencv + build: c:\dev\opencv-2.4.9\opencv\build
7. Press configure and select Visual Studio 12 2013  (Note here, version 12 of visual studio is 2013), and 64bit.

We use Eigen and TBB and this is the steps to get those into the build.
8. downlaod 3.2.2 from http://eigen.tuxfamily.org/index.php?title=Main_Page of eigen
9. extract it to c:\dev\ and rename the folder to something like eigen-3.2.2
10. download TBB from https://www.threadingbuildingblocks.org/download (version 4.3 for windows) and extract it to something like C:\dev\tbb43_20140724oss


Now we just need to configure the options for building inside cmake.

11. Disable Build Docs
12. Enable Build Examples
13. Disable Build with static crt
14. Disable With Cuda, Cufft, Dsshow GIGE_API
15. Enable With TBB and OpenMP

16. Press Configure again and it will highlight in red the new fields that you need to enter, ect paths to Eigen and TBB.


My paths look like this (Note that this is from older versions of eigen and tbb):

```
Eigen_Include_Path should be C:/dev/eigen-3.2.1
TBB_INCLUDE_DIR: C:/dev/tbb42_20140416oss/include
TBB_LIB_DIR: C:/dev/tbb42_20140416oss/lib/intel64/vc12
TBB_STDDEF_PATH: C:/dev/tbb42_20140416oss/include/tbb/tbb_stddef.h
```


## Modules

You can then select a clean location for your own modules and set the OPENCV_EXTRA_MODULES_PATH to it, like C:/dev/ascendprojects/Ascend Azure Pipeline/OpenCVModules




