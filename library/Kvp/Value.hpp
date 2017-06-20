#ifndef KVP_VALUE_HPP
#define KVP_VALUE_HPP

#include <Kvp/String.hpp>
#include <Kvp/DebugString.hpp>

KVP_NAMESPACE_BEGIN

//! \brief Represents a Value stored in a Database.
//!
class Value
{

    // ========================================================================
    // Lifecycle
    // ========================================================================

public:

    //! \brief Constructs the Value.
    //!
    explicit Value(const String& value);

    // ========================================================================
    // Comparison
    // ========================================================================

public:

    //! \brief Returns true if the two Value's are equal.
    //!
    friend bool operator ==(const Value& left, const Value& right);

    // ========================================================================
    // Accessors
    // ========================================================================

public:

    //! \brief Returns the original array of bytes as a String.
    //!
    String toString() const;

    // ========================================================================
    // Debug
    // ========================================================================

public:

    //! \brief Returns a human-readable form of the value.
    //!
    DebugString toDebugString() const;

    // ========================================================================
    // Variables
    // ========================================================================

private:

    String value_;

};

KVP_NAMESPACE_END

#endif // #ifndef KVP_VALUE_HPP
