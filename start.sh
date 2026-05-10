#!/bin/bash

# Set GBDK path
export GBDK_HOME="$(pwd)/tools/gbdk_linux64/gbdk"
export PATH="$GBDK_HOME/bin:$PATH"

echo "GBDK_HOME set to $GBDK_HOME"

# Check Java
if ! command -v java &> /dev/null
then
    echo "Java is required for Emulicious"
fi

echo "Setup complete"
