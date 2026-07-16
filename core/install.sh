#!/bin/bash

set -e
TARGET="seven5"
echo "Checking dependencies..."

if ! pkg-config --exists ncurses; then
    echo "ncurses not found. Installing..."

    if command -v apt >/dev/null 2>&1; then
        sudo apt update
        sudo apt install -y libncurses-dev
    elif command -v dnf >/dev/null 2>&1; then
        sudo dnf install -y ncurses-devel
    elif command -v pacman >/dev/null 2>&1; then
        sudo pacman -S --needed ncurses
    else
        echo "Unsupported package manager. Check README.md"
        exit 1
    fi
fi
echo "Dependencies Included..."
echo "Building Make File..."
make

echo "Build complete." 
if [ "$EUID" -eq 0 ]; then 
	install -m 755 "$TARGET" "/usr/local/bin/$TARGET" 
	echo "Installed successfully." 
	echo "Run: $TARGET" 

elif command -v sudo >/dev/null 2>&1; then 
	echo "Installing command system-wide..." 
	
	if sudo install -m 755 "$TARGET" "/usr/local/bin/$TARGET"; then 
		echo "Installed successfully." 
		echo "Run: $TARGET" 
	else 
		echo "System installation skipped." 
		echo "Run locally: ./$TARGET" 
		fi 
	else 
		echo "sudo is not available." 
		echo "Run locally: ./$TARGET" 
fi
