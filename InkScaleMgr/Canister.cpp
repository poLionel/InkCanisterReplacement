#include "Canister.hpp"
#include <iostream>
#include <Windows.h>
#include "Util.hpp"

#pragma region Constructor
Canister::Canister()
{
	maxCanister_ = maxInk_ + emptyCanister_;
	currentWeight_ = maxCanister_;
	isMachineOn_ = true;
	isPrinting_ = true;
}

#pragma endregion

double Canister::getWeight()
{
	return currentWeight_;
}

void Canister::setIsPrinting(bool _isPrinting)
{
	isPrinting_ = _isPrinting;
}

bool Canister::getIsPrinting()
{
	return isPrinting_;
}

void Canister::stopMachine()
{
	isMachineOn_ = false;
}

void Canister::setWeight(double _newWeight)
{
	currentWeight_ = _newWeight;
}

void Canister::canisterThread()
{
	double aleatoire = 0;

	while (isMachineOn_)
	{
		while (isPrinting_)
		{
			aleatoire = (double)Util::generateNumber() / 100.0;
			currentWeight_ -= aleatoire;
			Sleep(1000);
		}
	}
}