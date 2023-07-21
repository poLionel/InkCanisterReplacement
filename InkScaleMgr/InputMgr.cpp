#include <iostream>
#include <limits>
#include <sstream>
#include "InputMgr.hpp"

/*
* Windows.h header has the min() and max() macros
* and it creates a problem with cin.ignore() to clear
* the buffer
*/
#define NOMINMAX
#include <Windows.h>

using namespace std;

InputMgr::InputMgr(shared_ptr<IComponentsMgr> components) : components_(components)
{
	isMachineOn_ = true;
	canistersMap_ = components_->getMap();
}

void InputMgr::getNewWeight(string& _color, string& _newWeight)
{
	cout << "Canister Color ==> ";
	getline(cin, _color);
	cout << "New weight => ";
	getline(cin, _newWeight);
	cin.clear();
	cout << endl;
}

void InputMgr::colorInput(string _color, double _newWeight)
{
	bool correctName = false;
	bool correctInput = false;
	string temp;

	while (!correctInput)
	{
		getNewWeight(_color, temp);

		for (size_t t = 0; t < components_->getColors().size(); ++t)
			if (_color == components_->getColors().at(t))
				correctName = true;

		if (correctName)
		{
			stringstream ss(temp);
			if (ss >> _newWeight && ss.eof())
				correctInput = true;
		}
	}

	canistersMap_[_color]._Myfirst._Val.get()->setWeight(_newWeight);
}

void InputMgr::toDoInput(string& _input)
{
	cout << "What to do ? ";
	getline(cin, _input);
	cout << endl;
}

void InputMgr::inputControl(string& _input, Einput& _i)
{
	bool correctInput = false;

	while (!correctInput)
	{
		toDoInput(_input);

		if (_input == "setWeight")
		{
			_i = SetWeight;
			correctInput = true;
		}
		else if (_input == "ack")
		{
			_i = Ack;
			correctInput = true;
		}
		else if (_input == "pause")
		{
			_i = Pause;
			correctInput = true;
		}
		else if (_input == "stop")
		{
			_i = Stop;
			correctInput = true;
		}
		else if (_input == "nothing")
		{
			_i = Nothing;
			correctInput = true;
		}
	}
}

void InputMgr::ack()
{
	components_->getPtrScaleMgr()->errorRecovery();
}

void InputMgr::getInput(string& _input, string& _color, double& _newWeight, Einput& _i)
{
	inputControl(_input, _i);

	switch (_i)
	{
	case SetWeight:
		colorInput(_color, _newWeight);
		break;
	case Ack:
		ack();
		break;
	case Pause:
		components_->getPtrScaleMgr()->pause();
		break;
	case Stop:
		components_->getPtrScaleMgr()->stopProgram();
		isMachineOn_ = false;
		break;
	case Nothing:
		Sleep(1000);
		break;
	default:
		break;
	}

	Sleep(100);
}

void InputMgr::inputMgrThread()
{
	double newWeight;
	string color;
	string input;
	Einput i; //Todo changer nom de variable

	while (isMachineOn_)
		getInput(input, color, newWeight, i);
}