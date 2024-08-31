# Security Policy

## Supported Versions

The following versions are supported:

| Version | Supported          | End-Of-Life                      |
| ------- | ------------------ | -------------------------------- |
| 2.5.x   | :white_check_mark: | summer 2024, on release of 2.6.0 |
| 2.4.x   | :white_check_mark: | summer 2025, on release of 2.8.0 |
| 2.3.x   | :x:                | July 2023, on release of 2.4.0   |
| 2.2.x   | :white_check_mark: | August 2024, on release of 2.6.0 |
| 2.1.x   | :x:                | July 2022, on release of 2.2.0   |
| 2.0.x   | :x:                | August 2023, on release of 2.4.0 |
| 1.9.0   | :x:                | September 2021                   |
| 1.8.0   | :x:                | July 2022                        |
| 1.7.0   | :x:                | August 2020                      |
| 1.6.0   | :x:                | September 2021                   |
| 1.5.0   | :x:                | August 2020                      |
| 1.3.0   | :x:                | December 2018                    |
| 1.2.0   | :x:                | June 2018                        |
| 1.1.0   | :x:                | December 2017                    |
| 1.0.0   | :x:                | June 2017                        |
| 0.9.2-P1| :x:                | March 2017                       |
| 0.9.1   | :x:                | June 2016                        |

Starting with the Kea 1.7 release, all Kea versions with an odd minor
version number are development releases, and become EOL as soon as the
following stable release is published.

Limited past EOL support may be available to higher tier customers.
Please contact ISC sales, using this form: https://www.isc.org/contact/

## Reporting a Vulnerability

To report security vulnerability, please follow this instruction:

https://www.isc.org/reportbug/

Briefly, we prefer confidential issue on gitlab (not github). An issue is
much better, because it's easier to get more ISC engineers involved in it,
evolve the case as more information is known, update or extra information, etc.

Second best is to send e-mail (possibly encrypted) to kea-security@isc.org.

## Software Defects and Security Vulnerability Disclosure Policy

ISC treats the security of its software products very seriously. This
document discusses the evaluation of a defect severity and the process
in detail: https://kb.isc.org/docs/aa-00861

## Further reading

The **Kea security** section of Kea ARM discusses the technical
aspects, such as how to properly configure TLS certificates, how to secure
Kea deployment and also what the security incident handling process
looks like: https://kea.readthedocs.io/en/latest/arm/security.html#kea-security-processes

The **Past advisories** for Kea can be found on the KB: https://kb.isc.org/docs
On the left hand panel, see the `Security Advisiories` in the `Kea DHCP` section.
