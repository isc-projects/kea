// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
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

#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>

#include <cstring>
#include <iostream>
#include <fstream>
#include <memory>
#include <getopt.h>

// For cleaner 'does not exist or is not readable' output than
// openssl provides
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
// provided by OpenSSL. Their main use is to distinguish
// error cases in the unit tests.
const int DECODING_ERROR = 100;
const int BAD_OPTIONS = 101;
const int READ_ERROR = 102;
const int WRITE_ERROR = 103;
const int UNKNOWN_ERROR = 104;
const int NO_SUCH_FILE = 105;
const int FILE_PERMISSION_ERROR = 106;

void
usage() {
    std::cout << "Usage: b10-certgen [OPTION]..." << std::endl;
    std::cout << "Validate, create, or update a self-signed certificate for "
                 "use with b10-cmdctl" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "-c, --certfile=FILE\t\tfile to read or store the certificate"
              << std::endl;
    std::cout << "-f, --force\t\t\toverwrite existing certificate even if it"
              << std::endl <<"\t\t\t\tis valid" << std::endl;
    std::cout << "-h, --help\t\t\tshow this help" << std::endl;
    std::cout << "-k, --keyfile=FILE\t\tfile to store the generated private key"
              << std::endl;
    std::cout << "-w, --write\t\t\tcreate a new certificate if the given file"
              << std::endl << "\t\t\t\tdoes not exist, or if is is not valid"
              << std::endl;
    std::cout << "-q, --quiet\t\t\tprint no output when creating or validating"
              << std::endl;
}

/// \brief Returns true if the given file exists
///
/// \param filename The file to check
/// \return true if file exists
bool
fileExists(const std::string& filename) {
    return (access(filename.c_str(), F_OK) == 0);
}

/// \brief Returns true if the given file exists and is readable
///
/// \param filename The file to check
/// \return true if file exists and is readable
bool
fileIsReadable(const std::string& filename) {
    return (access(filename.c_str(), R_OK) == 0);
}

/// \brief Returns true if the given file exists and is writable
///
/// \param filename The file to check
/// \return true if file exists and is writable
bool
fileIsWritable(const std::string& filename) {
    return (access(filename.c_str(), W_OK) == 0);
}

class CertificateTool {
public:
    CertificateTool(bool quiet) : quiet_(quiet) {}

    int
    createKeyAndCertificate(const std::string& key_file_name,
                            const std::string& cert_file_name) {
        // Create and store a private key
        print("Creating key file " + key_file_name);
        RSA* rsa = RSA_generate_key(2048, 65537UL, NULL, NULL);
        std::ofstream key_file(key_file_name.c_str());
        if (!key_file.good()) {
            print(std::string("Error writing to ") + key_file_name +
                  ": " + std::strerror(errno));
            return (WRITE_ERROR);
        }
        BIO* key_mem = BIO_new(BIO_s_mem());
        PEM_write_bio_RSAPrivateKey(key_mem, rsa, NULL, NULL, 0, NULL, NULL);
        char* p;
        long len = BIO_get_mem_data(key_mem, &p);
        key_file.write(p, (unsigned) len);
        BIO_free(key_mem);
        if (!key_file.good()) {
            print(std::string("Error writing to ") + key_file_name +
                  ": " + std::strerror(errno));
            return (WRITE_ERROR);
        }
        key_file.close();

        // Certificate options, currently hardcoded.
        // For a future version we may want to make these
        // settable.
        X509* cert = X509_new();
        X509_set_version(cert, 2);
        BIGNUM* serial = BN_new();
        BN_pseudo_rand(serial, 64, 0, 0);
        BN_to_ASN1_INTEGER(serial, X509_get_serialNumber(cert));
        BN_free(serial);
        X509_NAME* name = X509_get_subject_name(cert);
        std::string cn("localhost");
        X509_NAME_add_entry_by_NID(name, NID_commonName, MBSTRING_ASC,
                                   (unsigned char*) cn.c_str(), cn.size(),
                                   -1, 0);
        std::string org("UNKNOWN");
        X509_NAME_add_entry_by_NID(name, NID_organizationName, MBSTRING_ASC,
                                   (unsigned char*) org.c_str(), org.size(),
                                   -1, 0);
        std::string cc("XX");
        X509_NAME_add_entry_by_NID(name, NID_countryName, MBSTRING_ASC,
                                   (unsigned char*) cc.c_str(), cc.size(),
                                   -1, 0);
        X509_set_issuer_name(cert, name);
        X509_gmtime_adj(X509_get_notBefore(cert), 0);
        X509_gmtime_adj(X509_get_notAfter(cert), 60*60*24*365L);
        EVP_PKEY* pkey = EVP_PKEY_new();
        EVP_PKEY_assign_RSA(pkey, rsa);
        X509_set_pubkey(cert, pkey);
        X509V3_CTX ec;
        X509V3_set_ctx_nodb(&ec);
        X509V3_set_ctx(&ec, cert, cert, NULL, NULL, 0);
        const std::string bc_val("critical,CA:TRUE,pathlen:1");
        X509_EXTENSION* bc = X509V3_EXT_conf_nid(NULL, &ec,
                                                 NID_basic_constraints,
                                                 (char*) bc_val.c_str());
        X509_add_ext(cert, bc, -1);
        X509_EXTENSION_free(bc);
        const std::string ku_val=("critical,keyCertSign,cRLSign");
        X509_EXTENSION* ku = X509V3_EXT_conf_nid(NULL, &ec,
                                                 NID_key_usage,
                                                 (char*) ku_val.c_str());
        X509_add_ext(cert, ku, -1);
        X509_EXTENSION_free(ku);
        const std::string ski_val("hash");
        X509_EXTENSION* ski = X509V3_EXT_conf_nid(NULL, &ec,
                                                  NID_subject_key_identifier,
                                                  (char*) ski_val.c_str());
        X509_add_ext(cert, ski, -1);
        X509_EXTENSION_free(ski);
        X509_sign(cert, pkey, EVP_sha256());

        print("Creating certificate file " + cert_file_name);
        std::ofstream cert_file(cert_file_name.c_str());
        if (!cert_file.good()) {
             print(std::string("Error writing to ") + cert_file_name +
                   ": " + std::strerror(errno));
             return (WRITE_ERROR);
        }
        BIO* cert_mem = BIO_new(BIO_s_mem());
        PEM_write_bio_X509(cert_mem, cert);
        p = NULL;
        len = BIO_get_mem_data(cert_mem, &p);
        cert_file.write(p, (unsigned) len);
        BIO_free(cert_mem);
        if (!cert_file.good()) {
            print(std::string("Error writing to ") + cert_file_name +
                  ": " + std::strerror(errno));
            return (WRITE_ERROR);
        }
        cert_file.close();
        X509_free(cert);
        RSA_free(rsa);
        return (0);
    }

    int
    validateCertificate(const std::string& certfile) {
        // Since we are dealing with a self-signed certificate here, we
        // also use the certificate to check itself; i.e. we add it
        // as a trusted certificate, then validate the certificate itself.
        BIO* in = BIO_new_file(certfile.c_str(), "r");
        if (in == NULL) {
            print("failed to read " + certfile);
            return (READ_ERROR);
        }
        X509* cert = PEM_read_bio_X509(in, NULL, NULL, NULL);
        BIO_free(in);
        if (cert == NULL) {
            print("failed to decode " + certfile);
            return (DECODING_ERROR);
        }
        X509_STORE* store = X509_STORE_new();
        X509_STORE_CTX* csc = X509_STORE_CTX_new();
        X509_STORE_CTX_init(csc, store, cert, NULL);
        STACK_OF(X509)* trusted = sk_X509_new_null();
        sk_X509_push(trusted, X509_dup(cert));
        X509_STORE_CTX_trusted_stack(csc, trusted);
        const int result = X509_verify_cert(csc); 
        const int cerror = X509_STORE_CTX_get_error(csc);
        X509_STORE_CTX_free(csc);
        X509_free(cert);

        if (result > 0) {
            print(certfile + " is valid");
            return (X509_V_OK);
        } else {
            print(certfile + " failed to verify: " +
                  X509_verify_cert_error_string(cerror));
            return (cerror);
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

            // First do some basic permission checks; both files
            // should either not exist, or be both readable
            // and writable
            // The checks are done one by one so all errors can
            // be enumerated in one go
            if (fileExists(certfile)) {
                if (!fileIsReadable(certfile)) {
                    print(certfile + " not readable: " + std::strerror(errno));
                    create_cert = false;
                }
                if (!fileIsWritable(certfile)) {
                    print(certfile + " not writable: " + std::strerror(errno));
                    create_cert = false;
                }
            }
            // The key file really only needs write permissions (for
            // b10-certgen that is)
            if (fileExists(keyfile)) {
                if (!fileIsWritable(keyfile)) {
                    print(keyfile + " not writable: " + std::strerror(errno));
                    create_cert = false;
                }
            }
            if (!create_cert) {
                print("Not creating new certificate, "
                      "check file permissions");
                return (FILE_PERMISSION_ERROR);
            }

            // If we reach this, we know that if they exist, we can both
            // read and write them, so now it's up to content checking
            // and/or force_create

            if (force_create || !fileExists(certfile) ||
                validateCertificate(certfile) != X509_V_OK) {
                return (createKeyAndCertificate(keyfile, certfile));
            } else {
                print("Not creating a new certificate (use -f to force)");
            }
        } else {
            if (!fileExists(certfile)) {
                print(certfile + ": " + std::strerror(errno));
                return (NO_SUCH_FILE);
            }
            if (!fileIsReadable(certfile)) {
                print(certfile + " not readable: " + std::strerror(errno));
                return (FILE_PERMISSION_ERROR);
            }
            int result = validateCertificate(certfile);
            if (result != 0) {
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
    // ERR_load_crypto_strings();

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

    // It would appear some environments insist on
    // char* here (Sunstudio on Solaris), so we const_cast
    // them to get rid of compiler warnings.
    const struct option long_options[] = {
        { const_cast<char*>("certfile"), required_argument, NULL, 'c' },
        { const_cast<char*>("force"), no_argument, NULL, 'f' },
        { const_cast<char*>("help"), no_argument, NULL, 'h' },
        { const_cast<char*>("keyfile"), required_argument, NULL, 'k' },
        { const_cast<char*>("write"), no_argument, NULL, 'w' },
        { const_cast<char*>("quiet"), no_argument, NULL, 'q' },
        { NULL, 0, NULL, 0 }
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
    if (create_cert && (certfile_default ^ keyfile_default)) {
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
