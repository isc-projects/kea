import ISC
import unittest

class TestCCWireEncoding(unittest.TestCase):
    def setUp(self): pass

    def test_to_wire_of_string(self):
        wire = ISC.CC.Message.to_wire({ "simple" : "string" })
        self.assertEqual(wire, b'Skan\x06simple(\x06string')

    def test_from_wire_of_string(self):
        wire = b'Skan\x06simple(\x06string'
        decoded = ISC.CC.Message.from_wire(wire)
        self.assertEqual(decoded["simple"], "string")

    def test_to_wire_of_binary_string(self):
        wire = ISC.CC.Message.to_wire({ "simple" : b'\x01\xff\x02\x85' })
        self.assertEqual(wire, b'Skan\x06simple!\x04\x01\xff\x02\x85')

    def test_from_wire_of_binary_string(self):
        wire = b'Skan\x06simple!\x04\x01\xff\x02\x85'
        decoded = ISC.CC.Message.from_wire(wire)
        self.assertEqual(decoded["simple"], b'\x01\xff\x02\x85')

    def test_to_wire_of_list(self):
        wire = ISC.CC.Message.to_wire({ "simple" : [ "string" ] })
        self.assertEqual(wire, b'Skan\x06simple#\x08(\x06string')

    def test_from_wire_of_list(self):
        wire = b'Skan\x06simple#\x08(\x06string'
        decoded = ISC.CC.Message.from_wire(wire)
        self.assertEqual(decoded["simple"], [ "string" ])

    def test_to_wire_of_hash(self):
        wire = ISC.CC.Message.to_wire({ "simple" : { "string" : 1 }})
        self.assertEqual(wire, b'Skan\x06simple"\n\x06string(\x011')

    def test_from_wire_of_hash(self):
        wire = b'Skan\x06simple"\n\x06string(\x011'
        decoded = ISC.CC.Message.from_wire(wire)
        self.assertEqual(decoded["simple"], { "string" : '1' })

    def test_to_wire_of_none(self):
        wire = ISC.CC.Message.to_wire({ "simple" : None })
        self.assertEqual(wire, b'Skan\x06simple\x04')

    def test_from_wire_of_none(self):
        wire = b'Skan\x06simple\x04'
        decoded = ISC.CC.Message.from_wire(wire)
        self.assertEqual(decoded["simple"], None)

    def test_to_wire_of_empty_string(self):
        wire = ISC.CC.Message.to_wire({ "simple" : "" })
        self.assertEqual(wire, b'Skan\x06simple(\x00')

    def test_from_wire_of_empty_string(self):
        wire = b'Skan\x06simple(\x00'
        decoded = ISC.CC.Message.from_wire(wire)
        self.assertEqual(decoded["simple"], "")

    def test_to_wire_of_utf8_string(self):
        wire = ISC.CC.Message.to_wire({ "simple" : "せんせい" })
        self.assertEqual(wire, b'Skan\x06simple(\x0c\xe3\x81\x9b\xe3\x82\x93\xe3\x81\x9b\xe3\x81\x84')

    def test_from_wire_of_utf8_string(self):
        wire = b'Skan\x06simple(\x0c\xe3\x81\x9b\xe3\x82\x93\xe3\x81\x9b\xe3\x81\x84'
        decoded = ISC.CC.Message.from_wire(wire)
        self.assertEqual(decoded["simple"], "せんせい")

    def test_to_wire_of_utf8_label(self):
        wire = ISC.CC.Message.to_wire({ "せんせい" : "string" })
        self.assertEqual(wire, b'Skan\x0c\xe3\x81\x9b\xe3\x82\x93\xe3\x81\x9b\xe3\x81\x84(\x06string')

    def test_from_wire_of_utf8_label(self):
        wire = b'Skan\x0c\xe3\x81\x9b\xe3\x82\x93\xe3\x81\x9b\xe3\x81\x84(\x06string'
        decoded = ISC.CC.Message.from_wire(wire)
        self.assertEqual(decoded["せんせい"], "string")

    def test_to_wire_of_bool_true(self):
        wire = ISC.CC.Message.to_wire({ "bool": True })
        self.assertEqual(wire, b'Skan\x04bool%\x01\x01')

    def test_to_wire_of_bool_false(self):
        wire = ISC.CC.Message.to_wire({ "bool": False })
        self.assertEqual(wire, b'Skan\x04bool%\x01\x00')

    def test_from_wire_of_bool_true(self):
        wire = b'Skan\x04bool%\x01\x01'
        decoded = ISC.CC.Message.from_wire(wire)
        self.assertEqual(decoded["bool"], True)

    def test_from_wire_of_bool_true(self):
        wire = b'Skan\x04bool%\x01\x00'
        decoded = ISC.CC.Message.from_wire(wire)
        self.assertEqual(decoded["bool"], False)

if __name__ == '__main__':
    unittest.main()
