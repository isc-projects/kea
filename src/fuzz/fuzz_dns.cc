// Copyright (C) 2025 Ada Logics Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////

#include <config.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <dns/exceptions.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/opcode.h>
#include <dns/question.h>
#include <dns/rcode.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>
#include <dns/rrtype.h>
#include <dns/tsig.h>
#include <dns/tsigkey.h>
#include <dns/tsigrecord.h>
#include <dns/master_lexer.h>
#include <dns/master_loader.h>
#include <util/buffer.h>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace isc::dns;
using namespace isc::util;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (size < 2) {
        return 0;
    }

    FuzzedDataProvider fdp(data, size);
    
    // Get a choice for which fuzzing path to take
    uint8_t choice = fdp.ConsumeIntegral<uint8_t>();
    
    // Reserve some data for different operations
    std::vector<uint8_t> wire_data = fdp.ConsumeBytes<uint8_t>(fdp.remaining_bytes() / 2);
    std::string string_data = fdp.ConsumeRemainingBytesAsString();
    
    // Fuzz DNS Name parsing from string
    if (choice % 8 == 0 && !string_data.empty()) {
        try {
            Name name(string_data);
            // Try various Name operations
            try {
                std::string text = name.toText();
                OutputBuffer buffer(0);
                name.toWire(buffer);
                
                // Try splitting at different positions
                if (name.getLabelCount() > 0) {
                    Name stripped = name.split(0);
                    Name reversed = name.reverse();
                }
                
                // Try comparison operations
                Name root = Name::ROOT_NAME();
                name.compare(root);
                
            } catch (const std::exception&) {
                // Ignore exceptions from operations
            }
        } catch (const std::exception&) {
            // Ignore exceptions from parsing
        }
    }
    
    // Fuzz DNS Name parsing from wire format
    if (choice % 8 == 1 && !wire_data.empty()) {
        try {
            InputBuffer buffer(&wire_data[0], wire_data.size());
            Name name(buffer);
            
            // Try operations on the parsed name
            try {
                name.toText();
                name.getLabelCount();
                name.getLength();
            } catch (const std::exception&) {
                // Ignore exceptions
            }
        } catch (const std::exception&) {
            // Ignore exceptions from parsing
        }
    }
    
    // Fuzz DNS Message parsing from wire
    if (choice % 8 == 2 && !wire_data.empty()) {
        try {
            InputBuffer buffer(&wire_data[0], wire_data.size());
            Message message(Message::PARSE);
            message.fromWire(buffer);
            
            // Try various Message operations
            try {
                message.getHeaderFlag(Message::HEADERFLAG_AA);
                message.getRcode();
                message.getQid();
                message.getRRCount(Message::SECTION_ANSWER);
                
                // Try iterating through sections
                for (int sec = Message::SECTION_QUESTION;
                     sec <= Message::SECTION_ADDITIONAL;
                     ++sec) {
                    Message::Section section = static_cast<Message::Section>(sec);
                    try {
                        auto it = message.beginSection(section);
                        auto it_end = message.endSection(section);
                        while (it != it_end) {
                            ++it;
                        }
                    } catch (const std::exception&) {
                        // Ignore iteration exceptions
                    }
                }
                
                // Try rendering back to wire
                MessageRenderer renderer;
                try {
                    message.toWire(renderer);
                } catch (const std::exception&) {
                    // Ignore rendering exceptions
                }
                
            } catch (const std::exception&) {
                // Ignore operation exceptions
            }
        } catch (const std::exception&) {
            // Ignore parsing exceptions
        }
    }
    
    // Fuzz Question parsing
    if (choice % 8 == 3 && !wire_data.empty()) {
        try {
            InputBuffer buffer(&wire_data[0], wire_data.size());
            Question question(buffer);
            
            try {
                question.toText();
                question.getName();
                question.getType();
                question.getClass();
                
                OutputBuffer out_buffer(0);
                question.toWire(out_buffer);
            } catch (const std::exception&) {
                // Ignore operation exceptions
            }
        } catch (const std::exception&) {
            // Ignore parsing exceptions
        }
    }
    
    // Fuzz RRset operations
    if (choice % 8 == 4 && !string_data.empty() && !wire_data.empty()) {
        try {
            Name name(string_data);
            RRsetPtr rrset = RRsetPtr(new RRset(name, RRClass::IN(), 
                                                 RRType::A(), RRTTL(3600)));
            
            // Try parsing RDATA from wire
            try {
                InputBuffer buffer(&wire_data[0], wire_data.size());
                if (wire_data.size() >= 4) {
                    rdata::ConstRdataPtr rdata = 
                        rdata::createRdata(RRType::A(), RRClass::IN(), 
                                          buffer, wire_data.size());
                    rrset->addRdata(rdata);
                }
            } catch (const std::exception&) {
                // Ignore RDATA parsing exceptions
            }
            
            // Try RRset operations
            try {
                rrset->toText();
                rrset->getRdataCount();
                
                OutputBuffer out_buffer(0);
                rrset->toWire(out_buffer);
            } catch (const std::exception&) {
                // Ignore operation exceptions
            }
        } catch (const std::exception&) {
            // Ignore exceptions
        }
    }
    
    // Fuzz TSIG operations
    if (choice % 8 == 5 && !string_data.empty() && wire_data.size() >= 16) {
        try {
            // Try creating a TSIG key
            TSIGKey key(string_data + ":secret");
            
            // Try creating TSIG RDATA and then a TSIG record
            try {
                InputBuffer buffer(&wire_data[0], wire_data.size());
                // Try to parse TSIG RDATA
                rdata::ConstRdataPtr rdata = 
                    rdata::createRdata(RRType::TSIG(), RRClass::ANY(), 
                                      buffer, wire_data.size());
                const rdata::any::TSIG& tsig_rdata = 
                    dynamic_cast<const rdata::any::TSIG&>(*rdata);
                
                // Create a TSIGRecord
                Name key_name(string_data);
                TSIGRecord tsig(key_name, tsig_rdata);
                tsig.toText();
                
                OutputBuffer out_buffer(0);
                tsig.toWire(out_buffer);
            } catch (const std::exception&) {
                // Ignore TSIG parsing exceptions
            }
            
            // Try TSIG context operations (sign operation is public)
            try {
                TSIGContext ctx(key);
                // Try signing some data
                if (!wire_data.empty()) {
                    ConstTSIGRecordPtr tsig_record = ctx.sign(0, &wire_data[0], wire_data.size());
                }
            } catch (const std::exception&) {
                // Ignore context exceptions
            }
        } catch (const std::exception&) {
            // Ignore key creation exceptions
        }
    }
    
    // Fuzz MasterLexer with string input
    if (choice % 8 == 6 && !string_data.empty()) {
        try {
            std::istringstream iss(string_data);
            MasterLexer lexer;
            lexer.pushSource(iss);
            
            // Try tokenizing (loop until we hit EOF token)
            for (int i = 0; i < 100; ++i) {
                try {
                    const MasterToken& token = lexer.getNextToken();
                    
                    // Stop if we hit EOF
                    if (token.getType() == MasterToken::END_OF_FILE) {
                        break;
                    }
                    
                    // Access token properties based on type
                    if (token.getType() == MasterToken::STRING ||
                        token.getType() == MasterToken::QSTRING) {
                        token.getString();
                        token.getStringRegion();
                    } else if (token.getType() == MasterToken::NUMBER) {
                        token.getNumber();
                    } else if (token.getType() == MasterToken::ERROR) {
                        token.getErrorCode();
                        token.getErrorText();
                    }
                } catch (const std::exception&) {
                    break;
                }
            }
        } catch (const std::exception&) {
            // Ignore lexer exceptions
        }
    }
    
    // Fuzz Message rendering operations
    if (choice % 8 == 7 && !string_data.empty()) {
        try {
            Message message(Message::RENDER);
            message.setQid(fdp.ConsumeIntegral<uint16_t>());
            message.setOpcode(Opcode::QUERY());
            message.setRcode(Rcode::NOERROR());
            
            // Try setting various flags
            message.setHeaderFlag(Message::HEADERFLAG_AA, 
                                 fdp.ConsumeBool());
            message.setHeaderFlag(Message::HEADERFLAG_RD, 
                                 fdp.ConsumeBool());
            message.setHeaderFlag(Message::HEADERFLAG_RA, 
                                 fdp.ConsumeBool());
            
            // Try adding a question
            try {
                Name qname(string_data);
                QuestionPtr question(new Question(qname, RRClass::IN(), 
                                                   RRType::A()));
                message.addQuestion(question);
            } catch (const std::exception&) {
                // Ignore question addition exceptions
            }
            
            // Try rendering
            try {
                MessageRenderer renderer;
                message.toWire(renderer);
            } catch (const std::exception&) {
                // Ignore rendering exceptions
            }
        } catch (const std::exception&) {
            // Ignore message creation exceptions
        }
    }
    
    return 0;
}
