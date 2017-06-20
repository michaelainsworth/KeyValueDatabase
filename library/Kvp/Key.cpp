#include <Kvp/Key.hpp>

KVP_NAMESPACE_BEGIN

Key::Key(const String& value) : value_(value) {}

DebugString Key::toDebugString() const
{
    return DebugString(value_);
}

bool operator ==(const Key& left, const Key& right)
{
    return left.value_ == right.value_;
}

bool operator <(const Key& left, const Key& right)
{
    return left.value_ < right.value_;
}

KVP_NAMESPACE_END


