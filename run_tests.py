"""Compile the actual C++ program and check its function and console behavior.

AI-generated test runner; uses Python's standard library only.
Run: python3 run_tests.py
An optional --source path checks a saved earlier version of main.cpp.
"""
from pathlib import Path
import argparse
import os
import shutil
import subprocess
import tempfile

parser = argparse.ArgumentParser()
parser.add_argument('--source', type=Path)
args = parser.parse_args()
root = Path(__file__).resolve().parent
source = args.source.resolve() if args.source else root / 'main.cpp'
compiler = os.environ.get('CXX', 'c++')
prompt = "Enter a string (or 'END' to quit): "
invalid = 'Invalid input: no valid IPv4 address found\n'
termination = 'Program terminated.\n'

def success(ip, address, port='none'):
    return f'Extracted IPv4 address: {ip} (decimal value: {address}, port: {port})\n'

sample_inputs = [
    'connecting to 192.168.1.1 now', 'server=10.0.0.255:8080end',
    '192a168.1.1.1', '192.168.1.1.',
    'Connection from 192.168.1.1 refused', '192.168.01.1',
    '1.2.3.4:99999', '12.34.56', 'no number here', 'END'
]
sample_results = [
    success('192.168.1.1', 3232235777), success('10.0.0.255', 167772415, 8080),
    success('168.1.1.1', 2818638081), invalid,
    success('192.168.1.1', 3232235777), invalid, invalid, invalid, invalid, termination
]
console_tests = [
    ('complete assignment sample', '\n'.join(sample_inputs) + '\n',
     ''.join(prompt + line for line in sample_results)),
    ('END terminates before later lines', 'END\n1.2.3.4\n', prompt + termination),
    ('case and spaces are significant', 'end\nEND \n END\nEND\n',
     (prompt + invalid) * 3 + prompt + termination),
    ('empty input line then END', '\nEND\n', prompt + invalid + prompt + termination),
    ('port zero prints zero', '1.2.3.4:0\nEND\n',
     prompt + success('1.2.3.4', 16909060, 0) + prompt + termination),
    ('invalid port followed by separate address', '1.2.3.4:65536 x 8.8.8.8:53\nEND\n',
     prompt + success('8.8.8.8', 134744072, 53) + prompt + termination),
    ('immediate end of file', '', prompt + termination),
    ('last line without newline', '1.2.3.4',
     prompt + success('1.2.3.4', 16909060) + prompt + termination),
]

with tempfile.TemporaryDirectory(prefix='ipv4-tests-') as folder:
    build = Path(folder)
    shutil.copyfile(source, build / 'main.cpp')
    shutil.copyfile(root / 'tests.cpp', build / 'tests.cpp')
    flags = ['-std=c++17', '-Wall', '-Wextra', '-Wpedantic', '-Werror',
             '-fsanitize=address,undefined', '-fno-omit-frame-pointer', '-g']
    print('Compiler:', subprocess.check_output([compiler, '--version'], text=True).splitlines()[0], flush=True)
    print('Flags:', ' '.join(flags), flush=True)
    for name in ['main', 'tests']:
        subprocess.run([compiler, *flags, str(build / (name + '.cpp')), '-o', str(build / name)], check=True)
    print('Builds completed with warnings treated as errors.\n', flush=True)
    result = subprocess.run([str(build / 'tests')], text=True, capture_output=True, timeout=30)
    print(result.stdout, end='', flush=True)
    if result.stderr:
        print(result.stderr, flush=True)
    failures = int(result.returncode != 0)
    passed = 0
    for label, user_input, expected in console_tests:
        actual = subprocess.run([str(build / 'main')], input=user_input, text=True,
                                capture_output=True, timeout=10)
        ok = actual.returncode == 0 and actual.stdout == expected and not actual.stderr
        passed += int(ok)
        failures += int(not ok)
        print(('PASS ' if ok else 'FAIL ') + 'console: ' + label)
        if not ok:
            print('  expected:', repr(expected))
            print('  actual:  ', repr(actual.stdout))
            if actual.stderr:
                print('  stderr:', actual.stderr)
    print(f'Console tests: {passed}/{len(console_tests)} passed')
    print('PASS: all checks completed without sanitizer diagnostics' if failures == 0
          else 'FAIL: inspect the differences above')
    raise SystemExit(0 if failures == 0 else 1)
