// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <botan/botan.h>
#include <botan/x509self.h>
#include <botan/x509stor.h>
#include <botan/rsa.h>
#include <botan/dsa.h>
#include <botan/data_src.h>
using namespace Botan;

#include <iostream>
#include <fstream>
#include <memory>
#include <getopt.h>

// For cleaner 'does not exist or is not readable' output than
// botan provides
#include <unistd.h>
#include <errno.h>

// This is a simple tool that creates a self-signed PEM certificate
// for use with BIND 10. It creates a simple certificate for initial
// setup. Currently, all values are hardcoded defaults. For future
// versions, we may want to add more options for administrators.

// It will create a PEM file containing a certificate with the following
// values:
// common name: localhost
// organization: BIND10
// country code: US

// Additional error return codes; these are specifically
// chosen to be distinct from validation error codes as
// provided by Botan. Their main use is to distinguish
// error cases in the unit tests.
const int DECODING_ERROR = 100;
const int BAD_OPTIONS = 101;
const int READ_ERROR = 102;
const int WRITE_ERROR = 103;
const int UNKNOWN_ERROR = 104;
const int NO_SUCH_FILE = 105;

void
usage() {
    std::cout << "Usage: b10-certgen [OPTION]..." << std::endl;
    std::cout << "Validate, create, or update a self-signed certificate for "
                 "use with b10-cmdctl" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "-c, --certfile=FILE\t\tfile to read or store the certificate"
              << std::endl;
    std::cout << "-f, --force\t\t\toverwrite existing certficate even if it"
              << std::endl <<"\t\t\t\tis valid" << std::endl;
    std::cout << "-h, --help\t\t\tshow this help" << std::endl;
    std::cout << "-k, --keyfile=FILE\t\tfile to store the generated private key"
              << std::endl;
    std::cout << "-w, --write\t\t\tcreate a new certificate if the given file "
                 "does not exist, or if is is not valid" << std::endl;
    std::cout << "-q, --quiet\t\t\tprint no output when creating or validating"
              << std::endl;
}

/// \brief Returns true if the given file exists and is readable
///
/// \param filename The file to check
/// \return true if file exists and is readable
bool
fileExists(const std::string& filename) {
    return (access(filename.c_str(), R_OK) == 0);
}

/// \brief Helper function for readable error output;
///
/// Returns string representation of X509 result code
/// This does not appear to be provided by Botan itself
///
/// \param code An \c X509_Code instance
/// \return A human-readable c string
const char*
X509CodeToString(const X509_Code& code) {
    // note that this list provides more than we would
    // need in this context, it is just the enum from
    // the source code of Botan.
    switch (code) {
    case VERIFIED:
        return ("verified");
    case UNKNOWN_X509_ERROR:
        return ("unknown x509 error");
    case CANNOT_ESTABLISH_TRUST:
        return ("cannot establish trust");
    case CERT_CHAIN_TOO_LONG:
        return ("certificate chain too long");
    case SIGNATURE_ERROR:
        return ("signature error");
    case POLICY_ERROR:
        return ("policy error");
    case INVALID_USAGE:
        return ("invalid usage");
    case CERT_FORMAT_ERROR:
        return ("certificate format error");
    case CERT_ISSUER_NOT_FOUND:
        return ("certificate issuer not found");
    case CERT_NOT_YET_VALID:
        return ("certificate not yet valid");
    case CERT_HAS_EXPIRED:
        return ("certificate has expired");
    case CERT_IS_REVOKED:
        return ("certificate has been revoked");
    case CRL_FORMAT_ERROR:
        return ("crl format error");
    case CRL_NOT_YET_VALID:
        return ("crl not yet valid");
    case CRL_HAS_EXPIRED:
        return ("crl has expired");
    case CA_CERT_CANNOT_SIGN:
        return ("CA cert cannot sign");
    case CA_CERT_NOT_FOR_CERT_ISSUER:
        return ("CA certificate not for certificate issuer");
    case CA_CERT_NOT_FOR_CRL_ISSUER:
        return ("CA certificate not for crl issuer");
    default:
        return ("Unknown X509 code");
    }
}

class CertificateTool {
public:
    CertificateTool(bool quiet) : quiet_(quiet) {}

    int
    createKeyAndCertificate(const std::string& key_file_name,
                            const std::string& cert_file_name) {
        try {
            AutoSeeded_RNG rng;

            // Create and store a private key
            RSA_PrivateKey key(rng, 2048);

            print("Creating key file " + key_file_name);
            std::ofstream key_file(key_file_name.c_str());
            key_file << PKCS8::PEM_encode(key, rng, "");
            if (!key_file.good()) {
                print(std::string("Error writing to ") + key_file_name +
                      ": " + strerror(errno));
                return WRITE_ERROR;
            }
            key_file.close();

            // Certificate options, currently hardcoded.
            // For a future version we may want to make these
            // settable.
            X509_Cert_Options opts;
            opts.common_name = "localhost";
            opts.organization = "BIND10";
            opts.country = "US";

            opts.CA_key();

            print("Creating certificate file " + cert_file_name);

            // The exact call changed aftert 1.8, adding the
            // hash function option
#if BOTAN_VERSION_CODE >= BOTAN_VERSION_CODE_FOR(1,9,0)
            X509_Certificate cert =
            X509::create_self_signed_cert(opts, key, "SHA-256", rng);
#else
            X509_Certificate cert =
            X509::create_self_signed_cert(opts, key, rng);
#endif

            std::ofstream cert_file(cert_file_name.c_str());
            if (!cert_file.good()) {
                print(std::string("Error writing to ") + cert_file_name +
                      ": " + strerror(errno));
                return (WRITE_ERROR);
            }
            cert_file << cert.PEM_encode();
            cert_file.close();
        } catch(std::exception& e) {
            std::cout << "Error creating key or certificate: " << e.what()
                      << std::endl;
            return (UNKNOWN_ERROR);
        }
        return (0);
    }

    int
    validateCertificate(const std::string& certfile) {
        // Since we are dealing with a self-signed certificate here, we
        // also use the certificate to check itself; i.e. we add it
        // as a trusted certificate, then validate the certficate itself.
        //const X509_Certificate cert(certfile);
        try {
            X509_Store store;
            DataSource_Stream in(certfile);
            store.add_trusted_certs(in);

            const X509_Code result = store.validate_cert(certfile);

            if (result == VERIFIED) {
                print(certfile + " is valid");
            } else {
                print(certfile + " failed to verify: " +
                      X509CodeToString(result));
            }
            return (result);
        } catch (const Botan::Decoding_Error& bde) {
            print(certfile + " failed to verify: " + bde.what());
            return (DECODING_ERROR);
        } catch (const Botan::Stream_IO_Error& bsie) {
            print(certfile + " not read: " + bsie.what());
            return (READ_ERROR);
        }
    }

    /// \brief Runs the tool
    ///
    /// \param create_cert  Create certificate if true, validate if false.
    ///                     Does nothing if certificate exists and is valid.
    /// \param force_create Create new certificate even if it is valid.
    /// \param certfile     Certificate file to read to or write from.
    /// \param keyfile      Key file to write if certificate is created.
    ///                     Ignored if create_cert is false
    /// \return zero on success, non-zero on failure
    int
    run(bool create_cert, bool force_create, const std::string& certfile,
        const std::string& keyfile)
    {
        if (create_cert) {
            // Unless force is given, only create it if the current
            // one is not OK
            if (force_create || !fileExists(certfile) ||
                validateCertificate(certfile) != VERIFIED) {
                return (createKeyAndCertificate(keyfile, certfile));
            } else {
                print(certfile + " exists and is valid. Not creating a new one");
            }
        } else {
            if (!fileExists(certfile)) {
                print(certfile + ": " + strerror(errno));
                return (NO_SUCH_FILE);
            }
            int result = validateCertificate(certfile);
            if (result != 0 && !quiet_) {
                print("Running with -w would overwrite the certificate");
            }
            return (result);
        }
        return (0);
    }
private:
    /// Prints the message to stdout unless quiet_ is true
    void print(const std::string& msg) {
        if (!quiet_) {
            std::cout << msg << std::endl;
        }
    }

    bool quiet_;
};

int
main(int argc, char* argv[])
{
    Botan::LibraryInitializer init;

    // create or check certificate
    bool create_cert = false;
    // force creation even if not necessary
    bool force_create = false;
    // don't print any output
    bool quiet = false;

    // default certificate file
    std::string certfile("cmdctl-certfile.pem");
    // default key file
    std::string keyfile("cmdctl-keyfile.pem");

    // whether or not the above values have been
    // overridden (used in command line checking)
    bool certfile_default = true;
    bool keyfile_default = true;

    struct option long_options[] = {
        { "certfile", required_argument, 0, 'c' },
        { "force", no_argument, 0, 'f' },
        { "help", no_argument, 0, 'h' },
        { "keyfile", required_argument, 0, 'k' },
        { "write", no_argument, 0, 'w' },
        { "quiet", no_argument, 0, 'q' },
        { 0, 0, 0, 0 }
    };

    int opt, option_index;
    while ((opt = getopt_long(argc, argv, "c:fhk:wq", long_options,
                              &option_index)) != -1) {
        switch (opt) {
            case 'c':
                certfile = optarg;
                certfile_default = false;
                break;
            case 'f':
                force_create = true;
                break;
            case 'h':
                usage();
                return (0);
                break;
            case 'k':
                keyfile = optarg;
                keyfile_default = false;
                break;
            case 'w':
                create_cert = true;
                break;
            case 'q':
                quiet = true;
                break;
            default:
                // A message will have already been output about the error.
                return (BAD_OPTIONS);
        }
    }

    if (optind < argc) {
        std::cout << "Error: extraneous arguments" << std::endl << std::endl;
        usage();
        return (BAD_OPTIONS);
    }

    // Some sanity checks on option combinations
    if ((create_cert && certfile_default && !keyfile_default) ||
        (create_cert && !certfile_default && keyfile_default)) {
        std::cout << "Error: keyfile and certfile must both be specified "
                     "if one of them is when calling b10-certgen in write "
                     "mode." << std::endl;
        return (BAD_OPTIONS);
    }
    if (!create_cert && !keyfile_default) {
        std::cout << "Error: keyfile is not used when not in write mode"
                  << std::endl;
        return (BAD_OPTIONS);
    }

    // Initialize the tool and perform the appropriate action(s)
    CertificateTool tool(quiet);
    return (tool.run(create_cert, force_create, certfile, keyfile));
}
