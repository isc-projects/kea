#include <dns/message.h>
#include <dns/buffer.h>
#include <dns/messagerenderer.h>
#include <vector>

#include "auth_util.h"

using namespace isc::dns;
using std::vector;

class QuestionInserter {
    public:
            QuestionInserter(Message* message) : message_(message) {}
                void operator()(const QuestionPtr question) {
                            message_->addQuestion(question);
                                }   
                    Message* message_;
};


namespace auth_util{
    void makeErrorMessage(Message &message, const Rcode &rcode){
        const qid_t qid = message.getQid();
        const bool rd = message.getHeaderFlag(MessageFlag::RD());
        const bool cd = message.getHeaderFlag(MessageFlag::CD());
        const Opcode& opcode = message.getOpcode();
        vector<QuestionPtr> questions;

        // If this is an error to a query, we should also copy the question section.
        if (opcode == Opcode::QUERY()) {
            questions.assign(message.beginQuestion(), message.endQuestion());
        }

        message.clear(Message::RENDER);
        message.setQid(qid);
        message.setOpcode(opcode);
        message.setHeaderFlag(MessageFlag::QR());
        message.setUDPSize(Message::DEFAULT_MAX_UDPSIZE);
        if (rd) {
            message.setHeaderFlag(MessageFlag::RD());
        }
        if (cd) {
            message.setHeaderFlag(MessageFlag::CD());
        }
        for_each(questions.begin(), questions.end(), QuestionInserter(&message));
        message.setRcode(rcode);
    }


    void messageToWire(Message &message, OutputBuffer &wireData){
        wireData.clear();
        MessageRenderer render(wireData);
        message.toWire(render);
    }
}
