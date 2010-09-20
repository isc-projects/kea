// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#ifndef _ISC_DATA_H
#define _ISC_DATA_H 1

#include <string>
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>
#include <stdexcept>
#include <exceptions/exceptions.h>

namespace isc { namespace data {

class Element;
// todo: describe the rationale behind ElementPtr?
typedef boost::shared_ptr<Element> ElementPtr;
typedef boost::shared_ptr<const Element> ConstElementPtr;

///
/// \brief A standard Data module exception that is thrown if a function
/// is called for an Element that has a wrong type (e.g. int_value on a
/// ListElement)
///
class TypeError : public isc::Exception {
public:
    TypeError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// \brief A standard Data module exception that is thrown if a parse
/// error is encountered when constructing an Element from a string
///
// i'd like to use Exception here but we need one that is derived from
// runtime_error (as this one is directly based on external data, and
// i want to add some values to any static data string that is provided)
class JSONError : public isc::Exception {
public:
    JSONError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// \brief The \c Element class represents a piece of data, used by
/// the command channel and configuration parts.
///
/// An \c Element can contain simple types (int, real, string, bool and
/// None), and composite types (list and string->element maps)
///
/// Elements should in calling functions usually be referenced through
/// an \c ElementPtr, which can be created using the factory functions
/// \c Element::create() and \c Element::fromJSON()
///
/// Notes to developers: Element is a base class, implemented by a
/// specific subclass for each type (IntElement, BoolElement, etc).
/// Element does define all functions for all types, and defaults to
/// raising a \c TypeError for functions that are not supported for
/// the type in question.
///
class Element {
    
private:
    // technically the type could be omitted; is it useful?
    // should we remove it or replace it with a pure virtual
    // function getType?
    int type;

protected:
    Element(int t) { type = t; }

public:
    // any is a special type used in list specifications, specifying
    // that the elements can be of any type
    enum types { integer, real, boolean, null, string, list, map, any };
    // base class; make dtor virtual
    virtual ~Element() {};

    /// \return the type of this element
    int getType() const { return (type); }

    /// Returns a string representing the Element and all its
    /// child elements; note that this is different from stringValue(),
    /// which only returns the single value of a StringElement
    ///
    /// The resulting string will contain the Element in JSON format.
    ///
    /// \return std::string containing the string representation
    std::string str() const;

    /// Returns the wireformat for the Element and all its child
    /// elements.
    ///
    /// \return std::string containing the element in wire format
    std::string toWire() const;
    void toWire(std::ostream& out) const;

    /// \name pure virtuals, every derived class must implement these

    /// \returns true if the other ElementPtr has the same type and
    ///          value
    virtual bool equals(const Element& other) const = 0;
    
    /// Converts the Element to JSON format and appends it to
    /// the given stringstream.
    virtual void toJSON(std::ostream& ss) const = 0;

    /// \name Type-specific getters
    ///
    /// \brief These functions only
    /// work on their corresponding Element type. For all other
    /// types, a TypeError is thrown.
    /// If you want an exception-safe getter method, use
    /// getValue() below
    //@{
    virtual long int intValue() const
    { isc_throw(TypeError, "intValue() called on non-integer Element"); };
    virtual double doubleValue() const
    { isc_throw(TypeError, "doubleValue() called on non-double Element"); };
    virtual bool boolValue() const
    { isc_throw(TypeError, "boolValue() called on non-Bool Element"); };
    virtual std::string stringValue() const
    { isc_throw(TypeError, "stringValue() called on non-string Element"); };
    virtual const std::vector<ConstElementPtr>& listValue() const {
        // replace with real exception or empty vector?
        isc_throw(TypeError, "listValue() called on non-list Element");
    };
    virtual const std::map<std::string, ConstElementPtr>& mapValue() const {
        // replace with real exception or empty map?
        isc_throw(TypeError, "mapValue() called on non-map Element");
    };
    //@}

    /// \name Exception-safe getters
    ///
    /// \brief The getValue() functions return false if the given reference
    /// is of another type than the element contains
    /// By default it always returns false; the derived classes
    /// override the function for their type, copying their
    /// data to the given reference and returning true
    ///
    //@{
    virtual bool getValue(long int& t);
    virtual bool getValue(double& t);
    virtual bool getValue(bool& t);
    virtual bool getValue(std::string& t);
    virtual bool getValue(std::vector<ConstElementPtr>& t);
    virtual bool getValue(std::map<std::string, ConstElementPtr>& t);
    //@}

    ///
    /// \name Exception-safe setters.
    ///
    /// \brief Return false if the Element is not
    /// the right type. Set the value and return true if the Elements
    /// is of the correct type
    ///
    //@{
    virtual bool setValue(const long int v);
    virtual bool setValue(const double v);
    virtual bool setValue(const bool t);
    virtual bool setValue(const std::string& v);
    virtual bool setValue(const std::vector<ConstElementPtr>& v);
    virtual bool setValue(const std::map<std::string, ConstElementPtr>& v);
    //@}



    // Other functions for specific subtypes

    /// \name ListElement functions
    ///
    /// \brief If the Element on which these functions are called are not
    /// an instance of ListElement, a TypeError exception is thrown.
    //@{
    /// Returns the ElementPtr at the given index. If the index is out
    /// of bounds, this function throws an std::out_of_range exception.
    /// \param i The position of the ElementPtr to return
    virtual ConstElementPtr get(const int i) const;

    /// Sets the ElementPtr at the given index. If the index is out
    /// of bounds, this function throws an std::out_of_range exception.
    /// \param i The position of the ElementPtr to set
    /// \param element The ElementPtr to set at the position
    virtual void set(const size_t i, ConstElementPtr element);

    /// Adds an ElementPtr to the list
    /// \param element The ElementPtr to add
    virtual void add(ConstElementPtr element);

    /// Removes the element at the given position. If the index is out
    /// of nothing happens.
    /// \param i The index of the element to remove.
    virtual void remove(const int i);

    /// Returns the number of elements in the list.
    virtual size_t size() const;
    //@}

    
    /// \name MapElement functions
    ///
    /// \brief If the Element on which these functions are called are not
    /// an instance of MapElement, a TypeError exception is thrown.
    //@{
    /// Returns the ElementPtr at the given key
    /// \param name The key of the Element to return
    /// \return The ElementPtr at the given key
    virtual ConstElementPtr get(const std::string& name) const;

    /// Sets the ElementPtr at the given key
    /// \param name The key of the Element to set
    virtual void set(const std::string& name, ConstElementPtr element);

    /// Remove the ElementPtr at the given key
    /// \param name The key of the Element to remove
    virtual void remove(const std::string& name);

    /// Checks if there is data at the given key
    /// \param name The key of the Element to remove
    /// \return true if there is data at the key, false if not.
    virtual bool contains(const std::string& name) const;

    /// Recursively finds any data at the given identifier. The
    /// identifier is a /-separated list of names of nested maps, with
    /// the last name being the leaf that is returned.
    ///
    /// For instance, if you have a MapElement that contains another
    /// MapElement at the key "foo", and that second MapElement contains
    /// Another Element at key "bar", the identifier for that last
    /// element from the first is "foo/bar".
    ///
    /// \param identifier The identifier of the element to find
    /// \return The ElementPtr at the given identifier. Returns a
    /// null ElementPtr if it is not found, which can be checked with
    /// Element::is_null(ElementPtr e).
    virtual ConstElementPtr find(const std::string& identifier) const;

    /// See \c Element::find()
    /// \param identifier The identifier of the element to find
    /// \param t Reference to store the resulting ElementPtr, if found.
    /// \return true if the element was found, false if not.
    virtual bool find(const std::string& identifier, ConstElementPtr t) const;
    //@}


    /// \name Factory functions
    
    // TODO: should we move all factory functions to a different class
    // so as not to burden the Element base with too many functions?
    // and/or perhaps even to a separate header?

    /// \name Direct factory functions
    /// \brief These functions simply wrap the given data directly
    /// in an Element object, and return a reference to it, in the form
    /// of an \c ElementPtr.
    /// These factory functions are exception-free (unless there is
    /// no memory available, in which case bad_alloc is raised by the
    /// underlying system).
    /// (Note that that is different from an NullElement, which
    /// represents an empty value, and is created with Element::create())
    //@{
    static ElementPtr create();
    static ElementPtr create(const long int i);
    static ElementPtr create(const int i) { return (create(static_cast<long int>(i))); };
    static ElementPtr create(const double d);
    static ElementPtr create(const bool b);
    static ElementPtr create(const std::string& s);
    // need both std:string and char *, since c++ will match
    // bool before std::string when you pass it a char *
    static ElementPtr create(const char *s) { return (create(std::string(s))); }

    /// \brief Creates an empty ListElement type ElementPtr.
    static ElementPtr createList();

    /// \brief Creates an empty MapElement type ElementPtr.
    static ElementPtr createMap();
    //@}


    /// \name Compound factory functions

    /// \brief These functions will parse the given string (JSON)
    /// representation  of a compound element. If there is a parse
    /// error, an exception of the type isc::data::JSONError is thrown.

    //@{
    /// Creates an Element from the given JSON string
    /// \param in The string to parse the element from
    /// \return An ElementPtr that contains the element(s) specified
    /// in the given string.
    static ElementPtr fromJSON(const std::string& in);

    /// Creates an Element from the given input stream containing JSON
    /// formatted data.
    ///
    /// \param in The string to parse the element from
    /// \return An ElementPtr that contains the element(s) specified
    /// in the given input stream.
    static ElementPtr fromJSON(std::istream& in) throw(JSONError);
    static ElementPtr fromJSON(std::istream& in, const std::string& file_name) throw(JSONError);

    /// Creates an Element from the given input stream, where we keep
    /// track of the location in the stream for error reporting.
    ///
    /// \param in The string to parse the element from
    /// \param line A reference to the int where the function keeps
    /// track of the current line.
    /// \param line A reference to the int where the function keeps
    /// track of the current position within the current line.
    /// \return An ElementPtr that contains the element(s) specified
    /// in the given input stream.
    // make this one private?
    static ElementPtr fromJSON(std::istream& in, const std::string& file, int& line, int &pos) throw(JSONError);
    //@}

    /// \name Type name conversion functions

    /// Returns the name of the given type as a string
    ///
    /// \param type The type to return the name of
    /// \return The name of the type, or "unknown" if the type
    ///         is not known.
    static std::string typeToName(Element::types type);

    /// Converts the string to the corresponding type
    /// Throws a TypeError if the name is unknown.
    ///
    /// \param type_name The name to get the type of
    /// \return the corresponding type value
    static Element::types nameToType(const std::string& type_name);

    /// \name Wire format factory functions

    /// These function pparse the wireformat at the given stringstream
    /// (of the given length). If there is a parse error an exception
    /// of the type isc::cc::DecodeError is raised.
    
    //@{
    /// Creates an Element from the wire format in the given
    /// stringstream of the given length.
    /// Since the wire format is JSON, thise is the same as
    /// fromJSON, and could be removed.
    ///
    /// \param in The input stringstream.
    /// \param length The length of the wireformat data in the stream
    /// \return ElementPtr with the data that is parsed.
    static ElementPtr fromWire(std::stringstream& in, int length);

    /// Creates an Element from the wire format in the given string
    /// Since the wire format is JSON, thise is the same as
    /// fromJSON, and could be removed.
    ///
    /// \param s The input string
    /// \return ElementPtr with the data that is parsed.
    static ElementPtr fromWire(const std::string& s);
    //@}
};

class IntElement : public Element {
    long int i;

public:
    IntElement(long int v) : Element(integer), i(v) { }
    long int intValue() const { return (i); }
    using Element::getValue;
    bool getValue(long int& t) { t = i; return (true); }
    using Element::setValue;
    bool setValue(const long int v) { i = v; return (true); }
    void toJSON(std::ostream& ss) const;
    bool equals(const Element& other) const;
};

class DoubleElement : public Element {
    double d;

public:
    DoubleElement(double v) : Element(real), d(v) {};
    double doubleValue() const { return (d); }
    using Element::getValue;
    bool getValue(double& t) { t = d; return (true); }
    using Element::setValue;
    bool setValue(const double v) { d = v; return (true); }
    void toJSON(std::ostream& ss) const;
    bool equals(const Element& other) const;
};

class BoolElement : public Element {
    bool b;

public:
    BoolElement(const bool v) : Element(boolean), b(v) {};
    bool boolValue() const { return (b); }
    using Element::getValue;
    bool getValue(bool& t) { t = b; return (true); }
    using Element::setValue;
    bool setValue(const bool v) { b = v; return (true); }
    void toJSON(std::ostream& ss) const;
    bool equals(const Element& other) const;
};

class NullElement : public Element {
public:
    NullElement() : Element(null) {};
    void toJSON(std::ostream& ss) const;
    bool equals(const Element& other) const;
};

class StringElement : public Element {
    std::string s;

public:
    StringElement(std::string v) : Element(string), s(v) {};
    std::string stringValue() const { return (s); }
    using Element::getValue;
    bool getValue(std::string& t) { t = s; return (true); }
    using Element::setValue;
    bool setValue(const std::string& v) { s = v; return (true); }
    void toJSON(std::ostream& ss) const;
    bool equals(const Element& other) const;
};

class ListElement : public Element {
    std::vector<ConstElementPtr> l;

public:
    ListElement() : Element(list) {}
    const std::vector<ConstElementPtr>& listValue() const { return (l); }
    using Element::getValue;
    bool getValue(std::vector<ConstElementPtr>& t) {
        t = l;
        return (true);
    }
    using Element::setValue;
    bool setValue(const std::vector<ConstElementPtr>& v) {
        l = v;
        return (true);
    }
    using Element::get;
    ConstElementPtr get(int i) const { return (l.at(i)); }
    using Element::set;
    void set(size_t i, ConstElementPtr e) {
        l.at(i) = e;
    }
    void add(ConstElementPtr e) { l.push_back(e); };
    using Element::remove;
    void remove(int i) { l.erase(l.begin() + i); };
    void toJSON(std::ostream& ss) const;
    size_t size() const { return (l.size()); }
    bool equals(const Element& other) const;
};

class MapElement : public Element {
    std::map<std::string, ConstElementPtr> m;

public:
    MapElement() : Element(map) {}
    // TODO: should we have direct iterators instead of exposing the std::map here?
    const std::map<std::string, ConstElementPtr>& mapValue() const {
        return (m);
    }
    using Element::getValue;
    bool getValue(std::map<std::string, ConstElementPtr>& t) {
        t = m;
        return (true);
    }
    using Element::setValue;
    bool setValue(std::map<std::string, ConstElementPtr>& v) {
        m = v;
        return (true);
    }
    using Element::get;
    ConstElementPtr get(const std::string& s) const {
        return (contains(s) ? m.find(s)->second : ConstElementPtr());
    }
    using Element::set;
    void set(const std::string& key, ConstElementPtr value);
    using Element::remove;
    void remove(const std::string& s) { m.erase(s); }
    bool contains(const std::string& s) const {
        return (m.find(s) != m.end());
    }
    void toJSON(std::ostream& ss) const;
    
    // we should name the two finds better...
    // find the element at id; raises TypeError if one of the
    // elements at path except the one we're looking for is not a
    // mapelement.
    // returns an empty element if the item could not be found
    ConstElementPtr find(const std::string& id) const;

    // find the Element at 'id', and store the element pointer in t
    // returns true if found, or false if not found (either because
    // it doesnt exist or one of the elements in the path is not
    // a MapElement)
    bool find(const std::string& id, ConstElementPtr t) const;

    bool equals(const Element& other) const;
};

/// Checks whether the given ElementPtr is a NULL pointer
/// \param p The ElementPtr to check
/// \return true if it is NULL, false if not.
bool isNull(ConstElementPtr p);

///
/// \brief Remove all values from the first ElementPtr that are
/// equal in the second. Both ElementPtrs MUST be MapElements
/// The use for this function is to end up with a MapElement that
/// only contains new and changed values (for ModuleCCSession and
/// configuration update handlers)
/// Raises a TypeError if a or b are not MapElements
void removeIdentical(ElementPtr a, ConstElementPtr b);

/// \brief Create a new ElementPtr from the first ElementPtr, removing all
/// values that are equal in the second. Both ElementPtrs MUST be MapElements.
/// The returned ElementPtr will be a MapElement that only contains new and
/// changed values (for ModuleCCSession and configuration update handlers).
/// Raises a TypeError if a or b are not MapElements
ConstElementPtr removeIdentical(ConstElementPtr a, ConstElementPtr b);

/// \brief Merges the data from other into element.
/// (on the first level). Both elements must be
/// MapElements.
/// Every string,value pair in other is copied into element
/// (the ElementPtr of value is copied, this is not a new object)
/// Unless the value is a NullElement, in which case the
/// key is removed from element, rather than setting the value to
/// the given NullElement.
/// This way, we can remove values from for instance maps with
/// configuration data (which would then result in reverting back
/// to the default).
/// Raises a TypeError if either ElementPtr is not a MapElement
void merge(ElementPtr element, ConstElementPtr other);

///
/// \brief Insert the Element as a string into stream.
///
/// This method converts the \c ElemetPtr into a string with
/// \c Element::str() and inserts it into the
/// output stream \c out.
///
/// This function overloads the global operator<< to behave as described in
/// ostream::operator<< but applied to \c ElementPtr objects.
///
/// \param os A \c std::ostream object on which the insertion operation is
/// performed.
/// \param e The \c ElementPtr object to insert.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream& operator<<(std::ostream& out, const Element& e);

bool operator==(const Element& a, const Element& b);
bool operator!=(const Element& a, const Element& b);
} }
#endif // _ISC_DATA_H

// Local Variables: 
// mode: c++
// End: 
