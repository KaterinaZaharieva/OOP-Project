#pragma once
#include "Image.h"
#include <vector> 
/*! class for Portable GrayMap 
* colours - 0�255 (gray scale), 0�65535 (gray scale), variable, black-to-white range
*/
class PGMImage : public Image
{
protected:
	std::vector <std::vector<int>> pixels;
public:
	/*! default constructor*/
	PGMImage();
	/*! constructor with parameters*/
	PGMImage(const std::string name, const std::string magicNumber, const int row, const int col, const int MaxValue, const std::vector <std::vector<int>> pixels);
	void clear() override;
	void readFile(std::ifstream&, std::string)  override;
	void printPixels() override;
	void saveAs(std::string) override;


	void grayscale() override;
	void monochrome() override;
	void negative() override;
	void rotate(int direction) override;

	Image* collage(int direction, std::string image2Name, std::string outImageName) override;

private:
	std::vector<std::vector<int>> rotateLeft(std::vector<std::vector<int>> transpose);
	std::vector<std::vector<int>> rotateRight(std::vector<std::vector<int>> transpose);

	std::vector<std::vector<int>> horizontal(std::vector<std::vector<int>> image2Pixels, int image2Col);
	std::vector<std::vector<int>> vertical(std::vector<std::vector<int>> image2Pixels, int image2Row);

};

