#include <Kvp/Value.hpp>

KVP_NAMESPACE_BEGIN

Value::Value(const String& value)
    : value_(value) {}

String Value::toString() const
{
    return value_;
}

DebugString Value::toDebugString() const
{
    return DebugString(value_);
}

bool operator ==(const Value& left, const Value& right)
{
    return left.value_ == right.value_;
}

KVP_NAMESPACE_END

