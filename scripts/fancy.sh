function displayInfo {
    echo -e "\e[46m\e[37m[•]\e[0m \e[36m$1\e[0m"
}

function displaySuccess {
    echo -e "\e[42m\e[37m[✓]\e[0m \e[32m$1\e[0m"
}

function displayWarning {
    echo -e "\e[43m\e[37m[⚠]\e[0m \e[33m$1\e[0m"
}

function displayError {
    echo -e "\e[41m\e[37m[x]\e[0m \e[31m$1\e[0m"
}
