#include "PPMImage.h"
#include <iostream>

PPMImage::PPMImage()
	:Image("","P3",0,0,0)
{
	this->pixels = std::vector<std::vector<RGB>>(0, std::vector<RGB>(0));
}

PPMImage::PPMImage(const std::string name, const std::string magicNumber, const int row, const int col, const int maxValue, const std::vector<std::vector<RGB>> pixels)
	:Image(name, magicNumber, row, col, maxValue)
{
	this->pixels = std::vector<std::vector<RGB>>(row, std::vector<RGB>(col));
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{ 
			this->pixels[i][j].red = pixels[i][j].red;
			this->pixels[i][j].green = pixels[i][j].green;
			this->pixels[i][j].blue = pixels[i][j].blue;
		}
	}
}

void PPMImage::clear()
{
	this->magicNumber = "";
	this->row = 0;
	this->col = 0;
	this->maxValue = 1;
	this->pixels.clear();
}
void PPMImage::readFile(std::ifstream& file, std::string fileName)
{
	this->fileName = fileName;
	file >> this->magicNumber;
	file >> this->row >> this->col;
	file >> this->maxValue;
	RGB pixel;
	for (int i = 0; i < row; i++)
	{
		pixels.push_back(std::vector<RGB>(col));
		for (int j = 0; j < col; j++)
		{
			file >> pixel.red;
			file >> pixel.green;
			file >> pixel.blue;
			this->pixels[i][j] = pixel;
		}
	}
}


void PPMImage::printPixels()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			std::cout << pixels[i][j].red << " " << pixels[i][j].green << " " << pixels[i][j].blue << "  ";
		}
		std::cout << std::endl;
	}
}

void PPMImage::saveAs(std::string fileName)
{
	std::ofstream file(fileName);
	if (file.is_open()) {

		file << this->magicNumber << std::endl;
		file << this->row << std::endl;
		file << this->col << std::endl;
		file << this->maxValue << std::endl;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				file << pixels[i][j].red << " " << pixels[i][j].green << " " << pixels[i][j].blue << std::endl;
			}
		}
		file.close();
	}
}

void PPMImage::grayscale()
{
	for (int i = 0; i < this->pixels.size(); i++)
	{
		for (int j = 0; j < this->pixels[i].size(); j++)
		{
			int grayShade = (pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue) / 3;
			pixels[i][j].red = grayShade;
			pixels[i][j].green = grayShade;
			pixels[i][j].blue = grayShade;
		}
	}
}

void PPMImage::monochrome()
{
	for (int i = 0; i < this->pixels.size(); i++)
	{
		for (int j = 0; j < this->pixels[i].size(); j++)
		{
			int grayShade = (pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue) / 3;
			if (grayShade > this->maxValue / 2)
			{
				grayShade = this->maxValue;
			}
			else
			{
				grayShade = 0;
			}
			pixels[i][j].red = grayShade;
			pixels[i][j].green = grayShade;
			pixels[i][j].blue = grayShade;
		}
	}
}

void PPMImage::negative()
{
	for (int i = 0; i < this->pixels.size(); i++)
	{
		for (int j = 0; j < this->pixels[i].size(); j++)
		{
			int grayShade = this->maxValue - ((pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue) / 3);
			pixels[i][j].red = grayShade;
			pixels[i][j].green = grayShade;
			pixels[i][j].blue = grayShade;
		}
	}
}

void PPMImage::rotate(int direction)
{
	std::vector<std::vector<RGB>> transpose(col, std::vector<RGB>(row));
	//left
	if (direction == 0) {
		transpose = rotateLeft(transpose);
	}
	//right
	if (direction == 1) {
		transpose = rotateRight(transpose);
	}
	pixels.clear();
	for (int i = 0; i < transpose.size(); i++)
	{
		pixels.push_back(std::vector<RGB>(transpose[i].size()));
		for (int j = 0; j < transpose[i].size(); j++)
		{
			pixels[i][j] = transpose[i][j];
		}
	}
	int tempCol = col;
	col = row;
	row = tempCol;

}

Image* PPMImage::collage(int direction, std::string image2Name, std::string outImageName)
{
	std::ifstream fileInput(image2Name);
	PPMImage image2;
	if (fileInput.is_open())
	{
		image2.readFile(fileInput, image2Name);
		fileInput.close();
	}
	int newMax;
	if (this->getMaxValue() >= image2.getMaxValue())
	{
		newMax = this->getMaxValue();
	}
	else
	{
		newMax = image2.getMaxValue();
	}
	// horizontal
	if (direction == 0)
	{
		std::vector<std::vector<RGB>> collage(this->row, std::vector<RGB>(this->col + image2.col));
		collage = horizontal(image2.pixels, image2.getCol());

		Image* result = new PPMImage(outImageName, this->magicNumber, this->row, this->col + image2.col, newMax, collage);
		result->saveAs(outImageName);
		return result;
	}
	// vertical
	else if (direction == 1)
	{
		std::vector<std::vector<RGB>> collage(this->row + image2.row, std::vector<RGB>(this->col));
		collage = vertical(image2.pixels, image2.getRow());

		Image* result = new PPMImage(outImageName, this->magicNumber, this->row + image2.row, this->col, newMax, collage);
		result->saveAs(outImageName);
		return result;
	}
}

std::vector<std::vector<RGB>> PPMImage::rotateLeft(std::vector<std::vector<RGB>> transpose)
{
	int countI = col - 1, countJ = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			transpose[countI][countJ] = pixels[i][j];
			countI--;
			if (countI == -1)
			{
				countI = col - 1;
			}
		}
		countJ++;
	}
	return transpose;
}

std::vector<std::vector<RGB>> PPMImage::rotateRight(std::vector<std::vector<RGB>> transpose)
{
	int countI = 0, countJ = row - 1;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			transpose[countI][countJ] = pixels[i][j];
			countI++;
			if (countI == col)
			{
				countI = 0;
			}
		}
		countJ--;
	}
	return transpose;
}

std::vector<std::vector<RGB>> PPMImage::horizontal(std::vector<std::vector<RGB>> image2Pixels, int image2Col)
{
	std::vector<std::vector<RGB>> collage(this->row, std::vector<RGB>(this->col + image2Col));
	for (int i = 0; i < this->row; i++)
	{
		for (int j = 0; j < this->col; j++)
		{
			collage[i][j] = this->pixels[i][j];
		}
	}
	for (int i = 0; i < this->row; i++)
	{
		for (int j = 0; j < image2Col; j++)
		{
			collage[i][this->col + j] = image2Pixels[i][j];
		}
	}
	return collage;
}

std::vector<std::vector<RGB>> PPMImage::vertical(std::vector<std::vector<RGB>> image2Pixels, int image2Row)
{
	std::vector<std::vector<RGB>> collage(this->row + image2Row, std::vector<RGB>(this->col));
	for (int i = 0; i < this->row; i++)
	{
		for (int j = 0; j < this->col; j++)
		{
			collage[i][j] = this->pixels[i][j];
		}
	}
	for (int i = 0; i < image2Row; i++)
	{
		for (int j = 0; j < this->col; j++)
		{
			collage[this->row + i][j] = image2Pixels[i][j];
		}
	}
	return collage;
}
