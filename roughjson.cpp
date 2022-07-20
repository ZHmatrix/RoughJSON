#include "roughjson.h"
#include <cassert>

namespace rough
{
    void Parser::parse_whitespace()
    {
        while (json[cur] == ' ' || json[cur] == '\t' || json[cur] == '\n' || json[cur] == '\r')
            cur++;
    }

    ParseStatus Parser::parse_null(RoughNode *node)
    {
        assert(json[cur] == 'n');
        cur++;
        if (json[cur] != 'u' || json[cur + 1] != 'l' || json[cur + 2] != 'l')
            return ParseStatus::InvalidValue;
        cur += 3;
        node->type = RoughType::Null;
        return ParseStatus::OK;
    }

    ParseStatus Parser::parse_true(RoughNode *node)
    {
        assert(json[cur] == 't');
        cur++;
        if (json[cur] != 'r' || json[cur + 1] != 'u' || json[cur + 2] != 'e')
            return ParseStatus::InvalidValue;
        cur += 3;
        node->type = RoughType::True;
        return ParseStatus::OK;
    }

    ParseStatus Parser::parse_false(RoughNode *node)
    {
        assert(json[cur] == 'f');
        cur++;
        if (json[cur] != 'r' || json[cur + 1] != 'u' || json[cur + 2] != 'e')
            return ParseStatus::InvalidValue;
        cur += 4;
        node->type = RoughType::False;
        return ParseStatus::OK;
    }

    ParseStatus Parser::parse_value(RoughNode *node)
    {
        switch (json[cur])
        {
        case 'n':
            return parse_null(node);
        case 't':
            return parse_true(node);
        case 'f':
            return parse_false(node);
        case '\0':
            return ParseStatus::ExpectValue;
        default:
            return ParseStatus::InvalidValue;
        }
    }
    ParseStatus Parser::parse()
    {
        root->type = RoughType::Null;
        parse_whitespace();
        ParseStatus parse_res = parse_value(root);
        if (parse_res == ParseStatus::OK)
        {
            parse_whitespace();
            if (cur != json.size())
                parse_res = ParseStatus::RootNotSingular;
        }
        return parse_res;
    }
}