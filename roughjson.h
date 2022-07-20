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

    // return status when parse
    enum class ParseStatus
    {
        OK,
        ExpectValue,
        InvalidValue,
        RootNotSingular
    };

    struct RoughNode
    {
        RoughType type;
    };

    class Parser
    {
    private:
        string json;
        // current parse position
        int cur;
        RoughNode *root;

        void parse_whitespace();
        ParseStatus parse_null(RoughNode *node);
        ParseStatus parse_true(RoughNode *node);
        ParseStatus parse_false(RoughNode *node);
        ParseStatus parse_value(RoughNode *node);

    public:
        Parser(const string &s) : json(s), cur(0), root(nullptr) {}
        ~Parser() {}
        ParseStatus parse();
        };

}

#endif /* ROUGHJSON_H__ */