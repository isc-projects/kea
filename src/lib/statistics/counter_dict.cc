#include <cassert>
#include <stdexcept>
#include <iterator>
#include <map>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <statistics/counter_dict.h>

namespace {
typedef boost::shared_ptr<isc::statistics::Counter> CounterPtr;
typedef std::map<std::string, CounterPtr> DictionaryMap;
}

namespace isc {
namespace statistics {

// Implementation detail class for CounterDictionary::ConstIterator
class CounterDictionaryConstIteratorImpl;

class CounterDictionaryImpl : boost::noncopyable {
private:
    DictionaryMap dictionary_;
    std::vector<std::string> elements_;
    const size_t items_;
    // Default constructor is forbidden; number of counter items must be
    // specified at the construction of this class.
    CounterDictionaryImpl();
public:
    CounterDictionaryImpl(const size_t items);
    ~CounterDictionaryImpl();
    void addElement(const std::string& name);
    void deleteElement(const std::string& name);
    Counter& getElement(const std::string& name);
public:
    CounterDictionaryConstIteratorImpl begin() const;
    CounterDictionaryConstIteratorImpl end() const;
};

// Constructor with number of items
CounterDictionaryImpl::CounterDictionaryImpl(const size_t items) :
    items_(items)
{
    // The number of items must not be 0
    if (items == 0) {
        isc_throw(isc::InvalidParameter, "Items must not be 0");
    }
}

// Destructor
CounterDictionaryImpl::~CounterDictionaryImpl() {}

void
CounterDictionaryImpl::addElement(const std::string& name) {
    // throw if the element already exists
    if (dictionary_.count(name) != 0) {
        isc_throw(isc::InvalidParameter,
                  "Element " << name << " already exists");
    }
    assert(items_ != 0);
    // Create a new Counter and add to the map
    dictionary_.insert(
        DictionaryMap::value_type(name, CounterPtr(new Counter(items_))));
}

void
CounterDictionaryImpl::deleteElement(const std::string& name) {
    size_t result = dictionary_.erase(name);
    if (result != 1) {
        // If an element with specified name does not exist, throw
        // isc::OutOfRange.
        isc_throw(isc::OutOfRange, "Element " << name << " does not exist");
    }
}

Counter&
CounterDictionaryImpl::getElement(const std::string& name) {
    try {
        return (*(dictionary_.at(name)));
    } catch (const std::out_of_range&) {
        // If an element with specified name does not exist, throw
        // isc::OutOfRange.
        isc_throw(isc::OutOfRange, "Element " << name << " does not exist");
    }
}

// Constructor
// Initialize impl_
CounterDictionary::CounterDictionary(const size_t items) :
    impl_(new CounterDictionaryImpl(items))
{}

// Destructor
// impl_ will be freed automatically with scoped_ptr
CounterDictionary::~CounterDictionary() {}

void
CounterDictionary::addElement(const std::string& name) {
    impl_->addElement(name);
}

void
CounterDictionary::deleteElement(const std::string& name) {
    impl_->deleteElement(name);
}

Counter&
CounterDictionary::getElement(const std::string& name) const {
    return (impl_->getElement(name));
}

Counter&
CounterDictionary::operator[](const std::string& name) const {
    return (impl_->getElement(name));
}

// Implementation detail class for CounterDictionary::ConstIterator
class CounterDictionaryConstIteratorImpl {
    public:
        CounterDictionaryConstIteratorImpl();
        ~CounterDictionaryConstIteratorImpl();
        CounterDictionaryConstIteratorImpl(
            const CounterDictionaryConstIteratorImpl &other);
        CounterDictionaryConstIteratorImpl &operator=(
            const CounterDictionaryConstIteratorImpl &source);
        CounterDictionaryConstIteratorImpl(
            DictionaryMap::const_iterator iterator);
    public:
        void increment();
        const CounterDictionary::ConstIterator::value_type&
            dereference() const;
        bool equal(const CounterDictionaryConstIteratorImpl& other) const;
    private:
        DictionaryMap::const_iterator iterator_;
};

CounterDictionaryConstIteratorImpl::CounterDictionaryConstIteratorImpl() {}

CounterDictionaryConstIteratorImpl::~CounterDictionaryConstIteratorImpl() {}

// Copy constructor: deep copy of iterator_
CounterDictionaryConstIteratorImpl::CounterDictionaryConstIteratorImpl(
    const CounterDictionaryConstIteratorImpl &other) :
    iterator_(other.iterator_)
{}

// Assignment operator: deep copy of iterator_
CounterDictionaryConstIteratorImpl &
CounterDictionaryConstIteratorImpl::operator=(
    const CounterDictionaryConstIteratorImpl &source)
{
    iterator_ = source.iterator_;
    return (*this);
}

// Constructor from implementation detail DictionaryMap::const_iterator
CounterDictionaryConstIteratorImpl::CounterDictionaryConstIteratorImpl(
    DictionaryMap::const_iterator iterator) :
    iterator_(iterator)
{}

CounterDictionaryConstIteratorImpl
CounterDictionaryImpl::begin() const {
    return (CounterDictionaryConstIteratorImpl(dictionary_.begin()));
}

CounterDictionaryConstIteratorImpl
CounterDictionaryImpl::end() const {
    return (CounterDictionaryConstIteratorImpl(dictionary_.end()));
}

void
CounterDictionaryConstIteratorImpl::increment() {
    ++iterator_;
    return;
}

const CounterDictionary::ConstIterator::value_type&
CounterDictionaryConstIteratorImpl::dereference() const {
    return (iterator_->first);
}

bool
CounterDictionaryConstIteratorImpl::equal(
    const CounterDictionaryConstIteratorImpl& other) const
{
    return (iterator_ == other.iterator_);
}

CounterDictionary::ConstIterator
CounterDictionary::begin() const {
    return (CounterDictionary::ConstIterator(
               CounterDictionaryConstIteratorImpl(impl_->begin())));
}

CounterDictionary::ConstIterator
CounterDictionary::end() const {
    return (CounterDictionary::ConstIterator(
               CounterDictionaryConstIteratorImpl(impl_->end())));
}

CounterDictionary::ConstIterator::ConstIterator() :
    impl_(new CounterDictionaryConstIteratorImpl())
{}

CounterDictionary::ConstIterator::~ConstIterator() {}

// Copy constructor: deep copy of impl_
CounterDictionary::ConstIterator::ConstIterator(
    const CounterDictionary::ConstIterator& source) :
    impl_(new CounterDictionaryConstIteratorImpl(*(source.impl_)))
{}

// Assignment operator: deep copy of impl_
CounterDictionary::ConstIterator &
CounterDictionary::ConstIterator::operator=(
    const CounterDictionary::ConstIterator &source)
{
    *impl_ = *source.impl_;
    return (*this);
}

// The constructor from implementation detail
CounterDictionary::ConstIterator::ConstIterator(
    const CounterDictionaryConstIteratorImpl& source) :
    impl_(new CounterDictionaryConstIteratorImpl(source))
{}

const CounterDictionary::ConstIterator::value_type&
CounterDictionary::ConstIterator::dereference() const
{
    return (impl_->dereference());
}

bool
CounterDictionary::ConstIterator::equal(
    CounterDictionary::ConstIterator const& other) const
{
    return (impl_->equal(*(other.impl_)));
}

void
CounterDictionary::ConstIterator::increment() {
    impl_->increment();
    return;
}

}   // namespace statistics
}   // namespace isc
