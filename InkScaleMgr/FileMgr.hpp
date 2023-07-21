#pragma once
#include "IComponentsMgr.hpp"

/**
* @brief manage writing data to a csv file
*/
class FileMgr : public IFileMgr
{
public :

	/**
	* @brief Constructor
	* 
	* @param _ptr the componentsMgr pointer
	*/
	FileMgr(std::shared_ptr<IComponentsMgr> _ptr);

	/**
	* @copydoc IFileMgr::appendToCSV(const std::vector<std::string>& _data)
	*/
	void appendToCSV(const std::vector<std::string>& _data) override;
    
private :

	/**
	* @brief clear the CVS file
	*/
	void clearCSV();

	///< reference to an IComponentsMgr pointer
	std::shared_ptr<IComponentsMgr> components_;

	///< data file
	const std::string file_ = "Data.csv";

	///< different csv data categories
	const std::vector<std::string> data_ = { "Color, Current weight, Previous weight, Status, Error" };

};