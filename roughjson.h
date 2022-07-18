#ifndef ROUGHJSON_H__
#define ROUGHJSON_H__

#include <string>

using std::string;

namespace rough
{
    // data type in json
    enum class RoughType
    {
        Null,
        False,
        True,
        Number,
        String,
        Array,
        Object
    };


    struct RoughNode
    {
        RoughType type;
    };

    int rough_parse(RoughNode *v, const string &json)
    {
    }

}

#endif /* ROUGHJSON_H__ */