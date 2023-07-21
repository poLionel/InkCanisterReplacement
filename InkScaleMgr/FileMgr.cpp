#include "FileMgr.hpp"
#include <fstream>

using namespace std;

FileMgr::FileMgr(shared_ptr<IComponentsMgr> _ptr) : components_(_ptr)
{
    clearCSV();
    appendToCSV(data_);
}

void FileMgr::clearCSV() 
{
    std::ofstream file;
    file.open(file_, std::ios_base::trunc);

    if (file.is_open()) {
        file.close();
    }
}

void FileMgr::appendToCSV(const vector<string>& _data)
{
    std::ofstream file;
    file.open(file_, std::ios_base::app);

    if (file.is_open()) {
        for (size_t i = 0; i < _data.size(); ++i) {
            file << _data[i];
            if (i != _data.size() - 1)
                file << ",";
        }
        file << "\n";
        file.close();
    }
}