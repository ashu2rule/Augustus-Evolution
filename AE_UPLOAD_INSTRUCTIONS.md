# Augustus Evolution — flat GitHub upload

Upload all `AE_*` files **individually** to the root of your `feature/intelligent-advisors-housing` branch. GitHub lets you select multiple files in one file-picker action. Do **not** upload the ZIP itself, and do not replace existing Augustus files.

- Open `AE_Prototype.html` locally for the simulated Advisor, Housing and Legion prototype.
- The diagnostic C code is standalone, **not integrated with Augustus yet**.
- On a computer with a C compiler, test using:
  `cc -std=c11 -Wall -Wextra -I. AE_diagnostics.c AE_test_diagnostics.c -o ae_test && ./ae_test`
- These flat filenames are a convenience for GitHub browser uploading. We can move them into native project directories later with Git.

**Do not upload the ZIP itself** to GitHub as a substitute for these source files.
