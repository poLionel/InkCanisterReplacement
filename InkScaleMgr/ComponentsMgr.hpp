#pragma once
#include "IComponentsMgr.hpp"

/**
* @brief Helper class that creates a Canister Map and initialize it
*        and shared_ptrs for every interfaces
*/
class ComponentsMgr : public IComponentsMgr
{
public:

	#pragma region Override methods

	/**
	* @copydoc ICanister::initComponentsPtr(std::shared_ptr<IComponentsMgr> ptr)
	*/
	void initComponentsPtr(std::shared_ptr<IComponentsMgr> ptr) override;

	/**
	* @copydoc ICanister::initPtrScaleMgr()
	*/
	void initPtrScaleMgr() override;

	/**
	* @copydoc ICanister::initPtrInputMgr()
	*/
	void initPtrInputMgr() override;

	/**
	* @copydoc ICanister::initPtrFileMgr()
	*/
	void initPtrFileMgr() override;

	/**
	* @copydoc ICanister::getPtrScaleMgr()
	*/
	std::shared_ptr<IInkScaleMgr> getPtrScaleMgr() const override;

	/**
	* @copydoc ICanister::getPtrInputMgr()
	*/
	std::shared_ptr<IInputMgr> getPtrInputMgr() const override;

	/**
	* @copydoc ICanister::getPtrFileMgr()
	*/
	std::shared_ptr<IFileMgr> getPtrFileMgr() const override;

	/**
	* @copydoc ICanister::getColor()
	*/
	std::array<std::string, 7> getColors() const override;

	/**
	* @copydoc ICanister::createMap
	*/
	std::map<std::string, std::tuple<std::shared_ptr<ICanister>, std::shared_ptr<std::list<double>>>> createMap() override;

	/**
	* @brief gets a map of canisters
	*
	* @return returns a map with the canisters names, the pointers to these objects and their weight lists
	*/
	std::map<std::string, std::tuple<std::shared_ptr<ICanister>, std::shared_ptr<std::list<double>>>> getMap() const override;
	
	#pragma endregion

private:

	#pragma region Methods

	/**
	* @brief  initializes a tuple of 2 pointers to a canister and its weight list
	*
	* @return returns the initialize tuple
	*/
	std::tuple<std::shared_ptr<ICanister>, std::shared_ptr<std::list<double>>> initTuple();

	#pragma endregion

	#pragma region Variables

	/**
	* @brief  map that contains the name of the canister, a pointer to every specific
	*         Canister and another pointer on his weight list
	*
	* @param  string name of the canister (the color)
	* @param  tuple -> pointer to a canister and a weight list
	*/
	std::map<std::string, std::tuple<std::shared_ptr<ICanister>, std::shared_ptr<std::list<double>>>> canistersMap_;

	///<array containing all the possible colors of the canisters
	const std::array<std::string, 7> colors_ = { "Black", "White", "Magenta", "Cyan", "Yellow", "Orange", "Purple" };

	///<reference to the interface of InkScaleMgr
	std::shared_ptr<IInkScaleMgr> ptrScaleMgr_;

	///< reference to the interface of InputMgr
	std::shared_ptr<IInputMgr> ptrInputMgr_;

	///< reference to the interface of FileMgr
	std::shared_ptr<IFileMgr> ptrFileMgr_;

	///<reference to the interface of IComponents
	std::shared_ptr<IComponentsMgr> self_ptr_;

	#pragma endregion
	
};