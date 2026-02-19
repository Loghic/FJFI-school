#!/bin/bash

# Build script with automatic error logging
# Usage: ./build.sh lesson1/ex1 [run]

set -o pipefail

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
LESSON=${1:-"lesson1"}
RUN_AFTER=${2:-""}
LOG_DIR="build-logs"
TIMESTAMP=$(date +%Y%m%d-%H%M%S)
LOG_FILE="$LOG_DIR/${LESSON//\//-}-$TIMESTAMP.log"

# Create log directory
mkdir -p "$LOG_DIR"

# Header
echo -e "${BLUE}======================================${NC}"
echo -e "${BLUE}🔨 Zig Build System${NC}"
echo -e "${BLUE}======================================${NC}"
echo -e "📁 Lesson:    ${YELLOW}$LESSON${NC}"
echo -e "📝 Log file:  ${YELLOW}$LOG_FILE${NC}"
echo -e "⏰ Time:      $(date '+%Y-%m-%d %H:%M:%S')"
echo -e "${BLUE}======================================${NC}"
echo ""

# Run build and capture output
echo -e "${BLUE}Building...${NC}\n"

zig build -Dlesson="$LESSON" 2>&1 | tee "$LOG_FILE"
BUILD_STATUS=${PIPESTATUS[0]}

echo ""
echo -e "${BLUE}======================================${NC}"

# Check build result
if [ $BUILD_STATUS -eq 0 ]; then
    echo -e "${GREEN}✅ BUILD SUCCESSFUL${NC}"

    # Find the binary name (replace / with -)
    BINARY_NAME="${LESSON//\//-}"
    BINARY_PATH="./zig-out/bin/$BINARY_NAME"

    if [ -f "$BINARY_PATH" ]; then
        echo -e "📦 Binary:    ${GREEN}$BINARY_PATH${NC}"

        # Show binary size
        SIZE=$(ls -lh "$BINARY_PATH" | awk '{print $5}')
        echo -e "📏 Size:      ${GREEN}$SIZE${NC}"
    fi

    # Save success log with a marker
    echo -e "\n=== BUILD SUCCESSFUL ===" >> "$LOG_FILE"

    # Run if requested
    if [ "$RUN_AFTER" = "run" ] && [ -f "$BINARY_PATH" ]; then
        echo -e "${BLUE}======================================${NC}"
        echo -e "${BLUE}🚀 Running program...${NC}\n"
        "$BINARY_PATH"
        RUN_STATUS=$?
        echo ""
        if [ $RUN_STATUS -eq 0 ]; then
            echo -e "${GREEN}✅ Program exited successfully${NC}"
        else
            echo -e "${RED}❌ Program exited with code $RUN_STATUS${NC}"
        fi
    fi

else
    echo -e "${RED}❌ BUILD FAILED${NC}"
    echo -e "📋 Error log: ${RED}$LOG_FILE${NC}"
    echo ""

    # Show last 15 lines of errors
    echo -e "${YELLOW}Last 15 lines of build output:${NC}"
    echo -e "${BLUE}--------------------------------------${NC}"
    tail -n 15 "$LOG_FILE"
    echo -e "${BLUE}--------------------------------------${NC}"

    # Save failure log with marker
    echo -e "\n=== BUILD FAILED ===" >> "$LOG_FILE"

    echo ""
    echo -e "${YELLOW}💡 Tips:${NC}"
    echo -e "  • Check syntax errors in your source files"
    echo -e "  • Run: ${BLUE}zig build -Dlesson=$LESSON --verbose${NC} for more details"
    echo -e "  • Full log: ${BLUE}cat $LOG_FILE${NC}"
fi

echo -e "${BLUE}======================================${NC}"

# Clean old logs (keep last 10)
LOG_COUNT=$(ls -1 "$LOG_DIR" 2>/dev/null | wc -l)
if [ "$LOG_COUNT" -gt 10 ]; then
    echo -e "\n${YELLOW}🧹 Cleaning old logs (keeping last 10)...${NC}"
    ls -t "$LOG_DIR"/* | tail -n +11 | xargs rm -f
fi

exit $BUILD_STATUS
