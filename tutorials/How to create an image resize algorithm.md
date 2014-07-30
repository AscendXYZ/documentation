
#How to create an image resize algorithm on Ascend Algorithm Platform using OpenCV.

Disclaimer: Work in progress.

## Entry Points
On ascend algorithm platform there are two entry points, where you have the option to create a normal console application and an algspec file with metadata about the algorithm. Instead of the console application you can also use c++/cli directly to create a mixing of managed code and native code and make it run on the Ascend Algorithm Platform. In this tutorial we will focus on the later. The target audience for this tutorial is users who are familiar using the cmake build system in opencv.

## Creating a OpenCV Module
Our platform is based on .Net and running on Microsoft Azure, the IaaS solution provided by Microsoft and you will be compiling your OpenCV to a managed dll that our platform can run.

First thing you want is to create a folder called `opencv_modules`, or a name of your choice, and inside this we will be creating our algorithms. Then we can tell the build system of OpenCV to build modules in this folder using the cmake property `OPENCV_EXTRA_MODULES_PATH' and point it to the created folder. To setup a OpenCV developer environment and introduction to CMAKE, you should read: LINK COMING


### CMakeLists.txt
Now create a Folder inside `opencv_modules` called `ascend_resizer`. Now you can create the CMakeLists.txt within this folder with the following content.

```
set(the_description "Ascend OpenCV Image Resizer")

ocv_define_module(ascend_resizer opencv_imgproc opencv_highgui)


set_target_properties(${PROJECT_NAME} PROPERTIES VS_DOTNET_REFERENCES "System;System.Core")
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/clr /EHa")
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /AI\"____PATH__TO__ASCEND.ALGORITHMS.INTERFACES.DLL____\" ")

if(CMAKE_CXX_FLAGS_DEBUG MATCHES "/RTC1")
   string(REPLACE "/RTC1" " " CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
endif()

if(CMAKE_CXX_FLAGS MATCHES "/EHsc")
   string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()


```
where the `____PATH__TO__ASCEND.ALGORITHMS.INTERFACES.DLL____` should be set to the path you downloaded the Ascend XYZ Algorithm Interfaces.


### OpenCV Module Code
You need to create the following two folders, `include/opencv2/ascend_resizer/` and `src/` and place the .hpp file in the first, and the .cpp file in the later.

`/src/resizer.cpp`
```

#include <opencv2/ascend_resizer/ascend_resizer.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace Ascend::Data;

ResizerAlgorithmOutput^ ResizerAlgorithm::ResizeImage()
{
	auto input = this->context->Payload;
	
	std::string imagePath = msclr::interop::marshal_as< std::string >(input->InputFile);
	std::string outName = msclr::interop::marshal_as< std::string >("resized" + Path::GetExtension(input->InputFile));
	
	cv::Mat src = cv::imread(imagePath);
	cv::Mat dst;


	double scale = input->Scale;                          //Default use the scale property
	if (input->Height != 0)                               // If a height is used, calculate scale based on this 
		scale = (double)input->Height / (double)src.rows;  
	if (input->Width != 0)                                // If a width is used, calculate scale based on this
		scale = (double)input->Width / (double)src.cols;

	//Resize the image using the interpolation given.
	cv::resize(src, dst, cv::Size(), scale, scale, input->Ínterpolation);
	cv::imwrite(outName, dst);


	auto result = gcnew ResizerAlgorithmOutput();
	result->Height = dst.rows;
	result->Width = dst.cols;
	result->Scale = scale;
	
	return result;
}

```

In the above script you will notice the opencv code, thats where you can do what you want in your algorithms, and a few lines of code dealing with input and output. To be able to import a algorithm like the one above, you need to implement a interface from the Ascend.Algorithm.Interfaces and we have found it easiest to copy paste the below code and modify the input and out parameters as needed.

`include/opencv2/ascend_resizer/ascend_resizer.hpp`
```


#ifndef __OPENCV_ASCEND_RESIZER_HPP__
#define __OPENCV_ASCEND_RESIZER_HPP__

#include "opencv2/core/core.hpp"

#using <Ascend.Algorithms.Interface.dll>
#include <msclr\marshal_cppstd.h>
//..
using namespace msclr::interop;

#ifdef __cplusplus


using namespace System::IO;
using namespace System;
using namespace System::Collections::Generic;
using namespace Ascend::Algorithms::Interface;
using namespace System::Threading::Tasks;

namespace Ascend
{
	namespace Data
	{

		    /// Algorithm Input
			public ref class ResizerAlgorithmInput
			{
			public:
				/// Properties that the Algorithm Caller will be providing as Payload
				property int Width;
				property int Height;
				property double Scale;
				property int Ínterpolation;

				/// The Image Path to where the image should be loaded. 
				/// The algorithm platform will parse incoming payloads and 
				/// place the image in the working folder and set this property.
				property System::String^ InputFile;
			};

			/// Algorithm Output, the new hight, width and the scale factor used.
			public ref class ResizerAlgorithmOutput
			{
			public :
				property int Width;
				property int Height;
				property double Scale;

			};
			

			public ref class ResizerAlgorithm : public IManagedAlgorithmHost < ResizerAlgorithmInput^, ResizerAlgorithmOutput^ >
			{
			private:
				IManagedAlgorithmContext<ResizerAlgorithmInput^>^ context;
			public:

				ResizerAlgorithmOutput^ ResizeImage();
				

				virtual Task<ResizerAlgorithmOutput^>^ RunAlgorithmAsync()
				{
					return Task::Factory->StartNew(gcnew Func<ResizerAlgorithmOutput^>(this, &ResizerAlgorithm::ResizeImage));
				}
				virtual void SetAlgorithmContext(IManagedAlgorithmContext<ResizerAlgorithmInput^>^ context)
				{
					this->context = context;
				}
			};

		
	}
}



#endif

#endif

```

For the novice C# programmer the above code makes sure to wrap the native code in managed Task object that can be executed on the platform. 

## Building and Packaging

Visual Studio is needed to compile these kind of algorithms and the solution files was generated using CMAKE. On a more general note, all algorithms should be compiled to target x64 to be able to run in the platform.

And if visual studio is not an option, we recommend looking into some of the other ways we let you create algorithms for the Ascend XYZ Algorithm Platform. _INSERT LINKS_

The code for this algorithm is available in the /opencv_modules folder inside this repository.
