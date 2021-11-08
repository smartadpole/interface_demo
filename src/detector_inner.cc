#include "src/detector_inner.h"
#include <opencv2/highgui.hpp>
#include "utils/timer.h"

DetectorInner::DetectorInner()
{
}


DetectorInner::~DetectorInner()
{
}

bool DetectorInner::Init()
{
    return true;
}

bool DetectorInner::GetDetectorResult(const cv::Mat &image, std::vector<Box> &boxes)
{
    std::cout << "detect run." << std::endl;
    return true;
}

void Display(const std::string name, const std::vector<Box> &boxes
             , const cv::Mat &image)
{

}