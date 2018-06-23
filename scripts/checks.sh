#!/bin/sh

source "$(dirname "$0")/fancy.sh"

layers_file=../src/venabili.c
warnings_counter=0

if [[ $(grep -i c_flash_mode "$layers_file") == "" ]]
then
    displayWarning "There is no flash mode key (c_flash_mode)"
    warnings_counter=$((warnings_counter+1))
fi

if [[ $warnings_counter -eq 0 ]]
then
    displaySuccess "All checks passed"
fi
