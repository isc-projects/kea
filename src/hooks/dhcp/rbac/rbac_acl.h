// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RBAC_ACL_H
#define RBAC_ACL_H

#include <cc/data.h>
#include <exceptions/exceptions.h>

#include <list>
#include <map>
#include <set>
#include <string>

#include <boost/shared_ptr.hpp>

#include <rbac/rbac_api.h>

namespace isc {
namespace rbac {

/// @brief Forward declaration of the access control list class.
class Acl;

/// @brief Type of shared pointers to Acl.
typedef boost::shared_ptr<Acl> AclPtr;

/// @brief Type of list of shared pointers to Acl.
typedef std::list<AclPtr> AclList;

/// @brief Type of the access control list table.
typedef std::map<std::string, AclPtr> AclTable;

/// @brief Access control list base class.
class Acl {
public:

    /// @brief Constructor.
    ///
    /// @param name Name of the access control list class.
    /// @throw Unexpected when name is empty.
    Acl(const std::string& name) : name_(name) {
        if (name.empty()) {
            isc_throw(Unexpected, "empty access control list name");
        }
    };

    /// @brief Destructor.
    virtual ~Acl() = default;

    /// @brief Returns the class name.
    ///
    /// @return the class name.
    std::string getClassName() const {
        return (name_);
    }

    /// @brief Match the access control list.
    ///
    /// @param command The command.
    /// @return whether the command matches the access control list.
    virtual bool match(const std::string& command) = 0;

    /// @brief Initialize the access control list table.
    static void initTable();

    /// @brief Parse an access control list.
    ///
    /// @param cfg Configuration of an access control list.
    /// @return the parsed access control list.
    static AclPtr parse(data::ConstElementPtr cfg);

    /// @brief Parse a list of access control lists.
    ///
    /// @param cfg Configuration of a list of access control lists.
    /// @return the list of parsed access control lists.
    static AclList parseList(data::ConstElementPtr cfg);

protected:
    /// @brief The class name.
    std::string name_;
};

/// @brief Alias of an access control list.
/// @note: not used at the exception of its parse class method.
class AliasAcl : public Acl {
public:

    /// @brief Constructor.
    ///
    /// @param acl The aliased acl.
    /// @param name The alias name.
    /// @throw Unexpected when the acl is null.
    AliasAcl(const std::string& name, const AclPtr& acl)
        : Acl("alias"), name_(name), acl_(acl) {
        if (!acl) {
            isc_throw(Unexpected, "null acl in alias");
        }
    }

    /// @brief Match the access control list.
    ///
    /// @param command The command.
    /// @return true when the acl matches, false otherwise.
    virtual bool match(const std::string& command) final {
        return (acl_->match(command));
    }

    /// @brief Returns the name.
    ///
    /// @return the name.
    std::string getName() const {
        return (name_);
    }

    /// @brief Returns the acl.
    ///
    /// @return the acl.
    const AclPtr& getAcl() const {
        return (acl_);
    }

    /// @brief Parse an access control list definition.
    ///
    /// @param def Definition of an access control list.
    static void parse(data::ConstElementPtr def);

private:
    /// @brief The alias name.
    std::string name_;

    /// @brief The access control list.
    AclPtr acl_;
};

/// Boolean operators.

/// @brief Negation of an access control list.
class NotAcl : public Acl {
public:

    /// @brief Constructor.
    ///
    /// @param acl The acl to negate.
    /// @throw Unexpected when the acl is null.
    NotAcl(const AclPtr& acl) : Acl("not"), acl_(acl) {
        if (!acl) {
            isc_throw(Unexpected, "null acl in not");
        }
    }

    /// @brief Match the access control list.
    ///
    /// @param command The command.
    /// @return the negation of the acl matching.
    virtual bool match(const std::string& command) final {
        return (!acl_->match(command));
    }

    /// @brief Returns the acl.
    ///
    /// @return the acl.
    const AclPtr& getAcl() const {
        return (acl_);
    }

private:
    /// @brief The access control list.
    AclPtr acl_;
};

/// @brief Conjunction of access control lists.
class AndAcl : public Acl {
public:

    /// @brief Constructor.
    ///
    /// @param acls Acls to conjugate.
    /// @throw Unexpected when an acl is null.
    AndAcl(const AclList& acls) : Acl("and"), acls_(acls) {
        for (const AclPtr& acl : acls) {
            if (!acl) {
                isc_throw(Unexpected, "null acl in and");
            }
        }
    }

    /// @brief Add an access control list.
    ///
    /// @param acl Acl to add.
    /// @throw Unexpected if the acl is null.
    void add(const AclPtr& acl) {
        if (!acl) {
            isc_throw(Unexpected, "add null acl in and");
        }
        acls_.push_back(acl);
    }

    /// @brief Match the access control list.
    ///
    /// @param command The command.
    /// @return true when all members match, false otherwise.
    virtual bool match(const std::string& command) final {
        for (const AclPtr& acl : acls_) {
            if (!acl->match(command)) {
                return (false);
            }
        }
        return (true);
    }

    /// @brief Returns the acls.
    ///
    /// @return the acls.
    const AclList& getAcls() const {
        return (acls_);
    }

private:
    /// @brief The list of access control lists.
    AclList acls_;
};

/// @brief Disjunction of access control lists.
class OrAcl : public Acl {
public:

    /// @brief Constructor.
    ///
    /// @param acls Acls to disjunct.
    /// @throw Unexpected when an acl is null.
    OrAcl(const AclList& acls) : Acl("or"), acls_(acls) {
        for (const AclPtr& acl : acls) {
            if (!acl) {
                isc_throw(Unexpected, "null acl in or");
            }
        }
    }

    /// @brief Add an access control list.
    ///
    /// @param acl Acl to add.
    /// @throw Unexpected if the acl is null.
    void add(const AclPtr& acl) {
        if (!acl) {
            isc_throw(Unexpected, "add null acl in or");
        }
        acls_.push_back(acl);
    }

    /// @brief Match the access control list.
    ///
    /// @param command The command.
    /// @return true when a member matches, false otherwise.
    virtual bool match(const std::string& command) final {
        for (const AclPtr& acl : acls_) {
            if (acl->match(command)) {
                return (true);
            }
        }
        return (false);
    }

    /// @brief Returns the acls.
    ///
    /// @return the acls.
    const AclList& getAcls() const {
        return (acls_);
    }

private:
    /// @brief The list of access control lists.
    AclList acls_;
};

/// @brief All access control list.
class AllAcl : public Acl {
public:

    /// @brief Constructor.
    AllAcl() : Acl("all") {
    }

    /// @brief Match the access control list.
    ///
    /// @return true.
    virtual bool match(const std::string&) final {
        return (true);
    }
};

/// @brief None access control list.
class NoneAcl : public Acl {
public:

    /// @brief Constructor.
    NoneAcl() : Acl("none") {
    }

    /// @brief Match the access control list.
    ///
    /// @return false.
    virtual bool match(const std::string&) final {
        return (false);
    }
};

/// @brief Explicit access control list.
class CommandsAcl : public Acl {
public:

    /// @brief Constructor.
    ///
    /// @param commands The set of command names.
    CommandsAcl(const std::set<std::string>& commands)
        : Acl("commands"), commands_(commands) {
    }

    /// @brief Add a command name.
    ///
    /// @param command The command name to add.
    void add(const std::string& command) {
        // Insert an already existing member is a noop.
        static_cast<void>(commands_.insert(command));
    }

    /// @brief Match the access control list.
    ///
    /// @return whether the command access matches.
    virtual bool match(const std::string& command) final {
        return (commands_.count(command) != 0);
    }

    /// @brief Returns the command names.
    ///
    /// @return the command names.
    const std::set<std::string>& getCommands() const {
        return (commands_);
    }

private:
    /// @brief The set of command names.
    std::set<std::string> commands_;
};

/// @brief Read or write access control list.
class AccessAcl : public Acl {
public:

    /// @brief Constructor.
    ///
    /// @param access The access read or write.
    AccessAcl(const std::string& access) : Acl("access"), access_(access) {
    }

    /// @brief Match the access control list.
    ///
    /// @return whether the command access matches.
    virtual bool match(const std::string& command) final {
        ApiPtr api(Api::getApiByName(command));
        return (api && (api->getAccess() == access_));
    }

    /// @brief Returns the access.
    ///
    /// @return the access.
    std::string getAccess() const {
        return (access_);
    }

private:
    /// @brief Access (read or write).
    std::string access_;
};

/// @brief Hook access control list.
class HookAcl : public Acl {
public:

    /// @brief Constructor.
    ///
    /// @param hook The hook name.
    HookAcl(const std::string& hook) : Acl("hook"), hook_(hook) {
    }

    /// @brief Match the access control list.
    ///
    /// @return whether the command is registered by the specified hook.
    virtual bool match(const std::string& command) final {
        ApiPtr api(Api::getApiByName(command));
        return (api && (api->getHook() == hook_));
    }

    /// @brief Returns the hook.
    ///
    /// @return the hook.
    std::string getHook() const {
        return (hook_);
    }

private:
    /// @brief Hook name.
    std::string hook_;
};

/// @brief The access control list table.
extern AclTable aclTable;

} // end of namespace rbac
} // end of namespace isc
#endif
