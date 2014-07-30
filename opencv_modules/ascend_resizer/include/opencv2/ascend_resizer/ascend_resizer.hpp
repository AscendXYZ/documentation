

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

			/// Algorithm Output, the new hight, widht and the scale factor used.
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
