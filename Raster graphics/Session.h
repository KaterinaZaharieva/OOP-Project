#pragma once
#include <vector>
#include <string>
#include "Image.h"
/*! class for the session information*/
class Session
{
private:
	int sessionID;
	std::vector <std::string> log;
	std::vector <std::string> commands;
	std::vector<Image*> images;
public:
	friend class SessionManager;
	/*! default constructor*/
	Session(int sessionID);
	/*! @return sessions id*/
	int getSessionID();

	/*! destructor */
	~Session();

	/*! adds a command that will be executed
	*@param command name
	*/
	void addLog(std::string message);
	/*! Adds the image to the current session. Not all transformations applied so far are applied to it
	* @param file name for a image
	*/
	void add(std::string image);
};


