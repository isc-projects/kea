// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include "config.h"
#include <fuzzer/FuzzedDataProvider.h>

#include <string>

#include <cc/data.h>
#include <cc/simple_parser.h>

#include <dhcpsrv/srv_config.h>
#include <dhcpsrv/cfg_option_def.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/cfg_iface.h>
#include <dhcpsrv/cfg_duid.h>
#include <dhcpsrv/cfg_expiration.h>
#include <dhcpsrv/cfg_mac_source.h>
#include <dhcpsrv/client_class_def.h>

#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dhcpsrv/parsers/option_data_parser.h>
#include <dhcpsrv/parsers/ifaces_config_parser.h>
#include <dhcpsrv/parsers/duid_config_parser.h>
#include <dhcpsrv/parsers/multi_threading_config_parser.h>
#include <dhcpsrv/parsers/sanity_checks_parser.h>
#include <dhcpsrv/parsers/expiration_config_parser.h>
#include <dhcpsrv/parsers/client_class_def_parser.h>
#include <dhcpsrv/parsers/host_reservation_parser.h>
#include <dhcpsrv/parsers/simple_parser4.h>
#include <dhcpsrv/parsers/simple_parser6.h>

#include "helper_func.h"

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* Data, size_t Size) {
    FuzzedDataProvider fdp(Data, Size);
    std::string payload = fdp.ConsumeRandomLengthString();

    std::string raw_payload(reinterpret_cast<const char*>(Data), Size);
    ElementPtr payload_elem =  nullptr;
    try {
        payload_elem = Element::fromJSON(payload);
    } catch (...) {
        return 0;
    }


    try {
        // Simple Parsing
        SimpleParser4::setAllDefaults(payload_elem);
        SimpleParser4::deriveParameters(payload_elem);
        SimpleParser6::setAllDefaults(payload_elem);
        SimpleParser6::deriveParameters(payload_elem);
    } catch (const isc::Exception&) {}
    try {
        // Configuration Option definition parsing
        //ElementPtr elem = fuzz::parseJSON(payload);
        CfgOptionDefPtr defs(new CfgOptionDef());
        OptionDefListParser defp4(AF_INET);
        defp4.parse(defs, payload_elem);
        //elem = fuzz::parseJSON(fdp.ConsumeRandomLengthString());
        OptionDefListParser defp6(AF_INET6);
        defp6.parse(defs, payload_elem);
    } catch (const isc::Exception&) {}
    try {

        // Configuration Option data parsing
        //ElementPtr elem = fuzz::parseJSON(payload);
        CfgOptionPtr opts(new CfgOption());
        CfgOptionDefPtr defs(new CfgOptionDef());
        OptionDataListParser odlp4(AF_INET, defs);
        odlp4.parse(opts, payload_elem, fdp.ConsumeBool());
        //elem = fuzz::parseJSON(fdp.ConsumeRandomLengthString());
        OptionDataListParser odlp6(AF_INET6, defs);
        odlp6.parse(opts, payload_elem, fdp.ConsumeBool());
    } catch (const isc::Exception&) {}
    try {

        // Interfaces configuration parsing
        //ElementPtr elem = fuzz::parseJSON(payload);
        CfgIfacePtr ifcfg(new CfgIface());
        IfacesConfigParser ifparser4(AF_INET, false);
        ifparser4.parse(ifcfg, payload_elem);
    } catch (const isc::Exception&) {}
    try {
        //ElementPtr elem = fuzz::parseJSON(payload);
        CfgIfacePtr ifcfg(new CfgIface());
        IfacesConfigParser ifparser6(AF_INET6, false);
        ifparser6.parse(ifcfg, payload_elem);
    } catch (const isc::Exception&) {}
    try {

        // DUID configuration parsing
        ElementPtr elem = fuzz::parseJSON(payload);
        CfgDUIDPtr duid(new CfgDUID());
        DUIDConfigParser duidp;
        duidp.parse(duid, elem);
    } catch (const isc::Exception&) {}
    try {

        // Configuration expiration parsing
        //ElementPtr elem = fuzz::parseJSON(payload);
        CfgExpirationPtr exp(new CfgExpiration());
        ExpirationConfigParser expp;
        expp.parse(payload_elem, exp);
    } catch (const isc::Exception&) {}
    try {

        // MAC list parsing
        CfgMACSource macs;
        MACSourcesListConfigParser macp;
        //ElementPtr elem = fuzz::parseJSON(payload);
        macp.parse(macs, payload_elem);
    } catch (const isc::Exception&) {}
    try {

        // Multi-Threading configuration parsing
        SrvConfig srv;
        //ElementPtr elem = fuzz::parseJSON(payload);
        MultiThreadingConfigParser mtcp;
        mtcp.parse(srv, payload_elem);
    } catch (const isc::Exception&) {}

    try {

        // Sanity Check parsing
        SrvConfig srv;
        //ElementPtr elem = fuzz::parseJSON(payload);
        SanityChecksParser scp;
        scp.parse(srv, payload_elem);
    } catch (const isc::Exception&) {}
    try {

        // Client Class definition parsing
        // ElementPtr elem = fuzz::parseJSON(payload);
        ClientClassDictionaryPtr dict(new ClientClassDictionary());
        ClientClassDefParser ccdp;
        ccdp.parse(dict, payload_elem, AF_INET);
        ccdp.parse(dict, payload_elem, AF_INET6);
    } catch (const isc::Exception&) {
        // Slient exceptions
    }


    try {
        // SubnetConfigParser parsing
        //ElementPtr elem = fuzz::parseJSON(payload);
        Subnet4ConfigParser scf(fdp.ConsumeBool());
        scf.parse(payload_elem, fdp.ConsumeBool());
    }
    catch (const isc::Exception&) {
        // Slient exceptions
    }


    // ControlSocketsParser
    try {
        ElementPtr elem = fuzz::parseJSON(payload);
        SrvConfig srv;
        ControlSocketsParser csp;
        csp.parse(srv, elem);
    } catch (const isc::Exception&) {
        // Slient exceptions
    }

    try {
        // Subnet6ConfigParser parsing
        ElementPtr elem = fuzz::parseJSON(payload);
        Subnet6ConfigParser scf(fdp.ConsumeBool());
        scf.parse(elem, fdp.ConsumeBool());
    } catch (const isc::Exception&) {
        // Slient exceptions
    }

    try {
        // D2ClientConfigParser parsing
        ElementPtr elem = fuzz::parseJSON(payload);
        D2ClientConfigParser d2p;
        d2p.parse(elem);
    } catch (const isc::Exception&) {
        // Slient exceptions
    }

    // Host Reservation parsing
    try {
        // Host Reservation parsing
        ElementPtr elem = fuzz::parseJSON(payload);
        HostReservationParser4 hrp;
        hrp.parse(SubnetID(10), elem, fdp.ConsumeBool());
    } catch (const isc::Exception&) {
        // Slient exceptions
    }

    try {
        // Host Reservation parsing
        ElementPtr elem = fuzz::parseJSON(payload);
        HostReservationParser6 hrp;
        hrp.parse(SubnetID(10), elem, fdp.ConsumeBool());
    } catch (const isc::Exception&) {
        // Slient exceptions
    }    
 
    return 0;
}
