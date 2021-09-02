// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PARKING_LOTS_H
#define PARKING_LOTS_H

#include <exceptions/exceptions.h>
#include <boost/any.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include <functional>
#include <iostream>
#include <sstream>
#include <list>
#include <unordered_map>
#include <mutex>
#include <thread>

namespace isc {
namespace hooks {

/// @brief Parking lot for objects, e.g. packets, for a hook point.
///
/// Callouts may instruct the servers to "park" processed packets, i.e. suspend
/// their processing until explicitly unparked. This is useful in cases when
/// callouts need to perform asynchronous operations related to the packet
/// processing and the packet must not be further processed until the
/// asynchronous operations are completed. While the packet is parked, the
/// new packets can be processed, so the server remains responsive to the
/// new requests.
///
/// Parking lots are created per hook point, so the callouts installed on the
/// particular hook point only have access to the parking lots dedicated to
/// them.
///
/// The parking lot object supports 5 actions: "park", "reference",
/// "dereference", "unpark", and "drop".
///
/// In the typical case, the server parks the object and the callouts reference
/// and unpark the objects. Therefore, the @ref ParkingLot object is not passed
/// directly to the callouts. Instead, a ParkingLotHandle object is provided
/// to the callout, which only provides access to "reference", "dereference",
/// and "unpark" operations.
///
/// Parking an object is performed, proactively by the server, before callouts
/// are invoked.  Referencing (and dereferencing) an object is performed by the
/// callouts before the @c CalloutHandle::NEXT_STEP_PARK is returned to the
/// server.
///
/// Trying to reference (or deference) and unparked object will result
/// in error. Referencing (reference counting) is an important part of the
/// parking mechanism, which allows multiple callouts, installed on the same
/// hook point, to perform asynchronous operations and guarantees that the
/// object remains parked until all those asynchronous operations complete.
/// Each such callout must call @c unpark() when it desires the object to
/// be unparked, but the object will only be unparked when all callouts call
/// this function, i.e. when all callouts signal completion of their respective
/// asynchronous operations.
///
/// Dereferencing, decrements the reference count without invoking the unpark
/// callback.  This allows hook callouts to proactively reference the object
/// in a callout and then cancel the reference should further processing
/// deem it the reference unnecessary.
///
/// The types of the parked objects provided as T parameter of respective
/// functions are most often shared pointers. One should not use references
/// to parked objects nor references to shared pointers to avoid premature
/// destruction of the parked objects.
class ParkingLot {
public:
    /// @brief Parks an object.
    ///
    /// @tparam Type of the parked object.
    /// @param parked_object object to be parked, e.g. pointer to a packet.
    /// @param unpark_callback callback function to be invoked when the object
    /// is unparked.
    /// @throw InvalidOperation if this object has already been parked.
    template<typename T>
    void park(T parked_object, std::function<void()> unpark_callback) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = find(parked_object);
        if (it != parking_.end()) {
            isc_throw(InvalidOperation, "object is already parked!");
        }

        // Add the object to the parking lot. At this point refcount = 0.
        ParkingInfo pinfo(parked_object, unpark_callback);
        parking_[makeKey(parked_object)] = pinfo;
    }

    /// @brief Increases reference counter for the parked object.
    ///
    /// This method is called by the callouts to increase a reference count
    /// on the object to be parked. It may only be called after the object
    /// has been parked
    ///
    /// @tparam Type of the parked object.
    /// @param parked_object object which will be parked.
    /// @return the integer number of references for this object.
    template<typename T>
    int reference(T parked_object) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = find(parked_object);
        if (it == parking_.end()) {
            isc_throw(InvalidOperation, "cannot reference an object"
                      " that has not been parked.");
        }

        // Bump and return the reference count
        return (++it->second.refcount_);
    }

    /// @brief Decreases the reference counter for the parked object.
    ///
    /// This method is called by the callouts to decrease the reference count
    /// on a parked object.
    ///
    /// @tparam Type of the parked object.
    /// @param parked_object parked object whose count should be reduced.
    /// @return the integer number of references for this object.
    template<typename T>
    int dereference(T parked_object) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = find(parked_object);
        if (it == parking_.end()) {
            isc_throw(InvalidOperation, "cannot dereference an object"
                      " that has not been parked.");
        }

        // Decrement and return the reference count.
        return (--it->second.refcount_);
    }

    /// @brief Signals that the object should be unparked.
    ///
    /// If the specified object is parked in this parking lot, the reference
    /// count is decreased as a result of this method. If the reference count
    /// is 0, the object is unparked and the callback is invoked. Typically, the
    /// callback points to a function which resumes processing of a packet.
    ///
    /// @tparam Type of the parked object.
    /// @param parked_object parked object to be unparked.
    /// @param force boolean value indicating if the reference counting should
    /// be ignored and the object should be unparked immediately.
    /// @return false if the object couldn't be unparked because there is
    /// no such object, true otherwise.
    template<typename T>
    bool unpark(T parked_object, bool force = false) {
        // Initialize as the empty function.
        std::function<void()> cb;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            auto it = find(parked_object);
            if (it == parking_.end()) {
                // No such parked object.
                return (false);
            }

            if (force) {
                it->second.refcount_ = 0;
            } else {
                --it->second.refcount_;
            }

            if (it->second.refcount_ <= 0) {
                // Unpark the packet and set the callback.
                cb = it->second.unpark_callback_;
                parking_.erase(it);
            }
        }

        // Invoke the callback if not empty.
        if (cb) {
            cb();
        }

        // Parked object found, so return true to indicate that the
        // operation was successful. It doesn't necessarily mean
        // that the object was unparked, but at least the reference
        // count was decreased.
        return (true);
    }

    /// @brief Removes parked object without calling a callback.
    ///
    /// @tparam Type of the parked object.
    /// @param parked_object parked object to be removed.
    /// @return false if the object couldn't be removed because there is
    /// no such object, true otherwise.
    template<typename T>
    bool drop(T parked_object) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = find(parked_object);
        if (it != parking_.end()) {
            // Parked object found.
            parking_.erase(it);
            return (true);
        }

        // No such object.
        return (false);
    }

    /// @brief Returns the current number of objects.
    size_t size() {
        std::lock_guard<std::mutex> lock(mutex_);
        return (parking_.size());
    }

public:

    /// @brief Holds information about parked object.
    struct ParkingInfo {
        /// @brief The parked object.
        boost::any parked_object_;

        /// @brief The pointer to callback.
        std::function<void()> unpark_callback_;

        /// @brief The current reference count.
        int refcount_;

        /// @brief Constructor.
        ///
        /// Default constructor.
        ParkingInfo() : refcount_(0) {}

        /// @brief Constructor.
        ///
        /// @param parked_object object being parked.
        /// @param callback pointer to the callback.
        ParkingInfo(const boost::any& parked_object,
                    std::function<void()> callback = 0)
            : parked_object_(parked_object), unpark_callback_(callback),
              refcount_(0) {}

        /// @brief Update parking information.
        ///
        /// @param parked_object parked object.
        /// @param callback pointer to the callback.
        void update(const boost::any& parked_object,
                    std::function<void()> callback) {
            parked_object_ = parked_object;
            unpark_callback_ = callback;
        }
    };

private:

    /// @brief Map which stores parked objects.
    typedef std::unordered_map<std::string, ParkingInfo> ParkingInfoList;

    /// @brief Type of the iterator in the list of parked objects.
    typedef ParkingInfoList::iterator ParkingInfoListIterator;

    /// @brief Container holding parked objects for this parking lot.
    ParkingInfoList parking_;

    /// @brief Construct the key for a given parked object.
    ///
    /// @tparam T parked object type.
    /// @param parked_object object from which the key should be constructed.
    /// @return string containing the object's key.
    template<typename T>
    std::string makeKey(T parked_object) {
        std::stringstream ss;
        ss << boost::any_cast<T>(parked_object);
        return (ss.str());
    }

    /// @brief Search for the information about the parked object.
    ///
    /// @tparam T parked object type.
    /// @param parked_object object for which to search.
    /// @return Iterator pointing to the parked object, or @c parking_.end()
    /// if no such object found.
    template<typename T>
    ParkingInfoListIterator find(T parked_object) {
        return (parking_.find(makeKey(parked_object)));
    }

    /// @brief The mutex to protect parking lot internal state.
    ///
    /// All public methods must enter of lock guard with the mutex
    /// before any access to the @c parking_ member.
    std::mutex mutex_;
};

/// @brief Type of the pointer to the parking lot.
typedef boost::shared_ptr<ParkingLot> ParkingLotPtr;

/// @brief Provides a limited view to the @c ParkingLot.
///
/// The handle is provided to the callouts which can reference and unpark
/// parked objects. The callouts should not park objects, therefore this
/// operation is not available.
///
/// The types of the parked objects provided as T parameter of respective
/// functions are most often shared pointers. One should not use references
/// to parked objects nor references to shared pointers to avoid premature
/// destruction of the parked objects.
class ParkingLotHandle {
public:

    /// @brief Constructor.
    ///
    /// @param parking_lot pointer to the parking lot for which the handle is
    /// created.
    ParkingLotHandle(const ParkingLotPtr& parking_lot)
        : parking_lot_(parking_lot) {
    }

    /// @brief Increases reference counter for the parked object.
    ///
    /// This method is called by the callouts to increase a reference count
    /// on the object to be parked. It must be called before the object is
    /// actually parked.
    ///
    /// @tparam Type of the parked object.
    /// @param parked_object object which will be parked.
    /// @return new reference count as an integer
    template<typename T>
    int reference(T parked_object) {
        return (parking_lot_->reference(parked_object));
    }

    /// @brief Decreases the reference counter for the parked object.
    ///
    /// This method is called by the callouts to decrease the reference count
    /// of a parked object.
    ///
    /// @tparam Type of the parked object.
    /// @param parked_object object which will be parked.
    /// @return new reference count as an integer
    template<typename T>
    int dereference(T parked_object) {
        return (parking_lot_->dereference(parked_object));
    }

    /// @brief Signals that the object should be unparked.
    ///
    /// If the specified object is parked in this parking lot, the reference
    /// count is decreased as a result of this method. If the reference count
    /// is 0, the object is unparked and the callback is invoked. Typically, the
    /// callback points to a function which resumes processing of a packet.
    ///
    /// @tparam Type of the parked object.
    /// @param parked_object parked object to be unparked.
    /// @return false if the object couldn't be unparked because there is
    /// no such object, true otherwise.
    template<typename T>
    bool unpark(T parked_object) {
        return (parking_lot_->unpark(parked_object));
    }

    /// @brief Removes parked object without calling a callback.
    ///
    /// It ignores any reference counts on the parked object.
    ///
    /// @tparam Type of the parked object.
    /// @param parked_object parked object to be removed.
    /// @return false if the object couldn't be removed because there is
    /// no such object, true otherwise.
    template<typename T>
    bool drop(T parked_object) {
        return (parking_lot_->drop(parked_object));
    }

private:

    /// @brief Parking lot to which this handle points.
    ParkingLotPtr parking_lot_;

};

/// @brief Pointer to the parking lot handle.
typedef boost::shared_ptr<ParkingLotHandle> ParkingLotHandlePtr;

/// @brief Collection of parking lots for various hook points.
class ParkingLots {
public:

    /// @brief Removes all parked objects.
    ///
    /// It doesn't invoke callbacks associated with the removed objects.
    void clear() {
        std::lock_guard<std::mutex> lock(mutex_);
        parking_lots_.clear();
    }

    /// @brief Returns pointer to the parking lot for a hook points.
    ///
    /// If the parking lot for the specified hook point doesn't exist, it is
    /// created.
    ///
    /// @param hook_index index of the hook point with which the parking
    /// lot is associated.
    /// @return Pointer to the parking lot.
    ParkingLotPtr getParkingLotPtr(const int hook_index) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (parking_lots_.count(hook_index) == 0) {
            parking_lots_[hook_index] = boost::make_shared<ParkingLot>();
        }
        return (parking_lots_[hook_index]);
    }

private:

    /// @brief Container holding parking lots for various hook points.
    std::unordered_map<int, ParkingLotPtr> parking_lots_;

    /// @brief The mutex to protect parking lots internal state.
    std::mutex mutex_;
};

/// @brief Type of the pointer to the parking lots.
typedef boost::shared_ptr<ParkingLots> ParkingLotsPtr;

} // end of namespace hooks
} // end of namespace isc

#endif
