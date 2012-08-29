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

#include <resolve/resolve.h>

#include <dns/message.h>
#include <dns/opcode.h>

using namespace isc::dns;

namespace {
    class SectionInserter {
    public:
        SectionInserter(MessagePtr message, const Message::Section sect) :
            message_(message), section_(sect)
        {}
        void operator()(const RRsetPtr rrset) {
            message_->addRRset(section_, rrset);
        }
        MessagePtr message_;
        const Message::Section section_;
    };
}

namespace isc {
namespace resolve {

void
makeErrorMessage(MessagePtr answer_message,
                 const Rcode& error_code)
{
    answer_message->clearSection(Message::SECTION_ANSWER);
    answer_message->clearSection(Message::SECTION_AUTHORITY);
    answer_message->clearSection(Message::SECTION_ADDITIONAL);

    answer_message->setRcode(error_code);
}

void initResponseMessage(const isc::dns::Message& query_message,
                         isc::dns::Message& response_message)
{
    response_message.setOpcode(query_message.getOpcode());
    response_message.setQid(query_message.getQid());
    assert(response_message.getRRCount(Message::SECTION_QUESTION) == 0);
    response_message.appendSection(Message::SECTION_QUESTION,
        query_message);
}

void initResponseMessage(const isc::dns::Question& question,
                         isc::dns::Message& response_message)
{
    response_message.setOpcode(isc::dns::Opcode::QUERY());
    response_message.addQuestion(question);
}

void copyResponseMessage(const Message& source, MessagePtr target) {
    target->setRcode(source.getRcode());

    target->appendSection(Message::SECTION_ANSWER, source);
    target->appendSection(Message::SECTION_AUTHORITY, source);
    target->appendSection(Message::SECTION_ADDITIONAL, source);
}


} // namespace resolve
} // namespace isc

