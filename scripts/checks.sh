#!/bin/sh

source "$(dirname "$0")/fancy.sh"

layers_file=../src/venabili.c
warnings_counter=0

function check_key
{
    if [[ $(grep -i "$1" "$layers_file") == "" ]]
    then
        displayWarning "There is no $2 key ($1)"
        warnings_counter=$((warnings_counter+1))
    else
        displayInfo "$2 key available"
    fi

}

# Important keys
check_key "c_flash_mode" "Flash mode"
check_key "k_enter"      "Enter"
check_key "k_space"      "Space"
check_key "k_backspace"  "Backspace"
check_key "k_delete"     "Delete"

if [[ $warnings_counter -eq 0 ]]
then
    echo
    displaySuccess "All checks passed"
fi
