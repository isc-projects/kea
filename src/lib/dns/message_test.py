from bind10_message import *
from struct import *

id = ["10","35"]
flags = ["85", "00"]
sections = ["00","01","00","02","00","00","00","00"]
query_raw_name = ["04","74","65","73","74","07","65","78","61","6d","70","6c","65","03","63","6f","6d","00"]
query_type_class = ["00","01","00","01"]
answer_compress = ["c0","0c"]
answer1_ttl_type_class_rdlen_rdata = ["00","01","00","01","00","00","0e","10","00","04","c0","00","02","01"]
answer2_ttl_type_class_rdlen_rdata = ["00","01","00","01","00","00","1c","20","00","04","c0","00","02","02"]

bytes = pack("B" * len(query_raw_name), *[int(i,16) for i in query_raw_name])
query_name = name(input_buffer(bytes))
print("query name is ", query_name.to_text())

message_raw_data = id + flags + sections + query_raw_name + query_type_class + answer_compress + answer1_ttl_type_class_rdlen_rdata + answer_compress + \
        answer2_ttl_type_class_rdlen_rdata

m = message(message_mode.PARSE)
message_bytes = pack("B" * len(message_raw_data), *[int(i,16) for i in message_raw_data])
m.from_wire(input_buffer(message_bytes))
if m.get_qid() == int("1035", 16):
    print("id is correct")

if m.get_opcode() == op_code.QUERY():
    print("opcode is correct")

if m.get_rcode() == rcode.NOERROR():
    print("rcode is correct")

if m.get_header_flag(message_flag.QR()):
    print("qr is correct")

if m.get_header_flag(message_flag.RD()):
    print("rd is correct")

if m.get_header_flag(message_flag.AA()):
    print("aa is correct")

if m.get_rr_count(section.QUESTION()) == 1:
    print("qustion rr count is correct")

if m.get_rr_count(section.ANSWER()) == 2:
    print("answer rr count is ok")

if m.get_rr_count(section.AUTHORITY()) == 0 and m.get_rr_count(section.ADDITIONAL()) == 0:
    print("authority and additional rr count is ok")

question_iter = question_iter(m)
question = question_iter.get_question()
print("question name is ", question.get_name().to_text())
if question.get_type() == rr_type.A():
    print("question rr type is A")
if question.get_class() == rr_class.IN():
    print("question rr class is IN")

answer_rrset_iter = section_iter(m, section.ANSWER())
answer = answer_rrset_iter.get_rrset()
print("answer part name is ", answer.get_name().to_text())
if answer.get_type() == rr_type.A() and answer.get_class() == rr_class.IN():
    print("answer part is A record and class IN")

rdata_iter = answer.get_rdata_iterator()
rdata_iter.first()
print("first part of rdata is ", rdata_iter.get_current().to_text())
rdata_iter.next()
print("second part of rdata is", rdata_iter.get_current().to_text())
rdata_iter.next()
if rdata_iter.is_last():
    print("answer part has two rr")
