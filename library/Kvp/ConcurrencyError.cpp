#include <Kvp/ConcurrencyError.hpp>

KVP_NAMESPACE_BEGIN

ConcurrencyError::ConcurrencyError(const String& message)
    : Error(message)
{}

KVP_NAMESPACE_END

