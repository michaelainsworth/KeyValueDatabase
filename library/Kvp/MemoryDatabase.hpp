#ifndef KVP_MEMORYDATABASE_HPP
#define KVP_MEMORYDATABASE_HPP

#include <Kvp/RealDatabase.hpp>
#include <map>

KVP_NAMESPACE_BEGIN

//! \brief Represents a Database stored in memory.
//!
class MemoryDatabase : public RealDatabase
{

    // ========================================================================
    //  Lifecycle
    // ========================================================================

public:

    MemoryDatabase();
    virtual ~MemoryDatabase();

    // ========================================================================
    // Accessors
    // ========================================================================

public:

    virtual CurrentValue read(const Key& key) const;

    // ========================================================================
    // Mutators
    // ========================================================================

public:

    virtual void create
    (
        const Key& key,
        const Value& value,
        const Atom& atom
    );

    virtual void update
    (
        const Key& key,
        const Value& value,
        const Atom& atom,
        const Atom& condition
    );

    virtual void delet(const Key& key, const Atom& condition);

    // ========================================================================
    // Helpers
    // ========================================================================

public:

    virtual void debug(std::ostream& outs) const;

    // ========================================================================
    // Variables
    // ========================================================================

private:

    typedef std::map<Key,CurrentValue> Map;
    Map map_;

};

KVP_NAMESPACE_END

#endif // #ifndef KVP_MEMORYDATABASE_HPP
