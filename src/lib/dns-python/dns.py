"""Python C bindings"""

import bind10_dns_noboost

class Name(bind10_dns_noboost.cName):
    """Python shadow class of cName"""

    def __init__(self, *args):
        """initializer"""
        super(Name, self).__init__(*args)

    def __len__(self):
        """length"""
        return self.getLength()

    def __str__(self):
        """string"""
        return self.toText()

    def __repr__(self):
        """representation"""
        return '<Name: ' + str(self) +'>'

class MessageRenderer(bind10_dns_noboost.cMessageRenderer):
    """Python shadow class of cMessageRenderer"""

    def __init__(self):
        """initializer"""
        super(MessageRenderer, self).__init__()

def fromText(text, downcase=False):
    """fromText factory"""
    return Name(text, downcase)

def fromWire(wire, position, downcase=False):
    """fromWire factory"""
    n = Name(wire, position, downcase)
    return (n, n.getPosition() - position)

def compare(n1, n2):
    """compare"""
    ncr = n1.compare(n2)
    return (ncr.getOrder(), \
                ncr.getCommonLabels(), \
                bind10_dns_noboost.NameRelation[ncr.getRelation()])

def concatenate(n1, n2):
    """concatenate"""
    return n1.concatenate(n2)
