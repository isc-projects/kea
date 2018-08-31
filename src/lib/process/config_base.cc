#include <process/config_base.h>
#include <log/logger_manager.h>
#include <log/logger_specification.h>
#include <list>

using namespace isc::log;
using namespace isc::data;

namespace isc {
namespace process {

void
ConfigBase::applyLoggingCfg() const {

    std::list<LoggerSpecification> specs;
    for (LoggingInfoStorage::const_iterator it = logging_info_.begin();
         it != logging_info_.end(); ++it) {
        specs.push_back(it->toSpec());
    }
    LoggerManager manager;
    manager.process(specs.begin(), specs.end());
}

bool
ConfigBase::equals(const ConfigBase& other) const {
    // If number of loggers is different, then configurations aren't equal.
    if (logging_info_.size() != other.logging_info_.size()) {
        return (false);
    }
    // Pass through all loggers and try to find the match for each of them
    // with the loggers from the other configuration. The order doesn't
    // matter so we can't simply compare the vectors.
    for (LoggingInfoStorage::const_iterator this_it =
             logging_info_.begin(); this_it != logging_info_.end();
         ++this_it) {
        bool match = false;
        for (LoggingInfoStorage::const_iterator other_it =
                 other.logging_info_.begin();
             other_it != other.logging_info_.end(); ++other_it) {
            if (this_it->equals(*other_it)) {
                match = true;
                break;
            }
        }
        // No match found for the particular logger so return false.
        if (!match) {
            return (false);
        }
    }

    return (true);
}

void
ConfigBase::copy(ConfigBase& other) const {
    // We will entirely replace loggers in the new configuration.
    other.logging_info_.clear();
    for (LoggingInfoStorage::const_iterator it = logging_info_.begin();
         it != logging_info_.end(); ++it) {
        other.addLoggingInfo(*it);
    }
}

ElementPtr
ConfigBase::toElement() const {
    ElementPtr result = Element::createMap();

    // Logging global map (skip if empty)
    if (!logging_info_.empty()) {
        ElementPtr logging = Element::createMap();
        // Set loggers list
        ElementPtr loggers = Element::createList();
        for (LoggingInfoStorage::const_iterator logger =
                 logging_info_.cbegin();
             logger != logging_info_.cend(); ++logger) {
            loggers->add(logger->toElement());
        }
        logging->set("loggers", loggers);
        result->set("Logging", logging);
    }

    return (result);
}

};
};
