#!/bin/sh

env | grep -E "^${1}=" | cut -d '=' -f 2
