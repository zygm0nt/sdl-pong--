#include "FileFactory.h"

bool
FileFactory::registerObject(std::string x) {
    return registerObject(x, x);
}

bool
FileFactory::registerObject(std::string x, std::string key) {
    _ObjectMap[key] = new FileObject(x);  
    _currentId++;

    return true;
}

void
FileFactory::unregisterObject(std::string x) {
    _currentId--;
}

FileFactory * FileFactory::_instance = NULL;
long FileFactory::_currentId = 0;

FileFactory *
FileFactory::getFactoryInstance() {
    if (_instance == NULL) 
        _instance = new FileFactory();
    return _instance;
}

Object *
FileFactory::getObject(std::string x) {
    return _ObjectMap[x];
}
