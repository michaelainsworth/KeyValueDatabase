#ifndef KVP_DEBUGSTRING_HPP
#define KVP_DEBUGSTRING_HPP

#include <Kvp/String.hpp>

KVP_NAMESPACE_BEGIN

//! \brief Represents a String formatted for humans.
//!
//! Both Key's and Value's are binary strings that can contain any sequence of
//! bytes (e.g., including non-printable characters and non-UTF8 characters).
//! When debugging the system, a human-friendly form of these binary strings
//! is more appropriate, hence this class.
class DebugString 
{

    // ========================================================================
    // Lifecycle
    // ========================================================================

public:

    //! \brief Constructs the DebugString.
    //!
    explicit DebugString(const String& value);

    // ========================================================================
    // Outpu
    // ========================================================================

public:

    //! \brief Writes the human-friendly form of the string.
    //!
    friend std::ostream& operator <<
    (
        std::ostream& outs,
        const DebugString& value
    );

    // ========================================================================
    // Variables
    // ========================================================================

private:

    String value_;

};

KVP_NAMESPACE_END

#endif // #ifndef KVP_DEBUGSTRING_HPP
