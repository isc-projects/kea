// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

#include <exceptions/exceptions.h>
#include <cc/data.h>

using namespace std;
using namespace isc;
using namespace isc::data;


/// @brief API documentation generator
class DocGen {
public:

    /// Output location of a file.
    const string OUTPUT = "guide/api.xml";

    /// Controls whether to print out extra information.
    bool verbose = false;

    /// @brief Load JSON files that each contain description of an API command
    ///
    /// @param files a vector with names of files.
    void loadFiles(const vector<string>& files) {

        map <string, ElementPtr> commands;

        int cnt = 0;

        int errors = 0; // number of errors encountered

        try {
            for (auto f : files) {
                string cmd = f;
                size_t pos = f.find_last_of('/');
                if (pos != string::npos) {
                    cmd = f.substr(pos + 1, -1);
                }
                cmd = cmd.substr(0, cmd.find("."));

                if (cmd == "_template") {
                    cout << "Skipping template file (_template.json)" << endl;
                    continue;
                }

                try {
                    cout << "Loading description of command " << cmd << "... ";
                    ElementPtr x = Element::fromJSONFile(f, false);
                    cout << "loaded, sanity check...";

                    sanityCheck(f, x);

                    cmds_.insert(make_pair(cmd, x));
                    cout << " looks ok." << endl;

                } catch (const exception& e) {
                    cout << "ERROR: " << e.what() << endl;
                    errors++;
                }

                if (errors) {
                    continue;
                }

                cnt++;
            }
        } catch (const Unexpected& e) {
            isc_throw(Unexpected, e.what() << " while processing "
                      << cnt + 1 << " file out of " << files.size());
        }

        cout << "Loaded " << cmds_.size() << " commands out of " << files.size()
             << " file(s), " << errors << " error(s) detected." << endl;
        if (errors) {
            isc_throw(Unexpected, errors << " error(s) detected while loading JSON files");
        }
    }

    /// @brief checks if mandatory string parameter is specified
    ///
    /// @param x a map that is being checked
    /// @param name name of the string element expected to be there
    /// @param fname name of the file (used in error reporting)
    /// @throw Unexpected if missing, different type or empty
    void requireString(const ElementPtr& x, const string& name, const string& fname) {
        if (!x->contains(name)) {
            isc_throw(Unexpected, "Mandatory '" + name + " field missing while "
                      "processing file " + fname);
        }
        if (x->get(name)->getType() != Element::string) {
            isc_throw(Unexpected, "'" + name + " field is present, but is not a string"
                      " in file " + fname);
        }
        if (x->get(name)->stringValue().empty()) {
            isc_throw(Unexpected, "'" + name + " field is present, is a string, but is "
                      "empty in file " + fname);
        }
    }

    /// @brief checks if mandatory list parameter is specified
    ///
    /// @param x a map that is being checked
    /// @param name name of the list element expected to be there
    /// @param fname name of the file (used in error reporting)
    /// @throw Unexpected if missing, different type or empty
    void requireList(const ElementPtr& x, const string& name, const string& fname) {
        if (!x->contains(name)) {
            isc_throw(Unexpected, "Mandatory '" + name + " field missing while "
                      "processing file " + fname);
        }
        if (x->get(name)->getType() != Element::list) {
            isc_throw(Unexpected, "'" + name + " field is present, but is not a list "
                      "in file " + fname);
        }

        ConstElementPtr l = x->get(name);

        if (l->size() == 0) {
            isc_throw(Unexpected, "'" + name + " field is a list, but is empty in file "
                      + fname);
        }

        // todo: check that every element is a string
    }

    /// @brief Checks that the essential parameters for each command are defined
    ///
    /// @param fname name of the file the data was read from (printed if error is detected)
    /// @param x a JSON map that contains content of the file
    void sanityCheck(const string& fname, const ElementPtr& x) {
        requireString(x, "name", fname);
        requireString(x, "brief", fname);
        requireList  (x, "support", fname);
        requireString(x, "avail", fname);
        requireString(x, "brief", fname);

        // They're optional.
        //requireString(x, "cmd-syntax", fname);
        //requireString(x, "cmd-comment", fname);
        //requireString(x, "resp-syntax", fname);
        //requireString(x, "resp-comment", fname);
    }

    /// @brief Writes ISC copyright note to the stream
    ///
    /// @param f stream to write copyrights to
    void generateCopyright(stringstream& f) {
        f << "<!--" << endl;
        f << " - Copyright (C) 2018 Internet Systems Consortium, Inc. (\"ISC\")" << endl;
        f << " -" << endl;
        f << " - This Source Code Form is subject to the terms of the Mozilla Public" << endl;
        f << " - License, v. 2.0. If a copy of the MPL was not distributed with this" << endl;
        f << " - file, You can obtain one at http://mozilla.org/MPL/2.0/." << endl;
        f << " -->" << endl;
        f << endl;
        f << "<!-- autogenerated using cmd_docgen. Do not edit by hand! -->" << endl;
    }

    /// @brief generates a link to command
    ///
    /// @param f stream to write the generated link to
    /// @param cmd name of the command
    void generateCmdLink(stringstream& f, const string& cmd) {
        f << "<command><link linkend=\"ref-" << cmd << "\">" << cmd
          << "</link></command>" << endl;
    }

    /// @brief generates lists of all commands.
    ///
    /// Currently there are several lists (or rather lists of lists). They all enumerate
    /// commands, but each list serving a different purpose:
    /// - list of commands supported by a daemon
    /// - list of commands provided by a hook
    ///
    /// @param f stream to write the generated lists to
    void generateLists(stringstream& f) {
        // Generate a list of all commands
        f << "  <para>Kea currently supports " << cmds_.size() << " commands:" << endl;

        bool first = true;
        for (auto cmd : cmds_) {
            if (!first) {
                f << ", ";
            }
            generateCmdLink(f, cmd.first);

            first = false;
        }

        f << ".</para>" << endl;

        // Generate a list of components:
        set<string> all_daemons;
        set<string> all_hooks;
        for (auto cmd : cmds_) {
            auto daemons = cmd.second->get("support");
            auto hook = cmd.second->get("hook");
            for (int i = 0; i < daemons->size(); i++) {
                string daemon = daemons->get(i)->stringValue();
                if (all_daemons.find(daemon) == all_daemons.end()) {
                    all_daemons.insert(daemon);
                }
            }
            if (hook) {
                string hook_txt = hook->stringValue();
                if (all_hooks.find(hook_txt) == all_hooks.end()) {
                    all_hooks.insert(hook_txt);
                }
            }
        }

        cout << all_daemons.size() << " daemon(s) detected." << endl;
        cout << all_hooks.size() << " hook lib(s) detected." << endl;

        for (auto daemon : all_daemons) {
            f << "<para xml:id=\"commands-" << daemon << "\">"
              << "Commands supported by " << daemon << " daemon: ";

            bool first = true;
            for (auto cmd : cmds_) {

                auto daemons = cmd.second->get("support");
                for (auto d : daemons->listValue()) {
                    if (d->stringValue() == daemon) {
                        if (!first) {
                            f << ", ";
                        }
                        generateCmdLink(f, cmd.first);
                        first = false;
                        break; // get to next command
                    }
                }
            }

            f << ".</para>" << endl;
        }


        for (auto hook : all_hooks) {
            f << "<para xml:id=\"commands-" << hook << "-lib\">"
              << "Commands supported by " << hook << " hook library: ";

            bool first = true;
            for (auto cmd : cmds_) {

                auto daemon_hook = cmd.second->get("hook");
                if (!daemon_hook || daemon_hook->stringValue() != hook) {
                    continue;
                }
                if (!first) {
                    f << ", ";
                }
                generateCmdLink(f, cmd.first);
                first = false;
            }

            f << ".</para>" << endl;
        }

    }

    /// @brief generates the whole API documentation
    void generateOutput() {

        stringstream f;

        generateCopyright(f);

        f << "<appendix xmlns=\"http://docbook.org/ns/docbook\" version=\"5.0\" xml:id=\"api\">"
          << endl;
        f << "  <title>API Reference</title>" << endl;


        generateLists(f);

        // Generate actual commands references.
        generateCommands(f);

        f << "</appendix>" << endl;

        ofstream file(OUTPUT.c_str(), ofstream::trunc);
        file << f.str();
        if (verbose) {
            cout << "----------------" << endl;
            cout << f.str();
            cout << "----------------" << endl;
        }
        file.close();

        cout << "Output written to " << OUTPUT << endl;
    }

    /// @brief generate sections for all commands
    ///
    /// @param f stream to write the commands to
    void generateCommands(stringstream& f){

        for (auto cmd : cmds_) {
            f << "<!-- start of " << cmd.first << " -->" << endl;
            f << "<section xml:id=\"reference-" << cmd.first << "\">" << endl;
            f << "<title>" << cmd.first << " reference</title>" << endl;
            generateCommand(f, cmd.second);
            f << "</section>" << endl;
            f << "<!-- end of " << cmd.first << " -->" << endl;
            f << endl;
        }
    }

    /// @brief replace all strings
    ///
    /// @param str [in,out] this string will have some replacements
    /// @param from what to replace
    /// @param to what to replace with
    void replaceAll(std::string& str, const std::string& from, const std::string& to) {
        if(from.empty())
            return;
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length();
        }
    }

    /// @brief escapes string to be safe for XML (docbook)
    ///
    /// @param txt string to be escaped
    /// @return escaped string
    string escapeString(string txt) {

        replaceAll(txt, "<", "&lt;");
        replaceAll(txt, ">", "&gt;");
        return (txt);
    }

    /// @brief generates standard description of command's response
    ///
    /// If a command doesn't have response syntax specified, we will
    /// assume it follows the usual syntax and provide the default description.
    string standardResponseSyntax() {
        stringstream t;

        t << "{" << endl
          << "    \"result\": <integer>," << endl
          << "    \"text\": <string>" << endl
          << "}" << endl;
        return (t.str());
    }

    /// @brief generates standard description of command's comment
    ///
    /// If a command doesn't have response syntax comment specified, we will
    /// assume it follows the usual syntax and provide the default description.
    string standardResponseComment() {
        stringstream t;

        t << "Result is an integer representation of the status. Currently supported"
          << " statuses are:" << endl
          << "<itemizedlist>" << endl
          << "  <listitem><para>0 - success</para></listitem>" << endl
          << "  <listitem><para>1 - error</para></listitem>" << endl
          << "  <listitem><para>2 - unsupported</para></listitem>" << endl
          << "  <listitem><para>3 - empty (command was completed successfully, but "
          <<                        "no data was affected or returned)</para>"
          <<                        "</listitem>" << endl
          << "</itemizedlist>" << endl;
        return (t.str());
    }

    /// @brief generates command description
    ///
    /// @param f stream to write the description to
    /// @param cmd pointer to JSON structure that describes the command
    void generateCommand(stringstream& f, const ElementPtr& cmd) {

        // command overview
        f << "<para xml:id=\"ref-" << cmd->get("name")->stringValue() << "\"><command>"
          << cmd->get("name")->stringValue() << "</command> - "
          << cmd->get("brief")->stringValue() << "</para>" << endl << endl;

        // command can be issued to the following daemons
        f << "<para>Supported by: ";
        ConstElementPtr daemons = cmd->get("support");
        for (int i = 0; i < daemons->size(); i++) {
            if (i) {
                f << ", ";
            }

            f << "<command><link linkend=\"commands-" << daemons->get(i)->stringValue()
              << "\">" << daemons->get(i)->stringValue() << "</link></command>";
        }
        f << "</para>" << endl << endl;

        // availability
        f << "<para>Availability: " << cmd->get("avail")->stringValue();
        auto hook = cmd->get("hook");
        if (hook) {
            f << " (<link linkend=\"commands-" << hook->stringValue() << "-lib\">"
              << hook->stringValue() << "</link>  hook)";
        } else {
            f << " (built-in)";
        }

        f << "</para>" << endl << endl;

        // description and examples
        f << "<para>Description and examples: See <xref linkend=\"command-"
          << cmd->get("name")->stringValue() << "\"/></para>" << endl << endl;

        // Command syntax:
        f << "<para>Command syntax:" << endl;
        if (cmd->contains("cmd-syntax")) {
            f << "  <screen>" << escapeString(cmd->get("cmd-syntax")->stringValue())
              << "</screen>" << endl;
        } else {
            f << "  <screen>{" << endl
              << "    \"command\": \"" << cmd->get("name")->stringValue() << "\"" << endl
              << "}</screen>" << endl;
        }
        if (cmd->contains("cmd-comment")) {
            f << escapeString(cmd->get("cmd-comment")->stringValue());
        }
        f << "</para>" << endl << endl;

        // Response syntax
        f << "<para>Response syntax:" << endl
          << "  <screen>";

        if (cmd->contains("resp-syntax")) {
            f << escapeString(cmd->get("resp-syntax")->stringValue());
        } else {
            f << escapeString(standardResponseSyntax());
        }
        f << "</screen>" << endl;

        if (cmd->contains("resp-comment")) {
            f << cmd->get("resp-comment")->stringValue();
        } else {
            f << standardResponseComment();
        }
        f << "</para>" << endl << endl;
    }

    map<string, ElementPtr> cmds_;
};

int main(int argc, const char*argv[]) {

    vector<string> files;

    for (int i = 1; i < argc; i++) {
        files.push_back(string(argv[i]));
    }

    cout << "Loading " << files.size() << " files(s)." << endl;

    try {
        DocGen doc_gen;

        doc_gen.loadFiles(files);

        doc_gen.generateOutput();
    } catch (const exception& e) {
        cerr << "ERROR: " << e.what() << endl;
    }

    return (0);
}
