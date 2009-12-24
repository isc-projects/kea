#ifndef _ISC_DATA_H
#define _ISC_DATA_H 1

#include <string>
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>

#include <iostream>

namespace isc { namespace data {

    // todo: include types and called function in the exception
    class TypeError : public std::exception {
    public:
        TypeError(std::string m = "Attempt to use function on wrong Element type") : msg(m) {}
        ~TypeError() throw() {}
        const char* what() const throw() { return msg.c_str(); }
    private:
        std::string msg;
    };

    class ParseError : public std::exception {
    public:
        ParseError(std::string m = "Parse error in element data", int l = 0, int p = 0) : msg(m), line(l), pos(p) {}
        ~ParseError() throw() {}
        const char* what() const throw();
    private:
        std::string msg;
        int line;
        int pos;
    };

    class DecodeError : public std::exception {
    public:
        DecodeError(std::string m = "Wire-format data is invalid") : msg(m) {}
        ~DecodeError() throw() {}
        const char* what() const throw() { return msg.c_str(); }
    private:
        std::string msg;
    };
    
    class Element;
    typedef boost::shared_ptr<Element> ElementPtr;

    class Element {
        
    private:
        // technically the type could be omitted; is it useful?
        // should we remove it or replace it with a pure virtual
        // function getType?
        int type;

    protected:
        Element(int t) { type = t; }

    public:
        enum types { integer, real, boolean, string, list, map };
        // base class; make dtor virtual
        virtual ~Element() {};

        // returns the type of this element
        int getType() { return type; };
        
        // pure virtuals, every derived class must implement these

        // returns a string representing the Element and all its
        // child elements; note that this is different from stringValue(),
        // which only returns the single value of a StringElement
        // A MapElement will be represented as { "name1": <value1>, "name2", <value2>, .. }
        // A ListElement will be represented as [ <item1>, <item2>, .. ]
        // All other elements will be represented directly
        virtual std::string str() = 0;

        // returns an xml representation for the Element and all its
        // child elements
        virtual std::string strXML(size_t prefix = 0) = 0;

        // returns the wireformat for the Element and all its child
        // elements
        virtual std::string toWire(int omit_length = 1) = 0;

        // Specific getters for each type. These functions only
        // work on their corresponding Element type. For all other
        // types, a TypeError is thrown.
        // If you want an exception-safe getter method, use
        // getValue() below
        virtual int intValue() { throw TypeError(); };
        virtual double doubleValue() { throw TypeError(); };
        virtual bool boolValue() { throw TypeError(); };
        virtual std::string stringValue() { throw TypeError(); };
        virtual const std::vector<boost::shared_ptr<Element> >& listValue() { throw TypeError(); }; // replace with real exception or empty vector?
        virtual const std::map<std::string, boost::shared_ptr<Element> >& mapValue() { throw TypeError(); }; // replace with real exception or empty map?

        // Other functions for specific subtypes

        // for lists
        virtual ElementPtr get(const int i) { throw TypeError(); };
        virtual void set(const int i, ElementPtr element) { throw TypeError(); };
        virtual void add(ElementPtr element) { throw TypeError(); };
        virtual void remove(const int i) { throw TypeError(); };
        virtual size_t size() { throw TypeError(); };

        // for maps
        virtual ElementPtr get(const std::string& name) { throw TypeError(); } ;
        virtual void set(const std::string& name, ElementPtr element) { throw TypeError(); };
        virtual void remove(const std::string& name) { throw TypeError(); };
        virtual bool contains(const std::string& s) { throw TypeError(); }
        virtual ElementPtr find(const std::string& identifier) { throw TypeError(); };
        virtual bool find(const std::string& id, ElementPtr& t) { return false; };

        //
        // the _value() functions return false if the given reference
        // is of another type than the element contains
        // By default it always returns false; the derived classes
        // should override the function for their type, copying their
        // data to the given reference and returning true
        //
        virtual bool getValue(int& t) { return false; };
        virtual bool getValue(double& t) { return false; };
        virtual bool getValue(bool& t) { return false; };
        virtual bool getValue(std::string& t) { return false; };
        virtual bool getValue(std::vector<ElementPtr>& t) { return false; };
        virtual bool getValue(std::map<std::string, ElementPtr>& t) { return false; };

        //
        // Exception-safe setters. Return false if the Element is not
        // the right type. Set the value and return true if the Elements
        // is of the correct type
        //
        virtual bool setValue(const int v) { return false; };
        virtual bool setValue(const double v) { return false; };
        virtual bool setValue(const bool t) { return false; };
        virtual bool setValue(const std::string& v) { return false; };
        virtual bool setValue(const std::vector<ElementPtr>& v) { return false; };
        virtual bool setValue(const std::map<std::string, ElementPtr>& v) { return false; };

        // should we move all factory functions to a different class
        // so as not to burden the Element base with too many functions?
        // and/or perhaps even to a separate header?

        // direct factory functions; will simply wrap
        // the argument in a shared Element pointer object
        // these return a NULL shared pointer if no memory could be
        // allocated
        static ElementPtr create(const int i);
        static ElementPtr create(const double d);
        static ElementPtr create(const bool b);
        static ElementPtr create(const std::string& s);
        // need both std:string and char *, since c++ will match
        // bool before std::string when you pass it a char *
        static ElementPtr create(const char *s) { return create(std::string(s)); }; 
        static ElementPtr create(const std::vector<ElementPtr>& v);
        static ElementPtr create(const std::map<std::string, ElementPtr>& m);

        // compound factory functions
        // return a NULL ElementPtr if there is a parse error or
        // the memory could not be allocated
        // example:
        // ElementPtr my_element = Element::createFromString("{\"foo\": [ 1, 2, false ] }");
        //static ElementPtr createFromString(std::stringstream& in);
        static ElementPtr createFromString(const std::string& in);
        static ElementPtr createFromString(std::istream& in) throw(ParseError);
        // make this one private?
        static ElementPtr createFromString(std::istream& in, int& line, int &pos) throw(ParseError);
        
        //static ElementPtr create_from_xml(std::stringstream& in);

        // factory functions for wireformat
        static ElementPtr fromWire(std::stringstream& in, int length);
        static ElementPtr fromWire(const std::string& s);
    };

    class IntElement : public Element {
        int i;

    public:
        IntElement(int v) : Element(integer), i(v) { };
        int intValue() { return i; }
        bool getValue(int& t) { t = i; return true; };
        bool setValue(const int v) { i = v; return true; };
        std::string str();
        std::string strXML(size_t prefix = 0);
        std::string toWire(int omit_length = 1);
    };

    class DoubleElement : public Element {
        double d;

    public:
        DoubleElement(double v) : Element(real), d(v) {};
        double doubleValue() { return d; }
        bool getValue(double& t) { t = d; return true; };
        bool setValue(const double v) { d = v; return true; };
        std::string str();
        std::string strXML(size_t prefix = 0);
        std::string toWire(int omit_length = 1);
    };

    class BoolElement : public Element {
        bool b;

    public:
        BoolElement(const bool v) : Element(boolean), b(v) {};
        bool boolValue() { return b; }
        bool getValue(bool& t) { t = b; return true; };
        bool setValue(const bool v) { b = v; return true; };
        std::string str();
        std::string strXML(size_t prefix = 0);
        std::string toWire(int omit_length = 1);
    };
    
    class StringElement : public Element {
        std::string s;

    public:
        StringElement(std::string v) : Element(string), s(v) {};
        std::string stringValue() { return s; };
        bool getValue(std::string& t) { t = s; return true; };
        bool setValue(const std::string& v) { s = v; return true; };
        std::string str();
        std::string strXML(size_t prefix = 0);
        std::string toWire(int omit_length = 1);
    };

    class ListElement : public Element {
        std::vector<ElementPtr> l;

    public:
        ListElement(std::vector<ElementPtr> v) : Element(list), l(v) {};
        const std::vector<ElementPtr>& listValue() { return l; }
        bool getValue(std::vector<ElementPtr>& t) { t = l; return true; };
        bool setValue(const std::vector<ElementPtr>& v) { l = v; return true; };
        ElementPtr get(int i) { return l.at(i); };
        void set(int i, ElementPtr e) { l[i] = e; };
        void add(ElementPtr e) { l.push_back(e); };
        void remove(int i) { l.erase(l.begin() + i); };
        std::string str();
        std::string strXML(size_t prefix = 0);
        std::string toWire(int omit_length = 1);
        size_t size() { return l.size(); }
    };

    class MapElement : public Element {
        std::map<std::string, ElementPtr> m;

    public:
        MapElement(std::map<std::string, ElementPtr> v) : Element(map), m(v) {};
        const std::map<std::string, ElementPtr>& mapValue() { return m; }
        bool getValue(std::map<std::string, ElementPtr>& t) { t = m; return true; };
        bool setValue(std::map<std::string, ElementPtr>& v) { m = v; return true; };
        ElementPtr get(const std::string& s) { return m[s]; };
        void set(const std::string& s, ElementPtr p) { m[s] = p; };
        void remove(const std::string& s) { m.erase(s); }
        bool contains(const std::string& s) { return m.find(s) != m.end(); }
        std::string str();
        std::string strXML(size_t prefix = 0);
        std::string toWire(int omit_length = 1);
        
        //
        // Encode into the CC wire format.
        //
        void toWire(std::ostream& ss);

        // we should name the two finds better...
        // find the element at id; raises TypeError if one of the
        // elements at path except the one we're looking for is not a
        // mapelement.
        // returns an empty element if the item could not be found
        ElementPtr find(const std::string& id);

        // find the Element at 'id', and store the element pointer in t
        // returns true if found, or false if not found (either because
        // it doesnt exist or one of the elements in the path is not
        // a MapElement)
        bool find(const std::string& id, ElementPtr& t);
    };

    bool isNull(ElementPtr p);
} }

// add a << operator for output streams so we can do
// ElementPtr foo = ...
// cout << "Element: " << foo;
std::ostream& operator <<(std::ostream &out, const isc::data::ElementPtr& e);

#endif // _ISC_DATA_H
