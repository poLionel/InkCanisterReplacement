#include "Util.hpp"
#include <random>

using namespace std;

int Util::generateNumber()
{
	random_device					rand_dev;
	default_random_engine			generator(rand_dev());
	uniform_int_distribution<int>	dir(20, 50);

	return dir(generator);
}