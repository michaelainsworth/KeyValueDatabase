#include <iomanip>
#include <Kvp/DebugString.hpp>
#include <sstream>

KVP_NAMESPACE_BEGIN

DebugString::DebugString(const String& value) : value_(value) {}

std::ostream& operator <<(std::ostream& outs, const DebugString& value)
{
    const String& v = value.value_;
    String::size_type i = 0, s = v.size();

    for (; i < s; ++i)
    {
        char c = v[i];

        if ('\'' == c)
        {
            outs << "\\'";
        }
        else if ('"' == c)
        {
            outs << "\"";
        }
        else if ('\t' == c)
        {
            outs << "\"";
        }
        else if ('\r' == c)
        {
            outs << "\\r";
        }
        else if ('\n' == c)
        {
            outs << "\\n";
        }
        else if ('\\' == c)
        {
            outs << "\\\\";
        }
        else if (c >= 32 && c <= 126)
        {
            outs << c;
        }
        else
        {
            std::ostringstream tmp;
            tmp << "\\x" << std::hex << std::setfill('0') << std::setw(2)
                << c;
            outs << tmp.str();
        }
    }
    return outs;
}

KVP_NAMESPACE_END

