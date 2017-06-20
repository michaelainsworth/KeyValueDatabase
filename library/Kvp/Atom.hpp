#ifndef KVP_ATOM_HPP
#define KVP_ATOM_HPP

#include <Kvp/UInt32.hpp>
#include <iostream>

KVP_NAMESPACE_BEGIN

//! \brief Represents an integer that changes atomically.
//!
//! The Database is a collection Key/Value/Atom tuples. The sole purpose for
//! the Atom class is to provide the "atomicity" in ACID. That is, when calling
//! create(), update() or delet() on the Database, you need to specify an Atom
//! as a condition. The operation will only succeed if the condition matches
//! that stored on file.
//!
//! Note that while you can think of an Atom as a version, it's probably more
//! accurate to think of it as a compare-and-swap (CAS) value. This becomes
//! important because the application can set it to whatever it chooses - it
//! does not necessarily increase monotonically.
class Atom 
{

    // ========================================================================
    // Lifecycle
    // ========================================================================

public:

    //! \brief Constructs the Atom with the integer specified.
    //!
    explicit Atom(UInt32 value);

    // ========================================================================
    // Comparison
    // ========================================================================

public:

    //! \brief Compares two Atom's for equality.
    //!
    friend bool operator ==(const Atom& left, const Atom& right);

    //! \brief Compares two Atom's for inequality.
    //!
    friend bool operator !=(const Atom& left, const Atom& right);

    // ========================================================================
    // Output
    // ========================================================================

public:

    //! \brief Writes the integer representation of the Atom.
    //!
    friend std::ostream& operator <<(std::ostream& out, const Atom& atom);

    // ========================================================================
    // Variables
    // ========================================================================

private:

    UInt32 value_;

};

KVP_NAMESPACE_END

#endif // #ifndef KVP_ATOM_HPP

