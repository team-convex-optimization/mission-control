# Mission Control

This script is meant to allow easy pipeline configuration while running the car headless (no terminal access).
To let this happens, please ensure this program is `System Setup` correctly.

## System Setup

1) Build the program with `./build.sh` (be sure to give the e`x`ecute flag first
2) run `crontab -e` and add `@reboot <path to mission control bin> &>/dev/null 2>&1

That's it! (in theory)
