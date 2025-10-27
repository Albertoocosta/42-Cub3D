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
TIMEOUT=15 # seconds timeout for each test (increased for valgrind)
VALGRIND_LOG="valgrind_output.log"

# Global variables for tracking results
VALID_PASSED=0
VALID_TOTAL=0
INVALID_PASSED=0
INVALID_TOTAL=0

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

# Function to automatically press ESC on any window that opens
auto_esc_daemon() {
	local timeout_duration="$1"
	local start_time=$(date +%s)
	
	while true; do
		local current_time=$(date +%s)
		local elapsed=$((current_time - start_time))
		
		# Stop if timeout exceeded
		if [ $elapsed -ge $timeout_duration ]; then
			break
		fi
		
		# Check for any window with "cub3D" in title and send ESC
		if command -v xdotool >/dev/null 2>&1; then
			local windows=$(xdotool search --name "cub3D" 2>/dev/null || true)
			if [ -n "$windows" ]; then
				for window in $windows; do
					xdotool windowactivate "$window" 2>/dev/null || true
					xdotool key --window "$window" Escape 2>/dev/null || true
				done
			fi
		fi
		
		sleep 0.1  # Check every 100ms
	done
}

# Function to test a single map file
test_map() {
	local map_file="$1"
	local expected_exit_code="$2"
	local test_type="$3"
	
	echo -e "${BLUE}Testing: $map_file${NC}"
	
	# Create temporary file for valgrind output
	local temp_valgrind_output=$(mktemp)
	
	# Start the auto-ESC daemon in background
	auto_esc_daemon $TIMEOUT &
	local daemon_pid=$!
	
	# Run cub3D with valgrind and timeout
	timeout $TIMEOUT valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		--log-file="$temp_valgrind_output" \
		$CUB3D_EXEC "$map_file" > /dev/null 2>&1
	local exit_code=$?
	
	# Kill the auto-ESC daemon
	kill $daemon_pid 2>/dev/null || true
	
	# Handle timeout
	if [ $exit_code -eq 124 ]; then
		echo -e "${YELLOW}  ⚠️  TIMEOUT (program took too long)${NC}"
		rm -f "$temp_valgrind_output"
		return 2
	fi
	
	# Check valgrind output for errors or leaks
	local has_memory_issues=false
	if grep -q "ERROR SUMMARY: [1-9]" "$temp_valgrind_output" || \
	   grep -q "definitely lost\|indirectly lost\|possibly lost" "$temp_valgrind_output" || \
	   grep -q "Invalid " "$temp_valgrind_output" || \
	   grep -q "Mismatched " "$temp_valgrind_output"; then
		has_memory_issues=true
	fi
	
	# If there are memory issues, append to the main log file
	if [ "$has_memory_issues" = true ]; then
		echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" >> "$VALGRIND_LOG"
		echo "MEMORY ISSUES FOUND - Testing: $map_file" >> "$VALGRIND_LOG"
		echo "Timestamp: $(date)" >> "$VALGRIND_LOG"
		echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" >> "$VALGRIND_LOG"
		cat "$temp_valgrind_output" >> "$VALGRIND_LOG"
		echo "" >> "$VALGRIND_LOG"
		echo -e "${RED}  ❌ MEMORY ISSUES DETECTED (logged to $VALGRIND_LOG)${NC}"
	fi
	
	# Clean up temp file
	rm -f "$temp_valgrind_output"
	
	# Check exit code
	if [ $exit_code -eq $expected_exit_code ]; then
		if [ "$has_memory_issues" = false ]; then
			echo -e "${GREEN}  ✅ OK (exit code: $exit_code, no memory issues)${NC}"
		else
			echo -e "${YELLOW}  ⚠️  EXIT CODE OK but memory issues found${NC}"
		fi
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
	
	echo -e "\n${YELLOW}━━━━━━━━━━━━━━━━━━━━┫ Testing $test_type maps ┣━━━━━━━━━━━━━━━━━━━━${NC}"
	
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
	
	# Store results in global variables
	if [ "$test_type" = "valid" ]; then
		VALID_PASSED=$passed
		VALID_TOTAL=$total
	elif [ "$test_type" = "invalid" ]; then
		INVALID_PASSED=$passed
		INVALID_TOTAL=$total
	fi
	
	# Print summary
	# echo -e "${BLUE}══════════════════════════════════════════════════════════════════════"
	# echo -e "${YELLOW}=== $test_type Summary ===${NC}"
	# echo -e "Total: $total"
	# echo -e "${GREEN}Passed: $passed${NC}"
	# echo -e "${RED}Failed: $failed${NC}"
	# if [ $timeout -gt 0 ]; then
	# 	echo -e "${YELLOW}Timeout: $timeout${NC}"
	# fi
	
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
	
	# Final summary with detailed counts
	echo -e "\n${YELLOW}━━━━━━━━┫ Final Result ${NC}"
	
	# Valid maps summary
	if [ $VALID_TOTAL -gt 0 ]; then
		echo -e "        ┃ Valid maps: ${GREEN}$VALID_PASSED${NC}/${BLUE}$VALID_TOTAL${NC} passed"
	else
		echo -e "Valid maps: ${YELLOW}No tests found${NC}"
	fi
	
	# Invalid maps summary
	if [ $INVALID_TOTAL -gt 0 ]; then
		echo -e "        ┃ Invalid maps: ${GREEN}$INVALID_PASSED${NC}/${BLUE}$INVALID_TOTAL${NC} passed"
	else
		echo -e "Invalid maps: ${YELLOW}No tests found${NC}"
	fi
	
	# Overall result
	if [ $total_failed -eq 0 ]; then
		echo -e "${GREEN}🎉 | All tests passed!${NC}"
	else
		echo -e "${RED}        ┃ ❌ $total_failed test(s) failed${NC}"
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

# Initialize valgrind log file
if [ -f "$VALGRIND_LOG" ]; then
	rm "$VALGRIND_LOG"
fi
echo "CUB3D VALGRIND TEST LOG" > "$VALGRIND_LOG"
echo "Generated on: $(date)" >> "$VALGRIND_LOG"
echo "═══════════════════════════════════════════════════════════════════════════════════════════════════════════" >> "$VALGRIND_LOG"
echo "" >> "$VALGRIND_LOG"

# Run the tests
echo -e "${BLUE}Starting cub3D tests with valgrind...${NC}"
echo -e "${YELLOW}Note: Memory issues will be logged to $VALGRIND_LOG${NC}"
echo -e "${YELLOW}Tests may take longer due to valgrind overhead${NC}"
run_tests
exit_code=$?

# Print final message about log file
if [ -s "$VALGRIND_LOG" ] && [ $(wc -l < "$VALGRIND_LOG") -gt 4 ]; then
	echo -e "\n${YELLOW}Memory issues were detected. Check $VALGRIND_LOG for details.${NC}"
else
	echo -e "\n${GREEN}🎉 | No memory leaks detected!${NC}"
fi

exit $exit_code