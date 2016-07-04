#ifndef SQL_COMMON_H
#define SQL_COMMON_H

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/member.hpp>

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace isc {
namespace dhcp {


/// @brief Used to map server data types with internal backend storage data
/// types.
enum ExchangeDataType {
    EXCHANGE_DATA_TYPE_NONE,
    EXCHANGE_DATA_TYPE_BOOL,
    EXCHANGE_DATA_TYPE_INT32,
    EXCHANGE_DATA_TYPE_INT64,
    EXCHANGE_DATA_TYPE_TIMESTAMP,
    EXCHANGE_DATA_TYPE_STRING,
    EXCHANGE_DATA_TYPE_BYTES
};

/// @brief Used to specify the direction of the data exchange between the
/// database and the server.
enum ExchangeDataTypeIO {
    EXCHANGE_DATA_TYPE_IO_IN,
    EXCHANGE_DATA_TYPE_IO_OUT,
    EXCHANGE_DATA_TYPE_IO_IN_OUT
};

/// @brief Used to map the column name with internal backend storage data types.
struct ExchangeColumnInfo {
    ExchangeColumnInfo () : name_(""), index_(0), type_io_(EXCHANGE_DATA_TYPE_IO_IN),
                            type_(EXCHANGE_DATA_TYPE_NONE) {};
    ExchangeColumnInfo (const char* name, const uint32_t index,
        const ExchangeDataTypeIO type_io, const ExchangeDataType type) :
        name_(name), index_(index), type_io_(type_io), type_(type) {};
    std::string name_;
    uint32_t index_;
    ExchangeDataTypeIO type_io_;
    ExchangeDataType type_;
};

typedef boost::shared_ptr<ExchangeColumnInfo> ExchangeColumnInfoPtr;

typedef boost::multi_index_container<
    // Container comprises elements of ExchangeColumnInfoPtr type.
    ExchangeColumnInfoPtr,
    // Here we start enumerating various indexes.
    boost::multi_index::indexed_by<
        // Sequenced index allows accessing elements in the same way as elements
        // in std::list.
        // Sequenced is an index #0.
        boost::multi_index::sequenced<>,
        // Start definition of index #1.
        boost::multi_index::hashed_non_unique<
            boost::multi_index::member<
                ExchangeColumnInfo,
                std::string,
                &ExchangeColumnInfo::name_
             >
        >,
        // Start definition of index #2.
        boost::multi_index::hashed_non_unique<
            boost::multi_index::member<
                ExchangeColumnInfo,
                uint32_t,
                &ExchangeColumnInfo::index_
            >
        >
    >
> ExchangeColumnInfoContainer;

/// Pointer to the ExchangeColumnInfoContainer object.
typedef boost::shared_ptr<ExchangeColumnInfoContainer> ExchangeColumnInfoContainerPtr;
/// Type of the index #1 - name.
typedef ExchangeColumnInfoContainer::nth_index<1>::type ExchangeColumnInfoContainerName;
/// Pair of iterators to represent the range of ExchangeColumnInfo having the
/// same name value. The first element in this pair represents
/// the beginning of the range, the second element represents the end.
typedef std::pair<ExchangeColumnInfoContainerName::const_iterator,
                  ExchangeColumnInfoContainerName::const_iterator> ExchangeColumnInfoContainerNameRange;
/// Type of the index #2 - index.
typedef ExchangeColumnInfoContainer::nth_index<2>::type ExchangeColumnInfoContainerIndex;
/// Pair of iterators to represent the range of ExchangeColumnInfo having the
/// same index value. The first element in this pair represents
/// the beginning of the range, the second element represents the end.
typedef std::pair<ExchangeColumnInfoContainerIndex::const_iterator,
                  ExchangeColumnInfoContainerIndex::const_iterator> ExchangeColumnInfoContainerIndexRange;

class SqlExchange {
public:
    SqlExchange () {}
    virtual ~SqlExchange() {}
    ExchangeColumnInfoContainer parameters_;   ///< Column names and types
};

} //dhcp
} //isc

#endif // SQL_COMMON_H
