#ifndef KVP_CONCURRENCYERROR_HPP
#define KVP_CONCURRENCYERROR_HPP

#include <Kvp/Common.hpp>
#include <Kvp/Error.hpp>

KVP_NAMESPACE_BEGIN

//! \brief Represents an error that occurred due to concurrent access.
//!
//! There are three mutating Database functions: create(), update() and
//! delet(). A ConcurrencyError can be thrown by any of these functions.
class ConcurrencyError : public Error
{

    // ========================================================================
    // Lifecycle
    // ========================================================================

public:

    //! \brief Constructs the error with a message.
    //!
    //! The message may contain additional error details.
    ConcurrencyError(const String& message);

};

KVP_NAMESPACE_END

#endif // #ifndef KVP_CONCURRENCYERROR_HPP
