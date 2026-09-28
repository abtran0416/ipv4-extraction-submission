# Exact prompts and AI assistance

The three prompts below were retrieved from the ChatGPT conversation titled Write C++ IPv4 Parser. Text is preserved as entered. The first prompt also included two assignment screenshots; the retrieval annotation about attachments is not part of the prompt.

Conversation: https://chatgpt.com/c/6ab9ea6a-5e8c-83ea-9cd4-d8f6d1f2320c

## Prompt 1 — September 27, 2026, 11:18 PM Central time

```text
I need help writing this program in C++. The purpose of the program is to go through a line of text and find whether or not there is a valid IPv4 address, along with a port if one is included. Please use the requirements I attached above.
My idea is to use a loop to go through the string one character at a time and check each part of the address. From there, the program would check whether each number is within the allowed range and whether the periods and colon are in the correct places. Can you help me turn this into a working program using straightforward loops, conditions, and functions?
Please use the exact extractIPv4 function given in the instructions and keep the input and output in main. Since the assignment does not allow functions that convert strings into numbers, show how to build each number from the individual digits.
One thing I want to understand is how the program knows where a possible address starts and ends. If there is an extra period or an invalid port, it needs to reject that whole group instead of returning just the part that looks correct. However, it should still check for a separate valid address later in the text.
Please follow the number limits, leading zero rules, and output format in the screenshots. The program should continue asking for input until END is entered. Explain how each part works with the rest of the program so I can follow what it is doing.
```

## Prompt 2 — September 27, 2026, 11:29 PM Central time

```text
Can you explain how the numbers are being built one digit at a time? For example, if the program reads 192, show what the stored value is after reading each character.
From there, explain how the four numbers are combined into the unsigned long address. I also want to understand why outAddress and outPort have an & in the function parameters and how main receives those values when the function itself returns true or false.
Please use the actual variables from the code when explaining this so I can follow where each value changes.
```

## Prompt 3 — September 27, 2026, 11:30 PM Central time

```text
Now I want to check how the program handles an input that looks like an address but is not valid. Can you go through what the code does with 192.168.1.1. and 1.2.3.4:65536? Both should be rejected completely, so I want to see where that happens in the code.
Also check 192a168.1.1.1. Since the letter separates the two groups, the program should be able to find 168.1.1.1 without joining it to 192.
Please check the actual code instead of just explaining what it should do. If it handles one of these incorrectly, show which part causes the problem and explain the change needed. Also check whether a very long group of digits could cause a problem before the program rejects it.
```

## Additional Codex assistance

Before these prompts were sent, a separate Codex conversation helped draft and revise them using the assignment screenshots and the wording style of an earlier EECS 140 report. The three prompts above therefore also reflect AI assistance with prompt writing.

After the linked conversation, the following request authorized Codex to review the code and prepare the remaining submission files. The nonbreaking space after the link is retained below.

```text
okay here is my outputs and chats, can you finish up the rest of the assignment for me https://chatgpt.com/c/6ab9ea6a-5e8c-83ea-9cd4-d8f6d1f2320c make sure the ai disclosure uses same format as the eecs 140 lab report
```

A later screenshot supplied the grading criteria and sample run, including the exact input prompt and invalid-input message. Codex applied the digit-loop correction discussed in ChatGPT, corrected the console output, generated and executed the additional tests, and prepared the disclosure and repository files. These code changes and additional automated tests were AI-assisted. My separate manual console work is described in WORK_LOG.md.

## Follow-up about personal console work

While preparing the revised submission, I provided these clarifications. They describe my manual work; they are not additional code-generation prompts.

```text
I did all the console commands intially between prompt 1 and 2 and then i found out the bug myself, then I was stuck on one part
```

```text
I forgot specifcially which one, also after prompt 3 and the tests, I tested it first itiially then found out the error then i had it help automate
```

WORK_LOG.md records that manual work and provides commands for repeating the steps. It does not present suggested commands as a saved terminal transcript or claim that a particular confirmed fix was the issue I personally noticed first.
