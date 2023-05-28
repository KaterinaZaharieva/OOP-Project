#include "Image.h"
#include <fstream>
#include <iostream>

Image::Image(std::string fileName, std::string magicNumber, int row, int col, int maxValue)
{
	setFileName(fileName);
	setMagicNumber(magicNumber);
	setRow(row);
	setCol(col);
	setMaxValue(maxValue);
}

void Image::setMagicNumber(const std::string magicNumber)
{
	if (magicNumber.compare("P1") || magicNumber.compare("P2") || magicNumber.compare("P3"))
	{
		this->magicNumber = magicNumber;
	}
}

std::string Image::getMagicNumber() const
{
	return this->magicNumber;
}

void Image::setMaxValue(const int maxValue)
{
	if (maxValue >= 0 && maxValue <= 255)
	{
		this->maxValue = maxValue;
	}
}

int Image::getMaxValue() const
{
	return this->maxValue;
}

int Image::getRow() const
{
	return this->row;
}

void Image::setRow(const int row)
{
	this->row = row;
}

int Image::getCol() const 
{
	return this->col;
}

void Image::setCol(const int col)
{
	this->col = col;
}

std::string Image::getFileName() const
{
	return this->fileName;
}

void Image::setFileName(const std::string fileName)
{
	this->fileName = fileName;
}
