#ifndef KVP_REALDATABASE_HPP
#define KVP_REALDATABASE_HPP

#include <Kvp/Common.hpp>
#include <Kvp/CurrentValue.hpp>
#include <Kvp/Key.hpp>
#include <Kvp/Value.hpp>

KVP_NAMESPACE_BEGIN

//! \brief Represents a "real" database.
//!
//! RealDatabase is an abstract base class, meant to be derived by full
//! key/value database implementations.
//!
//! Currently, there is only one implementation - MemoryDatabase, which is
//! basically a wrapper around a std::map<std::string,std::string>.
//!
//! See the documentation for the Database class on how member functions
//! should behave (e.g., in terms of exceptions, for example).
class RealDatabase
{

    // ========================================================================
    // Lifecycle
    // ========================================================================

public:

    //! \brief Dummy constructor.
    //!
    RealDatabase();

    //! \brief The destructor is virtual for the sake of the concrete classes.
    //!
    virtual ~RealDatabase();

private:

    // Noncopyable
    RealDatabase(const RealDatabase& that) = delete;
    RealDatabase(RealDatabase&& that) = delete;
    RealDatabase& operator =(const RealDatabase& that) = delete;
    RealDatabase& operator =(RealDatabase&& that) = delete;

    // ========================================================================
    // Accessors
    // ========================================================================

public:

    virtual CurrentValue read(const Key& key) const = 0;

    // ========================================================================
    // Mutators
    // ========================================================================

public:

    virtual void create
    (
        const Key& key,
        const Value& value,
        const Atom& atom
    ) = 0;

    virtual void update
    (
        const Key& key,
        const Value& value,
        const Atom& atom,
        const Atom& condition
    ) = 0;

    virtual void delet(const Key& key, const Atom& condition) = 0;

    // ========================================================================
    // Helpers
    // ========================================================================

public:

    virtual void debug(std::ostream& outs) const = 0;

};

KVP_NAMESPACE_END

#endif // #ifndef KVP_REALDATABASE_HPP
