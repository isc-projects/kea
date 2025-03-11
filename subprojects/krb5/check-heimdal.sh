#!/bin/sh

"$1" --all | grep Vendor | grep -q Heimdal

