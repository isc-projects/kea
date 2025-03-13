# Security Policy

## Supported Versions

The following versions are supported:

| Version | Supported          | End-Of-Life                      |
| ------- | ------------------ | -------------------------------- |
| 2.7.x   | :white_check_mark: | summer 2025, on release of 3.0.0 |
| 2.6.x   | :white_check_mark: | summer 2026, on release of 3.2.0 |
| 2.5.x   | :x:                | June 2024                        |
| 2.4.x   | :white_check_mark: | summer 2025, on release of 3.0.0 |
| 2.3.x   | :x:                | July 2023                        |
| 2.2.x   | :x:                | August 2024, on release of 2.6.0 |
| 2.1.x   | :x:                | July 2022                        |
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

Limited past EOL support may be available to higher-tier customers.
Please contact ISC sales, using this form: https://www.isc.org/contact/

## Reporting a Vulnerability

To report a security vulnerability, please follow the instructions on this
page:

https://www.isc.org/reportbug/

We prefer a confidential issue on GitLab (not GitHub). An issue is
much better, because it's easier to get more ISC engineers involved in it,
evolve the case as more information is known, update or add information, etc.

If a GitLab issue is not possible, please send e-mail (possibly encrypted)
to kea-security@isc.org.

## Reporting a Bug

We are working with the interests of the greater Internet at heart, and we
hope you are too. In that vein, we do not offer bug bounties. If you think
you have found a bug in Kea, we encourage you to report it responsibly at the
link above; if verified, we will be happy to credit you in our Release Notes.

## Software Defect and Security Vulnerability Disclosure Policy

ISC treats the security of its software products very seriously. This
document discusses the evaluation of a defect's severity and the process
in detail: https://kb.isc.org/docs/aa-00861

## Further Reading

The **Kea security** section of Kea ARM discusses the technical
aspects, such as how to properly configure TLS certificates and how to secure
Kea deployment, and also what the security incident handling process
looks like: https://kea.readthedocs.io/en/latest/arm/security.html#kea-security-processes

**Past advisories** for Kea can be found in our KB: https://kb.isc.org/docs.
On the left-hand panel, see the `Security Advisories` in the `Kea DHCP` section.
