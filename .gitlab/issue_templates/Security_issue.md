<!--
If you found the problem using generative AI tools and you have verified it
yourself to be true: write the report yourself and explain the problem as you
have learned it. This makes sure the AI-generated inaccuracies and invented
issues are filtered out early before they waste more people's time.  Even if you
write the report yourself, you must make sure to reveal the fact that 
a large-language model was used in your report.

As we take security reports seriously, we investigate each report with
priority. This work is both time- and energy-consuming and pulls us away from
doing other meaningful work. Fake and otherwise non-actionable reports
effectively prevent us from doing real project work and waste time and
resources.

We ban users immediately who submit fake reports to the project.
-->

### Summary
<!--
Concisely summarize the bug encountered,
preferably in one paragraph or less.
-->

### Kea versions affected
<!--
Make sure you are testing with the **latest** supported version of Kea.
See https://kea.readthedocs.io/en/latest/arm/intro.html#supported-platforms for the current list.
The latest source is available from https://www.isc.org/download/#Kea

-->

### Describe the bug
<!--
A clear and concise description of what the bug is. If you have used an LLM to discover the issue, please report that, and tell us which LLM you used, if possible. We would still like you to write the report yourself, in your own words, but need to know if the contribution was made with the use of an LLM.
-->

### To Reproduce
<!--
This is extremely important! Be precise and use itemized lists, please.

Even if a default configuration is affected, please include the full configuration files _you were testing with_.

Steps to reproduce the behavior:
1. Run Kea (which daemon? dhcpv4, dhcpv6, ddns, ca?) with the following config '...'
2. A client does A and sends packet B with options C,D,E via relay F that does '...'
3. The server then '...'
4. See error
-->

1.
2.
3.

### What is the current *bug* behavior?

### What is the expected *correct* behavior?
<!--
A clear and concise description of what you expected to happen:
The server is supposed to send back packet A with address B assigned.
-->

### Impact
<!--
How can this bug be exploited in an attack situation? 
What network access or privliges does the attacker have to have? 
Please refer to https://kea.readthedocs.io/en/latest/arm/security.html for our guidelines on how to deploy Kea responsibly. 
Please explain the impact on the Kea server, dhcp clients, or the network.
-->

### Environment:
<!--
 - Kea version: which release? if it's compiled from git, which revision. Use kea-dhcp4 -V to find out.
 - OS: [e.g. Ubuntu 16.04 x64]
 - Which features were compiled in (in particular which backends)
 - If/which hooks where loaded in
-->

### Additional Information
<!--
Add any other context about the problem here. In particular, feel free to share your config file and logs from around the time error occurred. Don't be shy to send more logs than you think are relevant. It is easy to grep large log files. It is tricky to guess what may have happened without any information.

Make sure you anonymize your config files (at the very least make sure you obfuscate your database credentials, but you may also replace your actual IP addresses and host names with example.com and 10.0.0.0/8 or 2001:db8::/32).

-->

### Confidentiality
We will follow up by posting any questions on the GitLab issue you have created here. GitLab will notify you via email, and you can reply to the email and your responses will be posted here for us to see. As long as the issue is marked as Confidential, nobody but ISC staff (the maintainers of the project) and you (the reporter) will be able to view the issue. 
ISC will remove the confidentiality flag after the vulnerability is fully disclosed, normally not until some time after publication of a patched version. Alternatively, if we determine this bug is not a significant security risk, we may remove the confidentiality flag earlier - but please do not remove it yourself. 

Please refrain from sharing the information with any other parties, and in particular, please do not post on any public message boards until we determine the severity of any vulnerability and have announced a fix or workaround.


### Acknowledgements
<!--
Please specify whether and how you would like to be publicly credited with
discovering the issue. We normally use the format:
First_name Last_name, Company_or_Team.
-->

<!-- DO NOT modify the following two lines. -->

/label ~Bug ~Security
/confidential

