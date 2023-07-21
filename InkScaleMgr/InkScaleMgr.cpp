#include <iostream>
#include <Windows.h>
#include "InkScaleMgr.hpp"
#include <iomanip>
#include <sstream>

using namespace std;

InkScaleMgr::InkScaleMgr(shared_ptr<IComponentsMgr> _components) : components_(_components)
{
	canistersMap_ = components_->getMap();
	maxCanister_ = maxInk_ + emptyCanister_;
	isPrinting_ = true;
	isMachineOn_ = true;
}

InkScaleMgr::Edetection InkScaleMgr::detectionState(double _currentWeight, double _oldWeight)
{
	decreasedWeight_ = _currentWeight <= _oldWeight;
	impossibleWeight_ = _currentWeight < emptyCanister_;
	tooMuchWeight_ = _currentWeight > maxCanister_;

	if (_currentWeight == maxCanister_ && _oldWeight <= X_)
		return NewCanister;
	else if (_currentWeight <= X_ && decreasedWeight_ && _currentWeight >= 0)
		return NoCanister;
	else if (_currentWeight <= Emax_ && _currentWeight >= Emin_ && decreasedWeight_ && !impossibleWeight_)
		return Empty;
	else if (_currentWeight <= A_ && decreasedWeight_ && !impossibleWeight_)
		return LowInkAlarm;
	else if (decreasedWeight_ && !impossibleWeight_ && (_oldWeight - _currentWeight <= 1.5) && !tooMuchWeight_)
		return CurrentCanister;

	return Error;
}

InkScaleMgr::EerrorType InkScaleMgr::errorType(double _currentWeight, double _oldWeight)
{
	decreasedWeight_ = _currentWeight <= _oldWeight;
	impossibleWeight_ = _currentWeight < 0;
	tooMuchWeight_ = _currentWeight > maxCanister_;

	if (tooMuchWeight_ || impossibleWeight_)
		return Error_Bad_Measurement;
	else if (_oldWeight - _currentWeight >= 1.5 && _currentWeight != 0)
		return Error_Too_Much_Decreasing;
	else if (!decreasedWeight_ && _currentWeight != 0)
		return Error_Refill;
	else if (_currentWeight <= X_ && _currentWeight >= 0)
		return Error_NoCanister;
	else if (_currentWeight <= Emax_ && _currentWeight >= Emin_ && decreasedWeight_)
		return Error_Empty;
	else
		return Unknown_Error;
}

void InkScaleMgr::errorRecovery()
{
	if (printingControl())
	{
		// Sets all the canister isPrinting variable to true
		for (auto itr = canistersMap_.begin(); itr != canistersMap_.end(); ++itr)
			canistersMap_[itr->first]._Myfirst._Val.get()->setIsPrinting(true);

		isPrinting_ = true;
	}
}

void InkScaleMgr::pause()
{
	//Sets all the canister isPrinting variable to false
	for (auto itr = canistersMap_.begin(); itr != canistersMap_.end(); ++itr)
		canistersMap_[itr->first]._Myfirst._Val.get()->setIsPrinting(false);

	isPrinting_ = false;
}

void InkScaleMgr::stopProgram()
{
	//pauses the program to avoid bug exit
	pause();

	//Sets all canisters isMachineOn_ variable to false
	for (auto itr = canistersMap_.begin(); itr != canistersMap_.end(); ++itr)
		canistersMap_[itr->first]._Myfirst._Val.get()->stopMachine();

	isMachineOn_ = false;
}



bool InkScaleMgr::printingControl()
{
	bool validPrint = true;
	double currentWeight;
	double oldWeight;
	Edetection d;
	EerrorType error;

	for (auto itr = canistersMap_.begin(); itr != canistersMap_.end(); ++itr)
	{
		//the previous currentWeight becomes the old one and the currentWeight takes the present weight of the canister
		oldWeight = canistersMap_[itr->first]._Get_rest()._Myfirst._Val.get()->front();
		currentWeight = canistersMap_[itr->first]._Myfirst._Val.get()->getWeight();

		//pushes to the front of the list the new weight
		canistersMap_[itr->first]._Get_rest()._Myfirst._Val.get()->push_front(currentWeight);

		//removes the last value of the list (the list only contains the currentWeight and the weight tested before the new one)
		canistersMap_[itr->first]._Get_rest()._Myfirst._Val.get()->pop_back();

		//prints the type of error
		d = detectionState(currentWeight, oldWeight);
		if (d == Error || d == Empty || d == NoCanister)
		{
			error = errorType(currentWeight, oldWeight);
			cout << itr->first << " : " << currentWeight << "kg "
				 << "(oldWeight " << oldWeight << "kg) Error => "
				 << ERRORS_MAP_.find(error)->second;
			cout << endl;
			validPrint = false;

			components_->getPtrFileMgr()->appendToCSV({ itr->first, to_string(currentWeight), to_string(oldWeight),
													   "Error", ERRORS_MAP_.find(error)->second });
		}
	}
	components_->getPtrFileMgr()->appendToCSV({});
	return validPrint;
}

void InkScaleMgr::output()
{
	string currentWeight;
	string previousWeight;
	Edetection state;
	vector<string> data;

	//used to convert double to string
	ostringstream temp;
	temp << fixed;
	temp << setprecision(2);

	//Header
	cout << setw(10) << left << "Color"
		 << setw(17) << left << "Current weight"
		 << setw(17) << left << "Previous weight" << "Status" << endl;

	for (auto it = canistersMap_.begin(); it != canistersMap_.end(); ++it)
	{
		temp << canistersMap_[it->first]._Get_rest()._Myfirst._Val.get()->front();
		currentWeight = temp.str();
		temp.str("");
		temp << canistersMap_[it->first]._Get_rest()._Myfirst._Val.get()->back();
		previousWeight = temp.str();
		temp.str("");
		state = detectionState(canistersMap_[it->first]._Get_rest()._Myfirst._Val.get()->front(), 
							   canistersMap_[it->first]._Get_rest()._Myfirst._Val.get()->back());

		cout << setw(10) << left << it->first
			 << setw(17) << currentWeight + " kg"
			 << setw(17) << previousWeight + " kg"
			 << STATES_MAP_.find(state)->second << endl;

		data = { it->first, currentWeight, previousWeight, STATES_MAP_.find(state)->second, "No Error"};
		components_->getPtrFileMgr()->appendToCSV(data);
	}
	cout << endl;

	//add empty line to CSV
	components_->getPtrFileMgr()->appendToCSV({});
}

void InkScaleMgr::inkScaleMgrThread()
{
	//Pushes the two first values in the list
	for (auto it = canistersMap_.begin(); it != canistersMap_.end(); ++it)
	{
		canistersMap_[it->first]._Get_rest()._Myfirst._Val.get()->push_back(0);
		canistersMap_[it->first]._Get_rest()._Myfirst._Val.get()->push_back(maxCanister_);
	}

	while (isMachineOn_)
	{
		if (isPrinting_)
		{
			//tests all canister values
			if (!printingControl())
			{
				isPrinting_ = false;
				pause();
			}

			//prints all canister states
			if (isPrinting_) 
				output();
		}

		Sleep(750);
	}
}