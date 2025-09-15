#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
CUB3D_EXEC="./cub3D"
MAPS_DIR="./assets/maps"
VALID_DIR="validMaps"
INVALID_DIR="invalidMaps"
TIMEOUT=5 # seconds timeout for each test

# Check if cub3D executable exists
if [ ! -f "$CUB3D_EXEC" ]; then
	echo -e "${RED}Error: $CUB3D_EXEC not found!${NC}"
	echo "Please make sure you're in the right directory and compile the project first."
	exit 1
fi

# Check if maps directory exists
if [ ! -d "$MAPS_DIR" ]; then
	echo -e "${RED}Error: $MAPS_DIR directory not found!${NC}"
	exit 1
fi

# Function to test a single map file
test_map() {
	local map_file="$1"
	local expected_exit_code="$2"
	local test_type="$3"
	
	echo -e "${BLUE}Testing: $map_file${NC}"
	
	# Run cub3D with timeout
	timeout $TIMEOUT $CUB3D_EXEC "$map_file" > /dev/null 2>&1
	local exit_code=$?
	
	# Handle timeout
	if [ $exit_code -eq 124 ]; then
		echo -e "${YELLOW}  ⚠️  TIMEOUT (program took too long)${NC}"
		return 2
	fi
	
	# Check exit code
	if [ $exit_code -eq $expected_exit_code ]; then
		echo -e "${GREEN}  ✅ OK (exit code: $exit_code)${NC}"
		return 0
	else
		echo -e "${RED}  ❌ ERROR (expected: $expected_exit_code, got: $exit_code)${NC}"
		return 1
	fi
}

# Function to recursively find and test maps
find_and_test_maps() {
	local search_dir="$1"
	local expected_exit_code="$2"
	local test_type="$3"
	
	local total=0
	local passed=0
	local failed=0
	local timeout=0
	
	echo -e "\n${YELLOW}=== Testing $test_type maps ===${NC}"
	
	# Find all .cub files recursively
	while IFS= read -r -d '' map_file; do
		((total++))
		test_map "$map_file" "$expected_exit_code" "$test_type"
		local result=$?
		
		if [ $result -eq 0 ]; then
			((passed++))
		elif [ $result -eq 1 ]; then
			((failed++))
		else
			((timeout++))
		fi
	done < <(find "$search_dir" -name "*.cub" -print0 2>/dev/null)
	
	# Print summary
	echo -e "${YELLOW}=== $test_type Summary ===${NC}"
	echo -e "Total: $total"
	echo -e "${GREEN}Passed: $passed${NC}"
	echo -e "${RED}Failed: $failed${NC}"
	if [ $timeout -gt 0 ]; then
		echo -e "${YELLOW}Timeout: $timeout${NC}"
	fi
	
	return $failed
}

# Main testing function
run_tests() {
	local total_failed=0
	
	# Test valid maps (should exit with 0)
	if [ -d "$MAPS_DIR/$VALID_DIR" ]; then
		find_and_test_maps "$MAPS_DIR/$VALID_DIR" 0 "valid"
		total_failed=$((total_failed + $?))
	else
		echo -e "${YELLOW}Warning: $VALID_DIR directory not found${NC}"
	fi
	
	# Test invalid maps (should NOT exit with 0)
	if [ -d "$MAPS_DIR/$INVALID_DIR" ]; then
		find_and_test_maps "$MAPS_DIR/$INVALID_DIR" 1 "invalid"
		total_failed=$((total_failed + $?))
	else
		echo -e "${YELLOW}Warning: $INVALID_DIR directory not found${NC}"
	fi
	
	# Final summary
	echo -e "\n${YELLOW}=== FINAL SUMMARY ===${NC}"
	if [ $total_failed -eq 0 ]; then
		echo -e "${GREEN}🎉 All tests passed!${NC}"
	else
		echo -e "${RED}❌ $total_failed test(s) failed${NC}"
	fi
	
	return $total_failed
}

# Make the cub3D executable if it doesn't exist or is outdated
if [ ! -f "$CUB3D_EXEC" ] || [ Makefile -nt "$CUB3D_EXEC" ]; then
	echo -e "${BLUE}Compiling cub3D...${NC}"
	make > /dev/null 2>&1
	if [ $? -ne 0 ]; then
		echo -e "${RED}Compilation failed!${NC}"
		exit 1
	fi
	echo -e "${GREEN}Compilation successful!${NC}"
fi

# Run the tests
echo -e "${BLUE}Starting cub3D tests...${NC}"
run_tests
exit $?