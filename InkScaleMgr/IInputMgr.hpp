#pragma once

/**
* @brief Interface for the InputMgr class
*/
class IInputMgr
{
public:

	/**
	* @brief permanent thread launched by main to manage some commands given by the user
	*/
	virtual void inputMgrThread() = 0;
};