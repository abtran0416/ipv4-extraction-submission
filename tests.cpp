// AI-generated function tests. This includes the actual parser, not a copy.
#define main ipv4_program_main
#include "main.cpp"
#undef main

#include <iomanip>
#include <vector>

struct TestCase
{
    string label;
    string input;
    bool found;
    unsigned long address;
    int port;
};

int main()
{
    const vector<TestCase> cases = {
        {"sample connecting", "connecting to 192.168.1.1 now", true, 3232235777UL, -1},
        {"sample server port", "server=10.0.0.255:8080end", true, 167772415UL, 8080},
        {"letter separates candidates", "192a168.1.1.1", true, 2818638081UL, -1},
        {"sample trailing period", "192.168.1.1.", false, 0UL, -1},
        {"sample connection", "Connection from 192.168.1.1 refused", true, 3232235777UL, -1},
        {"sample leading zero", "192.168.01.1", false, 0UL, -1},
        {"sample invalid port", "1.2.3.4:99999", false, 0UL, -1},
        {"sample three octets", "12.34.56", false, 0UL, -1},
        {"sample no address", "no number here", false, 0UL, -1},
        {"minimum address", "0.0.0.0", true, 0UL, -1},
        {"maximum address", "255.255.255.255", true, 4294967295UL, -1},
        {"minimum port", "0.0.0.0:0", true, 0UL, 0},
        {"maximum address and port", "255.255.255.255:65535", true, 4294967295UL, 65535},
        {"ordinary address", "1.2.3.4", true, 16909060UL, -1},
        {"ordinary port", "1.2.3.4:80", true, 16909060UL, 80},
        {"port one", "1.2.3.4:1", true, 16909060UL, 1},
        {"four digit port", "1.2.3.4:9999", true, 16909060UL, 9999},
        {"five digit port", "1.2.3.4:10000", true, 16909060UL, 10000},
        {"port above limit", "1.2.3.4:65536", false, 0UL, -1},
        {"six digit port", "1.2.3.4:100000", false, 0UL, -1},
        {"empty port", "1.2.3.4:", false, 0UL, -1},
        {"port double zero", "1.2.3.4:00", false, 0UL, -1},
        {"port leading zero", "1.2.3.4:080", false, 0UL, -1},
        {"port leading zero at limit", "1.2.3.4:065535", false, 0UL, -1},
        {"first octet above limit", "256.2.3.4", false, 0UL, -1},
        {"second octet above limit", "1.256.3.4", false, 0UL, -1},
        {"third octet above limit", "1.2.256.4", false, 0UL, -1},
        {"fourth octet above limit", "1.2.3.256", false, 0UL, -1},
        {"first octet leading zero", "01.2.3.4", false, 0UL, -1},
        {"second octet leading zero", "1.02.3.4", false, 0UL, -1},
        {"third octet leading zero", "1.2.03.4", false, 0UL, -1},
        {"fourth octet leading zero", "1.2.3.04", false, 0UL, -1},
        {"zero octet repeated digits", "1.2.3.000", false, 0UL, -1},
        {"four digit first octet", "1234.2.3.4", false, 0UL, -1},
        {"four digit last octet", "1.2.3.1234", false, 0UL, -1},
        {"one octet", "192", false, 0UL, -1},
        {"two octets", "1.2", false, 0UL, -1},
        {"three octets", "1.2.3", false, 0UL, -1},
        {"five octets no prefix salvage", "1.2.3.4.5", false, 0UL, -1},
        {"invalid first octet no suffix salvage", "999.1.2.3.4", false, 0UL, -1},
        {"empty second octet", "1..2.3.4", false, 0UL, -1},
        {"empty third octet", "1.2..4", false, 0UL, -1},
        {"empty fourth octet", "1.2.3.", false, 0UL, -1},
        {"leading period", ".1.2.3.4", false, 0UL, -1},
        {"leading colon", ":1.2.3.4", false, 0UL, -1},
        {"misplaced colon", "1.2:3.4", false, 0UL, -1},
        {"two adjacent colons", "1.2.3.4::80", false, 0UL, -1},
        {"second colon after port", "1.2.3.4:80:90", false, 0UL, -1},
        {"trailing colon after port", "1.2.3.4:80:", false, 0UL, -1},
        {"period after port", "1.2.3.4:80.", false, 0UL, -1},
        {"decimal-looking port", "1.2.3.4:80.5", false, 0UL, -1},
        {"empty string", "", false, 0UL, -1},
        {"spaces", "   ", false, 0UL, -1},
        {"punctuation only", "...:::...", false, 0UL, -1},
        {"garbage separates octets", "1.2a3.4", false, 0UL, -1},
        {"surrounding garbage", "abc[1.2.3.4]xyz", true, 16909060UL, -1},
        {"letters after port", "abc1.2.3.4:80xyz", true, 16909060UL, 80},
        {"sign after colon leaves empty port", "1.2.3.4:-1", false, 0UL, -1},
        {"plus after colon leaves empty port", "1.2.3.4:+80", false, 0UL, -1},
        {"punctuation as garbage separator", "1.2.3.4,", true, 16909060UL, -1},
        {"later address after bad port", "1.2.3.4:65536 x 8.8.8.8:53", true, 134744072UL, 53},
        {"later address after bad octet count", "1.2.3.4.5 x 8.8.8.8", true, 134744072UL, -1},
        {"later address after leading punctuation", ".1.2.3.4 x 8.8.8.8", true, 134744072UL, -1},
        {"multiple valid candidates use first", "1.2.3.4 x 8.8.8.8:53", true, 16909060UL, -1},
        {"letter separates port from later digits", "1.2.3.4:80a90", true, 16909060UL, 80},
        {"one million octet digits", string(1000000, '9') + ".2.3.4", false, 0UL, -1},
        {"one million port digits", "1.2.3.4:" + string(1000000, '9'), false, 0UL, -1},
        {"later address after huge candidate", string(1000000, '9') + " x 8.8.8.8", true, 134744072UL, -1}
    };

    int failed = 0;
    int total = 0;
    for (const TestCase& test : cases)
    {
        unsigned long address = 123UL;
        int port = 123;
        const bool found = extractIPv4(test.input, address, port);
        const bool passed = found == test.found && address == test.address && port == test.port;
        total++;
        if (!passed) failed++;
        cout << (passed ? "PASS " : "FAIL ") << total << ": " << test.label << '\n';
        if (test.input.size() <= 100)
            cout << "  input: " << quoted(test.input) << '\n';
        else
            cout << "  input length: " << test.input.size() << " (construction in tests.cpp)\n";
        cout << "  expected: " << test.found << ' ' << test.address << ' ' << test.port << '\n';
        cout << "  actual:   " << found << ' ' << address << ' ' << port << '\n';
    }

    // Same variables reused across success, failure, and zero-address success.
    unsigned long address = 0;
    int port = -1;
    bool passed = extractIPv4("1.2.3.4:80", address, port)
                  && address == 16909060UL && port == 80;
    passed = !extractIPv4("1.2.3.4:", address, port)
             && address == 0UL && port == -1 && passed;
    passed = extractIPv4("0.0.0.0", address, port)
             && address == 0UL && port == -1 && passed;
    total++;
    if (!passed) failed++;
    cout << (passed ? "PASS " : "FAIL ") << total << ": reused output variables\n";
    cout << "  expected and checked: success 16909060 80; failure 0 -1; success 0 -1\n";
    cout << "Function tests: " << (total - failed) << '/' << total << " passed\n";
    return failed == 0 ? 0 : 1;
}
