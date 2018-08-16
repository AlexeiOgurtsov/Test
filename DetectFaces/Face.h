#ifndef Face_HEADER
#define Face_HEADER

#include<opencv2/opencv.hpp>
#include<filesystem>

class Face
{
private:
	cv::Mat image;
	cv::Rect rectangle;
	std::string name;
	std::vector<cv::Point> coordinates;
	std::vector<cv::Rect> eyes;
	cv::Rect mouth;
	void mirrorEffect();

public:
	Face();
	Face(cv::Mat Image, std::string Name, std::vector<cv::Point> Coordinates, std::vector<cv::Rect> Eyes, cv::Rect Mouth);
	void setImage(cv::Mat Image);
	void setRectangle(cv::Rect Rectangle);
	void setName(std::string Name);
	void generateName(int numberOfFoundFace, std::string fileName);
	void setCoordinates(std::vector<cv::Point> Coordinates);
	void setEyes(std::vector<cv::Rect> Eyes);
	void setMouth(cv::Rect Mouth);
	cv::Mat getImage();
	cv::Rect getRectangle();
	std::string getName();
	std::vector<cv::Point> getCoordinates();
	std::vector<cv::Rect> getEyes();
	cv::Rect getMouth();
	void saveFace(std::filesystem::path fiileNamePath, std::string fileName);
	void makeCoordinates();
	void convertEyesCoordinatesFromRoiToImage(cv::Mat inputImage);
	void convertMouthCoordinatesFromRoiToImage(cv::Mat inputImage);
	std::vector<cv::Point> getEyesCoordinates();
	std::vector<cv::Point> getMouthCoordinates();
	std::vector<cv::Point> getCoordinatesFromRectangle(cv::Rect area);
	std::string makeAFullPathToSaveImage(std::filesystem::path fileNamePath, std::string fileName);
	~Face();
};
#endif

