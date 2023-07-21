#pragma once

/**
* @brief Interface of the InkScaleMgr class 
*/
class IInkScaleMgr
{
public:

	/**
	* @brief permanent thread launched by main, update the data and handle the output and input
	*/
	virtual void inkScaleMgrThread() = 0;

	/**
	* @brief checks if there is still an error and if not, sets the printing state of the canisters and the scaleMgr to true
	*/
	virtual void errorRecovery() = 0;

	/**
	* @brief pauses threads of canisters and the inkScaleMgr
	*/
	virtual void pause() = 0;

	/**
	* @brief stops the execution of the program
	*/
	virtual void stopProgram() = 0;

};