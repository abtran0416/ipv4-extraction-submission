# AI Disclosure

Anthony Tran — September 27, 2026

I used ChatGPT for the initial C++ program, requesting GPT-6 Astra with High reasoning. I also used Codex to help word the prompts and prepare the final files. The exact prompts are in `PROMPTS.md`.

After prompt 1, I compiled and ran the program myself before sending prompt 2. After prompt 3, I also tested the program manually, noticed an error, and asked for help automating the checks. My console work and the follow-up after each prompt are described in `WORK_LOG.md`.

ChatGPT generated the initial `extractIPv4` function and `main`. I asked it to explain how the digits became numbers, how the address was stored, and how the output parameters worked. I also requested a review of malformed input and long digit groups.

Codex made three final corrections: limiting the digit-reading loops to prevent the counters from overflowing, matching the required input prompt, and adding the missing invalid-input message. These were AI-made code changes. I noticed an error during my own testing, but I did not retain enough detail to identify which of these issues I saw first.

Codex generated and ran the additional automated tests: 69 function checks and 8 console checks passed. Those automated results are separate from my manual console testing. Codex also helped draft this disclosure. The original source and the changes are included in `history/`.
