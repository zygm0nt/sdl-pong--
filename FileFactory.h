#ifndef _FILE_FACTORY_H_
#define _FILE_FACTORY_H_

#include "FileObject.h"
#include <map>
#include <string>

class FileFactory { 
    protected:
        static FileFactory* _instance;
        static long _currentId;

        std::map<std::string, Object *> _ObjectMap;

        FileFactory() {  }

    public:
        bool registerObject(std::string x);
        bool registerObject(std::string x, std::string key);
        void unregisterObject(std::string x);

        static FileFactory * getFactoryInstance();

        Object * getObject(std::string x);

};

#endif
