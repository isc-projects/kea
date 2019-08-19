---
name: Bug report
about: Create a report to help us improve

---

If you believe your bug report is a security issue (e.g. a packet that can kill the server), DO NOT REPORT IT HERE. Please use https://www.isc.org/community/report-bug/ instead or send mail to security-office(at)isc(dot)org.

**Describe the bug**
A clear and concise description of what the bug is.

**To Reproduce**
Steps to reproduce the behavior:
1. Run Kea (which daemon? dhcpv4, dhcpv6, ddns, ca?) with the following config '...'
2. A client does A and sends packet B with options C,D,E via relay F that does '...'
3. The server then '...'
4. See error

**Expected behavior**
A clear and concise description of what you expected to happen:
The server is supposed to send back packet A with address B assigned.

**Environment:**
 - Kea version: which release? if it's compiled from git, which revision. Use kea-dhcp4 -V to find out.
 - OS: [e.g. Ubuntu 16.04 x64]
 - Which features were compiled in (in particular which backends)
 - If/which hooks where loaded in

**Additional Information**
Add any other context about the problem here. In particular, feel free to share your config file and logs from around the time error occurred. Don't be shy to send more logs than you think are relevant. It is easy to grep large log files. It is tricky to guess what may have happened without any information.

Make sure you anonymize your config files (at the very lease make sure you obfuscate your database credentials, but you may also replace your actual IP addresses and host names with example.com and 10.0.0.0/8 or 2001:db8::/32).

**Contacting you**
How can ISC reach you to discuss this matter further? If you do not specify any means such as e-mail, jabber id or a telephone, we may send you a message on github with questions when we have them.
