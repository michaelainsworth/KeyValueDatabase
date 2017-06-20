#include <Kvp/CurrentValue.hpp>

KVP_NAMESPACE_BEGIN

CurrentValue::CurrentValue() : exists_(false), value_(""), atom_(0) {}

CurrentValue::CurrentValue(const Value& value, const Atom& atom)
    : exists_(true), value_(value), atom_(atom) {}

bool CurrentValue::exists() const { return exists_; }

const Value& CurrentValue::value() const {
    return value_;
}

const Atom& CurrentValue::atom() const { return atom_; }

CurrentValue::operator bool() const
{
    return exists_;
}

KVP_NAMESPACE_END

