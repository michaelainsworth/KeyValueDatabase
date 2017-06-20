#ifndef KVP_CURRENTVALUE_HPP
#define KVP_CURRENTVALUE_HPP

#include <Kvp/Common.hpp>
#include <Kvp/Value.hpp>
#include <Kvp/Atom.hpp>

KVP_NAMESPACE_BEGIN

//! \brief Contains a Value and Atom.
//!
//! A CurrentValue indicates the value in a Key/Value/Atom tuple at a
//! particular point in time (as indicated by the Atom).
class CurrentValue
{

    // ========================================================================
    // Lifecycle
    // ========================================================================

public:

    //! \brief Constructs an "empty" CurrentValue.
    //!
    //! An "empty" CurrentValue has a Value consisting of 0 bytes and an
    //! Atom containing the integer 0. It also casts to a "false" value (like
    //! calling the exists() function).
    CurrentValue();
    
    //! \brief Constructs a non-empty CurrentValue.
    //!
    //! Note that a non-empty CurrentValue CAN STILL CONTAIN A 0-BYTE VALUE
    //! AND AN ATOM CONTAINING THE INTEGER 0. However, casting it to a boolean
    //! value (or calling the exists() function) will return true.
    CurrentValue(const Value& value, const Atom& atom);

    // ========================================================================
    // Accessors
    // ========================================================================

    //! \brief A convenience function for exists().
    //!
    operator bool() const;

    //! \brief Returns true if the CurrentValue is non-empty.
    //!
    bool exists() const;

    //! \brief Returns the Value.
    //!
    const Value& value() const;

    //! \brief Returns the Atom.
    //!
    const Atom& atom() const;

    // ========================================================================
    // Variable
    // ========================================================================

private:

    bool exists_;
    Value value_;
    Atom atom_;

};

KVP_NAMESPACE_END

#endif // #ifndef KVP_CURRENTVALUE_HPP
