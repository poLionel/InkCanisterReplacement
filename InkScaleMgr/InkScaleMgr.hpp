#pragma once
#include "IComponentsMgr.hpp"

/**
* @brief Complex class, almost handle the whole program
*/
class InkScaleMgr : public IInkScaleMgr
{
public:

	/**
	* @brief Constructor
	* 
	* @param components IComponentsMgr ptr
	*/
	InkScaleMgr(std::shared_ptr<IComponentsMgr> components);

	#pragma region Override methods

	/**
	* @copydoc IInkScaleMgr::inkScaleMgrThread()
	*/
	void inkScaleMgrThread() override;

	/**
	* @copydoc IInkScaleMgr::errorRecovery()
	*/
	void errorRecovery() override;

	/**
	* @copydoc IInkScaleMgr::pause()
	*/
	void pause() override;

	/**
	* @copydoc IInkScaleMgr::pause()
	*/
	void stopProgram() override;

	#pragma endregion

private:

	#pragma region Enum

	/**
	* @brief Enum which contains all the different possible states for a canister
	*/
	enum Edetection { NewCanister, CurrentCanister, LowInkAlarm, Empty, NoCanister, Error };

	/**
	* @brief Enum which contains all the different possible errors (some are not used for the moment)
	*/
	enum EerrorType { Error_Refill, Error_Bad_Measurement, Error_Too_Much_Decreasing, Error_NoCanister, Error_Empty, Unknown_Error };

	#pragma endregion

	#pragma region Methods

	/**
	* @brief Prints the state of all the canisters if there is no error
	*/
	void output();

	/**
	* @brief Updates the weights of the canisters and the list and checks if they can print
	*		 otherwise prints the error type
	*
	* @return whether all the canisters can print or not
	*/
	bool printingControl();

	/**
	* @brief Determines the current state of a canister
	*
	* @param _currentWeight the current Weight
	* @param _oldWeight the old Weight
	* @return state of type Edetection
	*/
	Edetection detectionState(double _currentWeight, double _oldWeight);

	/**
	* @brief Determines which error it is (if there is one) and prints the error type
	*
	* @param _currentWeight the current Weight
	* @param _oldWeight the old Weight
	* @return error of type Eerror
	*/
	EerrorType errorType(double _currentWeight, double _oldWeight);

	#pragma endregion 

	#pragma region Variables
	/**
	* @brief map that contains the names of the canister, a pointer to every specific
	*        Canister and another pointer on its weight list
	*
	* @param _string name of the canister (the color)
	* @param _tuple pointer to a canister and a weight list
	*/
	std::map<std::string, std::tuple<std::shared_ptr<ICanister>, std::shared_ptr<std::list<double>>>> canistersMap_;

	///< contains all possible states of a canister and their value as a string
	const std::map<Edetection, std::string> STATES_MAP_ = { {NewCanister, "New Canister"}, {CurrentCanister, "Current Canister"},
													    {LowInkAlarm, "Low Ink Alarm"}, {Empty, "Empty Canister"}, 
												        {NoCanister, "No Canister"}, {Error, "Error"}};

	///<contains all possible errors and their value as a string
	const std::map<EerrorType, std::string> ERRORS_MAP_ = { {Error_Refill, "Refill"}, {Error_Bad_Measurement, "Bad Mesearument"},
												  {Error_Too_Much_Decreasing, "Too much decreasing"}, {Error_NoCanister, "No Canister"}, 
												  {Error_Empty, "Empty Canister"}, {Unknown_Error, "Unknown error"}};

	///<checks if the canisters can print or not
	bool isPrinting_; 

	///<checks if the machine is still working
	bool isMachineOn_;

	///<checks if the weight is decreasing (oldWeight - currentWeight)
	bool decreasedWeight_;

	///<check if the weight is superior than an empty canister
	bool impossibleWeight_;

	///<checks if the weight is superior than the max weight of a canister
	bool tooMuchWeight_;

	///<weight of an empty canister + the max capacity of ink in a canister (emptyCanister + maxInk)
	double maxCanister_;

	///<weight of the max capacity of ink in a canister
	const double maxInk_ = 11.0;

	///<weight of a empty canister
	const double emptyCanister_ = 1.0;

	///<upper limit of the low ink alarm state
	const double A_ = 0.5 + emptyCanister_;

	///<upper limit of the empty state
	const double Emax_ = 0.15 + emptyCanister_;

	///<lower limit of the empty state
	const double Emin_ = Emax_ - 0.5;

	///<upper limit of the noCanister state
	const double X_ = Emin_;

	///<ptr to the componentsMgr
	std::shared_ptr<IComponentsMgr> components_;

	#pragma endregion
};