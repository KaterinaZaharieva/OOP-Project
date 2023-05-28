#include "PGMImage.h"
#include <iostream>

PGMImage::PGMImage()
	:Image("","P2",0,0,0)
{
	this->pixels = std::vector<std::vector<int>>(0, std::vector<int>(0));
}

PGMImage::PGMImage(const std::string name, const std::string magicNumber, const int row, const int col, const int maxValue, const std::vector<std::vector<int>> pixels)
	:Image(name, magicNumber, row, col, maxValue)
{
	this->pixels = std::vector<std::vector<int>>(row, std::vector<int>(col));
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			this->pixels[i][j] = pixels[i][j];
		}
	}
}

void PGMImage::clear()
{
	this->magicNumber = "";
	this->row = 0;
	this->col = 0;
	this->maxValue = 1;
	this->pixels.clear();
}

void PGMImage::readFile(std::ifstream& fileOpener, std::string fileName)
{
	this->fileName = fileName;
	fileOpener >> this->magicNumber;
	fileOpener >> this->row >> this->col;
	fileOpener >> this->maxValue;
	int temp = 0;
	for (int i = 0; i < row; i++)
	{
		pixels.push_back(std::vector<int>(col));
		for (int j = 0; j < col; j++)
		{
			fileOpener >> temp;
			pixels[i][j] = temp;
		}
	}
}

void PGMImage::printPixels()
{
	for (int i = 0; i < pixels.size(); i++)
	{
		for (int j = 0; j < pixels[i].size(); j++)
		{
			std::cout << pixels[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void PGMImage::saveAs(std::string fileName)
{
	std::ofstream file(fileName);
	if (file.is_open()) {

		file << this->magicNumber << std::endl;
		file << this->row << std::endl;
		file << this->col << std::endl;
		file << this->maxValue << std::endl;
		for (int i = 0; i < pixels.size(); i++)
		{
			for (int j = 0; j < pixels[i].size(); j++)
			{
				file << pixels[i][j] << "  ";
			}
			file << std::endl;
		}
		file.close();
	}
}

void PGMImage::grayscale()
{
	std::cout << "Could not convert P2 to grayscale." << std::endl;
}

void PGMImage::monochrome()
{
	for (int i = 0; i < this->pixels.size(); i++)
	{
		for (int j = 0; j < pixels[i].size(); j++)
		{
			if (pixels[i][j] > this->maxValue / 2)
			{
				pixels[i][j] = this->maxValue;
			}
			else
			{
				pixels[i][j] = 0;
			}
		}
	}
}

void PGMImage::negative()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int grayShade = 1 - pixels[i][j];
			pixels[i][j] = grayShade;
		}
	}
}

void PGMImage::rotate(int direction)
{
	std::vector<std::vector<int>> transpose(col, std::vector<int>(row));
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
		pixels.push_back(std::vector<int>(transpose[i].size()));
		for (int j = 0; j < transpose[i].size(); j++)
		{
			pixels[i][j] = transpose[i][j];
		}
	}
	int tempCol = col;
	col = row;
	row = tempCol;

}

Image* PGMImage::collage(int direction, std::string image2Name, std::string outImageName)
{
	std::ifstream fileInput(image2Name);
	PGMImage image2;
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
		std::vector<std::vector<int>> collage(this->row, std::vector<int>(this->col + image2.col));
		collage = horizontal(image2.pixels, image2.getCol());

		Image* result = new PGMImage(outImageName, this->magicNumber, this->row, this->col + image2.col, newMax, collage);
		result->saveAs(outImageName);
		return result;
	}
	// vertical
	else if (direction == 1)
	{
		std::vector<std::vector<int>> collage(this->row + image2.row, std::vector<int>(this->col));
		collage = vertical(image2.pixels, image2.getRow());

		Image* result = new PGMImage(outImageName, this->magicNumber, this->row + image2.row, this->col, newMax, collage);
		result->saveAs(outImageName);
		return result;
	}
}

std::vector<std::vector<int>> PGMImage::rotateLeft(std::vector<std::vector<int>> transpose)
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

std::vector<std::vector<int>> PGMImage::rotateRight(std::vector<std::vector<int>> transpose)
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

std::vector<std::vector<int>> PGMImage::horizontal(std::vector<std::vector<int>> image2Pixels, int image2Col)
{
	std::vector<std::vector<int>> collage(this->row, std::vector<int>(this->col + image2Col));
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

std::vector<std::vector<int>> PGMImage::vertical(std::vector<std::vector<int>> image2Pixels, int image2Row)
{
	std::vector<std::vector<int>> collage(this->row + image2Row, std::vector<int>(this->col));
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
