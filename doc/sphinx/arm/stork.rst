.. _stork:

*************************
Monitoring Kea with Stork
*************************

It is usually desired to monitor running Kea services. Kea exposes many sources of informations:
configuration files, API, statistics, logs, open database content and more. It may be sometimes
overwhelming to keep up. ISC started the Stork project to address this problem for both Kea
and BIND 9. Stork can address a variety of scenarios:

- you can use Stork as a dashboard. It provides you with an insight into what exactly is going
  on with your servers. In particular, it can provide up to date details regarding pool
  utilization in your subnets and shared networks, can monitor state of your HA pair (and
  provide extra insight in case of failover and recovery events), lets you list, filter and
  search for specific host reservations and more. For this capability, you need to deploy
  a single Stork server and one Stork agent on each machine you want to monitor.

- you can use Stork agent to integrate Kea with Prometheus and Grafana. Once you deploy a Stork
  agent, it starts acting as Prometheus exporter. If you deploy Prometheus in your network, you
  will be able to visualize statistics as time-series using Grafana.

- you can do both of the above. If you have Grafana deployed in your network, you can let Stork
  know its location. In this configuration, Stork will let you inspect the current status and
  will provide a customized link to Grafana to see how a given property behaved over time.

Stork is available in source code, but also as native Deb and RPM packages, which makes it easy
to install on most popular systems. For more details, please see
`Stork ARM <https://stork.readthedocs.io>`_ or `Stork project page <https://gitlab.isc.org/isc-projects/stork>`_.
The former has a nice collection of screenshots that is frequently updated. It will let you quickly
formulate a first impression of what is currently available. Stork is being rapidly developed with
monthly release. Please check back frequently.

.. _grafana:
.. _prometheus:

Kea statistics in Grafana
=========================

The ISC Stork project provides an agent, that can be deployed along side Kea and BIND 9. It will
expose Kea statistics in a format that's acceptable by Prometheus.
One of the major benefits of Prometheus is that it turns repeated one time observation into time series,
which lets you monitor how certain behaviors change over time. It is easy to use other tools
to visualize data available in Prometheus. The most common approach is to use
Grafana to provide visual dashboards. The Stork project provides dashboard
definitions for Kea and BIND 9 that can be imported into Grafana very easily.

You can learn more about Prometheus and Grafana on their websites: `Prometheus homepage <https://prometheus.io/>`_
and `Grafana homepage <https://grafana.com/>`_.
