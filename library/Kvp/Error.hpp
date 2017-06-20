#ifndef KVP_ERROR_HPP
#define KVP_ERROR_HPP

#include <Kvp/Common.hpp>
#include <Kvp/String.hpp>
#include <stdexcept>

KVP_NAMESPACE_BEGIN

//! \brief Represents a generic error thrown by the library.
//!
//! The derived ConcurrencyError is used for concurrent access to individual
//! Key's. This, higher-level, Error class, can be used for other types of
//! errors, such as filesystem failures, for example.
class Error : public std::runtime_error
{

    // ========================================================================
    // Lifecycle
    // ========================================================================

public:

    //! \brief Constructs the error with the message supplied.
    //!
    Error(const String& message);

};

KVP_NAMESPACE_END

#endif // #ifndef KVP_ERROR_HPP
