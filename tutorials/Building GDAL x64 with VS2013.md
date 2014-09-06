# How to build GDAL x64 with VS2013

1. Download the latest GDAL source code from http://download.osgeo.org/gdal/. Extract the files into a folder e.g. C:\dev\gdal-1.9.2\.
2. In windows 8 start screen, type Visual studio Tools, which opens C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\Shortcuts and run VS2013 x64 Native Tools Command Prompt.
3. Change path  C:\dev\gdal-1.9.2\
4. Run C:\> nmake /f makefile.vc MSVC_VER=1800 WIN64=YES
