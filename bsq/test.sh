#!/bin/bash

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Test directory
TEST_DIR="maps"
PROG="./bsq"

# Check if bsq exists
if [ ! -f "$PROG" ]; then
    echo -e "${RED}[ERROR]${NC} BSQ program not found. Please compile first."
    exit 1
fi

# Run tests
PASSED=0
FAILED=0

echo "Running tests..."
echo ""

for map_file in "$TEST_DIR"/*.txt; do
    test_name=$(basename "$map_file")
    
    # Run the test and capture output and exit code
    output=$("$PROG" "$map_file" 2>&1)
    exit_code=$?
    
    # Check if test passed (exit code 0 and has output)
    if [ $exit_code -eq 0 ] && [ -n "$output" ]; then
        echo -e "${GREEN}[PASS]${NC} $test_name"
        ((PASSED++))
    else
        echo -e "${RED}[FAIL]${NC} $test_name (exit code: $exit_code)"
        ((FAILED++))
    fi
done

echo ""
echo "================================"
echo -e "Total: $((PASSED + FAILED)) tests"
echo -e "${GREEN}Passed: $PASSED${NC}"
echo -e "${RED}Failed: $FAILED${NC}"
echo "================================"

# Exit with appropriate code
if [ $FAILED -eq 0 ]; then
    exit 0
else
    exit 1
fi
