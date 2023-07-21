#include "ComponentsMgr.hpp"
#include <thread>
#include <vector>
#include <iostream>
#include <limits>

using namespace std;

int main()
{
	//Documentation and start of the programm
	cout << "Bonjour, \nCeci un programme simulant l'utilisation des bidons dans la machine\n";
	cout << "Voici les differentes commandes disponibles : \n- setWeight : permet de modifier le poids d'un bidon";
	cout << "\n- pause : permet de mettre en pause le programme\n- ack : permet de relancer le programme";
	cout << "\n- stop : permet d'arrêter le programme\n- nothing : ne fais rien";
	cout << "\n\nFaites attention aux majuscule et minuscule, les entrees doivent etre exactes pour etre validee.\n\n";
	cout << "Press Enter to start the machine\n";
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n');

	//Instanciation of the components manager
	shared_ptr<IComponentsMgr> componentsMgr = make_shared<ComponentsMgr>();
	componentsMgr->initComponentsPtr(componentsMgr);

	//Map, inkScaleMgr, inputMgr and threads initialization
	map<string, tuple<shared_ptr<ICanister>, shared_ptr<list<double>>>> canistersMap = componentsMgr->createMap();

	componentsMgr->initPtrFileMgr();
	componentsMgr->initPtrScaleMgr();
	componentsMgr->initPtrInputMgr();

	//Starting up threads
	thread inputMgr(&IInputMgr::inputMgrThread, componentsMgr->getPtrInputMgr());
	thread scaleMgr(&IInkScaleMgr::inkScaleMgrThread, componentsMgr->getPtrScaleMgr());

	vector<thread> vecOfThreads;
	for (auto itr = canistersMap.begin(); itr != canistersMap.end(); ++itr)
		vecOfThreads.push_back(thread(&ICanister::canisterThread, canistersMap[itr->first]._Myfirst._Val));

	//Waiting for threads to end;
	for (size_t i = 0; i < vecOfThreads.size(); ++i)
		vecOfThreads[i].join();

	scaleMgr.join();
	inputMgr.join();
}