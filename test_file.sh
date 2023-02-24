#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo -e "\e[31mUSAGE: $0 host port\e[0m"
    exit 0
fi

USERNAME="Anonymous"
PASS=""

HOST=$1
PORT=$2
MKFIFO=`which mkfifo`
PIPE=fifo
OUT=outfile
TAIL=`which tail`
NC="`which nc` -C"
TIMEOUT=1 #max time before reading server response


getcode()
{
    sleep $TIMEOUT
    local code=$1
    echo -e "\e[34mWaiting for $code reply-code\e[0m"
    local data=`$TAIL -n 1 $OUT |cat -e |grep "^$code.*[$]$" |wc -l`
    return $data
}

print_failed()
{
    echo -e "\e[31m$1 test failed\e[0m"
    echo -e "Expected reply-code: \e[33m$2\e[0m"
    echo -e "Received : [\e[32m"`$TAIL -n 1 $OUT| cat -e`"\e[0m]"
    echo -e "\e[31mKO\e[0m"
}

print_succeeded()
{
    echo -e "\e[32m$1 test succeeded\e[0m"
    echo -e "\e[32mOK\e[0m"
    kill_client 2>&1 >/dev/null
}

launch_client()
{
    local host=$1
    local port=$2

    $MKFIFO $PIPE
    ($TAIL -f $PIPE 2>/dev/null | $NC $host $port &> $OUT &) >/dev/null 2>/dev/null

    echo -e "\e[34mConnecting to $host : $port\e[0m"
    sleep $TIMEOUT
    getcode 220
    if [[ $? -eq 1 ]]; then
        echo -e "\e[32mReply-code OK\e[0m"
        return 1
    else
        echo -e "\e[31mConnection to $host:$port failed\e[0m"
        echo -e "Expected reply-code: \e[33m220\e[0m"
        echo -e "Received : [\e[32m"`tail -n 1 $OUT |cat -e`"\e[0m]"
        return 0
    fi
}

launch_test()
{
    local test_name=$1
    local cmd=$2
    local code=$3

    echo -e "\e[34mSending [$cmd^M$]\e[0m"
    echo "$cmd" >$PIPE
    getcode $code
    if [[ ! $? -eq 1 ]]; then
        print_failed "$test_name" "$code"
        kill_client
        clean
    fi
    echo -e "\e[32mReply-code OK\e[0m"
}

kill_client()
{
    local nc=`which nc`

    if [ `pidof $TAIL | wc -l` -ne 0 ]
    then
        killall $TAIL &>/dev/null
    fi
    if [ `pidof $nc | wc -l` -ne 0 ]
    then
        killall $nc &>/dev/null
    fi
    rm -f $PIPE $OUT &> /dev/null
}

clean()
{
    rm -f $PIPE $OUT log &>/dev/null
}

# ! Simple authentication with USER + PASS command
test_authentification_simple()
{
    local test_name="Authentication"

    local cmd1="USER $USERNAME"
    local cmd2="PASS $PASS"

    launch_client $HOST $PORT
    if [[ ! $? -eq 1 ]]; then
        echo "KO"
        kill_client
        return
    fi

    launch_test "$test_name" "$cmd1" 331
    launch_test "$test_name" "$cmd2" 230

    print_succeeded "$test_name"
    return
}

test_authentification_invalid_password()
{
    local test_name="Authentication with invalid password"

    local cmd1="USER $USERNAME"
    local cmd2="PASS invalid"

    launch_client $HOST $PORT
    if [[ ! $? -eq 1 ]]; then
        echo "KO"
        kill_client
        return
    fi

    launch_test "$test_name" "$cmd1" 331
    launch_test "$test_name" "$cmd2" 530

    print_succeeded "$test_name"
    return
}


test_authentification_no_credentials()
{
    local test_name="Authentication with no credentials"

    local cmd1="USER"
    local cmd2="PASS"

    launch_client $HOST $PORT
    if [[ ! $? -eq 1 ]]; then
        echo "KO"
        kill_client
        return
    fi

    launch_test "$test_name" "$cmd1" 501
    launch_test "$test_name" "$cmd2" 503

    print_succeeded "$test_name"
    return
}

test_authentification_username_only()
{
    local test_name="Authentication with only username"

    local cmd1="USER $USERNAME"

    launch_client $HOST $PORT
    if [[ ! $? -eq 1 ]]; then
        echo "KO"
        kill_client
        return
    fi

    launch_test "$test_name" "$cmd1" 331

    print_succeeded "$test_name"
    return
}

test_authentification_password_only()
{
    local test_name="Authentication with only password"

    local cmd1="PASS $PASS"

    launch_client $HOST $PORT
    if [[ ! $? -eq 1 ]]; then
        echo "KO"
        kill_client
        return
    fi

    launch_test "$test_name" "$cmd1" 503

    print_succeeded "$test_name"
    return
}

test_authentification_multiple_usernames()
{
    local test_name="Authentication with multiple usernames"

    local cmd1="USER $USERNAME"
    local cmd2="USER another"
    local cmd3="PASS $PASS"

    launch_client $HOST $PORT
    if [[ ! $? -eq 1 ]]; then
        echo "KO"
        kill_client
        return
    fi

    launch_test "$test_name" "$cmd1" 331
    launch_test "$test_name" "$cmd2" 530
    launch_test "$test_name" "$cmd3" 230

    print_succeeded "$test_name"
    return
}

# ! HELP command no arguments
test_help_no_arguments()
{
    local test_name="[HELP command No arguments]"

    local cmd="HELP"

    launch_client $HOST $PORT

    if [[ ! $? -eq 1 ]]; then
        echo "KO"
        kill_client
        return
    fi

    echo -e "------------------ HELP ---------------------"

    launch_test "$test_name" "$cmd" 214

    print_succeeded "$test_name"

    echo -e "---------------------------------------------"

    return
}

# ! HELP command with arguments
test_help_arguments()
{
    local test_name="[HELP command with argument]"

    local cmd="HELP USER"

    launch_client $HOST $PORT

    if [[ ! $? -eq 1 ]]; then
        echo "KO"
        kill_client
        return
    fi

    echo -e "--------------- HELP arguments ---------------"

    launch_test "$test_name" "$cmd" 214

    print_succeeded "$test_name"

    echo -e "---------------------------------------------"

    return
}

# ! NOOP command
test_noop()
{
    local test_name="[NOOP command]"

    local cmd="NOOP"

    launch_client $HOST $PORT
    if [[ ! $? -eq 1 ]]; then
        echo "KO"
        kill_client
        return
    fi

    echo -e "------------------ NOOP ---------------------"

    launch_test "$test_name" "$cmd" 200

    echo -e "---------------------------------------------"


    print_succeeded "$test_name"
    return
}

# ! PWD command
test_pwd()
{
    local test_name="PWD command"

    local cmd1="USER $USERNAME"
    local cmd2="PASS $PASS"
    local cmd3="PWD"

    launch_client $HOST $PORT
    if [[ ! $? -eq 1 ]]; then
        echo "KO"
        kill_client
        return
    fi

    launch_test "$test_name" "$cmd1" 331
    launch_test "$test_name" "$cmd2" 230
    launch_test "$test_name" "$cmd3" 257

    print_succeeded "$test_name"
    return
}

# ! CWD command
test_cwd()
{
    local test_name="CWD command"

    local cmd1="USER $USERNAME"
    local cmd2="PASS $PASS"
    local cmd3="CWD /"

    launch_client $HOST $PORT
    if [[ ! $? -eq 1 ]]; then
        echo "KO"
        kill_client
        return
    fi

    launch_test "$test_name" "$cmd1" 331
    launch_test "$test_name" "$cmd2" 230
    launch_test "$test_name" "$cmd3" 250

    print_succeeded "$test_name"
    return
}

# ! CDUP command
test_cdup()
{
    local test_name="CDUP command"

    local cmd1="USER $USERNAME"
    local cmd2="PASS $PASS"
    local cmd3="CDUP"

    launch_client $HOST $PORT
    if [[ ! $? -eq 1 ]]; then
        echo "KO"
        kill_client
        return
    fi

    launch_test "$test_name" "$cmd1" 331
    launch_test "$test_name" "$cmd2" 230
    launch_test "$test_name" "$cmd3" 250

    print_succeeded "$test_name"
    return
}

# ! PASV command
test_pasv()
{
    local test_name="PASV command"

    local cmd1="USER $USERNAME"
    local cmd2="PASS $PASS"
    local cmd3="PASV"

    launch_client $HOST $PORT
    if [[ ! $? -eq 1 ]]; then
        echo "KO"
        kill_client
        return
    fi

    launch_test "$test_name" "$cmd1" 331
    launch_test "$test_name" "$cmd2" 230
    launch_test "$test_name" "$cmd3" 227

    print_succeeded "$test_name"
    return
}



test_authentification_simple
# test_authentification_invalid_password
# test_authentification_no_credentials
# test_authentification_username_only
# test_authentification_password_only
# test_authentification_multiple_usernames

# test_pwd

test_pasv

test_help_no_arguments
test_help_arguments
test_noop

clean


