// Copyright (C) 2010-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DNS_RDATACLASS_H
#define DNS_RDATACLASS_H

#include <dns/master_loader.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rrttl.h>
#include <dns/rrtype.h>
#include <dns/serial.h>
#include <util/buffer.h>

#include <boost/shared_ptr.hpp>

#include <memory>
#include <stdint.h>
#include <string>
#include <vector>

namespace isc {
namespace dns {

class Name;
class MasterLexer;
class MasterLoaderCallbacks;
class AbstractMessageRenderer;

namespace rdata {
namespace any {

struct TSIGImpl;

/// \brief \c rdata::TSIG class represents the TSIG RDATA as defined %in
/// RFC2845.
///
/// This class implements the basic interfaces inherited from the abstract
/// \c rdata::Rdata class, and provides trivial accessors specific to the
/// TSIG RDATA.
class TSIG : public Rdata {
public:
    explicit TSIG(const std::string& type_str);
    TSIG(isc::util::InputBuffer& buffer, size_t rdata_len);
    TSIG(const TSIG& other);
    TSIG(
        MasterLexer& lexer, const Name* name,
        MasterLoader::Options options, MasterLoaderCallbacks& callbacks);
    virtual std::string toText() const;
    virtual void toWire(isc::util::OutputBuffer& buffer) const;
    virtual void toWire(AbstractMessageRenderer& renderer) const;
    virtual int compare(const Rdata& other) const;

    /// \brief Constructor from RDATA field parameters.
    ///
    /// The parameters are a straightforward mapping of %TSIG RDATA
    /// fields as defined %in RFC2845, but there are some implementation
    /// specific notes as follows.
    ///
    /// \c algorithm is a \c Name object that specifies the algorithm.
    /// For example, if the algorithm is HMAC-SHA256, \c algorithm would be
    /// \c Name("hmac-sha256").
    ///
    /// \c time_signed corresponds to the Time Signed field, which is of
    /// 48-bit unsigned integer type, and therefore cannot exceed 2^48-1;
    /// otherwise, an exception of type \c OutOfRange will be thrown.
    ///
    /// \c mac_size and \c mac correspond to the MAC Size and MAC fields,
    /// respectively.  When the MAC field is empty, \c mac must be null.
    /// \c mac_size and \c mac must be consistent %in that \c mac_size is 0 if
    /// and only if \c mac is null; otherwise an exception of type
    /// InvalidParameter will be thrown.
    ///
    /// The same restriction applies to \c other_len and \c other_data,
    /// which correspond to the Other Len and Other Data fields, respectively.
    ///
    /// This constructor internally involves resource allocation, and if
    /// it fails, a corresponding standard exception will be thrown.
    TSIG(const Name& algorithm, uint64_t time_signed, uint16_t fudge,
         uint16_t mac_size, const void* mac, uint16_t original_id,
         uint16_t error, uint16_t other_len, const void* other_data);

    /// \brief Assignment operator.
    ///
    /// It internally allocates a resource, and if it fails a corresponding
    /// standard exception will be thrown.
    /// This operator never throws an exception otherwise.
    ///
    /// This operator provides the strong exception guarantee: When an
    /// exception is thrown the content of the assignment target will be
    /// intact.
    TSIG& operator=(const TSIG& source);

    /// \brief The destructor.
    ~TSIG();

    /// \brief Return the algorithm name.
    ///
    /// This method never throws an exception.
    const Name& getAlgorithm() const;

    /// \brief Return the value of the Time Signed field.
    ///
    /// The returned value does not exceed 2^48-1.
    ///
    /// This method never throws an exception.
    uint64_t getTimeSigned() const;

    /// \brief Return the value of the Fudge field.
    ///
    /// This method never throws an exception.
    uint16_t getFudge() const;

    /// \brief Return the value of the MAC Size field.
    ///
    /// This method never throws an exception.
    uint16_t getMACSize() const;

    /// \brief Return the value of the MAC field.
    ///
    /// If the MAC field is empty, it returns null.
    /// Otherwise, the memory region beginning at the address returned by
    /// this method is valid up to the bytes specified by the return value
    /// of \c getMACSize().
    /// The memory region is only valid while the corresponding \c TSIG
    /// object is valid.  The caller must hold the \c TSIG object while
    /// it needs to refer to the region or it must make a local copy of the
    /// region.
    ///
    /// This method never throws an exception.
    const void* getMAC() const;

    /// \brief Return the value of the Original ID field.
    ///
    /// This method never throws an exception.
    uint16_t getOriginalID() const;

    /// \brief Return the value of the Error field.
    ///
    /// This method never throws an exception.
    uint16_t getError() const;

    /// \brief Return the value of the Other Len field.
    ///
    /// This method never throws an exception.
    uint16_t getOtherLen() const;

    /// \brief Return the value of the Other Data field.
    ///
    /// The same note as \c getMAC() applies.
    ///
    /// This method never throws an exception.
    const void* getOtherData() const;
private:
    std::unique_ptr<TSIGImpl> constructFromLexer(MasterLexer& lexer, const Name* origin);

    std::unique_ptr<TSIGImpl> impl_;
};

} // end of namespace "any"

namespace ch {

class A : public Rdata {
public:
    explicit A(const std::string& type_str);
    A(isc::util::InputBuffer& buffer, size_t rdata_len);
    A(const A& other);
    A(
        MasterLexer& lexer, const Name* name,
        MasterLoader::Options options, MasterLoaderCallbacks& callbacks);
    virtual std::string toText() const;
    virtual void toWire(isc::util::OutputBuffer& buffer) const;
    virtual void toWire(AbstractMessageRenderer& renderer) const;
    virtual int compare(const Rdata& other) const;
};

} // end of namespace "ch"

namespace generic {
namespace detail {

/// \brief Construct a Name object using a master lexer and optional origin.
///
/// This is a convenient shortcut of commonly used code pattern that would
/// be used to build RDATA that contain a domain name field.
///
/// Note that this function throws an exception against invalid input.
/// The (direct or indirect) caller's responsibility needs to expect and
/// handle exceptions appropriately.
///
/// \throw MasterLexer::LexerError The next token from lexer is not string.
/// \throw Other Exceptions from the \c Name class constructor if the next
/// string token from the lexer does not represent a valid name.
///
/// \param lexer A \c MasterLexer object.  Its next token is expected to be
/// a string that represent a domain name.
/// \param origin If non null, specifies the origin of the name to be
/// constructed.
///
/// \return A new Name object that corresponds to the next string token of
/// the \c lexer.
inline Name
createNameFromLexer(MasterLexer& lexer, const Name* origin) {
    const MasterToken::StringRegion& str_region =
        lexer.getNextToken(MasterToken::STRING).getStringRegion();
    return (Name(str_region.beg, str_region.len, origin));
}

template<class Type, uint16_t typeCode>
class TXTLikeImpl;

} // namespace detail

class NS : public Rdata {
public:
    explicit NS(const std::string& type_str);
    NS(isc::util::InputBuffer& buffer, size_t rdata_len);
    NS(const NS& other);
    NS(
        MasterLexer& lexer, const Name* name,
        MasterLoader::Options options, MasterLoaderCallbacks& callbacks);
    virtual std::string toText() const;
    virtual void toWire(isc::util::OutputBuffer& buffer) const;
    virtual void toWire(AbstractMessageRenderer& renderer) const;
    virtual int compare(const Rdata& other) const;

    /// Specialized constructor
    ///
    explicit NS(const Name& nsname) : nsname_(nsname) {
    }
    ///
    /// Specialized methods
    ///
    const Name& getNSName() const;
private:
    Name nsname_;
};

struct OPTImpl;

class OPT : public Rdata {
public:
    explicit OPT(const std::string& type_str);
    OPT(isc::util::InputBuffer& buffer, size_t rdata_len);
    OPT(const OPT& other);
    OPT(
        MasterLexer& lexer, const Name* name,
        MasterLoader::Options options, MasterLoaderCallbacks& callbacks);
    virtual std::string toText() const;
    virtual void toWire(isc::util::OutputBuffer& buffer) const;
    virtual void toWire(AbstractMessageRenderer& renderer) const;
    virtual int compare(const Rdata& other) const;

    // The default constructor makes sense for OPT as it can be empty.
    OPT();
    OPT& operator=(const OPT& source);
    ~OPT();

    /// \brief A class representing a pseudo RR (or option) within an
    /// OPT RR (see RFC 6891).
    class PseudoRR {
    public:
        /// \brief Constructor.
        /// \param code The OPTION-CODE field of the pseudo RR.
        /// \param data The OPTION-DATA field of the pseudo
        /// RR. OPTION-LENGTH is set to the length of this vector.
        PseudoRR(uint16_t code,
                 boost::shared_ptr<std::vector<uint8_t> >& data);

        /// \brief Return the option code of this pseudo RR.
        uint16_t getCode() const;

        /// \brief Return the option data of this pseudo RR.
        const uint8_t* getData() const;

        /// \brief Return the length of the option data of this
        /// pseudo RR.
        uint16_t getLength() const;

    private:
        uint16_t code_;
        boost::shared_ptr<std::vector<uint8_t>> data_;
    };

    /// \brief Append a pseudo RR (option) in this OPT RR.
    ///
    /// \param code The OPTION-CODE field of the pseudo RR.
    /// \param data The OPTION-DATA field of the pseudo RR.
    /// \param length The size of the \c data argument. OPTION-LENGTH is
    /// set to this size.
    /// \throw isc::InvalidParameter if this pseudo RR would cause
    /// the OPT RDATA to overflow its RDLENGTH.
    void appendPseudoRR(uint16_t code, const uint8_t* data, uint16_t length);

    /// \brief Return a vector of the pseudo RRs (options) in this
    /// OPT RR.
    ///
    /// Note: The returned reference is only valid during the lifetime
    /// of this \c generic::OPT object. It should not be used
    /// afterwards.
    const std::vector<PseudoRR>& getPseudoRRs() const;

private:
    std::unique_ptr<OPTImpl> impl_;
};

class PTR : public Rdata {
public:
    explicit PTR(const std::string& type_str);
    PTR(isc::util::InputBuffer& buffer, size_t rdata_len);
    PTR(const PTR& other);
    PTR(
        MasterLexer& lexer, const Name* name,
        MasterLoader::Options options, MasterLoaderCallbacks& callbacks);
    virtual std::string toText() const;
    virtual void toWire(isc::util::OutputBuffer& buffer) const;
    virtual void toWire(AbstractMessageRenderer& renderer) const;
    virtual int compare(const Rdata& other) const;

    ///
    /// Specialized constructor
    ///
    explicit PTR(const Name& ptr_name) : ptr_name_(ptr_name) {
    }
    ///
    /// Specialized methods
    ///
    const Name& getPTRName() const;
private:
    Name ptr_name_;
};

struct RRSIGImpl;

/// \brief \c rdata::RRSIG class represents the RRSIG RDATA as defined %in
/// RFC4034.
///
/// This class implements the basic interfaces inherited from the abstract
/// \c rdata::Rdata class, and provides trivial accessors specific to the
/// RRSIG RDATA.
class RRSIG : public Rdata {
public:
    explicit RRSIG(const std::string& type_str);
    RRSIG(isc::util::InputBuffer& buffer, size_t rdata_len);
    RRSIG(const RRSIG& other);
    RRSIG(
        MasterLexer& lexer, const Name* name,
        MasterLoader::Options options, MasterLoaderCallbacks& callbacks);
    virtual std::string toText() const;
    virtual void toWire(isc::util::OutputBuffer& buffer) const;
    virtual void toWire(AbstractMessageRenderer& renderer) const;
    virtual int compare(const Rdata& other) const;

    RRSIG& operator=(const RRSIG& source);
    ~RRSIG();

    // specialized methods
    const RRType& typeCovered() const;
private:
    // helper function for string and lexer constructors
    std::unique_ptr<RRSIGImpl> constructFromLexer(MasterLexer& lexer, const Name* origin);

    std::unique_ptr<RRSIGImpl> impl_;
};

class SOA : public Rdata {
public:
    explicit SOA(const std::string& type_str);
    SOA(isc::util::InputBuffer& buffer, size_t rdata_len);
    SOA(const SOA& other);
    SOA(
        MasterLexer& lexer, const Name* name,
        MasterLoader::Options options, MasterLoaderCallbacks& callbacks);
    virtual std::string toText() const;
    virtual void toWire(isc::util::OutputBuffer& buffer) const;
    virtual void toWire(AbstractMessageRenderer& renderer) const;
    virtual int compare(const Rdata& other) const;

    SOA(const Name& mname, const Name& rname, uint32_t serial,
        uint32_t refresh, uint32_t retry, uint32_t expire,
        uint32_t minimum);

    /// \brief Returns the serial stored in the SOA.
    Serial getSerial() const;

    /// brief Returns the minimum TTL field value of the SOA.
    uint32_t getMinimum() const;
private:
    /// Note: this is a prototype version; we may reconsider
    /// this representation later.
    Name mname_;
    Name rname_;
    /// serial, refresh, retry, expire, minimum, stored in network byte order
    uint8_t numdata_[20];
};

struct TKEYImpl;

/// \brief \c rdata::TKEY class represents the TKEY RDATA as defined %in
/// RFC2930.
///
/// This class implements the basic interfaces inherited from the abstract
/// \c rdata::Rdata class, and provides trivial accessors specific to the
/// TKEY RDATA.
class TKEY : public Rdata {
public:
    explicit TKEY(const std::string& type_str);
    TKEY(isc::util::InputBuffer& buffer, size_t rdata_len);
    TKEY(const TKEY& other);
    TKEY(
        MasterLexer& lexer, const Name* name,
        MasterLoader::Options options, MasterLoaderCallbacks& callbacks);
    virtual std::string toText() const;
    virtual void toWire(isc::util::OutputBuffer& buffer) const;
    virtual void toWire(AbstractMessageRenderer& renderer) const;
    virtual int compare(const Rdata& other) const;

    /// \brief Constructor from RDATA field parameters.
    ///
    /// The parameters are a straightforward mapping of %TKEY RDATA
    /// fields as defined %in RFC2930.
    ///
    /// This RR is pretty close to the TSIG RR with 32 bit timestamps,
    /// or the RRSIG RR with a second "other" data field.
    ///
    /// This constructor internally involves resource allocation, and if
    /// it fails, a corresponding standard exception will be thrown.
    ///
    /// \param algorithm The DNS name of the algorithm e.g. gss-tsig.
    /// \param inception The inception time (in seconds since 1970).
    /// \param expire The expire time (in seconds since 1970).
    /// \param mode The mode e.g. Diffie-Hellman (2) or GSS-API (3).
    /// \param error The error code (extended error space shared with TSIG).
    /// \param key_len The key length (0 means no key).
    /// \param key The key (can be 0).
    /// \param other_len The other data length (0 means no other data).
    /// \param other_data The other data (can be and usually is 0).
    TKEY(const Name& algorithm, uint32_t inception, uint32_t expire,
         uint16_t mode, uint16_t error, uint16_t key_len,
         const void* key, uint16_t other_len, const void* other_data);

    /// \brief Assignment operator.
    ///
    /// It internally allocates a resource, and if it fails a corresponding
    /// standard exception will be thrown.
    /// This operator never throws an exception otherwise.
    ///
    /// This operator provides the strong exception guarantee: When an
    /// exception is thrown the content of the assignment target will be
    /// intact.
    TKEY& operator=(const TKEY& source);

    /// \brief The destructor.
    ~TKEY();

    /// \brief Return the algorithm name.
    ///
    /// This method never throws an exception.
    const Name& getAlgorithm() const;

    /// \brief Return the value of the Inception field as a number.
    ///
    /// This method never throws an exception.
    uint32_t getInception() const;

    /// \brief Return the value of the Inception field as a string.
    std::string getInceptionDate() const;

    /// \brief Return the value of the Expire field as a number.
    ///
    /// This method never throws an exception.
    uint32_t getExpire() const;

    /// \brief Return the value of the Expire field as a string.
    std::string getExpireDate() const;

    /// \brief Return the value of the Mode field.
    ///
    /// This method never throws an exception.
    uint16_t getMode() const;

    /// \brief Return the value of the Error field.
    ///
    /// This method never throws an exception.
    uint16_t getError() const;

    /// \brief Return the value of the Key Len field.
    ///
    /// This method never throws an exception.
    uint16_t getKeyLen() const;

    /// \brief Return the value of the Key field.
    ///
    /// This method never throws an exception.
    const void* getKey() const;

    /// \brief Return the value of the Other Len field.
    ///
    /// This method never throws an exception.
    uint16_t getOtherLen() const;

    /// \brief Return the value of the Other Data field.
    ///
    /// The same note as \c getMAC() applies.
    ///
    /// This method never throws an exception.
    const void* getOtherData() const;

    /// \brief The GSS_API constant for the Mode field.
    static const uint16_t GSS_API_MODE;

private:
    std::unique_ptr<TKEYImpl> constructFromLexer(MasterLexer& lexer, const Name* origin);

    std::unique_ptr<TKEYImpl> impl_;
};

class TXT : public Rdata {
public:
    explicit TXT(const std::string& type_str);
    TXT(isc::util::InputBuffer& buffer, size_t rdata_len);
    TXT(const TXT& other);
    TXT(
        MasterLexer& lexer, const Name* name,
        MasterLoader::Options options, MasterLoaderCallbacks& callbacks);
    virtual std::string toText() const;
    virtual void toWire(isc::util::OutputBuffer& buffer) const;
    virtual void toWire(AbstractMessageRenderer& renderer) const;
    virtual int compare(const Rdata& other) const;

    TXT& operator=(const TXT& source);
    ~TXT();

private:
    typedef isc::dns::rdata::generic::detail::TXTLikeImpl<TXT, 16> TXTImpl;
    std::unique_ptr<TXTImpl> impl_;
};
} // namespace generic


namespace in {

class A : public Rdata {
public:
    explicit A(const std::string& type_str);
    A(isc::util::InputBuffer& buffer, size_t rdata_len);
    A(const A& other);
    A(
        MasterLexer& lexer, const Name* name,
        MasterLoader::Options options, MasterLoaderCallbacks& callbacks);
    virtual std::string toText() const;
    virtual void toWire(isc::util::OutputBuffer& buffer) const;
    virtual void toWire(AbstractMessageRenderer& renderer) const;
    virtual int compare(const Rdata& other) const;
private:
    uint32_t addr_;             // raw IPv4 address (network byte order)
};

class AAAA : public Rdata {
public:
    explicit AAAA(const std::string& type_str);
    AAAA(isc::util::InputBuffer& buffer, size_t rdata_len);
    AAAA(const AAAA& other);
    AAAA(
        MasterLexer& lexer, const Name* name,
        MasterLoader::Options options, MasterLoaderCallbacks& callbacks);
    virtual std::string toText() const;
    virtual void toWire(isc::util::OutputBuffer& buffer) const;
    virtual void toWire(AbstractMessageRenderer& renderer) const;
    virtual int compare(const Rdata& other) const;
private:
    uint8_t addr_[16];        // raw IPv6 address (network byte order)
};

/// \brief \c rdata::DHCID class represents the DHCID RDATA as defined %in
/// RFC4701.
///
/// This class implements the basic interfaces inherited from the abstract
/// \c rdata::Rdata class, and provides trivial accessors specific to the
/// DHCID RDATA.
class DHCID : public Rdata {
public:
    explicit DHCID(const std::string& type_str);
    DHCID(isc::util::InputBuffer& buffer, size_t rdata_len);
    DHCID(const DHCID& other);
    DHCID(
        MasterLexer& lexer, const Name* name,
        MasterLoader::Options options, MasterLoaderCallbacks& callbacks);
    virtual std::string toText() const;
    virtual void toWire(isc::util::OutputBuffer& buffer) const;
    virtual void toWire(AbstractMessageRenderer& renderer) const;
    virtual int compare(const Rdata& other) const;

    /// \brief Return the digest.
    ///
    /// This method never throws an exception.
    const std::vector<uint8_t>& getDigest() const;

private:
    // helper for string and lexer constructors
    void constructFromLexer(MasterLexer& lexer);

    /// \brief Private data representation
    ///
    /// Opaque data at least 3 octets long as per RFC4701.
    ///
    std::vector<uint8_t> digest_;
};

} // end of namespace "in"
} // end of namespace "rdata"
} // end of namespace "dns"
} // end of namespace "isc"
#endif // DNS_RDATACLASS_H
