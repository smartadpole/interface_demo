#ifndef FILEOPERATOR_H
#define FILEOPERATOR_H
#include <opencv2/highgui.hpp>

namespace file_op
{
enum FileType{IMAGE=1, VIDEO};
const std::string IMAGE_SUFFIX = "png bmp tiff tif jpg jpeg";
const std::string VIDEO_SUFFIX = "mp4 avi wav wma ts flv mkv wmv asf f4v m1v m4v mov mpeg mpg rm vob";
enum FileStatus {NOT_EXIST, FILE, DIR};

using StringList = std::vector<std::string>;
using IntList = std::vector<int>;

class File
{
public:
    File();
    ~File();

public:
    /**
    * @brief load files in dir recurrsive
    * @param flag    IAMGE，VIDEO
    *
    * @return fileNums file number for every dir
    * @author   sunhao
    */
    static bool Walk(const std::string &filePath
                   , const FileType flag
                   , IntList& fileNums, StringList &fileName);
    static bool WalkImage(const std::string &filePath, IntList& fileNums, StringList &fileName);
    static bool WalkVideo(const std::string &filePath, IntList& fileNums, StringList &fileName);

    static bool Exist(const std::string file);
    static bool MkdirFromFile(const std::string file) ;
    static bool Remove(const std::string& file);
    static bool RemoveDir(const std::string& path);
    static bool Write(std::ofstream& stream, const cv::Mat& img);
    static bool Read(std::ifstream& stream, cv::Mat& img);
    static int CreatDir(const std::string path);

private:
    static FileStatus CheckType(const std::string file);

private:
    std::string file;
};
} // namespace file_op
#endif // FILEOPERATOR_H
