#include <Kvp/Error.hpp>

KVP_NAMESPACE_BEGIN

Error::Error(const String& message) : std::runtime_error(message) {}

KVP_NAMESPACE_END

