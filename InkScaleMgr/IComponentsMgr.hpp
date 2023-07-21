#pragma once
#include "ICanister.hpp"
#include "IInkScaleMgr.hpp"
#include "IInputMgr.hpp"
#include "IFileMgr.hpp"

#include <array>
#include <list>
#include <map>
#include <string>
#include <tuple>
#include <memory>

class IComponentsMgr
{
public :
	/**
	* @brief initializes a shared_ptr for the ComponentsMgr
	*/
	virtual void initComponentsPtr(std::shared_ptr<IComponentsMgr> ptr) = 0;

	/**
	* @brief initializes a shared_ptr for the InkScaleMgr
	*/
	virtual void initPtrScaleMgr() = 0;

	/**
	* @brief initializes a shared_ptr for the InputMgr
	*/
	virtual void initPtrInputMgr() = 0;

	/**
	* @brief initializes a shared_ptr for the FileMgr
	*/
	virtual void initPtrFileMgr() = 0;

	/**
	* @brief gets the pointer of the InkScaleMgr
	*
	* @return a shared_ptr of the InkScaleMgr
	*/
	virtual std::shared_ptr<IInkScaleMgr> getPtrScaleMgr() const = 0;

	/**
	* @brief gets the pointer of the InputMgr
	*
	* @return a shared_ptr of the InputMgr
	*/
	virtual std::shared_ptr<IInputMgr> getPtrInputMgr() const = 0;

	/**
	* @brief gets the pointer of the FileMgr
	*
	* @return a shared_ptr of the FileMgr
	*/
	virtual std::shared_ptr<IFileMgr> getPtrFileMgr() const = 0;

	/**
	* @brief gets the array containing the colors of the canisters
	*
	* @return the array containing the colors of the canisters
	*/
	virtual std::array<std::string, 7> getColors() const = 0;

	/**
	* @brief gets a map of canisters
	*
	* @return a map with the canisters names, the pointers to these objects and their weight lists
	*/
	virtual std::map<std::string, std::tuple<std::shared_ptr<ICanister>,
		                          std::shared_ptr<std::list<double>>>> getMap() const = 0;

	/**
	* @brief creates a map of Canisters
	*
	* @return a map with the Canisters names, the pointers to these objects and their weight lists
	*/
	virtual std::map<std::string, std::tuple<std::shared_ptr<ICanister>, 
								  std::shared_ptr<std::list<double>>>> createMap() = 0;

};
