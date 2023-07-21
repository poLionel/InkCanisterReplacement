#pragma once
/**
* @brief Interface for the class Canister
*/
class ICanister
{
public:
	/**
	* @brief permanent thread launched by main to reduce the weight of a canister over time while machine is on
	*/
	virtual void canisterThread() = 0;

	/**
	* @brief gets the weight of a canister
	*
	* @return the weight of a canister
	*/
	virtual double getWeight() = 0;

	/**
	* @brief says whether a canister can print or not
	*
	* @param isPrinting print condition of a canister
	*/
	virtual void setIsPrinting(bool _isPrinting) = 0;

	/**
	* @brief gets the printing condition of a canister
	*
	* @return true if a canister can print
	*/
	virtual bool getIsPrinting() = 0;

	/**
	* @brief sets the isMachineOn variable to false
	*/
	virtual void stopMachine() = 0;

	/**
	* @brief sets the weight of a canister
	*/
	virtual void setWeight(double newWeight) = 0;
};