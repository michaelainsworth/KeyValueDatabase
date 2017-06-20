#include <Kvp/Database.hpp>
#include <Kvp/MemoryDatabase.hpp>

KVP_NAMESPACE_BEGIN

Database::Database()
    : pDatabase_(new MemoryDatabase())
{}

void Database::create(const Key& key, const Value& value, const Atom& atom)
{
    pDatabase_->create(key, value, atom);
}

CurrentValue Database::read(const Key& key) const
{
    return pDatabase_->read(key);
};

void Database::update
(
    const Key& key,
    const Value& value,
    const Atom& atom,
    const Atom& condition
)
{
    pDatabase_->update(key, value, atom, condition);
}

void Database::delet(const Key& key, const Atom& condition)
{
    pDatabase_->delet(key, condition);
}

void Database::debug(std::ostream& outs) const
{
    return pDatabase_->debug(outs);
}

KVP_NAMESPACE_END

