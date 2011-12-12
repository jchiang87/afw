// -*- lsst-c++ -*-
#ifndef AFW_TABLE_TreeIteratorBase_h_INCLUDED
#define AFW_TABLE_TreeIteratorBase_h_INCLUDED

#include "boost/iterator/iterator_facade.hpp"

#include "lsst/afw/table/detail/Access.h"
#include "lsst/afw/table/detail/RecordData.h"
#include "lsst/afw/table/RecordBase.h"

namespace lsst { namespace afw { namespace table {

struct TableImpl;

/**
 *  @brief An iterator that processes records in an order that corresponds to their
 *         parent/child relationships.
 *
 *  Because TreeIteratorBase dereferences to RecordBase, it is usually wrapped
 *  with the boost::transform_iterator adapter to return a final record class
 *  in the iterator-returning methods of a final table class.
 *
 *  @sa TreeMode
 */
class TreeIteratorBase : 
        public boost::iterator_facade<TreeIteratorBase,RecordBase,boost::forward_traversal_tag,RecordBase> 
{
public:

    TreeIteratorBase() : _record(), _mode(DEPTH_FIRST) {}

    TreeIteratorBase(
        detail::RecordData * record,
        PTR(detail::TableImpl) const & table, 
        ModificationFlags const & flags,
        TreeMode mode
    ) : _record(record, table, flags), _mode(mode)
    {}

    TreeMode getMode() const { return _mode; }

private:

    friend class boost::iterator_core_access;

    RecordBase const & dereference() const {
        assert(_record._data);
        assert(_record._table);
        return _record;
    }

    bool equal(TreeIteratorBase const & other) const { return _record == other._record; }

    void increment();

    RecordBase _record;    
    TreeMode _mode;
};

inline TreeIteratorBase RecordBase::_asTreeIterator(TreeMode mode) const {
    return TreeIteratorBase(_data, _table, *this, mode);
}

}}} // namespace lsst::afw::table

#endif // !AFW_TABLE_TreeIteratorBase_h_INCLUDED
