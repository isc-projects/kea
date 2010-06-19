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

// $Id: message_python.cc 2010-03-08 18:44:00 feng $

#include <boost/python.hpp>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/exception_translator.hpp>
#include <boost/python/return_internal_reference.hpp>
#include <boost/python/copy_const_reference.hpp>
#include <boost/shared_ptr.hpp>

#include <cassert>

#include <exceptions/exceptions.h>

#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/rrtype.h>
#include <dns/rrclass.h>
#include <dns/rrttl.h>
#include <dns/rrset.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrsetlist.h>
#include <dns/question.h>
#include <dns/message.h>

using namespace isc::dns;
using namespace boost::python;

#define DEFINE_EXCEPTION_TRANSLATOR(ex) \
  void ex##_translator(const Exception &x){ PyErr_SetString(PyExc_UserWarning, x.what()); }

#define REGISTER_EXCEPTION(ex) register_exception_translator<ex>(&ex##_translator)

namespace
{
        using isc::Exception;
        using isc::OutOfRange;
        using isc::Unexpected;

        DEFINE_EXCEPTION_TRANSLATOR(Exception)
        DEFINE_EXCEPTION_TRANSLATOR(OutOfRange)
        DEFINE_EXCEPTION_TRANSLATOR(Unexpected)
        DEFINE_EXCEPTION_TRANSLATOR(InvalidBufferPosition)
        DEFINE_EXCEPTION_TRANSLATOR(EmptyLabel)
        DEFINE_EXCEPTION_TRANSLATOR(TooLongName)
        DEFINE_EXCEPTION_TRANSLATOR(TooLongLabel)
        DEFINE_EXCEPTION_TRANSLATOR(BadLabelType)
        DEFINE_EXCEPTION_TRANSLATOR(BadEscape)
        DEFINE_EXCEPTION_TRANSLATOR(IncompleteName)
        DEFINE_EXCEPTION_TRANSLATOR(InvalidRRType)
        DEFINE_EXCEPTION_TRANSLATOR(IncompleteRRType)
        DEFINE_EXCEPTION_TRANSLATOR(InvalidRRClass)
        DEFINE_EXCEPTION_TRANSLATOR(IncompleteRRClass)
        DEFINE_EXCEPTION_TRANSLATOR(InvalidRRTTL)
        DEFINE_EXCEPTION_TRANSLATOR(IncompleteRRTTL)
        DEFINE_EXCEPTION_TRANSLATOR(EmptyRRset)
        DEFINE_EXCEPTION_TRANSLATOR(DuplicateRRset)

        using isc::dns::rdata::InvalidRdataLength;
        using isc::dns::rdata::InvalidRdataText;
        using isc::dns::rdata::CharStringTooLong;
        DEFINE_EXCEPTION_TRANSLATOR(InvalidRdataLength)
        DEFINE_EXCEPTION_TRANSLATOR(InvalidRdataText)
        DEFINE_EXCEPTION_TRANSLATOR(CharStringTooLong)

        DEFINE_EXCEPTION_TRANSLATOR(MessageTooShort);
        DEFINE_EXCEPTION_TRANSLATOR(InvalidMessageSection);
        DEFINE_EXCEPTION_TRANSLATOR(InvalidMessageOperation);
        DEFINE_EXCEPTION_TRANSLATOR(InvalidMessageUDPSize);


        class PyInputBuffer : public InputBuffer
        {
            public:
            PyInputBuffer(object bytes) : InputBuffer(0,0)
            {
                if (PyBytes_Check(bytes.ptr())) {
                    Py_ssize_t len = 0;
                    PyBytes_AsStringAndSize(bytes.ptr(), (char **)&data_, &len);
                    assert(len >= 0);
                    len_ = len;
                }
            }
        };

        class PyOutputBuffer : public OutputBuffer
        {
        public:
            PyOutputBuffer(size_t len) : OutputBuffer(len){}
            object getBytes() const
            {
                PyObject *bytes = PyBytes_FromStringAndSize((char *)getData(), getLength());
                return object(handle<>(bytes));
            }

            void writeBytes(object bytes)
            {
                if (PyBytes_Check(bytes.ptr()))
                {
                    uint8_t *raw_data = NULL;
                    Py_ssize_t raw_data_len = 0;
                    PyBytes_AsStringAndSize(bytes.ptr(), (char **)&raw_data,
                                            &raw_data_len);
                    assert(raw_data_len >= 0);
                    writeData(raw_data, raw_data_len);

                }
            }


    };

    class PyMessageRenderer : public MessageRenderer
    {
        public:
            PyMessageRenderer(OutputBuffer &buffer) : MessageRenderer(buffer){}
            object getBytes() const
            {
                PyObject *bytes = PyBytes_FromStringAndSize((char *)getData(), getLength());
                return object(handle<>(bytes));
            }

            void writeBytes(object bytes)
            {
                if (PyBytes_Check(bytes.ptr()))
                {
                    uint8_t *raw_data = NULL;
                    Py_ssize_t raw_data_len = 0;
                    PyBytes_AsStringAndSize(bytes.ptr(), (char **)&raw_data,
                                            &raw_data_len);
                    assert(raw_data_len >= 0);
                    writeData(raw_data, raw_data_len);
                }
            }

    };

    class RRsetList_iterator_wrapper
    {
        public:
            RRsetList_iterator_wrapper(const RRsetList& list) : cur_(list.begin()), end_(list.end()){}
            RRsetPtr Next()
            {
                if(cur_ == end_) 
                {
                    PyErr_SetObject(PyExc_StopIteration, Py_None);
                    throw_error_already_set();
                }

                RRsetPtr rrset = *cur_;
                ++cur_;
                return rrset;
            }

            static RRsetList_iterator_wrapper create(RRsetList &list)
            {
                return RRsetList_iterator_wrapper(list);
            }

        private:
            RRsetList::const_iterator cur_;
            RRsetList::const_iterator end_;
    };

    class Question_iterator_wrapper
    {
        public:
            Question_iterator_wrapper(const Message &message) : cur_(message.beginQuestion()), end_(message.endQuestion()){}
            QuestionPtr getQuestion() const { return *cur_;}
            bool isLast() {return cur_ == end_;}
            void next(){ ++cur_;}
        private:
            QuestionIterator cur_;
            QuestionIterator end_;
    };
   
    class Section_iterator_wrapper
    {
        public:
            Section_iterator_wrapper(const Message &message, const Section &section) : cur_(message.beginSection(section)), end_(message.endSection(section)){}
            RRsetPtr getRRset() const { return *cur_;}
            bool isLast() {return cur_ == end_;}
            void next(){ ++cur_;}

        private:
            RRsetIterator cur_;
            RRsetIterator end_;
    };

 
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(write_name_overloads, writeName, 1, 2)
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(to_text_overloads, toText, 0, 1)
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(find_rrset_overloads, findRRset, 1, 2)
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(add_rrset_overloads, addRRset, 2, 3)
}
     
BOOST_PYTHON_MODULE(bind10_dns)
{
    REGISTER_EXCEPTION(Exception);
    REGISTER_EXCEPTION(OutOfRange);
    REGISTER_EXCEPTION(Unexpected);
    REGISTER_EXCEPTION(InvalidBufferPosition);
    REGISTER_EXCEPTION(EmptyLabel);
    REGISTER_EXCEPTION(TooLongName);
    REGISTER_EXCEPTION(TooLongLabel);
    REGISTER_EXCEPTION(BadLabelType);
    REGISTER_EXCEPTION(BadEscape);
    REGISTER_EXCEPTION(IncompleteName);
    REGISTER_EXCEPTION(InvalidRRClass);
    REGISTER_EXCEPTION(IncompleteRRClass);
    REGISTER_EXCEPTION(InvalidRRTTL);
    REGISTER_EXCEPTION(IncompleteRRTTL);
    REGISTER_EXCEPTION(EmptyRRset);
    REGISTER_EXCEPTION(InvalidRdataLength);
    REGISTER_EXCEPTION(InvalidRdataText);
    REGISTER_EXCEPTION(CharStringTooLong);
    REGISTER_EXCEPTION(DuplicateRRset);
    REGISTER_EXCEPTION(MessageTooShort);
    REGISTER_EXCEPTION(InvalidMessageSection);
    REGISTER_EXCEPTION(InvalidMessageOperation);
    REGISTER_EXCEPTION(InvalidMessageUDPSize);


    class_<InputBuffer>("cpp_input_buffer", init<const void *, size_t>())
       .def("get_length", &InputBuffer::getLength)
       .def("get_position", &InputBuffer::getPosition)
       .def("set_position", &InputBuffer::setPosition)
       .def("read_uint8", &InputBuffer::readUint8)
       .def("read_uint16", &InputBuffer::readUint16)
       .def("read_uint32", &InputBuffer::readUint32)
       .def("read_data", &InputBuffer::readData);

    class_<PyInputBuffer, bases<InputBuffer> >("input_buffer", init<object>());

    class_<OutputBuffer>("cpp_output_buffer", init<size_t>())
        .def("get_capacity", &OutputBuffer::getCapacity)
        .def("get_length", &OutputBuffer::getLength)
        .def("skip", &OutputBuffer::skip)
        .def("clear", &OutputBuffer::clear)
        .def("write_uint8", &OutputBuffer::writeUint8)
        .def("write_uint16", &OutputBuffer::writeUint16)
        .def("write_uint16_at", &OutputBuffer::writeUint16At)
        .def("write_uint32", &OutputBuffer::writeUint32);


    class_<PyOutputBuffer, bases<OutputBuffer> >("output_buffer", init<size_t>())
        .def("get_data", &PyOutputBuffer::getBytes)
        .def("write_data", &PyOutputBuffer::writeBytes);


    enum_<NameComparisonResult::NameRelation>("name_relation")
        .value("SUPER_DOMAIN", NameComparisonResult::SUPERDOMAIN)
        .value("SUB_DOMAIN", NameComparisonResult::SUBDOMAIN)
        .value("EQUAL", NameComparisonResult::EQUAL)
        .value("COMMAON_ANCESTOR", NameComparisonResult::COMMONANCESTOR);

    class_<NameComparisonResult>("name_comparison_result", init<int, unsigned int, NameComparisonResult::NameRelation>())
        .def("get_order", &NameComparisonResult::getOrder)
        .def("get_common_labels", &NameComparisonResult::getCommonLabels)
        .def("get_relation", &NameComparisonResult::getRelation);

    class_<MessageRenderer>("cpp_message_render", init<OutputBuffer &>())
        .def("get_Length", &MessageRenderer::getLength)
        .def("skip", &MessageRenderer::skip)
        .def("clear", &MessageRenderer::clear)
        .def("write_uint8", &MessageRenderer::writeUint8)
        .def("write_uint16", &MessageRenderer::writeUint16)
        .def("write_uint16_at", &MessageRenderer::writeUint16At)
        .def("write_uint32", &MessageRenderer::writeUint32)
        .def("write_name", &MessageRenderer::writeName, write_name_overloads(args("name", "compress")));


   class_<PyMessageRenderer, bases<MessageRenderer> >("message_render", init<OutputBuffer &>())
        .def("get_data", &PyMessageRenderer::getBytes)
        .def("write_data", &PyMessageRenderer::writeBytes);

   class_<Name>("name", init<const std::string &, optional<bool> >())
       .def(init<InputBuffer &, optional<bool> >())
       .def("at", &Name::at)
       .def("get_lenght", &Name::getLength)
       .def("get_label_count", &Name::getLabelCount)
       .def("to_text", &Name::toText, to_text_overloads())
       .def("to_wire", (void (Name::*)(MessageRenderer &)const)&Name::toWire)
       .def("to_wire", (void (Name::*)(OutputBuffer&)const)&Name::toWire)
       .def("compare", &Name::compare)
       .def("split", (Name(Name::*)(unsigned int, unsigned int)const)&Name::split)
       .def("split", (Name(Name::*)(unsigned int)const)&Name::split)
       .def("concatenate", &Name::concatenate)
       .def("downcase", &Name::downcase, return_value_policy<reference_existing_object>())       
       .def("is_wildcard", &Name::isWildcard)
       .def(self == self)
       .def(self != self)
       .def(self < self)
       .def(self <= self)
       .def(self > self)
       .def(self >= self);

   class_<RRType>("rr_type", init<uint16_t>())
       .def(init<const std::string &>())
       .def(init<InputBuffer &>())
       .def("to_text", &RRType::toText)
       .def("to_wire", (void (RRType::*)(MessageRenderer &)const)&RRType::toWire)
       .def("to_wire", (void (RRType::*)(OutputBuffer &)const )&RRType::toWire)
       .def("get_code", &RRType::getCode)
       .def(self == self)
       .def(self != self)
       .def(self < self)
       .def("DNAME", &RRType::DNAME, return_value_policy<copy_const_reference>())
       .staticmethod("DNAME")
       .def("MX", &RRType::MX, return_value_policy<copy_const_reference>())
       .staticmethod("MX")
       .def("DNSKEY", &RRType::DNSKEY, return_value_policy<copy_const_reference>())
       .staticmethod("DNSKEY")
       .def("TXT", &RRType::TXT, return_value_policy<copy_const_reference>())
       .staticmethod("TXT")
       .def("RRSIG", &RRType::RRSIG, return_value_policy<copy_const_reference>())
       .staticmethod("RRSIG")
       .def("NSEC", &RRType::NSEC, return_value_policy<copy_const_reference>())
       .staticmethod("NSEC")
       .def("AAAA", &RRType::AAAA, return_value_policy<copy_const_reference>())
       .staticmethod("AAAA")
       .def("DS", &RRType::DS, return_value_policy<copy_const_reference>())
       .staticmethod("DS")
       .def("OPT", &RRType::OPT, return_value_policy<copy_const_reference>())
       .staticmethod("OPT")
       .def("A", &RRType::A, return_value_policy<copy_const_reference>())
       .staticmethod("A")
       .def("NS", &RRType::NS, return_value_policy<copy_const_reference>())
       .staticmethod("NS")
       .def("CNAME", &RRType::CNAME, return_value_policy<copy_const_reference>())
       .staticmethod("CNAME")
       .def("SOA", &RRType::SOA, return_value_policy<copy_const_reference>())
       .staticmethod("SOA")
       .def("IXFR", &RRType::IXFR, return_value_policy<copy_const_reference>())
       .staticmethod("IXFR")
       .def("AXFR", &RRType::AXFR, return_value_policy<copy_const_reference>())
       .staticmethod("AXFR")
       .def("ANY", &RRType::ANY, return_value_policy<copy_const_reference>())
       .staticmethod("ANY");

   class_<RRClass>("rr_class", init<uint16_t>())
       .def(init<const std::string &>())
       .def(init<InputBuffer &>())
       .def("to_text", &RRClass::toText)
       .def("to_wire", (void (RRClass::*)(MessageRenderer &)const)&RRClass::toWire)
       .def("to_wire", (void (RRClass::*)(OutputBuffer&)const)&RRClass::toWire)
       .def("get_code", &RRClass::getCode)
       .def(self == self)
       .def(self != self)
       .def(self < self)
       .def("IN", &RRClass::IN, return_value_policy<copy_const_reference>())
       .staticmethod("IN")
       .def("CH", &RRClass::CH, return_value_policy<copy_const_reference>())
       .staticmethod("CH")
       .def("HS", &RRClass::HS, return_value_policy<copy_const_reference>())
       .staticmethod("HS")
       .def("NONE", &RRClass::NONE, return_value_policy<copy_const_reference>())
       .staticmethod("NONE")
       .def("ANY", &RRClass::ANY, return_value_policy<copy_const_reference>())
       .staticmethod("ANY");

    class_<RRTTL>("rr_ttl", init<uint32_t>())
       .def(init<const std::string &>())
       .def(init<InputBuffer &>())
       .def("to_text", &RRTTL::toText)
       .def("to_wire", (void (RRTTL::*)(MessageRenderer &)const)&RRTTL::toWire)
       .def("to_wire", (void (RRTTL::*)(OutputBuffer&)const)&RRTTL::toWire)
       .def("get_value", &RRTTL::getValue)
       .def(self == self)
       .def(self != self)
       .def(self < self)
       .def(self <= self)
       .def(self > self)
       .def(self >= self);

    using isc::dns::rdata::Rdata;
    class_<Rdata, boost::shared_ptr<Rdata>, boost::noncopyable>("abstract_rdata", no_init)
        .def("to_text", &Rdata::toText)
        .def("to_wire", (void (Rdata::*)(OutputBuffer &)const )&Rdata::toWire)
        .def("to_wire", (void (Rdata::*)(MessageRenderer &)const)&Rdata::toWire)
        .def("compare", &Rdata::compare);

    using isc::dns::rdata::generic::Generic;
    class_<Generic, bases<Rdata> >("rdata", init<const std::string &>())
        .def(init<InputBuffer &, size_t>())
        .def("to_text", &Generic::toText)
        .def("to_wire", (void(Generic:: *)(OutputBuffer &)const)&Generic::toWire)
        .def("to_wire", (void(Generic:: *)(MessageRenderer &)const)&Generic::toWire)
        .def("compare", &Generic::compare);

    using isc::dns::rdata::ch::A;
    class_<A, bases<Rdata> >("a_rdata", init<const std::string &>()).def(init<InputBuffer &, size_t>())
        .def("to_text", &A::toText)
        .def("to_wire", (void(A:: *)(OutputBuffer &)const)&A::toWire)
        .def("to_wire", (void(A:: *)(MessageRenderer &)const)&A::toWire)
        .def("compare", &A::compare);



    def("create_rdata", (rdata::RdataPtr (*)(const RRType &, const RRClass &, const std::string &))rdata::createRdata);
    def("create_rdata", (rdata::RdataPtr (*)(const RRType &, const RRClass &, InputBuffer &, size_t))rdata::createRdata);
    def("create_rdata", (rdata::RdataPtr (*)(const RRType &, const RRClass &, const Rdata &))rdata::createRdata);
    
    class_<AbstractRRset, boost::noncopyable>("abstract_rrset", no_init)
        .def("get_rdata_count", &AbstractRRset::getRdataCount)
        .def("get_name", &AbstractRRset::getName, return_internal_reference<>())
        .def("get_class", &AbstractRRset::getClass, return_internal_reference<>())
        .def("get_type", &AbstractRRset::getType, return_internal_reference<>())
        .def("get_ttl", &AbstractRRset::getTTL, return_internal_reference<>())
        .def("set_name", &AbstractRRset::setName)
        .def("set_ttl", &AbstractRRset::setTTL)
        .def("to_text", &AbstractRRset::toText)
        .def("to_wire", (unsigned int (AbstractRRset::*)(MessageRenderer &)const)&AbstractRRset::toWire) 
        .def("to_wire", (unsigned int (AbstractRRset::*)(OutputBuffer&)const)&AbstractRRset::toWire) 
        .def("add_rdata", (void (AbstractRRset::*)(rdata::ConstRdataPtr))&AbstractRRset::addRdata)
        .def("add_rdata", (void (AbstractRRset::*)(const rdata::Rdata &))&AbstractRRset::addRdata)
        .def("get_rdata_iterator", &AbstractRRset::getRdataIterator);
    
    class_<RdataIterator, boost::shared_ptr<RdataIterator>, boost::noncopyable>("rdata_iter",no_init)
        .def("first", &RdataIterator::first)
        .def("next", &RdataIterator::next)
        .def("get_current", &RdataIterator::getCurrent, return_internal_reference<>())
        .def("is_last", &RdataIterator::isLast);
    
    class_<BasicRRset, bases<AbstractRRset>, boost::noncopyable>("basic_rrset", init<const Name &, const RRClass &, const RRType &, const RRTTL &>())
        .def("get_rdata_count", &BasicRRset::getRdataCount)
        .def("get_name", &BasicRRset::getName, return_internal_reference<>())
        .def("get_class", &BasicRRset::getClass, return_internal_reference<>())
        .def("get_type", &BasicRRset::getType, return_internal_reference<>())
        .def("get_ttl", &BasicRRset::getTTL, return_internal_reference<>())
        .def("set_name", &BasicRRset::setName)
        .def("set_ttl", &BasicRRset::setTTL)
        .def("to_text", &BasicRRset::toText)
        .def("to_wire", (unsigned int (BasicRRset::*)(MessageRenderer &)const)&BasicRRset::toWire) 
        .def("to_wire", (unsigned int (BasicRRset::*)(OutputBuffer&)const)&BasicRRset::toWire)
        .def("add_rdata", (void (BasicRRset::*)(rdata::ConstRdataPtr))&BasicRRset::addRdata)
        .def("add_rdata", (void (BasicRRset::*)(const rdata::Rdata &))&BasicRRset::addRdata)
        .def("get_rdata_iterator", &BasicRRset::getRdataIterator);

    class_<RRset, boost::shared_ptr<RRset>, bases<BasicRRset>, boost::noncopyable>("rrset", init<const Name&, const RRClass &, const RRType &, const RRTTL &>())
        .def("set_name", &RRset::setName)
        .def("set_ttl", &RRset::setTTL)
        .def("add_rrsig", (void (RRset::*)(const rdata::RdataPtr))&RRset::addRRsig)
        .def("add_rrsig", (void (RRset::*)(AbstractRRset &))&RRset::addRRsig)
        .def("add_rrsig", (void (RRset::*)(RRsetPtr))&RRset::addRRsig)
        .def("remove_rrsig", &RRset::removeRRsig)
        .def("get_rrsig", &RRset::getRRsig);
   
    class_<RRsetList, boost::noncopyable>("rrset_list", init<>())
        .def("add_rrset", &RRsetList::addRRset)
        .def("find_rrset", &RRsetList::findRRset) 
        .def("__iter__", &RRsetList_iterator_wrapper::create)
        .def("__len__", &RRsetList::size);


    class_<Question, boost::shared_ptr<Question> >("question", init<InputBuffer &>())
        .def(init<const Name &, const RRClass &, const RRType &>())
        .def("get_name", &Question::getName, return_internal_reference<>())
        .def("get_type", &Question::getType, return_internal_reference<>())
        .def("get_class", &Question::getClass, return_internal_reference<>())
        .def("to_text", &Question::toText)
        .def("to_wire", (unsigned int(Question::*)(MessageRenderer &)const)&Question::toWire)
        .def("to_wire", (unsigned int (Question::*)(OutputBuffer&)const)&Question::toWire);

   class_<MessageFlag>("message_flag", no_init)
        .def("get_bit", &MessageFlag::getBit)
        .def("QR", &MessageFlag::QR, return_value_policy<copy_const_reference>())
        .staticmethod("QR")
        .def("AA", &MessageFlag::AA, return_value_policy<copy_const_reference>())
        .staticmethod("AA")
        .def("TC", &MessageFlag::TC, return_value_policy<copy_const_reference>())
        .staticmethod("TC")
        .def("RD", &MessageFlag::RD, return_value_policy<copy_const_reference>())
        .staticmethod("RD")
        .def("RA", &MessageFlag::RA, return_value_policy<copy_const_reference>())
        .staticmethod("RA")
        .def("AD", &MessageFlag::AD, return_value_policy<copy_const_reference>())
        .staticmethod("AD")
        .def("CD", &MessageFlag::CD, return_value_policy<copy_const_reference>())
        .staticmethod("CD");
      
       class_<Opcode>("op_code", no_init)
        .def("get_code", &Opcode::getCode)
        .def(self == self)
        .def("to_text", &Opcode::toText)
        .def("QUERY", &Opcode::QUERY, return_value_policy<copy_const_reference>())
        .staticmethod("QUERY")
        .def("IQUERY", &Opcode::IQUERY, return_value_policy<copy_const_reference>())
        .staticmethod("IQUERY")
        .def("STATUS", &Opcode::STATUS, return_value_policy<copy_const_reference>())
        .staticmethod("STATUS")
        .def("RESERVED3", &Opcode::RESERVED3, return_value_policy<copy_const_reference>())
        .staticmethod("RESERVED3")
        .def("NOTIFY", &Opcode::NOTIFY, return_value_policy<copy_const_reference>())
        .staticmethod("NOTIFY")
        .def("UPDATE", &Opcode::UPDATE, return_value_policy<copy_const_reference>())
        .staticmethod("UPDATE")
        .def("RESERVED6", &Opcode::RESERVED6, return_value_policy<copy_const_reference>())
        .staticmethod("RESERVED6")
        .def("RESERVED7", &Opcode::RESERVED7, return_value_policy<copy_const_reference>())
        .staticmethod("RESERVED7")
        .def("RESERVED8", &Opcode::RESERVED8, return_value_policy<copy_const_reference>())
        .staticmethod("RESERVED8")
        .def("RESERVED9", &Opcode::RESERVED9, return_value_policy<copy_const_reference>())
        .staticmethod("RESERVED9")
        .def("RESERVED10", &Opcode::RESERVED10, return_value_policy<copy_const_reference>())
        .staticmethod("RESERVED10")
        .def("RESERVED11", &Opcode::RESERVED11, return_value_policy<copy_const_reference>())
        .staticmethod("RESERVED11")
        .def("RESERVED12", &Opcode::RESERVED12, return_value_policy<copy_const_reference>())
        .staticmethod("RESERVED12")
        .def("RESERVED13", &Opcode::RESERVED13, return_value_policy<copy_const_reference>())
        .staticmethod("RESERVED13")
        .def("RESERVED14", &Opcode::RESERVED14, return_value_policy<copy_const_reference>())
        .staticmethod("RESERVED14")
        .def("RESERVED15", &Opcode::RESERVED15, return_value_policy<copy_const_reference>())
        .staticmethod("RESERVED15");
      
    class_<Rcode>("rcode", init<uint16_t>())
        .def("get_code", &Rcode::getCode)
        .def(self == self)
        .def("to_text", &Rcode::toText)
        .def("NOERROR", &Rcode::NOERROR, return_value_policy<copy_const_reference>())
        .staticmethod("NOERROR")
        .def("FORMERR", &Rcode::FORMERR, return_value_policy<copy_const_reference>())
        .staticmethod("FORMERR")
        .def("SERVFAIL", &Rcode::SERVFAIL, return_value_policy<copy_const_reference>())
        .staticmethod("SERVFAIL")
        .def("NXDOMAIN", &Rcode::NXDOMAIN, return_value_policy<copy_const_reference>())
        .staticmethod("NXDOMAIN")
        .def("NOTIMP", &Rcode::NOTIMP, return_value_policy<copy_const_reference>())
        .staticmethod("NOTIMP")
        .def("REFUSED", &Rcode::REFUSED, return_value_policy<copy_const_reference>())
        .staticmethod("REFUSED")
        .def("YXDOMAIN", &Rcode::YXDOMAIN, return_value_policy<copy_const_reference>())
        .staticmethod("YXDOMAIN")
        .def("YXRRSET", &Rcode::YXRRSET, return_value_policy<copy_const_reference>())
        .staticmethod("YXRRSET")
        .def("NXRRSET", &Rcode::NXRRSET, return_value_policy<copy_const_reference>())
        .staticmethod("NXRRSET")
        .def("NOTAUTH", &Rcode::NOTAUTH, return_value_policy<copy_const_reference>())
        .staticmethod("NOTAUTH")
        .def("NOTZONE", &Rcode::NOTZONE, return_value_policy<copy_const_reference>())
        .staticmethod("NOTZONE")
        .def("RESERVED11", &Rcode::RESERVED11, return_value_policy<copy_const_reference>())
        .staticmethod("RESERVED11")
        .def("RESERVED12", &Rcode::RESERVED12, return_value_policy<copy_const_reference>())
        .staticmethod("RESERVED12")
        .def("RESERVED13", &Rcode::RESERVED13, return_value_policy<copy_const_reference>())
        .staticmethod("RESERVED13")
        .def("RESERVED14", &Rcode::RESERVED14, return_value_policy<copy_const_reference>())
        .staticmethod("RESERVED14")
        .def("RESERVED15", &Rcode::RESERVED15, return_value_policy<copy_const_reference>())
        .staticmethod("RESERVED15")
        .def("BADVERS", &Rcode::BADVERS, return_value_policy<copy_const_reference>())
        .staticmethod("BADVERS");
      
    class_<Section>("section", no_init)
        .def("get_code", &Section::getCode)
        .def(self == self)
        .def(self != self)
        .def("QUESTION", &Section::QUESTION, return_value_policy<copy_const_reference>())
        .staticmethod("QUESTION")
        .def("ANSWER", &Section::ANSWER, return_value_policy<copy_const_reference>())
        .staticmethod("ANSWER")
        .def("AUTHORITY", &Section::AUTHORITY, return_value_policy<copy_const_reference>())
        .staticmethod("AUTHORITY")
        .def("ADDITIONAL", &Section::ADDITIONAL, return_value_policy<copy_const_reference>())
        .staticmethod("ADDITIONAL");

    enum_<Message::Mode>("message_mode")
        .value("PARSE", Message::PARSE)
        .value("RENDER", Message::RENDER);

    class_<Message, boost::noncopyable>("message", init<Message::Mode>())
        .def("get_header_flag", &Message::getHeaderFlag)
        .def("set_header_flag", &Message::setHeaderFlag)
        .def("clear_header_flag", &Message::clearHeaderFlag)
        .def("is_dnsssec_supported", &Message::isDNSSECSupported)
        .def("set_dnssec_supported", &Message::setDNSSECSupported)
        .def("parse_header", &Message::parseHeader)
        .def("get_udp_size", &Message::getUDPSize)
        .def("set_udp_size", &Message::setUDPSize)
        .def("get_qid", &Message::getQid)
        .def("set_qid", &Message::setQid)
        .def("get_rcode", &Message::getRcode, return_internal_reference<>())
        .def("set_rcode", &Message::setRcode)
        .def("get_opcode", &Message::getOpcode, return_internal_reference<>())
        .def("set_opcode", &Message::setOpcode, with_custodian_and_ward<1,2>())
        .def("to_text", &Message::toText)
        .def("get_rr_count", &Message::getRRCount)
        .def("add_question", (void (Message:: *)(QuestionPtr))&Message::addQuestion)
        .def("add_question", (void (Message:: *)(const Question&))&Message::addQuestion)
        //.def("remove_question", &Message::removeQuestion)
        .def("add_rrset", &Message::addRRset, add_rrset_overloads(args("section","rrset","sign")))
        //.def("remove_rrset", &Message::removeRRset)
        .def("clear", &Message::clear)
        .def("make_response", &Message::makeResponse)
        .def("to_wire", &Message::toWire)
        .def("from_wire", &Message::fromWire);

    class_<Question_iterator_wrapper>("question_iter", init<const Message &>())
        .def("get_question", &Question_iterator_wrapper::getQuestion)
        .def("is_last", &Question_iterator_wrapper::isLast)
        .def("next", &Question_iterator_wrapper::next);

    class_<Section_iterator_wrapper>("section_iter", init<const Message &, const Section &>())
        .def("get_rrset", &Section_iterator_wrapper::getRRset)
        .def("is_last", &Section_iterator_wrapper::isLast)
        .def("next", &Section_iterator_wrapper::next);
}
 
