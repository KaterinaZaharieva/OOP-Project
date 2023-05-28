#pragma once
#include "Image.h"
#include <vector> 
/*! class for Portable BitMap image
*colours - 0–1 (white & black)
*/
class PBMImage : public Image
{
protected:
	std::vector <std::vector<int>> pixels;
public:
	/*! default constructor*/
	PBMImage();
	/*! constructor with parameters*/
	PBMImage(const std::string name, const std::string magicNumber, const int row, const int col,const int MaxValue,const std::vector <std::vector<int>> pixels);
	std::vector<std::vector<int>> getPixels() const;

	void clear() override;
	void readFile(std::ifstream&, std::string)  override;
	void printPixels() override;
	void saveAs(std::string fileName) override;


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

