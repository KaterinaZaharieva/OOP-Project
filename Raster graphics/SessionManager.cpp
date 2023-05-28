#include "SessionManager.h"
#include <iostream>
#include <algorithm>
void SessionManager::menu()
{
	std::string command;
	std::vector<std::string> arguments;
	while (command != "exit")
	{
		std::cout << "> ";
		command.clear();
		std::getline(std::cin, command);
		int counter = 0;
		arguments.clear();
		for (int i = 0; i < command.size() + 1; i++)
		{
			if (command[i] == ' ' || command[i] == '\0')
			{
				arguments.push_back(command.substr(i - counter, counter));
				counter = 0;
			}
			else {
				counter++;
			}
		}
		std::for_each(command.begin(), command.end(), [](char& c)
			{
				c = ::tolower(c);
			});

		if (command.find("load") != -1)
		{
			if (arguments.size() == 1)
			{
				std::cout << "You cannot start a session without entering a photo name" << std::endl;
			}
			else
			{
				currentSessionID = sessions.size() + 1;
				Session session(currentSessionID);
				sessions.push_back(session);
				std::cout << "Session with ID: " << currentSessionID << " started" << std::endl;
				for (int i = 1; i < arguments.size(); i++)
				{
					std::string fileName = arguments[i];
					sessions[currentSessionID - 1].add(fileName);
				}
			}
		}
		else if (command.find("add") != -1)
		{
			std::string fileName = arguments[1];
			if (currentSessionID == 0)
			{
				std::cout << "You cannot add images without loading 1 or more images, there is not started session." << std::endl;
			}
			else
			{
				for (int i = 1; i < arguments.size(); i++)
				{
					sessions[currentSessionID - 1].add(fileName);
				}
			}
		}
		else if (command.find("grayscale") != -1)
		{
			sessions[currentSessionID - 1].addLog("grayscale");
			sessions[currentSessionID - 1].commands.push_back(command);
		}
		else if (command.find("monochrome") != -1)
		{
			sessions[currentSessionID - 1].addLog("monochrome");
			sessions[currentSessionID - 1].commands.push_back(command);
		}
		else if (command.find("negative") != -1)
		{
			sessions[currentSessionID - 1].addLog("negative");
			sessions[currentSessionID - 1].commands.push_back(command);
		}
		else if (command.find("rotate") != -1 && (arguments[1] == "left" || arguments[1] == "right"))
		{
			sessions[currentSessionID - 1].addLog(command);
			sessions[currentSessionID - 1].commands.push_back(command);
		}
		else if (command.find("undo") != -1)
		{
			undo();
		}
		else if (command.find("session info") != -1)
		{
			sessionInfo();
		}
		else if (command.find("switch") != -1)
		{
			switchSession(atoi(arguments[1].c_str()));
		}
		else if (command.find("collage") != -1)
		{
			if (arguments.size() != 5)
			{
				std::cout << "Not enough arguments have been entered to make a collage" << std::endl;
				std::cout << "The required arguments are: direction two image names and collage name" << std::endl;
			}
			else
			{
				int direction = 0;
				int image1ID = -1, image2ID = -1;
				for (int i = 0; i < sessions[currentSessionID - 1].images.size(); i++)
				{
					if (sessions[currentSessionID - 1].images[i]->getFileName() == arguments[2])
					{
						image1ID = i;
					}
					if (sessions[currentSessionID - 1].images[i]->getFileName() == arguments[3])
					{
						image2ID = i;
					}
				}
				if (image1ID == -1 || image2ID == -1)
				{
					std::cout << "The source images are not added to the session" << std::endl;
					return;
				}
				if (arguments[2].compare(arguments[2].size() - 3, 3, arguments[3], arguments[3].size() - 3, 3) != 0 && arguments[2].compare(arguments[2].size() - 3, 3, arguments[4], arguments[4].size() - 3, 3) != 0)
				{
					std::cout << "Cannot make a collage from different types!" << std::endl;
					return;
				}
				if (command.find("horizontal") != -1)
				{
					direction = 0;

					Image* collage = sessions[currentSessionID - 1].images[image1ID]->collage(direction, sessions[currentSessionID - 1].images[image1ID]->getFileName(), arguments[4]);
					std::cout << "New collage  \"" << arguments[4] << "\" created" << std::endl;
					sessions[currentSessionID - 1].add(collage->getFileName());
				}
				if (command.find("vertical") != -1)
				{
					direction = 1;

					Image* collage = sessions[currentSessionID - 1].images[image1ID]->collage(direction, sessions[currentSessionID - 1].images[image1ID]->getFileName(), arguments[4]);
					std::cout << "New collage  \"" << arguments[4] << "\" created" << std::endl;
					sessions[currentSessionID - 1].add(collage->getFileName());
				}
			}

		}
		else if (command.find("help") != -1)
		{
			//std::cout << "close" << "       " << "" << std::endl;
			std::cout << "- save" << "       " << "saves the files in the session" << std::endl;
			std::cout << "- save as <file>" << "     " << "saves the first file in the session in <file>" << std::endl;
			std::cout << "- help" << "      " << "prints this information" << std::endl;
			std::cout << "- exit" << "      " << "exists the program" << std::endl;
			std::cout << "- grayscale" << "      " << "Convert all color images in the current session to those using shades of gray.If black and white images are included in the current session, they should not be modified" << std::endl;
			std::cout << "- monochrome" << "      " << " Convert all color images in the current session to ones that have only black and white pixels,without any shades of gray.If the image is already monochrome, this transformation does not change it." << std::endl;
			std::cout << "- negative" << "      " << "A the negative transformation(color inversion) of the images in the current session." << std::endl;
			std::cout << "- rotate <direction>" << "      " << "This command applies a 90 degree rotation in the submitted direction." << std::endl;
			//std::cout << "- undo" << "      " << "Undo command that removes the last transformation in the current session.If a new session is started and then the undo command is entered immediately, it should have no effect." << std::endl;
			std::cout << "- add <image>" << "      " << "Adds the image to the current session. Not all transformations applied so far are applied to it" << std::endl;
			std::cout << "- session info" << "      " << "Enables the user to receive detailed information about the current user session, its identification number,the participating images, as well as the set of transformations that are to be applied to the respective images participating in the session." << std::endl;
			std::cout << "- switch <session> " << "      " << "Switches to a session with an ID number. If a session with such a number does not exist, display an appropriate error message" << std::endl;
			std::cout << "- collage <direction> <image1> <image2><outimage>" << "      " << "Creates a collage of two images (in the same format and the same dimension) available in the current session.The result is saved in a new image, which is added to the current session." << std::endl;
		}
		else if (command.find("as") != -1)
		{
			for (int j = 0; j < sessions[currentSessionID - 1].log.size(); j++)
			{
				if (sessions[currentSessionID - 1].log[j].find("grayscale") != -1)
				{
					sessions[currentSessionID - 1].images[0]->grayscale();
				}
				else 	if (sessions[currentSessionID - 1].log[j].find("monochrome") != -1)
				{
					sessions[currentSessionID - 1].images[0]->monochrome();
				}
				else  if (sessions[currentSessionID - 1].log[j].find("negative") != -1)
				{

					sessions[currentSessionID - 1].images[0]->negative();

				}
				else if (sessions[currentSessionID - 1].log[j].find("rotate") != -1)
				{
					int direction = 0;
					if (sessions[currentSessionID - 1].log[j].find("left") != -1)
					{
						direction = 0;
					}
					else if (sessions[currentSessionID - 1].log[j].find("right") != -1)
					{
						direction = 1;
					}
					sessions[currentSessionID - 1].images[0]->rotate(direction);
				}
			}
			std::cout << "Enter name to save file as :" << std::endl;
			std::string newName;
			std::getline(std::cin, newName);
			sessions[currentSessionID - 1].images[0]->saveAs(newName);
		}
		else if (command.find("save") != -1)
		{
			for (int j = 0; j < sessions[currentSessionID - 1].log.size(); j++)
			{
				modify(j);
				j--;
				sessions[currentSessionID - 1].log.erase(sessions[currentSessionID - 1].log.begin());
			}
			for (int i = 0; i < sessions[currentSessionID - 1].images.size(); i++)
			{
				sessions[currentSessionID - 1].images[i]->saveAs(sessions[currentSessionID - 1].images[i]->getFileName());
			}
		}
		else if (command.find("exit") != -1)
		{
			return;
		}
		else
		{
			std::cout << "There is no such command! Type help to see all the commands" << std::endl;
		}
	}
}

SessionManager::SessionManager()
{
	this->currentSessionID = 0;
}

void SessionManager::modify(int commandIndex)
{
	if (sessions[currentSessionID - 1].log[commandIndex].find("grayscale") != -1)
	{
		for (int i = 0; i < sessions[currentSessionID - 1].images.size(); i++)
		{
			sessions[currentSessionID - 1].images[i]->grayscale();
		}
	}
	else if (sessions[currentSessionID - 1].log[commandIndex].find("monochrome") != -1)
	{
		for (int i = 0; i < sessions[currentSessionID - 1].images.size(); i++)
		{
			sessions[currentSessionID - 1].images[i]->monochrome();
		}
	}
	else  if (sessions[currentSessionID - 1].log[commandIndex].find("negative") != -1)
	{
		for (int i = 0; i < sessions[currentSessionID - 1].images.size(); i++)
		{
			sessions[currentSessionID - 1].images[i]->negative();
		}
	}
	else if (sessions[currentSessionID - 1].log[commandIndex].find("rotate") != -1)
	{
		int direction = 0;
		if (sessions[currentSessionID - 1].log[commandIndex].find("left") != -1)
		{
			direction = 0;
		}
		else if (sessions[currentSessionID - 1].log[commandIndex].find("right") != -1)
		{
			direction = 1;
		}
		for (int i = 0; i < sessions[currentSessionID - 1].images.size(); i++)
		{
			sessions[currentSessionID - 1].images[i]->rotate(direction);
		}
	}
}

void SessionManager::switchSession(int sessionID)
{
	for (int i = 0; i < sessions.size(); i++)
	{
		if (sessions[i].getSessionID() == sessionID)
		{
			currentSessionID = i + 1;
			std::cout << "You switched to session with ID: "<< sessionID << "!" << std::endl;
			sessionInfo();
			return;
		}
	}
	std::cout << "There is not a session with this id" << std::endl;
}

void SessionManager::undo()
{
	std::cout << "Feature not implemented yet" << std::endl;
	//sessions[currentSessionID - 1].commands.pop_back();
}

void SessionManager::sessionInfo()
{
	if (currentSessionID == 0)
	{
		std::cout << "No session in progress." << std::endl;
		return;
	}
	std::cout << "Name of images in the session: ";
	for (int i = 0; i < sessions[currentSessionID - 1].images.size(); i++)
	{
		std::cout << sessions[currentSessionID - 1].images[i]->getFileName() << " ";
	}
	std::cout << std::endl;
	if (sessions[currentSessionID - 1].log.size() > 0)
	{
		std::cout << "Pending transformations: ";
		for (int i = 0; i < sessions[currentSessionID - 1].log.size(); i++)
		{
			std::cout << sessions[currentSessionID - 1].log[i] << " ";
		}
	}
	else
	{
		std::cout << "No transformations entered.";
	}
	std::cout << std::endl;
}
