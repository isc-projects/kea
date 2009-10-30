#ifndef _ISC_DATA_H
#define _ISC_DATA_H 1

#include <string>
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>

#include <iostream>

namespace ISC { namespace Data {

    // todo: include types and called function in the exception
    class TypeError : public std::exception {
    public:
        TypeError(std::string m = "Attempt to use function on wrong Element type") : msg(m) {}
        ~TypeError() throw() {}
        const char* what() const throw() { return msg.c_str(); }
    private:
        std::string msg;
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
        // function get_type?
        int type;

    protected:
        Element(int t) { type = t; }

    public:
        enum types { integer, real, boolean, string, list, map };
        // base class; make dtor virtual
        virtual ~Element() {};

        int get_type() { return type; };
        // pure virtuals, every derived class must implement these
        virtual std::string str() = 0;
        virtual std::string str_xml(size_t prefix = 0) = 0;
        virtual std::string to_wire(int omit_length = 1) = 0;

        // virtual function templates must match, so we
        // need separate getters for all subclassed types
        // since all derived types only implement their own specific
        // ones, we provide a default implementation
        // These should probably throw an exception
        // These could also be removed if we want to force the user
        // to use get_value()
        virtual int int_value() { throw TypeError(); };
        virtual double double_value() { throw TypeError(); };
        virtual bool bool_value() { throw TypeError(); };
        virtual std::string string_value() { throw TypeError(); };
        virtual const std::vector<boost::shared_ptr<Element> >& list_value() { throw TypeError(); }; // replace with real exception or empty vector?
        virtual const std::map<std::string, boost::shared_ptr<Element> >& map_value() { throw TypeError(); }; // replace with real exception or empty map?

        // hmm, these are only for specific subtypes, but we would
        // like to call them on the ElementPtr...

        // for lists
        // TODO: what to do as default implementation (ie. when element of wrong type)?
        virtual ElementPtr get(const int i) { throw TypeError(); };
        virtual void set(const int i, ElementPtr element) { throw TypeError(); };
        virtual void add(ElementPtr element) { throw TypeError(); };
        virtual void remove(ElementPtr element) { throw TypeError(); };

        // for maps
        // TODO: what to do as default implementation (ie. when element of wrong type)?
        virtual ElementPtr get(const std::string& name) { throw TypeError(); } ;
        virtual void set(const std::string& name, ElementPtr element) { throw TypeError(); };
        virtual void remove(const std::string& name) { throw TypeError(); };
        virtual ElementPtr find(const std::string& identifier) { throw TypeError(); };
        virtual bool find(const std::string& id, ElementPtr& t) { return false; };

        //
        // the _value() functions return false if the given reference
        // is of another type than the element contains
        // By default it always returns false; the derived classes
        // should override the function for their type, copying their
        // data to the given reference and returning true
        //
        virtual bool get_value(int& t) { return false; };
        virtual bool get_value(double& t) { return false; };
        virtual bool get_value(bool& t) { return false; };
        virtual bool get_value(std::string& t) { return false; };
        virtual bool get_value(std::vector<ElementPtr>& t) { return false; };
        virtual bool get_value(std::map<std::string, ElementPtr>& t) { return false; };

        virtual bool set_value(const int v) { return false; };
        virtual bool set_value(const double v) { return false; };
        virtual bool set_value(const bool t) { return false; };
        virtual bool set_value(const std::string& v) { return false; };
        virtual bool set_value(const std::vector<ElementPtr>& v) { return false; };
        virtual bool set_value(const std::map<std::string, ElementPtr>& v) { return false; };

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
        static ElementPtr create_from_string(std::stringstream& in);
        //static ElementPtr create_from_xml(std::stringstream& in);

        static ElementPtr from_wire(std::stringstream& in, int length);
        static ElementPtr from_wire(const std::string& s);
    };

    class IntElement : public Element {
        int i;

    public:
        IntElement(int v) : Element(integer), i(v) { };
        int int_value() { return i; }
        bool get_value(int& t) { t = i; return true; };
        bool set_value(const int v) { i = v; return true; };
        std::string str();
        std::string str_xml(size_t prefix = 0);
        std::string to_wire(int omit_length = 1);
    };

    class DoubleElement : public Element {
        double d;

    public:
        DoubleElement(double v) : Element(real), d(v) {};
        double double_value() { return d; }
        bool get_value(double& t) { t = d; return true; };
        bool set_value(const double v) { d = v; return true; };
        std::string str();
        std::string str_xml(size_t prefix = 0);
        std::string to_wire(int omit_length = 1);
    };

    class BoolElement : public Element {
        bool b;
		
    public:
        BoolElement(const bool v) : Element(boolean), b(v) {};
        bool bool_value() { return b; }
        bool get_value(bool& t) { t = b; return true; };
        bool set_value(const bool v) { b = v; return true; };
        std::string str();
        std::string str_xml(size_t prefix = 0);
        std::string to_wire(int omit_length = 1);
    };
	
    class StringElement : public Element {
        std::string s;

    public:
        StringElement(std::string v) : Element(string), s(v) {};
        std::string string_value() { return s; };
        bool get_value(std::string& t) { t = s; return true; };
        bool set_value(const std::string& v) { s = v; return true; };
        std::string str();
        std::string str_xml(size_t prefix = 0);
        std::string to_wire(int omit_length = 1);
    };

    class ListElement : public Element {
        std::vector<ElementPtr> l;

    public:
        ListElement(std::vector<ElementPtr> v) : Element(list), l(v) {};
        const std::vector<ElementPtr>& list_value() { return l; }
        bool get_value(std::vector<ElementPtr>& t) { t = l; return true; };
        bool set_value(const std::vector<ElementPtr>& v) { l = v; return true; };
        ElementPtr get(int i) { return l[i]; };
        void set(int i, ElementPtr e) { l[i] = e; };
        void add(ElementPtr e) { l.push_back(e); };
        std::string str();
        std::string str_xml(size_t prefix = 0);
        std::string to_wire(int omit_length = 1);
    };

    class MapElement : public Element {
        std::map<std::string, ElementPtr> m;

    public:
        MapElement(std::map<std::string, ElementPtr> v) : Element(map), m(v) {};
        const std::map<std::string, ElementPtr>& map_value() { return m; }
        bool get_value(std::map<std::string, ElementPtr>& t) { t = m; return true; };
        bool set_value(std::map<std::string, ElementPtr>& v) { m = v; return true; };
        ElementPtr get(const std::string& s) { return m[s]; };
        void set(const std::string& s, ElementPtr p) { m[s] = p; };
        void remove(const std::string& s) { m.erase(s); }
        std::string str();
        std::string str_xml(size_t prefix = 0);
        std::string to_wire(int omit_length = 1);
        
        //
        // Encode into the CC wire format.
        //
	void to_wire(std::ostream& ss);

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

} }

// add a << operator for output streams so we can do
// ElementPtr foo = ...
// cout << "Element: " << foo;
std::ostream& operator <<(std::ostream &out, const ISC::Data::ElementPtr& e);

#endif // _ISC_DATA_H
