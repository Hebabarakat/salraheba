

#!/bin/bash

################################################################################
# SET SOME CONFIG VARIABLES
################################################################################
R=$RANDOM

TMP_DIR="/tmp"
COMMANDFILE="$TMP_DIR/hbtn_checker_command_$R"
COMMANDFILE_REAL_SHELL="$TMP_DIR/hbtn_checker_command_real_shell_$R"
STATUS="$TMP_DIR/hbtn_checker_status_$R"
OUTPUTFILE="$TMP_DIR/hbtn_checker_output_$R"
ERROR_OUTPUTFILE="$TMP_DIR/hbtn_checker_error_output_$R"
VALGRIND_OUTPUTFILE="$TMP_DIR/hbtn_checker_valgrind_$R"
LTRACE_OUTPUTFILE="$TMP_DIR/hbtn_checker_ltrace_output_$R"
EXPECTED_STATUS="$TMP_DIR/hbtn_checker_expected_status_$R"
EXPECTED_OUTPUTFILE="$TMP_DIR/hbtn_checker_expected_output_$R"
EXPECTED_ERROR_OUTPUTFILE="$TMP_DIR/hbtn_checker_expected_error_output_$R"
TMP_FILE="$TMP_DIR/hbtn_checker_tmp_$R"
ENV_TMP_FILE="$TMP_DIR/hbtn_env_$R"
LTRACE_ALLOWED_FUNCTIONS_FILE="./allowed_functions"

################################################################################
# MOST USED COMMANDS, IN CASE THE ENVIRONMENT IS MISSING
################################################################################
WHICH="/usr/bin/which"
SLEEP=`$WHICH sleep`
SLEEPSECONDS=2 # Valgrind needs at least 2 seconds to execute properly
LTRACE=`$WHICH ltrace`
ECHO=`$WHICH echo`
CAT=`$WHICH cat`
GREP=`$WHICH grep`
WC=`$WHICH wc`
RM=`$WHICH rm`
TOUCH=`$WHICH touch`
CHMOD=`$WHICH chmod`
PIDOF=`$WHICH pidof`
KILLALL=`$WHICH killall`
KILL=`$WHICH kill`
VALGRIND=`$WHICH valgrind`
SED=`$WHICH sed`
DIFF=`$WHICH diff`
HEAD=`$WHICH head`
TAIL=`$WHICH tail`
CUT=`$WHICH cut`
PS=`$WHICH ps`
HEAD=`$WHICH head`
CP=`$WHICH cp`
ENV=`$WHICH env`

################################################################################
# COMMAND-LINE OPTIONS AND PARAMETERS
################################################################################
usage=0

valgrind_error=0
valgrind_leak=0
ltrace=0

force_diff=0

function usage()
{
	exitcode=$1

$ECHO "Usage: $0 shell test_file

Options:
--valgrind_error              Checks for valgrind errors
--valgrind_leak               Cehcks for valgrind leaks
--valgrind                    Checks for both valgrind errors and leaks
--ltrace                      Checks for forbidden system/library calls

--diff                        Force to print the output diff

--help                        Prints the help and exit"

	exit $exitcode
}

################################################################################
# PARSE COMMAND-LINE PARAMETERS
################################################################################
for arg in "$@"
do
	if [ "$arg" == "--valgrind_error" ]
	then
		let valgrind_error=1
		shift $ARGV
	elif [ "$arg" == "--valgrind_leak" ]
	then
		let valgrind_leak=1
		shift $ARGV
	elif [ "$arg" == "--valgrind" ]
	then
		let valgrind_error=1
		let valgrind_leak=1
		shift $ARGV
	elif [ "$arg" == "--ltrace" ]
	then
		let ltrace=1
		shift $ARGV
	elif [ "$arg" == "--diff" ]
	then
		let force_diff=1
		shift $ARGV
	elif [ "$arg" == "--help" ]
	then
		let usage=1
		shift $ARGV
	fi
done

[[ "$usage" -eq "1" ]] && usage 0
[[ "$#" -lt "2" ]] && usage 1

HSHELL=$1
TEST_FILE=$2
REAL_SHELL=`$WHICH sh`

################################################################################
# UTILITIES FUNCTIONS
################################################################################
function stop_process()
{
	prog=$1
	base_shell=${prog##*/}

	# for pid in `ps aux | grep "$base_shell" | cut -d' ' -f3`
	# do
	# 	kill -9 $pid > /dev/null 2>&1
	# done

	running_shells=`$PIDOF "$base_shell" | $WC -l`
	if [ "$running_shells" -ne "0" ]
	then
		$KILLALL -9 "$base_shell" > /dev/null 2>&1
	fi
}

function cleanup()
{
	stop_process $HSHELL
	$RM -f $COMMANDFILE
	$RM -f $COMMANDFILE_REAL_SHELL
	$RM -f $STATUS
	$RM -f $OUTPUTFILE
	$RM -f $ERROR_OUTPUTFILE
	$RM -f $CHECK_OUTPUTFILE
	$RM -f $VALGRIND_OUTPUTFILE
	$RM -f $LTRACE_OUTPUTFILE
	$RM -f $EXPECTED_STATUS
	$RM -f $EXPECTED_OUTPUTFILE
	$RM -f $EXPECTED_ERROR_OUTPUTFILE
	$RM -f $TMP_FILE
	$RM -f $ENV_TMP_FILE
}

function print_diff()
{
	input=$1
	params=$2

	$ECHO -n "(command)["
	if [ ! -z "$input" ]
	then
		$ECHO -e -n "echo \"$input\" | "
	fi
	$ECHO -n "$HSHELL"
	if [ ! -z "$params" ]
	then
		$ECHO -n " $params"
	fi
	$ECHO "]"
	$ECHO ""

	$ECHO "[GOT]:"
	$ECHO -n "(stdout)["
	$CAT $OUTPUTFILE
	$ECHO "](Length: `$CAT $OUTPUTFILE | $WC -c`)"
	$ECHO -n "(stderr)["
	$CAT $ERROR_OUTPUTFILE
	$ECHO "](Length: `$CAT $ERROR_OUTPUTFILE | $WC -c`)"
	$ECHO -n "(status)["
	$CAT $STATUS
	$ECHO -e "]\n"

	$ECHO "[EXPECTED]:"
	$ECHO -n "(stdout)["
	$CAT $EXPECTED_OUTPUTFILE
	$ECHO "](Length: `$CAT $EXPECTED_OUTPUTFILE | $WC -c`)"
	$ECHO -n "(stderr)["
	$CAT $EXPECTED_ERROR_OUTPUTFILE
	$ECHO "](Length: `$CAT $EXPECTED_ERROR_OUTPUTFILE | $WC -c`)"
	$ECHO -n "(status)["
	$CAT $EXPECTED_STATUS
	$ECHO -e "]\n"

	$ECHO "Environment:"
	$CAT $ENV_TMP_FILE | $GREP -v "LS_COLORS"
}

################################################################################
# START
################################################################################
stop_process $HSHELL
status=0
params=""

################################################################################
# READ AND EXECUTE CHECK SCRIPT
################################################################################
source $TEST_FILE

################################################################################
# REATRIEVE SHELL INPUT (STDIN) AND PARAMS
################################################################################
if [ -z ${shell_input+x} ]
then
	echo "The variable \$shell_input is not defined in $TEST_FILE!"
	exit 1
fi
if [ ! -z ${shell_params+x} ]
then
	params=$shell_params
fi

################################################################################
# FUNCTION "check_setup" CAN BE DEFINED IN THE CHECK SCRIPT
################################################################################
if [ -n "$(type -t check_setup)" ] && [ "$(type -t check_setup)" = function ]
then
	check_setup
fi

shell_pid=0
shell_ppid=0
differs=0

################################################################################
# PREPARING COMMAND SCRIPT FILE
################################################################################
$ECHO -e -n "$ECHO " > $COMMANDFILE
$ECHO -e -n "\"$shell_input\"" >> $COMMANDFILE
$ECHO -e -n " | " >> $COMMANDFILE
if [ $valgrind_error -ne 0 ] || [ $valgrind_leak -ne 0 ]
then
	$ECHO -e -n "$VALGRIND --log-file=\"$VALGRIND_OUTPUTFILE\" " >> $COMMANDFILE
fi
$ECHO -e "\"$HSHELL\" $params > \"$OUTPUTFILE\" 2> \"$ERROR_OUTPUTFILE\"" >> $COMMANDFILE
$ECHO -e "$ECHO -n \$? > \"$STATUS\"" >> $COMMANDFILE
$CHMOD +x $COMMANDFILE

################################################################################
# TEST COMMAND AGAINST STUDENT SHELL
################################################################################
. $COMMANDFILE &
$SLEEP $SLEEPSECONDS
stop_process $COMMANDFILE
# stop_process $HSHELL

################################################################################
# PARSE VALGRIND OUTPUT TO RETRIEVE SHELL PID
################################################################################
if [ $valgrind_error -ne 0 ] || [ $valgrind_leak -ne 0 ]
then
	# stop valgrind
	valgrind_pid=`$PIDOF valgrind.bin`
	if [ -n "$valgrind_pid" ]
	then
		$KILL -9 "$valgrind_pid" > /dev/null 2>&1
	fi

	content=`$CAT $VALGRIND_OUTPUTFILE`
	regex="==([0-9]+)== Parent PID: ([0-9]+)"
	if [[ $content =~ $regex ]]
	then
		let shell_pid=${BASH_REMATCH[1]}
		let shell_ppid=${BASH_REMATCH[2]}

		# DISCARD PARENT PROCESS OUTPUT
		$ECHO "$content" | $GREP -v -e "^==$shell_ppid" > $VALGRIND_OUTPUTFILE
	fi
fi

################################################################################
# RUN LTRACE
################################################################################
if [ $ltrace -ne 0 ]
then
	($ECHO "$shell_input" | $LTRACE -bc -o "$LTRACE_OUTPUTFILE" "$HSHELL" $params > /dev/null 2>&1 &)
	$SLEEP $SLEEPSECONDS
	stop_process $LTRACE
fi

function check_diff()
{
	let differs=0

	########################################################################
	# CHECK DIFF
	########################################################################
	diff_out=`$DIFF $OUTPUTFILE $EXPECTED_OUTPUTFILE`
	diff_err=`$DIFF $ERROR_OUTPUTFILE $EXPECTED_ERROR_OUTPUTFILE`
	diff_status=`$DIFF $STATUS $EXPECTED_STATUS`
	if [ ! -z "$diff_out" ] || [ ! -z "$diff_err" ] || [ ! -z "$diff_status" ]
	then
		let differs=1
		let status=1
	fi
}

################################################################################
# FUNCTION "sh_setup" CAN BE DEFINED IN THE CHECK SCRIPT
################################################################################
if [ -n "$(type -t sh_setup)" ] && [ "$(type -t sh_setup)" = function ]
then
	sh_setup
fi

################################################################################
# RUN SH IN ORDER TO COMPARE OUTPUTS
################################################################################
if [ -z ${compare_with_sh+x} ] || [ $compare_with_sh -ne 0 ]
then
	########################################################################
	# PREPARING COMMAND SCRIPT FILE
	########################################################################
	$ECHO -e -n "$ECHO " > $COMMANDFILE_REAL_SHELL
	$ECHO -e -n "\"$shell_input\"" >> $COMMANDFILE_REAL_SHELL
	cmd=" | \"$REAL_SHELL\" $params > \"$EXPECTED_OUTPUTFILE\" 2> \"$EXPECTED_ERROR_OUTPUTFILE\" ; $ECHO -n \$? > \"$EXPECTED_STATUS\""
	$ECHO -e $cmd >> $COMMANDFILE_REAL_SHELL
	$CHMOD +x $COMMANDFILE_REAL_SHELL

	. $COMMANDFILE_REAL_SHELL &

	$SLEEP $SLEEPSECONDS
	stop_process $COMMANDFILE_REAL_SHELL

	# REPLACE REAL SHELL'S NAME WITH STUDENT'S SHELL NAME ON ERROR OUTPUT
	# EXAMPLE: '/bin/sh: 1: qwerty: not found'
	# BECOMES: './hsh: 1: qwerty: not found'
	$SED -i "s@${REAL_SHELL}@${HSHELL}@g" $EXPECTED_OUTPUTFILE
	$SED -i "s@${REAL_SHELL}@${HSHELL}@g" $EXPECTED_ERROR_OUTPUTFILE

	check_diff
fi

################################################################################
# Save environment used during correction
################################################################################
$ENV > $ENV_TMP_FILE

################################################################################
# FUNCTION "check_callback" CAN BE DEFINED IN THE CHECK SCRIPT
################################################################################
if [ -n "$(type -t check_callback)" ] && [ "$(type -t check_callback)" = function ]
then
	check_callback $status
	let status=$?
fi

################################################################################
# PRINT OUTPUTS COMPARISON
################################################################################
if [ $differs -ne 0 ] || [ $force_diff -ne 0 ]
then
	print_diff "$shell_input" "$params"
fi

errors=0
leaks=0
################################################################################
# CHECK VALGRIND ERRORS AND MEMORY LEAKS
################################################################################
if [ $valgrind_error -ne 0 ] || [ $valgrind_leak -ne 0 ]
then
	########################################################################
	# CHECK FOR VALGRIND ERRORS
	########################################################################
	content=`$CAT $VALGRIND_OUTPUTFILE`
	regex="ERROR SUMMARY: ([1-9][0-9]*) errors"
	if [[ $content =~ $regex ]]
	then
		let errors=1
	fi

	########################################################################
	# CHECK FOR VALGRIND LEAKS
	########################################################################
	content=`$CAT $VALGRIND_OUTPUTFILE`
	regex="(LEAK SUMMARY:)"
	if [[ $content =~ $regex ]]
	then
		let leaks=1
	fi

	########################################################################
	# PRINT VALGRIND LOG IF ERROR OR LEAK DETECTED
	########################################################################
	if [ $errors -ne 0 ] || [ $leaks -ne 0 ]
	then
		$ECHO "[VALGRIND]:"
		$CAT "$VALGRIND_OUTPUTFILE"
		$ECHO ""

		let status=1
	fi
fi

################################################################################
# CHECK LTRACE
################################################################################
if [ $ltrace -ne 0 ]
then
	########################################################################
	# PARSE LTRACE OUTPUT TO KEEP ONLY A LIST OF CALLED FUNCTIONS
	########################################################################
	functions_called=`$CAT $LTRACE_OUTPUTFILE | $HEAD -n -2 | $TAIL -n +3 | $SED -e 's/  */ /g' | $SED -e 's/^ //g' | $CUT -d' ' -f5 | $GREP -vw 'function' | $GREP -vwe '--------------------' | $GREP -vw 'calls'`

	for f in $functions_called
	do
		################################################################
		# CHECK THAT THE FUNCTION IS PART OF THE ALLOWED FUNCTIONS
		################################################################
		if [ `$GREP -w "$f" "$LTRACE_ALLOWED_FUNCTIONS_FILE" | $WC -l` -eq 0 ]
		then
			$ECHO "Function '$f' is not allowed"
			let status=1
		fi
	done
fi

################################################################################
# CLEANUP AND QUIT
################################################################################
cleanup

[[ $status -eq 0 ]] && $ECHO -n "OK"
exit $status

1.0.1

#!/bin/bash

################################################################################
# Description for the intranet check (one line, support Markdown syntax)
# Execute `/bin/ls`

################################################################################
# The variable 'compare_with_sh' IS OPTIONNAL
#
# Uncomment the following line if you don't want the output of the shell
# to be compared against the output of /bin/sh
#
# It can be useful when you want to check a builtin command that sh doesn't
# implement
# compare_with_sh=0

################################################################################
# The variable 'shell_input' HAS TO BE DEFINED
#
# The content of this variable will be piped to the student's shell and to sh
# as follows: "echo $shell_input | ./hsh"
#
# It can be empty and multiline
shell_input="/bin/ls"

################################################################################
# The variable 'shell_params' IS OPTIONNAL
#
# The content of this variable will be passed to as the paramaters array to the
# shell as follows: "./hsh $shell_params"
#
# It can be empty
# shell_params=""

################################################################################
# The function 'check_setup' will be called BEFORE the execution of the shell
# It allows you to set custom VARIABLES, prepare files, etc
# If you want to set variables for the shell to use, be sure to export them,
# since the shell will be launched in a subprocess
#
# Return value: Discarded
function check_setup()
{
	return 0
}

################################################################################
# The function 'sh_setup' will be called AFTER the execution of the students
# shell, and BEFORE the execution of the real shell (sh)
# It allows you to set custom VARIABLES, prepare files, etc
# If you want to set variables for the shell to use, be sure to export them,
# since the shell will be launched in a subprocess
#
# Return value: Discarded
function sh_setup()
{
	return 0
}

################################################################################
# The function `check_callback` will be called AFTER the execution of the shell
# It allows you to clear VARIABLES, cleanup files, ...
#
# It is also possible to perform additionnal checks.
# Here is a list of available variables:
# STATUS -> Path to the file containing the exit status of the shell
# OUTPUTFILE -> Path to the file containing the stdout of the shell
# ERROR_OUTPUTFILE -> Path to the file containing the stderr of the shell
# EXPECTED_STATUS -> Path to the file containing the exit status of sh
# EXPECTED_OUTPUTFILE -> Path to the file containing the stdout of sh
# EXPECTED_ERROR_OUTPUTFILE -> Path to the file continaing the stderr of sh
#
# Parameters:
#     $1 -> Status of the comparison with sh
#             0 -> The output is the same as sh
#             1 -> The output differs from sh
#
# Return value:
#     0  -> Check succeed
#     1  -> Check fails
function check_callback()
{
	status=$1

	return $status
}

1.0.2
(command)[echo "/bin/ls" | ./hsh]

[GOT]:
(stdout)[$ AUTHORS
README.md
_exce.c
allowed_functions
bin_ls.bash
builin.c
checker.bash
helpfunction.c
hsh
imain.c
main.h
non.c
test
$ ](Length: 127)
(stderr)[](Length: 0)
(status)[1]

[EXPECTED]:
(stdout)[allowed_functions
AUTHORS
bin_ls.bash
builin.c
checker.bash
_exce.c
helpfunction.c
hsh
imain.c
main.h
non.c
README.md
test
](Length: 123)
(stderr)[](Length: 0)
(status)[0]

Environment:
HOSTNAME=14b2d5484351
LANGUAGE=en_US:en
PWD=/tmp/correction/5061299701348596180853594885297029628022_5/235/407622
TZ=America/Los_Angeles
HOME=/root
LANG=en_US.UTF-8
SHLVL=2
LC_ALL=en_US.UTF-8
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
OLDPWD=/
_=/usr/bin/env
[VALGRIND]:
==237== Memcheck, a memory error detector
==237== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==237== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==237== Command: ./hsh
==237== Parent PID: 234
==237== 
==237== 
==237== HEAP SUMMARY:
==237==     in use at exit: 512 bytes in 1 blocks
==237==   total heap usage: 3 allocs, 2 frees, 4,728 bytes allocated
==237== 
==237== LEAK SUMMARY:
==237==    definitely lost: 0 bytes in 0 blocks
==237==    indirectly lost: 0 bytes in 0 blocks
==237==      possibly lost: 0 bytes in 0 blocks
==237==    still reachable: 512 bytes in 1 blocks
==237==         suppressed: 0 bytes in 0 blocks
==237== Rerun with --leak-check=full to see details of leaked memory
==237== 
==237== For lists of detected and suppressed errors, rerun with: -s
==237== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)



1.0.3

(command)[echo "/bin/ls" | ./hsh]

[GOT]:
(stdout)[$ AUTHORS
README.md
_exce.c
allowed_functions
bin_ls.bash
builin.c
checker.bash
helpfunction.c
hsh
imain.c
main.h
non.c
test
$ ](Length: 127)
(stderr)[](Length: 0)
(status)[1]

[EXPECTED]:
(stdout)[allowed_functions
AUTHORS
bin_ls.bash
builin.c
checker.bash
_exce.c
helpfunction.c
hsh
imain.c
main.h
non.c
README.md
test
](Length: 123)
(stderr)[](Length: 0)
(status)[0]

Environment:
HOSTNAME=14b2d5484351
LANGUAGE=en_US:en
PWD=/tmp/correction/5061299701348596180853594885297029628022_5/235/407622
TZ=America/Los_Angeles
HOME=/root
LANG=en_US.UTF-8
SHLVL=2
LC_ALL=en_US.UTF-8
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
OLDPWD=/
_=/usr/bin/env
[VALGRIND]:
==237== Memcheck, a memory error detector
==237== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==237== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==237== Command: ./hsh
==237== Parent PID: 234
==237== 
==237== 
==237== HEAP SUMMARY:
==237==     in use at exit: 512 bytes in 1 blocks
==237==   total heap usage: 3 allocs, 2 frees, 4,728 bytes allocated
==237== 
==237== LEAK SUMMARY:
==237==    definitely lost: 0 bytes in 0 blocks
==237==    indirectly lost: 0 bytes in 0 blocks
==237==      possibly lost: 0 bytes in 0 blocks
==237==    still reachable: 512 bytes in 1 blocks
==237==         suppressed: 0 bytes in 0 blocks
==237== Rerun with --leak-check=full to see details of leaked memory
==237== 
==237== For lists of detected and suppressed errors, rerun with: -s
==237== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)