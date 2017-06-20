#ifndef KVP_KEY_HPP
#define KVP_KEY_HPP

#include <Kvp/String.hpp>
#include <Kvp/DebugString.hpp>

KVP_NAMESPACE_BEGIN

//! \brief Represents a unique identifier for a Value.
//!
class Key 
{

    // ========================================================================
    // Lifecycle
    // ========================================================================

public:

    //! \brief Constructs the Key from the String supplied.
    //!
    explicit Key(const String& value);

    // ========================================================================
    // Comparison
    // ========================================================================

    //! \brief Returns true if the two Key's are equal.
    //!
    friend bool operator ==(const Key& left, const Key& right);

    //! \brief Returns true if the left Key is less than the right Key.
    //!
    //! This function is primarily used for the MemoryDatabase class.
    friend bool operator <(const Key& left, const Key& right);

    // ========================================================================
    // Helper
    // ========================================================================

public:

    //! \brief Returns a human-readable form of the Key.
    //!
    DebugString toDebugString() const;

    // ========================================================================
    // Variables
    // ========================================================================

private:

    String value_;

};

KVP_NAMESPACE_END

#endif // #ifndef KVP_KEY_HPP
