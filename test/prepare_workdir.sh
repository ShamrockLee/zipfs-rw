# shellcheck shell=sh

# shellcheck disable=SC3043 # Use the local keyword since it's everywhere.

set -eu

WORKDIR="$(mktemp --directory --tmpdir workdir_zip_sample_special_XXXXXX)"

# https://unix.stackexchange.com/questions/520035/exit-trap-with-posix
# https://unix.stackexchange.com/questions/235582/keep-exit-codes-when-trapping-sigint-and-similar/526562#526562
cleanup() {
	local RET="${ERR:-$?}"
	local SIG="${1:-EXIT}"
	trap - "$SIG"
	if [ "$SIG" != "EXIT" ]; then
		trap - EXIT
	fi
	rm -rf "$WORKDIR"
	if [ "$SIG" = "EXIT" ]; then
		exit "$RET"
	else
		kill -s "$SIG" "$$"
	fi
}

for _SIG in EXIT ABRT HUP INT PIPE QUIT TERM; do
	# shellcheck disable=SC2064 # We meant to expand "$_SIG" now instead of when signaled
	trap "cleanup $_SIG" "$_SIG"
done
unset _SIG
