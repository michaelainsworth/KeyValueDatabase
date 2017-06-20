#include <Kvp/Atom.hpp>

KVP_NAMESPACE_BEGIN

Atom::Atom(UInt32 value) : value_(value) {}

bool operator ==(const Atom& left, const Atom& right)
{
    return left.value_ == right.value_;
}

bool operator !=(const Atom& left, const Atom& right)
{
    return left.value_ != right.value_;
}

std::ostream& operator <<(std::ostream& out, const Atom& atom)
{
    out << atom.value_;
    return out;
}

KVP_NAMESPACE_END


