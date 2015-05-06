

#ifndef CONTEXT_H
#define CONTEXT_H

#include <stats/observation.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace stats {

class StatContext {
 public:
    std::map<std::string, ObservationPtr> stats;
};

 typedef boost::shared_ptr<StatContext> StatContextPtr;

};
};

#endif // CONTEXT_H
