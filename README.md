# IPv4 Extraction Assignment

This C++ program finds one valid IPv4 address and an optional port within a line of text. It checks each candidate completely and builds the numbers one digit at a time.

## Compile and run

From this folder, enter:

```sh
c++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp -o ipv4
./ipv4
```

Enter a line when prompted. Enter exactly `END` to quit. Invalid input prints a message, and the program continues asking for input.

## Test the program

Run the C++ function tests:

```sh
c++ -std=c++17 -Wall -Wextra -Wpedantic tests.cpp -o ipv4_tests
./ipv4_tests
```

To also check the console output, run:

```sh
python3 run_tests.py
```

The Python runner needs a C++17 compiler with AddressSanitizer and UndefinedBehaviorSanitizer support. It uses Python's standard library only. Codex ran these automated checks on September 27, 2026: 69 function checks and 8 console checks passed. The actual results are in `test_results.txt`.

## Submission files

- `main.cpp`: final source code.
- `tests.cpp` and `run_tests.py`: test cases and runner.
- `test_results.txt`: automated test results.
- `AI_DISCLOSURE.md`: short disclosure of AI use and code changes.
- `PROMPTS.md`: exact prompts entered in the code-generation chat.
- `WORK_LOG.md`: work after each prompt, personal console work, and AI-assisted follow-up.
- `history/`: original generated code, the changes, and its automated test results.

Compile `main.cpp` and `tests.cpp` separately. The history file is an earlier version, not an additional source file to link into the final program.

If a line contains multiple separate valid addresses, the program returns the first one from left to right. This is an assumption because the assignment does not specify which one to choose. The long-input tests use one million digits; the original digit-counter overflow was identified by code inspection rather than an executed input large enough to overflow an `int`.
