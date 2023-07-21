#pragma once
#include "ICanister.hpp"

/**
* @brief Installation of an ink canister and declaration
*		 of the methods to reduce its weight and to
*		 return the weight for the scale manager
*/
class Canister : public ICanister
{
public:

	/**
	* @brief Constructor
	*/
	Canister();

	#pragma region Override methods

	/**
	* @copydoc ICanister::canisterThread()
	*/
	void canisterThread() override;

	/**
	* @copydoc ICanister::getWeight()
	*/
	double getWeight() override;

	/**
	* @copydoc ICanister::setIsPrinting(bool isPrinting)
	*/
	void setIsPrinting(bool _isPrinting) override;

	/**
	* @copydoc ICanister::getIsPrinting()
	*/
	bool getIsPrinting() override;

	/**
	* @copydoc ICaniser::stopMachine()
	*/
	void stopMachine() override;

	/**
	* @copydoc ICanister::getIsPrinting(double newWeight)
	*/
	void setWeight(double _newWeight) override;

	#pragma endregion

private:

	#pragma region Variables

	///<Maximum weight of ink in a canister
	const double maxInk_ = 11.0;

	///<Weight of an empty canister
	const double emptyCanister_ = 1.0;

	///<Maximum weight of a canister (weight of the empty canister + weight of ink)
	double maxCanister_;

	///<Current weight of a canister
	double currentWeight_;

	///<State of the machine (true if the machine is on)
	bool isMachineOn_;

	///<Printing state of the machine (true if the machine is printing)
	bool isPrinting_;

	#pragma endregion
};