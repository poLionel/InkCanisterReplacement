#include "ComponentsMgr.hpp"
#include "InkScaleMgr.hpp"
#include "Canister.hpp"
#include "InputMgr.hpp"
#include "FileMgr.hpp"
#include <random>

using namespace std;

#pragma region Initializer

	void ComponentsMgr::initComponentsPtr(shared_ptr<IComponentsMgr> _ptr) 
	{
		self_ptr_ = _ptr;
	}

	void ComponentsMgr::initPtrScaleMgr()
	{
		ptrScaleMgr_ = make_shared<InkScaleMgr>(self_ptr_);
	}

	void ComponentsMgr::initPtrInputMgr()
	{
		ptrInputMgr_ = make_shared<InputMgr>(self_ptr_);
	}

	void ComponentsMgr::initPtrFileMgr()
	{
		ptrFileMgr_ = make_shared<FileMgr>(self_ptr_);
	}

	map<string, tuple<shared_ptr<ICanister>, shared_ptr<list<double>>>> ComponentsMgr::createMap()
	{
		map<string, tuple<shared_ptr<ICanister>, shared_ptr<list<double>>>> temp;

		for (size_t t = 0; t < colors_.size(); ++t)
			temp.insert(pair<string, tuple<shared_ptr<ICanister>, shared_ptr<list<double>>>>(ComponentsMgr::colors_[t], ComponentsMgr::initTuple()));

		return canistersMap_ = temp;
	}

	tuple<shared_ptr<ICanister>, shared_ptr<list<double>>> ComponentsMgr::initTuple()
	{
		shared_ptr<ICanister> test = make_shared<Canister>();

		return make_tuple(test, make_shared<list<double>>());
	}

	#pragma endregion

#pragma region getter

	shared_ptr<IInkScaleMgr> ComponentsMgr::getPtrScaleMgr() const
	{
		return ptrScaleMgr_;
	}

	shared_ptr<IInputMgr> ComponentsMgr::getPtrInputMgr() const
	{
		return ptrInputMgr_;
	}

	shared_ptr<IFileMgr> ComponentsMgr::getPtrFileMgr() const
	{
		return ptrFileMgr_;
	}

	array<string, 7> ComponentsMgr::getColors() const
	{
		return colors_;
	}

	map<string, tuple<shared_ptr<ICanister>, shared_ptr<list<double>>>> ComponentsMgr::getMap() const
	{
		return canistersMap_;
	}

	#pragma endregion


