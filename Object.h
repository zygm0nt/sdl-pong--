#ifndef _FACTORY_OBJECT_H_
#define _FACTORY_OBJECT_H_

#include <string>

class Object { 
    private:
        long _objectId;
        std::string objectName;

    public:
        Object() { }
        Object(long i) { _objectId = i; };
};

#endif
