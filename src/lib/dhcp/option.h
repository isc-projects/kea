// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef OPTION_H_
#define OPTION_H_

#include <string>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <util/buffer.h>

namespace isc {
namespace dhcp {

class Option {
public:
    /// length of the usual DHCPv4 option header (there are exceptions)
    const static size_t OPTION4_HDR_LEN = 2;

    /// length of any DHCPv6 option header
    const static size_t OPTION6_HDR_LEN = 4;

    /// defines option universe DHCPv4 or DHCPv6
    enum Universe { V4, V6 };

    /// a collection of DHCPv6 options
    typedef std::multimap<unsigned int, boost::shared_ptr<Option> >
    OptionCollection;

    /// @brief a factory function prototype
    ///
    /// @param u option universe (DHCPv4 or DHCPv6)
    /// @param type option type
    /// @param buf pointer to a buffer
    /// @param offset offset to first data byte in that buffer
    /// @param len data length of this option
    ///
    /// @return a pointer to a created option object
    typedef boost::shared_ptr<Option> Factory(Option::Universe u,
                                              unsigned short type,
                                              boost::shared_array<uint8_t>& buf,
                                              unsigned int offset,
                                              unsigned int len);

    /// @brief ctor, used for options constructed, usually during transmission
    ///
    /// @param u option universe (DHCPv4 or DHCPv6)
    /// @param type option type
    Option(Universe u, unsigned short type);

    /// @brief ctor, used for received options
    ///
    /// boost::shared_array allows sharing a buffer, but it requires that
    /// different instances share pointer to the whole array, not point
    /// to different elements in shared array. Therefore we need to share
    /// pointer to the whole array and remember offset where data for
    /// this option begins
    ///
    /// @param u specifies universe (V4 or V6)
    /// @param type option type
    /// @param buf pointer to a buffer
    /// @param offset offset in a buffer pointing to first byte of data
    /// @param len length of the option data
    Option(Universe u, unsigned short type,
           const boost::shared_array<uint8_t>& buf, unsigned int offset,
           unsigned int len);

    /// @brief Constructor, used for received options.
    ///
    /// This constructor takes vector<uint8_t>& which is used in cases
    /// when content of the option will be copied and stored within
    /// option object. V4 Options follow that approach already.
    /// TODO Migrate V6 options to that approach.
    ///
    /// @param u specifies universe (V4 or V6)
    /// @param type option type (0-255 for V4 and 0-65535 for V6)
    /// @param data content of the option
    Option(Universe u, unsigned short type, std::vector<uint8_t>& data);

    /// @brief Constructor, used for received options.
    ///
    /// This contructor is similar to the previous one, but it does not take
    /// the whole vector<uint8_t>, but rather subset of it.
    ///
    /// TODO: This can be templated to use different containers, not just
    /// vector. Prototype should look like this:
    /// template<typename InputIterator> Option(Universe u, uint16_t type,
    /// InputIterator first, InputIterator last);
    ///
    /// vector<int8_t> myData;
    /// Example usage: new Option(V4, 123, myData.begin()+1, myData.end()-1)
    /// This will create DHCPv4 option of type 123 that contains data from
    /// trimmed (first and last byte removed) myData vector.
    ///
    /// @param u specifies universe (V4 or V6)
    /// @param type option type (0-255 for V4 and 0-65535 for V6)
    /// @param first iterator to the first element that should be copied
    /// @param last iterator to the next element after the last one
    ///        to be copied.
    Option(Universe u, uint16_t type,
           std::vector<uint8_t>::const_iterator first,
           std::vector<uint8_t>::const_iterator last);

    /// @brief returns option universe (V4 or V6)
    ///
    /// @return universe type
    Universe
    getUniverse() { return universe_; };

    /// @brief Writes option in wire-format to a buffer.
    ///
    /// Writes option in wire-format to buffer, returns pointer to first unused
    /// byte after stored option (that is useful for writing options one after
    /// another). Used in DHCPv6 options.
    ///
    /// TODO: Migrate DHCPv6 code to pack(OutputBuffer& buf) version
    ///
    /// @param buf pointer to a buffer
    /// @param buf_len length of the buffer
    /// @param offset offset to place, where option shout be stored
    ///
    /// @return offset to first unused byte after stored option
    ///
    virtual unsigned int
    pack(boost::shared_array<uint8_t>& buf, unsigned int buf_len,
         unsigned int offset);

    /// @brief Writes option in a wire-format to a buffer.
    ///
    /// Method will throw if option storing fails for some reason.
    ///
    /// TODO Once old (DHCPv6) implementation is rewritten,
    /// unify pack4() and pack6() and rename them to just pack().
    ///
    /// @param buf output buffer (option will be stored there)
    virtual void
    pack4(isc::util::OutputBuffer& buf);


    /// @brief Parses buffer.
    ///
    /// Parses received buffer, returns offset to the first unused byte after
    /// parsed option.
    ///
    /// @param buf pointer to buffer
    /// @param buf_len length of buf
    /// @param offset offset, where start parsing option
    /// @param parse_len how many bytes should be parsed
    ///
    /// @return offset after last parsed octet
    virtual unsigned int
    unpack(const boost::shared_array<uint8_t>& buf,
           unsigned int buf_len,
           unsigned int offset,
           unsigned int parse_len);

    /// Returns string representation of the option.
    ///
    /// @param indent number of spaces before printing text
    ///
    /// @return string with text representation.
    virtual std::string
    toText(int indent = 0);

    /// Returns option type (0-255 for DHCPv4, 0-65535 for DHCPv6)
    ///
    /// @return option type
    unsigned short
    getType();

    /// Returns length of the complete option (data length + DHCPv4/DHCPv6
    /// option header)
    ///
    /// @return length of the option
    virtual unsigned short
    len();

    /// @brief Returns length of header (2 for v4, 4 for v6)
    ///
    /// @return length of option header
    virtual unsigned short
    getHeaderLen();

    /// returns if option is valid (e.g. option may be truncated)
    ///
    /// @return true, if option is valid
    virtual bool
    valid();

    /// Returns pointer to actual data.
    ///
    /// @return pointer to actual data (or NULL if there is no data)
    virtual const std::vector<uint8_t>&
    getData();

    /// Adds a sub-option.
    ///
    /// Some DHCPv6 options can have suboptions. This method allows adding
    /// options within options.
    ///
    /// Note: option is passed by value. That is very convenient as it allows
    /// downcasting from any derived classes, e.g. shared_ptr<Option6_IA> type
    /// can be passed directly, without any casts. That would not be possible
    /// with passing by reference. addOption() is expected to be used in
    /// many places. Requiring casting is not feasible.
    ///
    /// @param opt shared pointer to a suboption that is going to be added.
    void
    addOption(boost::shared_ptr<Option> opt);

    /// Returns shared_ptr to suboption of specific type
    ///
    /// @param type type of requested suboption
    ///
    /// @return shared_ptr to requested suoption
    boost::shared_ptr<isc::dhcp::Option>
    getOption(unsigned short type);

    /// Attempts to delete first suboption of requested type
    ///
    /// @param type Type of option to be deleted.
    ///
    /// @return true if option was deleted, false if no such option existed
    bool
    delOption(unsigned short type);

    uint8_t getUint8();

    uint16_t getUint16();

    uint32_t getUint32();

    /// just to force that every option has virtual dtor
    virtual
    ~Option();

protected:

    /// Builds raw (over-wire) buffer of this option, including all
    /// defined suboptions. Version for building DHCPv4 options.
    ///
    /// @param buf output buffer (built options will be stored here)
    /// @param buf_len buffer length (used for buffer overflow checks)
    /// @param offset offset from start of the buf buffer
    ///
    /// @return offset to the next byte after last used byte
    virtual unsigned int
    pack4(boost::shared_array<uint8_t>& buf,
          unsigned int buf_len,
          unsigned int offset);

    /// Builds raw (over-wire) buffer of this option, including all
    /// defined suboptions. Version for building DHCPv4 options.
    ///
    /// @param buf output buffer (built options will be stored here)
    /// @param buf_len buffer length (used for buffer overflow checks)
    /// @param offset offset from start of the buf buffer
    ///
    /// @return offset to the next byte after last used byte
    virtual unsigned int
    pack6(boost::shared_array<uint8_t>& buf,
          unsigned int buf_len,
          unsigned int offset);

    /// Parses provided buffer and creates DHCPv4 options.
    ///
    /// @param buf buffer that contains raw buffer to parse (on-wire format)
    /// @param buf_len buffer length (used for buffer overflow checks)
    /// @param offset offset from start of the buf buffer
    ///
    /// @return offset to the next byte after last parsed byte
    virtual unsigned int
    unpack4(const boost::shared_array<uint8_t>& buf,
            unsigned int buf_len,
            unsigned int offset,
            unsigned int parse_len);

    /// Parses provided buffer and creates DHCPv6 options.
    ///
    /// @param buf buffer that contains raw buffer to parse (on-wire format)
    /// @param buf_len buffer length (used for buffer overflow checks)
    /// @param offset offset from start of the buf buffer
    ///
    /// @return offset to the next byte after last parsed byte
    virtual unsigned int
    unpack6(const boost::shared_array<uint8_t>& buf,
            unsigned int buf_len,
            unsigned int offset,
            unsigned int parse_len);

    /// @brief A private method used for option correctness.
    ///
    /// It is used in constructors. In there are any problems detected
    /// (like specifying type > 255 for DHCPv4 option), it will throw
    /// BadValue or OutOfRange exceptions.
    void check();

    /// option universe (V4 or V6)
    Universe universe_;

    /// option type (0-255 for DHCPv4, 0-65535 for DHCPv6)
    unsigned short type_;

    /// contains content of this data
    std::vector<uint8_t> data_;

    /// TODO: Remove this field. vector<uint8_t> should be used
    /// instead.
    /// data is a shared_pointer that points out to the
    /// whole packet. offset_ specifies where data for
    /// this option begins.
    unsigned int offset_;

    /// collection for storing suboptions
    OptionCollection options_;

    /// TODO: probably 2 different containers have to be used for v4 (unique
    /// options) and v6 (options with the same type can repeat)
};

} // namespace isc::dhcp
} // namespace isc

#endif
