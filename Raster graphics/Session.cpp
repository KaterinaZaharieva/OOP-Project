#include "Session.h"
#include "Image.h"
#include "PPMImage.h"
#include "PGMImage.h"
#include "PBMImage.h"
#include <fstream>
#include <iostream>

Session::Session(int sessionID)
{
    this->sessionID = sessionID;
}

int Session::getSessionID()
{
    return this->sessionID;
}

Session::~Session()
{
    for (int i = 0; i < images.size(); i++)
    {
        delete images[i];
    }
    images.clear();
}

void Session::addLog(std::string message)
{
    this->log.push_back(message);
}

void Session::add(std::string image)
{
    if (image.find(".ppm") != -1)
    {
        PPMImage* toAdd = new PPMImage();
        std::ifstream fileInput(image);
        if (fileInput.is_open())
        {
            std::cout << "Image \"" << image << "\" added" << std::endl;
            toAdd->readFile(fileInput, image);
            fileInput.close();
            images.push_back(toAdd);
        }
        else
        {
            std::cout << "File doesn't exist and can't be opened." << std::endl;
            return;
        }
    }
    else if (image.find(".pbm") != -1)
    {
        PBMImage* toAdd = new PBMImage();
        std::ifstream fileInput(image);
        if (fileInput.is_open())
        {
            std::cout << "Image \"" << image << "\" added" << std::endl;
            toAdd->readFile(fileInput, image);
            fileInput.close();
            images.push_back(toAdd);
        }
        else
        {
            std::cout << "File doesn't exist and can't be opened." << std::endl;
            return;
        }
    }
    else if (image.find(".pgm") != -1)
    {
        PGMImage* toAdd = new PGMImage();
        std::ifstream fileInput(image);
        if (fileInput.is_open())
        {
            std::cout << "Image \"" << image << "\" added" << std::endl;
            toAdd->readFile(fileInput, image);
            fileInput.close();
            images.push_back(toAdd);
        }
        else
        {
            std::cout << "File doesn't exist and can't be opened." << std::endl;
            return;
        }
    }
    else
    {
        std::cout << "File isn't the correct format: PPM, PGM, PBM and can't be open." << std::endl;
        return;
    }
}