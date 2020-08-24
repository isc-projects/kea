// Copyright (C) 2012-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MASTER_LEXER_STATE_H
#define MASTER_LEXER_STATE_H 1

#include <dns/master_lexer.h>

namespace isc {
namespace dns {

namespace master_lexer_internal {

/// \brief Tokenization state for \c MasterLexer.
///
/// This is a base class of classes that represent various states of a single
/// tokenization session of \c MasterLexer, i.e., the states used for a
/// single call to \c MasterLexer::getNextToken().
///
/// It follows the convention of the state design pattern: each derived class
/// corresponds to a specific state, and the state transition takes place
/// through the virtual method named \c handle().  The \c handle() method
/// takes the main \c MasterLexer object that holds all necessary internal
/// context, and updates it as necessary; each \c State derived class is
/// completely stateless.
///
/// The initial transition takes place in a static method of the base class,
/// \c start().  This is mainly for implementation convenience; we need to
/// pass options given to \c MasterLexer::getNextToken() for the initial
/// state, so it makes more sense to separate the interface for the transition
/// from the initial state.
///
/// If the whole lexer transition is completed within start(), it sets the
/// identified token and returns NULL; otherwise it returns a pointer to
/// an object of a specific state class that completes the session
/// on the call of handle().
///
/// As is usual in the state design pattern, the \c State class is made
/// a friend class of \c MasterLexer and can refer to its internal details.
/// This is intentional; essentially its a part of \c MasterLexer and
/// is defined as a separate class only for implementation clarity and better
/// testability.  It's defined in a publicly visible header, but that's only
/// for testing purposes.  No normal application or even no other classes of
/// this library are expected to use this class.
class State {
public:
    /// \brief Virtual destructor.
    ///
    /// In our usage this actually doesn't matter, but some compilers complain
    /// about it and we need to silence them.
    virtual ~State() {}

    /// \brief Begin state transitions to get the next token.
    ///
    /// This is the first method that \c MasterLexer needs to call for a
    /// tokenization session.  The lexer passes a reference to itself
    /// and options given in \c getNextToken().
    ///
    /// \throw MasterLexer::ReadError Unexpected I/O error
    /// \throw std::bad_alloc Internal resource allocation failure
    ///
    /// \param lexer The lexer object that holds the main context.
    /// \param options The options passed to getNextToken().
    /// \return A pointer to the next state object or NULL if the transition
    /// is completed.
    static const State* start(MasterLexer& lexer,
                              MasterLexer::Options options);

    /// \brief Handle the process of one specific state.
    ///
    /// This method is expected to be called on the object returned by
    /// start(). In the usual state transition design pattern, it would
    /// return the next state. But as we noticed, we never have another
    /// state, so we simplify it by not returning anything instead of
    /// returning NULL every time.
    ///
    /// \throw MasterLexer::ReadError Unexpected I/O error
    /// \throw std::bad_alloc Internal resource allocation failure
    ///
    /// \param lexer The lexer object that holds the main context.
    virtual void handle(MasterLexer& lexer) const = 0;

    /// \brief Types of states.
    ///
    /// Specific states are basically hidden within the implementation,
    /// but we'd like to allow tests to examine them, so we provide
    /// a way to get an instance of a specific state.
    enum ID {
        CRLF,                  ///< Just seen a carriage-return character
        String,                ///< Handling a string token
        QString,               ///< Handling a quoted string token
        Number                 ///< Handling a number
    };

    /// \brief Returns a \c State instance of the given state.
    ///
    /// This is provided only for testing purposes so tests can check
    /// the behavior of each state separately.  \c MasterLexer shouldn't
    /// need this method.
    static const State& getInstance(ID state_id);

    /// \name Read-only accessors for testing purposes.
    ///
    /// These allow tests to inspect some selected portion of the internal
    /// states of \c MasterLexer.  These shouldn't be used except for testing
    /// purposes.
    ///@{
    bool wasLastEOL(const MasterLexer& lexer) const;
    const MasterToken& getToken(const MasterLexer& lexer) const;
    size_t getParenCount(const MasterLexer& lexer) const;
    ///@}

protected:
    /// \brief An accessor to the internal implementation class of
    /// \c MasterLexer.
    ///
    /// This is provided for specific derived classes as they are not direct
    /// friends of \c MasterLexer.
    ///
    /// \param lexer The lexer object that holds the main context.
    /// \return A pointer to the implementation class object of the given
    /// lexer.  This is never NULL.
    MasterLexer::MasterLexerImpl* getLexerImpl(MasterLexer& lexer) const {
        return (lexer.impl_);
    }
};

} // namespace master_lexer_internal
} // namespace dns
} // namespace isc
#endif  // MASTER_LEXER_STATE_H

// Local Variables:
// mode: c++
// End:
