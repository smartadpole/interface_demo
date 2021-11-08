#include "detector.h"
#include <iostream>
#include <unistd.h>
#include "utils/utils.h"

void Help()
{
    ERROR_PRINT("please input: ");
    INFO_PRINT("\tinput image dir: [string]");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        Help();
        return 0;
    }

    std::string inputDir = argv[1];
    Detector *detector = Create();

    std::string imagesTxt = inputDir + "/image.txt";
    std::vector<std::string> imageNameList;
    std::vector<std::string> lidarNameList;

    ReadFile(imagesTxt, imageNameList);

    const size_t size = imageNameList.size();
    for (size_t i = 0; i < size; ++i)
    {
        auto imageName = imageNameList.at(i);

        std::string imagePath(inputDir + "/" + imageName);
        auto image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
        if (image.empty())
        {
            ERROR_PRINT("empty data in file <" + imageName + ">");
            continue;
        }

        std::vector<Box> boxes;

        detector->GetDetectorResult(image, boxes);
    }

    Destroy(detector);
}
