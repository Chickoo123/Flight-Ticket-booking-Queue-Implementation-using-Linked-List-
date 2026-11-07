#!/usr/bin/env bash
# End-to-end smoke tests: drive the interactive programs with scripted input.
set -euo pipefail
cd "$(dirname "$0")/.."

expect() { grep -qF -- "$2" <<<"$1" || { echo "FAIL: expected '$2'"; echo "$1"; exit 1; }; }

# Flight queue: names with spaces, blank-name rejection, FIFO processing.
out=$(printf '1\nAsha Mehta\n1\n   \nRavi Kumar\nxyz\n3\n2\n3\n4\n' | ./build/flight_booking)
expect "$out" "Ticket ID: 1"
expect "$out" "Value cannot be empty"
expect "$out" "Ticket ID: 2"
expect "$out" "That is not a number"
expect "$out" "#1  Asha Mehta"
expect "$out" "Processing booking for Asha Mehta (Ticket ID 1)"

# Train stack: LIFO cancel and view.
out=$(printf '1\nT100\n1\nT200\n3\n2\n4\n5\n' | ./build/train_booking)
expect "$out" "Current ticket: T200"
expect "$out" "Cancelling ticket: T200"
expect "$out" "newest first"

# EOF must terminate cleanly instead of looping forever.
printf '1\n' | timeout 5 ./build/flight_booking >/dev/null
printf '' | timeout 5 ./build/train_booking >/dev/null

echo "Smoke tests passed."
