# shellcheck shell=sh

# shellcheck disable=SC3043 # Use the local keyword since it's everywhere.

# shellcheck source-path=SCRIPTDIR
. "$(dirname "$0")/../prepare_workdir.sh"

set -eu

if [ "$#" -ge 1 ]; then
	OUTPUT="$1"
else
	OUTPUT="$(dirname "$0")/sample_special.zip"
fi

OUTPUT="$(realpath "$OUTPUT")"

if [ -e "$OUTPUT" ]; then
	rm -v "$OUTPUT"
fi
