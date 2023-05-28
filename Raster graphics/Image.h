#pragma once
#include<string>
#include <vector>
#include <fstream>
#include "RGB.h"
/*! base class for image*/
class Image
{
protected:

	std::string fileName;
	std::string magicNumber;
	int row;
	int col;
	int maxValue;
public:
	/*! constructor with parameters*/
	Image(const std::string fileName, const std::string magicNumber, const int row, const int col, const int maxValue);

	/*! setter for the special number on the photo that tells what type it is
	*@param the special number on the photo that tells what type it is
	*/
	void setMagicNumber(const std::string magicNumber);
	/*! getter for the special number on the photo that tells what type it is
	*@return the special number on the photo that tells what type it is
	*/
	std::string getMagicNumber() const;
	/*! setter for the largest pixel value in the photo
	* @param the largest pixel value in the photo
	*/
	void setMaxValue(const int maxValue);
	/*! getter for the largest pixel value in the photo
	* @return the largest pixel value in the photo
	*/
	int getMaxValue() const;
	/*! getter for the number of pixel rows
	* @return the number of pixel rows
	*/
	int getRow()const ;
	/*! setter for the number of pixel rows
	* @param the number of pixel rows
	*/
	void setRow(const int row);
	/*! getter for the number of pixel columns
	* @return the number of pixel columns
	*/
	int getCol() const;
	/*! setter for the number of pixel columns
	* @param the number of pixel columns
	*/
	void setCol(const int col);
	/*! getter for the name of the file 
	* @return the name of the file
	*/
	std::string getFileName() const;
	/*! setter for the name of the file
	* @param the name of the file
	*/
	void setFileName(const std::string fileName);

	virtual void clear() = 0;

	/*! reads a file for a image
	* @param stream and name of the file 
	*/
	virtual void readFile(std::ifstream&, std::string) = 0;
	/*! prints the pixels for the image
	*/
	virtual void printPixels() = 0;
	/*! saves image in file
	* @param file name
	*/
	virtual void saveAs(std::string) = 0;

	/*! Convert all color images in the current session to those using shades of gray.
If black and white images are included in the current session, they should not be modified.*/
	virtual void grayscale() = 0;
	/*! Convert all color images in the current session to ones that have only black and white pixels,
without any shades of gray. If the image is already monochrome, this transformation does not change it.*/
	virtual void monochrome() = 0;
	/*! A the negative transformation(color inversion) of the images in the current session.*/
	virtual void negative() = 0;
	/*! This command applies a 90 degree rotation in the appropriate direction.0 - left 1 - right
	* @param rotating direction
	*/
	virtual void rotate(int direction) = 0;
	/*! Creates a collage of two images (in the same format and the same dimension) available in the current session.
	*The result is saved in a new image, which is added to the current session. horizontal - 0  vertical - 1
	* @param horizontal or vertical direction in which we want the collage, name of second image for the collage 
	and filename where we will save the collagee 
	*/
	virtual Image* collage(int direction,std::string image2Name, std::string outImageName) = 0;
};
