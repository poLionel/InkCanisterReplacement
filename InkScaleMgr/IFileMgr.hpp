#pragma once
#include <string>
#include <vector>

/**
* @brief Interface for the FileMgr class
*/
class IFileMgr
{
public:

	/**
	* @brief add data to the CSV file
	* 
	* @param _data data to add
	*/
	virtual void appendToCSV(const std::vector<std::string>& _data) = 0;
};