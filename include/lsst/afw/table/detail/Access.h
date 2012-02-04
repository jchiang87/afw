// -*- lsst-c++ -*-
#ifndef AFW_TABLE_DETAIL_Access_h_INCLUDED
#define AFW_TABLE_DETAIL_Access_h_INCLUDED

#include <cstring>

#include "lsst/ndarray/Manager.h"
#include "lsst/afw/table/FieldBase.h"
#include "lsst/afw/table/Schema.h"
#include "lsst/afw/table/detail/SchemaImpl.h"

namespace lsst { namespace afw { namespace table {

class BaseRecord;
class BaseTable;

namespace detail {

/**
 *  @internal
 *
 *  @brief Friendship-aggregation class for afw/table.
 *
 *  Access is a collection of static member functions that provide access to internals of other
 *  classes.  It allows many classes to just declare Access as a friend rather than a long list of
 *  related classes.  This is less secure, but it's obviously not part of the public interface,
 *  and that's good enough.
 */
class Access {
public:

    /// @internal @brief Return a sub-field key corresponding to the nth element.
    template <typename T>
    static Key<typename Key<T>::Element> extractElement(KeyBase<T> const & kb, int n) {
        return Key<typename Key<T>::Element>(
            static_cast<Key<T> const &>(kb)._offset + n * sizeof(typename Key<T>::Element)
        );
    }

    /// @internal @brief Access to the private Key constructor.
    template <typename T>
    static Key<T> makeKey(Field<T> const & field, int offset) {
        return Key<T>(offset, field);
    }

    /// @internal @brief Access to the private Key constructor.
    static Key<Flag> makeKey(int offset, int bit) {
        return Key<Flag>(offset, bit);
    }

    /// @internal @brief Add some padding to a schema without adding a field.
    static void padSchema(Schema & schema, int bytes) {
        schema._edit();
        schema._impl->_recordSize += bytes;
    }

    /// @internal @brief Mark a schema as persistent (SchemaImpl is what inherits from Citizen).
    static void markPersistent(Schema const & schema) {
        schema._impl->markPersistent();
    }

};

}}}} // namespace lsst::afw::table::detail

#endif // !AFW_TABLE_DETAIL_Access_h_INCLUDED
