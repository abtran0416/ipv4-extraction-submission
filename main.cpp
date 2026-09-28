#include <iostream>
#include <string>

using namespace std;

// Returns true if a valid address was found, false otherwise.
//
// On success:
// outAddress holds the 32-bit value.
// outPort holds the port number, or -1 if no port was present.
//
// On failure:
// outAddress is set to 0.
// outPort is set to -1.
bool extractIPv4(const std::string& str,
                 unsigned long& outAddress,
                 int& outPort)
{
    // Default failure values.
    outAddress = 0;
    outPort = -1;

    size_t i = 0;

    // Search through the entire input line.
    while (i < str.length())
    {
        /*
         * Step 1:
         * Skip garbage characters.
         *
         * Only digits, periods, and colons can be part
         * of a possible IPv4 token.
         */
        while (i < str.length())
        {
            char c = str[i];

            bool digit = (c >= '0' && c <= '9');

            if (digit || c == '.' || c == ':')
            {
                break;
            }

            i++;
        }

        // No more possible candidates.
        if (i >= str.length())
        {
            break;
        }

        /*
         * Step 2:
         * Find the entire candidate token.
         *
         * We continue until we reach a character that is
         * NOT a digit, period, or colon.
         */
        size_t start = i;

        while (i < str.length())
        {
            char c = str[i];

            bool digit = (c >= '0' && c <= '9');

            if (!(digit || c == '.' || c == ':'))
            {
                break;
            }

            i++;
        }

        size_t end = i;

        /*
         * Candidate is str[start] through str[end - 1].
         *
         * Now validate the ENTIRE candidate.
         */
        size_t pos = start;

        bool valid = true;

        unsigned long address = 0;

        /*
         * Step 3:
         * Read exactly four octets.
         */
        for (int octet = 0; octet < 4; octet++)
        {
            /*
             * Each octet must begin with a digit.
             */
            if (pos >= end ||
                str[pos] < '0' ||
                str[pos] > '9')
            {
                valid = false;
                break;
            }

            size_t numberStart = pos;

            int value = 0;
            int digitCount = 0;

            /*
             * Build the number one digit at a time.
             *
             * Example:
             *
             * "192"
             *
             * value = 1
             * value = 1 * 10 + 9 = 19
             * value = 19 * 10 + 2 = 192
             */
            while (pos < end &&
                   str[pos] >= '0' &&
                   str[pos] <= '9')
            {
                /*
                 * We only need to accumulate the first
                 * 3 digits because more than 3 digits
                 * automatically makes an octet invalid.
                 */
                if (digitCount == 3)
                {
                    valid = false;
                    break;
                }

                value = value * 10 + (str[pos] - '0');

                digitCount++;
                pos++;
            }

            /*
             * Octet rules:
             *
             * 1-3 digits
             * value 0-255
             * no leading zero unless the number is exactly 0
             */
            if (!valid)
            {
                valid = false;
                break;
            }

            if (digitCount > 1 &&
                str[numberStart] == '0')
            {
                valid = false;
                break;
            }

            if (value > 255)
            {
                valid = false;
                break;
            }

            /*
             * Add the octet into the 32-bit address.
             *
             * Think of the address as base 256:
             *
             * A.B.C.D
             *
             * (((A * 256) + B) * 256 + C) * 256 + D
             */
            address = address * 256UL + value;

            /*
             * After the first three octets,
             * there MUST be a period.
             */
            if (octet < 3)
            {
                if (pos >= end || str[pos] != '.')
                {
                    valid = false;
                    break;
                }

                pos++;
            }
        }

        /*
         * Step 4:
         * Check for an optional port.
         */
        int port = -1;

        if (valid && pos < end)
        {
            /*
             * Anything after the fourth octet must begin
             * with ':'.
             */
            if (str[pos] != ':')
            {
                valid = false;
            }
            else
            {
                pos++;

                /*
                 * A colon must actually have a port after it.
                 */
                if (pos >= end ||
                    str[pos] < '0' ||
                    str[pos] > '9')
                {
                    valid = false;
                }
                else
                {
                    size_t portStart = pos;

                    int portValue = 0;
                    int portDigits = 0;

                    /*
                     * Build the port one digit at a time.
                     */
                    while (pos < end &&
                           str[pos] >= '0' &&
                           str[pos] <= '9')
                    {
                        /*
                         * Ports may contain at most 5 digits.
                         * We do not need to keep accumulating
                         * after that.
                         */
                        if (portDigits == 5)
                        {
                            valid = false;
                            break;
                        }

                        portValue = portValue * 10 + (str[pos] - '0');

                        portDigits++;
                        pos++;
                    }

                    /*
                     * Port rules:
                     *
                     * 1-5 digits
                     * value 0-65535
                     * no leading zero unless exactly 0
                     */
                    if (!valid)
                    {
                        valid = false;
                    }
                    else if (portDigits > 1 &&
                             str[portStart] == '0')
                    {
                        valid = false;
                    }
                    else if (portValue > 65535)
                    {
                        valid = false;
                    }
                    else
                    {
                        port = portValue;
                    }
                }
            }
        }

        /*
         * VERY IMPORTANT:
         *
         * We must have consumed the ENTIRE candidate.
         *
         * This prevents something like:
         *
         * 1.2.3.4.5
         *
         * from being accepted as:
         *
         * 1.2.3.4
         */
        if (valid && pos != end)
        {
            valid = false;
        }

        /*
         * If the whole candidate passed, return it.
         */
        if (valid)
        {
            outAddress = address;
            outPort = port;

            return true;
        }

        /*
         * Otherwise, the outer loop continues.
         *
         * Notice that i already points to the END of the
         * failed candidate, so we do not accidentally search
         * inside a malformed token.
         */
    }

    return false;
}


int main()
{
    string input;

    while (true)
    {
        cout << "Enter a string (or 'END' to quit): ";
        getline(cin, input);

        // Stop if input ends unexpectedly.
        if (!cin)
        {
            break;
        }

        // END is case-sensitive as required.
        if (input == "END")
        {
            break;
        }

        unsigned long address;
        int port;

        if (extractIPv4(input, address, port))
        {
            /*
             * Recover the four octets from the 32-bit
             * numerical address for printing.
             */
            unsigned long A =
                (address / 16777216UL) % 256;

            unsigned long B =
                (address / 65536UL) % 256;

            unsigned long C =
                (address / 256UL) % 256;

            unsigned long D =
                address % 256;

            cout << "Extracted IPv4 address: "
                 << A << "."
                 << B << "."
                 << C << "."
                 << D
                 << " (decimal value: "
                 << address
                 << ", port: ";

            if (port == -1)
            {
                cout << "none";
            }
            else
            {
                cout << port;
            }

            cout << ")" << endl;
        }
        else
        {
            cout << "Invalid input: no valid IPv4 address found" << endl;
        }
    }

    cout << "Program terminated." << endl;

    return 0;
}

