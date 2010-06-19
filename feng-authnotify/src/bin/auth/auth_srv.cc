// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <boost/utility.hpp>

#include <exceptions/exceptions.h>

#include <dns/buffer.h>
#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/question.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>
#include <dns/message.h>
#include <config/ccsession.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <xfr/xfrout_client.h>

#include <datasrc/query.h>
#include <datasrc/data_source.h>
#include <datasrc/static_datasrc.h>
#include <datasrc/sqlite3_datasrc.h>

#include <cc/data.h>

#include "common.h"
#include "auth_srv.h"
#include "asio_link.h"
#include "auth_util.h"
#include "spec_config.h"

#include <boost/lexical_cast.hpp>

using namespace std;

using namespace isc;
using namespace isc::datasrc;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::data;
using namespace isc::config;
using namespace isc::xfr;

class AuthSrvImpl : private boost::noncopyable{
public:
    enum {DEFAULT_LOCAL_UDPSIZE = 4096};
    AuthSrvImpl();

    isc::data::ElementPtr setDbFile(const isc::data::ElementPtr config);
    void setVerbose(bool on) { verbose_mode_ = on;}
    bool getVerbose()const { return verbose_mode_;}
    void setConfigSession(ModuleCCSession *cs) { cs_ = cs;}
    ModuleCCSession *getConfigSession() { return cs_;}
    void nag(const string &info){
        if (verbose_mode_)
            cerr << "[AuthSrv] " << info;
    }
    void processQuery(asio_link::UserInfo &userInfo);

private:
    void processNormalQuery(asio_link::UserInfo &userInfo);
    void processAxfrQuery(asio_link::UserInfo &uerInfo);
    void processIxfrQuery(asio_link::UserInfo &userInfo, const std::string &queryZoneName);

    std::string db_file_;
    ModuleCCSession* cs_;
    MetaDataSrc data_sources_;
    /// We keep a pointer to the currently running sqlite datasource
    /// so that we can specifically remove that one should the database
    /// file change
    ConstDataSrcPtr cur_datasrc_;
    bool verbose_mode_;
};

AuthSrvImpl::AuthSrvImpl() : cs_(NULL), verbose_mode_(false)
{
    // cur_datasrc_ is automatically initialized by the default constructor,
    // effectively being an empty (sqlite) data source.  once ccsession is up
    // the datasource will be set by the configuration setting
    // add static data source
    data_sources_.addDataSrc(ConstDataSrcPtr(new StaticDataSrc));
}


void
AuthSrvImpl::processQuery(asio_link::UserInfo &userInfo)
{
    assert(userInfo.isMessageValid());
    Message &message = userInfo.getMessage();
    nag("[AuthSrv] received a message :\n" + message.toText() + "\n");
    const Opcode &opcode = message.getOpcode();
    if (opcode == Opcode::QUERY()){
        QuestionPtr question = *message.beginQuestion();
        const RRType &qtype = question->getType();
        if (qtype == RRType::AXFR())
            processAxfrQuery(userInfo);
        else if (qtype == RRType::IXFR())
            processIxfrQuery(userInfo, question->getName().toText());
        else 
            processNormalQuery(userInfo);
    }else{
        nag("unsupported opcode\n");
        auth_util::makeErrorMessage(message, Rcode::NOTIMP());
    }
}



void
AuthSrvImpl::processNormalQuery(asio_link::UserInfo &userInfo)
{
    Message &message = userInfo.getMessage();
    if (message.getRRCount(Section::QUESTION()) != 1) {
        auth_util::makeErrorMessage(message, Rcode::FORMERR());
    }
    else{
        const bool dnssec_ok = message.isDNSSECSupported();
        //const uint16_t remote_bufsize = message.getUDPSize();

        message.makeResponse();
        message.setHeaderFlag(MessageFlag::AA());
        message.setRcode(Rcode::NOERROR());
        message.setDNSSECSupported(dnssec_ok);
        message.setUDPSize(AuthSrvImpl::DEFAULT_LOCAL_UDPSIZE);

        try {
            Query query(message, dnssec_ok);
            data_sources_.doQuery(query);
        } catch (const Exception& ex) {
            nag(std::string("Internal error, returning SERVFAIL: ") + ex.what() + "\n");
            auth_util::makeErrorMessage(message, Rcode::SERVFAIL());
        }
        //response_renderer.setLengthLimit(userInfo.getProtocolType() == asio_link::UserInfo::QueryThroughUDP ? remote_bufsize : 65535);
    }

    //message.toWire(response_renderer);
    //nag(std::string("sending a response (") + boost::lexical_cast<string>(response_renderer.getLength()) 
    //        + " bytes):\n" + message.toText() + "\n");
}

void 
AuthSrvImpl::processAxfrQuery(asio_link::UserInfo &userInfo)
{
    string path(UNIX_SOCKET_FILE);
    XfroutClient xfr_client(path);
    try {
        xfr_client.connect();
        OutputBuffer rawData(0);
        auth_util::messageToWire(userInfo.getMessage(), rawData);
        xfr_client.sendXfroutRequestInfo(userInfo.getSocket(), (uint8_t *)rawData.getData(),
                rawData.getLength());
        xfr_client.disconnect();
    }   
    catch (const exception & err) {
        nag(std::string("error handle xfr query:") + err.what() + "\n");
    }
}

void 
AuthSrvImpl::processIxfrQuery(asio_link::UserInfo &userInfo, const std::string &queryZoneName)
{
    //TODO check with the conf-mgr whether current server is the auth of the zone
    isc::cc::Session tmp_session_with_xfr;
    tmp_session_with_xfr.establish();
    const string remote_ip_address = userInfo.getIPAddress();
    ElementPtr notify_command = Element::createFromString("{\"command\": [\"notify\", {\"zone_name\" : \""
                                                            + queryZoneName 
                                                            + "\", \"master_ip\" : \""
                                                            + remote_ip_address
                                                            + "\"}]}");
    unsigned int seq = tmp_session_with_xfr.group_sendmsg(notify_command, "Xfrin");
    ElementPtr env, answer;
    tmp_session_with_xfr.group_recvmsg(env, answer, false, seq);
    int rcode;
    ElementPtr err = parseAnswer(rcode, answer);
    if (rcode != 0) 
        nag("notify send failed\n");
    
}


ElementPtr
AuthSrvImpl::setDbFile(const isc::data::ElementPtr config) {
    ElementPtr answer = isc::config::createAnswer();
    ElementPtr final;

    if (config && config->contains("database_file")) {
        db_file_ = config->get("database_file")->stringValue();
        final = config;
    } else if (cs_ != NULL) {
        bool is_default;
        string item("database_file");
        ElementPtr value = cs_->getValue(is_default, item);
        db_file_ = value->stringValue();
        final = Element::createFromString("{}");
        final->set(item, value);
    } else {
        return (answer);
    }

    if (verbose_mode_) {
        cerr << "[AuthSrv] Data source database file: " << db_file_ << endl;
    }

    // create SQL data source
    // Note: the following step is tricky to be exception-safe and to ensure
    // exception guarantee: We first need to perform all operations that can
    // fail, while acquiring resources in the RAII manner.  We then perform
    // delete and swap operations which should not fail.
    DataSrcPtr datasrc_ptr(new Sqlite3DataSrc);
    datasrc_ptr->init(final);
    data_sources_.addDataSrc(datasrc_ptr);

    // The following code should be exception free.
    if (cur_datasrc_ != NULL) {
        data_sources_.removeDataSrc(cur_datasrc_);
    }
    cur_datasrc_ = datasrc_ptr;

    return (answer);
}


AuthSrv::AuthSrv() : impl_(new AuthSrvImpl) {
}

AuthSrv::~AuthSrv() {
    delete impl_;
}


void
AuthSrv::setVerbose(const bool on) {
    impl_->setVerbose(on);
}

bool
AuthSrv::getVerbose() const {
    return (impl_->getVerbose());
}

void
AuthSrv::setConfigSession(ModuleCCSession* cs) {
    impl_->setConfigSession(cs);
}

ModuleCCSession*
AuthSrv::configSession() const {
    return (impl_->getConfigSession());
}
    
void
AuthSrv::processQuery(asio_link::UserInfo &userInfo)
{
    impl_->processQuery(userInfo);
}

    
ElementPtr
AuthSrv::updateConfig(isc::data::ElementPtr new_config) {
    try {
        // the ModuleCCSession has already checked if we have
        // the correct ElementPtr type as specified in our .spec file
        ElementPtr answer = isc::config::createAnswer();
        answer = impl_->setDbFile(new_config);

        return answer;
    } catch (const isc::Exception& error) {
        impl_->nag(std::string("[AuthSrv] error: ") + error.what() + "\n");
        return isc::config::createAnswer(1, error.what());
    }
}
