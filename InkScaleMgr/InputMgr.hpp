#pragma once
#include "IComponentsMgr.hpp"

/**
* @brief class that handles inputs in order to change the weight of the canisters
*/
class InputMgr : public IInputMgr
{
public:

	/**
	* @brief Constructor
	* 
	* @param _components IComponents ptr
	*/
	InputMgr(std::shared_ptr<IComponentsMgr> _components);

	/**
	* @copydoc IInputMgr::inputMgrThread()
	*/
	void inputMgrThread() override;

private:

	#pragma region Enum

	/**
	* @brief enum which contains all the possible actions for the inputMgr
	*/
	enum Einput { SetWeight, Ack, Pause, Stop, Nothing };

	#pragma endregion

	#pragma region Methods

	/**
	* @brief gets the new weight of a canister
	*
	* @param _color the canister's color
	* @param _newWeight the new weight of a canister
	*/
	void getNewWeight(std::string& _color, std::string& _newWeight);

	/**
	* @brief asks for the action to be taken
	*
	* @param _input the action to be taken
	*/
	void toDoInput(std::string& _input);

	/**
	* @brief controls if the input for the action to be taken is correct
	*
	* @param _input the action to be taken
	* @param _i which action was chosen
	*/
	void inputControl(std::string& _input, Einput& _i);

	/**
	* @brief control if the canister color and new weight is correct
	*
	* @param _color the canister color
	* @param _newWeight the canister new weight
	*/
	void colorInput(std::string _color, double _newWeight);

	/**
	* @brief handles inputs and chooses what action to take
	*
	* @param _input the action to be taken
	* @param _color the canister color
	* @param _newWeight the canister new weight
	* @param _i which action was chosen
	*/
	void getInput(std::string& _input, std::string& _color, double& _newWeight, Einput& _i);

	/**
	* @brief calls the errorRecovery method from inkScaleMgr (also used as a restart method if inkScaleMgr is on pause)
	*/
	void ack();

	#pragma endregion

	#pragma region Variables
	/**
	* @brief  map that contains the name of the canister, a pointer to every specific
	*		  Canister and another pointer on its weight list
	*
	* @param  string name of a canister (the color)
	* @param  tuple pointer to a canister and a weight list
	*/
	std::map<std::string, std::tuple<std::shared_ptr<ICanister>, std::shared_ptr<std::list<double>>>> canistersMap_;

	///<checks if the machine is still working
	bool isMachineOn_;

	///< IComponents ptr
	std::shared_ptr<IComponentsMgr> components_;

	#pragma endregion

};