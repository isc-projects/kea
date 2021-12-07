.. _stork:

*************************
Monitoring Kea With Stork
*************************

Most administrators want to be able to monitor any Kea services that are running. Kea offers so many
pieces of information - configuration files, API, statistics, logs, open database content, and more -
that it may sometimes
be overwhelming to keep up. ISC's Stork project is intended to address this problem for both Kea
and BIND 9. Stork is useful in a variety of ways:

- Stork can be used as a dashboard. It provides insight into what exactly is happening
  on the servers. In particular, it allows users to: see up-to-date details regarding pool
  utilization in subnets and shared networks; monitor the state of the HA pair (and
  provide extra insight in case of failover and recovery events); list, filter, and
  search for specific host reservations; and more. Only
  a single Stork server needs to be deployed, and one Stork agent on each machine to be monitored.

- The Stork agent can integrate Kea with Prometheus and Grafana. Once the Stork
  agent is active on the server, it serves as a Prometheus exporter. Users who have deployed
  Prometheus in their networks can visualize statistics as time series using Grafana.

- Stork can act as both a dashboard and an integrator for Prometheus/Grafana. Once Stork
  is linked to where Grafana is deployed on the network, users can inspect the current status and
  visit a customized link to Grafana to see how a given property behaves over time.

Stork is available as source code, but also as native deb and RPM packages, which makes it easy
to install on most popular systems. For more details, please see the
`Stork ARM <https://stork.readthedocs.io>`_ or the `Stork project page <https://gitlab.isc.org/isc-projects/stork>`_.
The ARM has a nice collection of screenshots that is frequently updated, to give users
an idea of what is currently available. Stork is in the midst of full development with
monthly releases, so please check back frequently.

.. _grafana:
.. _prometheus:

Kea Statistics in Grafana
=========================

The ISC Stork project provides an agent that can be deployed alongside Kea. It
exposes Kea statistics in a format that is accepted by Prometheus.
One of the major benefits of Prometheus is that it turns repeated one-time observations into time series,
which lets users monitor how certain behaviors change over time. It is easy to use other tools
to visualize data available in Prometheus; the most common approach is to use
Grafana to provide visual dashboards. The Stork project provides dashboard
definitions for Kea that can be imported into Grafana very easily.

Learn more about Prometheus and Grafana on their websites: `Prometheus <https://prometheus.io/>`
and `Grafana <https://grafana.com/>`.
