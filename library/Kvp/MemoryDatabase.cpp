#include <Kvp/MemoryDatabase.hpp>
#include <Kvp/ConcurrencyError.hpp>
#include <boost/format.hpp>

using boost::format;
using std::make_pair;

KVP_NAMESPACE_BEGIN

MemoryDatabase::MemoryDatabase()
    : RealDatabase(), map_()
{}

MemoryDatabase::~MemoryDatabase() {}

void MemoryDatabase::create
(
    const Key& key,
    const Value& value,
    const Atom& atom
)
{
    Map::const_iterator it = map_.find(key);
    Map::const_iterator end = map_.end();

    if (it != end)
    {
        throw ConcurrencyError
        (
            (
                format
                (
                    "An error occurred when creating the key '%s'. "
                    "The key specified already exists."
                ) % key.toDebugString()
            ).str()
        );
    }

    CurrentValue cv(value, atom);
    map_.insert(make_pair(key, cv));
}


CurrentValue MemoryDatabase::read(const Key& key) const
{
    Map::const_iterator it = map_.find(key);
    Map::const_iterator end = map_.end();

    CurrentValue cv;

    if (it != end)
    {
        cv = it->second;
    }

    return cv;
}

void MemoryDatabase::update
(
    const Key& key,
    const Value& value,
    const Atom& atom,
    const Atom& condition
)
{
    CurrentValue cv = read(key);
    if (!cv)
    {
        throw ConcurrencyError
        (
            (
                format
                (
                    "An error occurred when updating the key '%s'. "
                    "The key specified does not exist."
                ) % key.toDebugString()
            ).str()
        );
    }

    Atom cvv = cv.atom();
    if (cvv != condition)
    {
        throw ConcurrencyError
        (
            (
                format
                (
                    "An error occurred when updating the key '%s'. "
                    "The atom condition %i does not match the current "
                    "atom %i."
                ) % key.toDebugString() % condition % cvv
            ).str()
        );
    }

    Map::const_iterator it = map_.find(key);
    map_.erase(it);

    cv = CurrentValue(value, atom);
    map_.insert(make_pair(key, cv));
}

void MemoryDatabase::delet(const Key& key, const Atom& condition)
{
    CurrentValue cv = read(key);
    if (!cv)
    {
        throw ConcurrencyError
        (
            (
                format
                (
                    "An error occurred when deleting the key '%s'. "
                    "The key specified does not exist."
                ) % key.toDebugString()
            ).str()
        );
    }

    Atom cvv = cv.atom();
    if (cvv != condition)
    {
        throw ConcurrencyError
        (
            (
                format
                (
                    "An error occurred when deleting the key '%s'. "
                    "The atom condition %i does not match the current "
                    "atom %i."
                ) % key.toDebugString() % condition % cvv
            ).str()
        );
    }

    Map::const_iterator it = map_.find(key);
    map_.erase(it);
}


void MemoryDatabase::debug(std::ostream& outs) const
{
    Map::const_iterator it = map_.begin();
    Map::const_iterator end = map_.end();

    outs << "Key count: " << map_.size() << "\n\n";

    Map::size_type i = 0;
    for (; it != end; ++it)
    {
        Key key = it->first;
        CurrentValue currentValue = it->second;

        outs << "#" << i << "\n";
        outs << "    Key: " << key.toDebugString() << "\n"
             << "   Atom: " << currentValue.atom() << "\n"
             << "  Value: " << currentValue.value().toDebugString() << "\n\n";

        ++i;
    }
}

KVP_NAMESPACE_END

