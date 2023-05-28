#pragma once
#include "Image.h"
#include <vector>
/*! class for Portable PixMap 
* colours - 16777216 (0–255 for each RGB channel), some support for 0-65535 per channel
*/
class PPMImage : public Image
{
protected:
	std::vector <std::vector<RGB>> pixels;

public:
	/*! default constructor*/
	PPMImage();
	/*! constructor with parameters*/
	PPMImage(const std::string name, const std::string magicNumber, const int row, const int col, const int MaxValue, const std::vector <std::vector<RGB>> pixels);
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
	std::vector<std::vector<RGB>> rotateLeft(std::vector<std::vector<RGB>> transpose);
	std::vector<std::vector<RGB>> rotateRight(std::vector<std::vector<RGB>> transpose);

	std::vector<std::vector<RGB>> horizontal(std::vector<std::vector<RGB>> image2Pixels, int image2Col);
	std::vector<std::vector<RGB>> vertical(std::vector<std::vector<RGB>> image2Pixels, int image2Row);
};

