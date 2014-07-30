
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

