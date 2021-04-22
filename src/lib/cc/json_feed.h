// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef JSON_FEED_H
#define JSON_FEED_H

#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <util/state_model.h>
#include <boost/shared_ptr.hpp>
#include <stdint.h>
#include <string>
#include <vector>

namespace isc {
namespace config {

class JSONFeed;

/// @brief Pointer to the @ref JSONFeed.
typedef boost::shared_ptr<JSONFeed> JSONFeedPtr;

/// @brief Pointer to the const @ref JSONFeed.
typedef boost::shared_ptr<const JSONFeed> ConstJSONFeedPtr;

/// @brief A generic exception thrown upon an error in the @ref JSONFeed.
class JSONFeedError : public Exception {
public:
    JSONFeedError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief State model for asynchronous read of data in JSON format.
///
/// Kea control channel uses stream sockets for forwarding commands received
/// by the Kea Control Agent to respective Kea services. The responses may
/// contain large amounts of data (e.g. lease queries may return thousands
/// of leases). Such responses rarely fit into a single data buffer and
/// require multiple calls to receive/read or asynchronous receive/read.
///
/// A receiver performing multiple reads from a socket must be able to
/// locate the boundaries of the command within the data stream. The
/// @ref JSONFeed state model solves this problem.
///
/// When the partial data is read from the stream socket it should be provided
/// to the @ref JSONFeed using @ref JSONFeed::postBuffer and then the
/// @ref JSONFeed::poll should be called to start processing the received
/// data. The actual JSON structure can be preceded by whitespaces. When first
/// occurrence of one of the '{' or '[' characters is found in the stream it is
/// considered a beginning of the JSON structure. The model includes an internal
/// counter of new '{' and '[' occurrences. The counter increases one of these
/// characters is found. When any of the '}' or ']' is found, the counter
/// is decreased. When the counter is decreased to 0 it indicates that the
/// entire JSON structure has been received and processed.
///
/// As '{', '}', '[' and ']' can be embedded in JSON strings two states
/// for strings and escape in strings are required. Note the processing
/// of escapes is greatly simplified compared to ECMA 404 figure 5.
///
/// Added support for '#' to end of line (bash), '//' to end of line (C++)
/// and '/*' to '*/' (C) comments both before JSON and inside JSON.

/// Note that this mechanism doesn't check if the JSON structure is well
/// formed. It merely detects the end of the JSON structure if this structure
/// is well formed. The structure is validated when @ref JSONFeed::toElement
/// is called to retrieve the data structures encapsulated with
/// @ref isc::data::Element objects.
class JSONFeed : public util::StateModel {
public:

    /// @name States supported by the @ref JSONFeed
    ///
    //@{

    /// @brief State indicating a beginning of a feed.
    static const int RECEIVE_START_ST = SM_DERIVED_STATE_MIN + 1;

    /// @brief Skipping whitespaces before actual JSON.
    static const int WHITESPACE_BEFORE_JSON_ST = SM_DERIVED_STATE_MIN + 2;

    /// @brief Skipping an end-of-line comment before actual JSON.
    static const int EOL_COMMENT_BEFORE_JSON_ST = SM_DERIVED_STATE_MIN + 3;

    /// @brief Starting one of the comments beginning with a slash before actual JSON.
    static const int START_COMMENT_BEFORE_JSON_ST = SM_DERIVED_STATE_MIN + 4;

    /// @brief Skipping a C style comment before actual JSON.
    static const int C_COMMENT_BEFORE_JSON_ST = SM_DERIVED_STATE_MIN + 5;

    /// @brief Stopping a C style comment before actual JSON.
    static const int STOP_COMMENT_BEFORE_JSON_ST = SM_DERIVED_STATE_MIN + 6;

    /// @brief Found first opening brace or square bracket.
    static const int JSON_START_ST = SM_DERIVED_STATE_MIN + 7;

    /// @brief Parsing JSON.
    static const int INNER_JSON_ST = SM_DERIVED_STATE_MIN + 8;

    /// @brief Parsing JSON string.
    static const int STRING_JSON_ST = SM_DERIVED_STATE_MIN + 9;

    /// @brief JSON escape next character.
    static const int ESCAPE_JSON_ST = SM_DERIVED_STATE_MIN + 10;

    /// @brief Skipping an end-of-line comment.
    static const int EOL_COMMENT_ST = SM_DERIVED_STATE_MIN + 11;

    /// @brief Starting one of the comments beginning with a slash.
    static const int START_COMMENT_ST = SM_DERIVED_STATE_MIN + 12;

    /// @brief Skipping a C style comment.
    static const int C_COMMENT_ST = SM_DERIVED_STATE_MIN + 13;

    /// @brief Stopping a C style comment.
    static const int STOP_COMMENT_ST = SM_DERIVED_STATE_MIN + 14;

    /// @brief Found last closing brace or square bracket.
    static const int JSON_END_ST = SM_DERIVED_STATE_MIN + 15;

    /// @brief Found opening and closing brace or square bracket.
    ///
    /// This doesn't however indicate that the JSON is well formed. It
    /// only means that matching closing brace or square bracket was
    /// found.
    static const int FEED_OK_ST = SM_DERIVED_STATE_MIN + 100;

    /// @brief Invalid syntax detected.
    ///
    /// For example, non matching braces or invalid characters found.
    static const int FEED_FAILED_ST = SM_DERIVED_STATE_MIN + 101;

    //@}


    /// @name Events used during data processing.
    ///
    //@{

    /// @brief Chunk of data successfully read and parsed.
    static const int DATA_READ_OK_EVT = SM_DERIVED_EVENT_MIN + 1;

    /// @brief Unable to proceed with parsing until new data is provided.
    static const int NEED_MORE_DATA_EVT = SM_DERIVED_EVENT_MIN + 2;

    /// @brief New data provided and parsing should continue.
    static const int MORE_DATA_PROVIDED_EVT = SM_DERIVED_EVENT_MIN + 3;

    /// @brief Found opening brace and the matching closing brace.
    static const int FEED_OK_EVT = SM_DERIVED_EVENT_MIN + 100;

    /// @brief Invalid syntax detected.
    static const int FEED_FAILED_EVT = SM_DERIVED_EVENT_MIN + 101;

    //@}

    /// @brief Constructor.
    JSONFeed();

    /// @brief Initializes state model.
    ///
    /// Initializes events and states. It sets the model to @c RECEIVE_START_ST
    /// and the next event to @c START_EVT.
    void initModel();

    /// @brief Runs the model as long as data is available.
    ///
    /// It processes the input data character by character until it reaches the
    /// end of the input buffer, in which case it returns. The next event is set
    /// to @c NEED_MORE_DATA_EVT to indicate the need for providing additional
    /// data using @ref JSONFeed::postBuffer. This function also returns when
    /// the end of the JSON structure has been detected or when an error has
    /// occurred.
    void poll();

    /// @brief Checks if the model needs additional data to continue.
    ///
    /// The caller can use this method to check if the model expects additional
    /// data to be provided to finish processing input data.
    ///
    /// @return true if more data is needed, false otherwise.
    bool needData() const;

    /// @brief Checks if the data have been successfully processed.
    bool feedOk() const;

    /// @brief Returns error string when data processing has failed.
    std::string getErrorMessage() const {
        return (error_message_);
    }

    /// @brief Returns the text parsed into the buffer.
    std::string getProcessedText() const {
        return (output_);
    }

    /// @brief Returns processed data as a structure of @ref isc::data::Element
    /// objects.
    ///
    /// @throw JSONFeedError if the received JSON is not well formed.
    data::ElementPtr toElement() const;

    /// @brief Receives additional data read from a data stream.
    ///
    /// A caller invokes this method to pass additional chunk of data received
    /// from the stream.
    ///
    /// @param buf Pointer to a buffer holding additional input data.
    /// @param buf_size Size of the data in the input buffer.
    void postBuffer(const void* buf, const size_t buf_size);


private:

    /// @brief Make @ref runModel private to make sure that the caller uses
    /// @ref poll method instead.
    using StateModel::runModel;

    /// @brief Define events used by the feed.
    virtual void defineEvents();

    /// @brief Verifies events used by the feed.
    virtual void verifyEvents();

    /// @brief Defines states of the feed.
    virtual void defineStates();

    /// @brief Transition to failure state.
    ///
    /// This method transitions the model to @ref FEED_FAILED_ST and
    /// sets next event to FEED_FAILED_EVT.
    ///
    /// @param error_msg Error message explaining the failure.
    void feedFailure(const std::string& error_msg);

    /// @brief A method called when state model fails.
    ///
    /// @param explanation Error message explaining the reason for failure.
    virtual void onModelFailure(const std::string& explanation);

    /// @brief Retrieves next byte of data from the buffer.
    ///
    /// During normal operation, when there is no more data in the buffer,
    /// the NEED_MORE_DATA_EVT is set as next event to signal the need for
    /// calling @ref JSONFeed::postBuffer.
    ///
    /// @throw JSONFeedError If current event is already set to
    /// NEED_MORE_DATA_EVT or MORE_DATA_PROVIDED_EVT. In the former case, it
    /// indicates that the caller failed to provide new data using
    /// @ref JSONFeed::postBuffer. The latter case is highly unlikely
    /// as it indicates that no new data were provided but the state of the
    /// parser was changed from NEED_MORE_DATA_EVT or the data were provided
    /// but the data buffer is empty. In both cases, it is a programming
    /// error.
    char getNextFromBuffer();

    /// @brief This method is called when invalid event occurred in a particular
    /// state.
    ///
    /// This method simply throws @ref JSONFeedError informing about invalid
    /// event occurring for the particular state. The error message includes
    /// the name of the handler in which the exception has been thrown.
    /// It also includes the event which caused the exception.
    ///
    /// @param handler_name Name of the handler in which the exception is
    /// thrown.
    /// @param event An event which caused the exception.
    ///
    /// @throw JSONFeedError.
    void invalidEventError(const std::string& handler_name,
                           const unsigned int event);

    /// @brief Tries to read next byte from buffer.
    ///
    /// @param [out] next A reference to the variable where read data should be
    /// stored.
    ///
    /// @return true if character was successfully read, false otherwise.
    bool popNextFromBuffer(char& next);

    /// @name State handlers.
    ///
    //@{

    /// @brief Handler for RECEIVE_START_ST.
    void receiveStartHandler();

    /// @brief Handler for WHITESPACE_BEFORE_JSON_ST.
    void whiteSpaceBeforeJSONHandler();

    /// @brief Handler for EOL_COMMENT_BEFORE_JSON_ST.
    void eolCommentBeforeJSONHandler();

    /// @brief Handler for START_COMMENT_BEFORE_JSON_ST.
    void startCommentBeforeJSONHandler();

    /// @brief Handler for C_COMMENT_BEFORE_JSON_ST.
    void cCommentBeforeJSONHandler();

    /// @brief Handler for STOP_COMMENT_BEFORE_JSON_ST.
    void stopCommentBeforeJSONHandler();

    /// @brief Handler for the FIRST_BRACE_ST.
    void innerJSONHandler();

    /// @brief Handler for the STRING_JSON_ST.
    void stringJSONHandler();

    /// @brief Handler for the ESCAPE_JSON_ST;
    void escapeJSONHandler();

    /// @brief Handler for EOL_COMMENT_ST.
    void eolCommentHandler();

    /// @brief Handler for START_COMMENT_ST.
    void startCommentHandler();

    /// @brief Handler for C_COMMENT_ST.
    void cCommentHandler();

    /// @brief Handler for STOP_COMMENT_ST.
    void stopCommentHandler();

    /// @brief Handler for the JSON_END_ST.
    void endJSONHandler();

    //@}

    /// @brief Internal buffer from which the feed reads data.
    std::vector<char> buffer_;

    /// @brief Holds pointer to the next byte in the buffer to be read.
    size_t data_ptr_;

    /// @brief Error message set by @ref onModelFailure.
    std::string error_message_;

    /// @brief A counter increased when '{' or '[' is found and decreased when
    /// '}' or ']' is found in the stream.
    uint64_t open_scopes_;

    /// @brief Holds processed data.
    std::string output_;
};

} // end of namespace config
} // end of namespace isc

#endif // JSON_FEED_H
