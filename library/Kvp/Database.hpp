#ifndef KVP_DATABASE_HPP
#define KVP_DATABASE_HPP

#include <Kvp/Common.hpp>
#include <Kvp/CurrentValue.hpp>
#include <Kvp/Key.hpp>
#include <Kvp/RealDatabasePointer.hpp>

KVP_NAMESPACE_BEGIN

//! \brief Represents a collection of Key/Value/Atom tuples.
//!
//! A Database has CRUD operations - Create, Read, Update and Delete.
//! Transactions are not supported. That is, when calling more than one
//! non-const member function (create() then update() for example), it is
//! entirely possible for the second call to fail. However, within the
//! scope of a single non-const member function, it should fully succeed
//! or fully fail - the data should never be corrupted. Implementing
//! "transactions" on top of a key value store is possible. For example, by
//! using event sourcing, where a group of "events" are committed as a 
//! single unit.
//!
//! The Database classes uses the "pointer to implementation" idiom in order
//! to hide the implemenation. This means that you can freely pass Database
//! objects around.
class Database
{

    // ========================================================================
    // Lifecycle
    // ========================================================================

public:

    //! \brief Instantiates an empty MemoryDatabase.
    //!
    Database();

    // ========================================================================
    // Accessors
    // ========================================================================

public:

    //! \brief Returns the Value and Atom identified by Key.
    //!
    //! This method should NOT throw an exception if the key does not exist.
    //! Instead, it should return an empty CurrentValue (i.e., one where
    //! exists() returns false).
    CurrentValue read(const Key& key) const;

    // ========================================================================
    // Mutators
    // ========================================================================

public:

    //! \brief Creates a new Key/Value/Atom tuple in the database.
    //!
    //! This method will throw a ConcurencyError if the key already exists.
    void create(const Key& key, const Value& value, const Atom& atom);

    //! \brief Updates the Key/Value/Atom tuple in the database.
    //!
    //! This method will throw a ConcurrencyError if the key does not already
    //! exist, or if condition does not match the atom of the current
    //! tuple.
    void update
    (
        const Key& key,
        const Value& value,
        const Atom& atom,
        const Atom& condition
    );

    //! \brief Deletes the Key/Value/Atom tuple from the database.
    //!
    //! This method will throw a ConcurrencyError if the Key does not already
    //! exist, or if condition does not match the atom of the current value.
    void delet(const Key& key, const Atom& condition);

    // ========================================================================
    // Helpers
    // ========================================================================

public:

    //! \brief Writes the Database contents in human-readable form.
    //!
    void debug(std::ostream& outs) const;

    // ========================================================================
    // Variables
    // ========================================================================

private:

    //! \brief Contains a pointer to a concrete Database implementation.
    //!
    RealDatabasePointer pDatabase_;

};

KVP_NAMESPACE_END

#endif // #ifndef KVP_DATABASE_HPP
