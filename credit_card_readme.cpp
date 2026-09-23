
# CreditCardValidation.md

## Overview
This program reads a credit card number entered by the user and determines
whether it is **valid** or **invalid**. A number is considered valid if it
satisfies three conditions:

1. It has between 13 and 16 digits.
2. It starts with an accepted prefix — `4` (Visa), `5` (MasterCard), `37`
   (American Express), or `6` (Discover).
3. It passes the Luhn (Mod 10) check.

The corresponding source file is `CreditCardValidation.cpp`.

---

## OOP Concepts Used

Strictly speaking, this program is written in a **procedural style** rather
than a class-based object-oriented style — there are no user-defined classes,
objects, constructors, or inheritance hierarchies. However, it still applies
several ideas that OOP is built on, and it is worth being explicit about what
is and isn't present:

* **Abstraction.** Each function hides *how* a sub-task is done behind a
  simple interface. For example, `isValid()` does not need to know how
  `sumOfDoubleEvenPlace()` performs its digit-doubling arithmetic — it just
  calls the function and uses the result. This is the same principle that
  underlies method abstraction in OOP: the caller depends only on *what* a
  function does, not *how*.
* **Encapsulation of behavior (function-level, not object-level).** Each
  function has a single, well-defined responsibility (`getDigit()` only
  collapses a two-digit number, `getSize()` only counts digits, and so on).
  This mirrors the OOP principle of encapsulating one responsibility per
  unit, even though here the "unit" is a function rather than a class.
* **Modularity / separation of concerns.** The program is broken into seven
  small functions instead of one large block of code, which is the same
  design motivation behind splitting a class into multiple methods.
* **No inheritance, polymorphism, or true encapsulation of state.** There are
  no classes, no private data members, and no objects being instantiated. If
  true OOP were required, the natural refactor would be to create a
  `CreditCard` class with a private `long long number` data member and the
  seven functions rewritten as its member methods (e.g.
  `card.isValid()` instead of `isValid(number)`).

---

## Algorithm

The program follows these main steps:

1. **Input.** `main()` prompts the user and reads the card number into a
   `long long` variable (a regular `int` would overflow, since a 16-digit
   number is far larger than `int` can hold).

2. **Length check.** `getSize(number)` counts the digits by repeatedly
   dividing the number by 10 until it reaches 0. `isValid()` rejects the
   number immediately if the digit count is not between 13 and 16.

3. **Prefix check.** `prefixMatched(number, d)` determines whether `number`
   begins with the digit(s) `d`:
   * `getSize(d)` finds how many digits `d` has (1 for `4`, `5`, `6`; 2 for
     `37`).
   * `getPrefix(number, k)` extracts the first `k` digits of `number` by
     dividing off the trailing digits.
   * The extracted prefix is compared to `d`.
   `isValid()` calls this once for each accepted prefix (`4`, `5`, `37`, `6`)
   and requires at least one to match.

4. **Luhn check (Mod 10 algorithm).**
   * `sumOfOddPlace(number)` sums the digits in odd positions counting from
     the right (1st, 3rd, 5th, …), using `% 10` to read the last digit and
     `/ 100` to skip to the next odd position.
   * `sumOfDoubleEvenPlace(number)` sums the digits in even positions
     counting from the right, but first **doubles** each digit. If doubling
     produces a two-digit result, `getDigit()` adds the two digits together
     to collapse it back to a single digit (e.g., 8 → 16 → 1+6 → 7).
   * `isValid()` adds the two sums together. If the total is evenly
     divisible by 10, the card number is valid.

5. **Output.** `main()` prints whether the entered number is valid or
   invalid based on the boolean returned by `isValid()`.

**Step-by-step trace for `4388576018410707`:**
* Digit count = 16 → passes length check.
* Starts with `4` → passes prefix check (Visa).
* Odd-place sum + doubled-even-place sum = a multiple of 10 → passes Luhn
  check → program reports **valid**.

---

## Possible Error Points

* **Integer overflow.** Using `int` instead of `long long` for the card
  number would cause overflow, since a 16-digit number exceeds the range of
  a 32-bit `int`. This is why `long long` is used throughout.
* **Leading zero loss.** Because the number is read as a numeric type
  (`long long`) rather than a string, a card number that legitimately starts
  with a leading `0` would lose that digit on input. This is a limitation of
  reading the number as an integer instead of as a string.
* **Non-numeric input.** If the user types letters, symbols, or spaces,
  `cin >> number` will fail silently (the stream enters a fail state), and
  the program may behave unpredictably or use a garbage/leftover value. The
  program does not currently validate that the input stream succeeded.
* **Off-by-one errors in `getPrefix()` and `getSize()`.** These functions
  rely on precise digit-counting logic. An off-by-one bug here (e.g., in the
  loop that strips trailing digits) would cause `prefixMatched()` to compare
  against the wrong digits, silently breaking the prefix check.
* **Odd/even place miscounting in the Luhn functions.** `sumOfOddPlace()`
  and `sumOfDoubleEvenPlace()` both depend on correctly starting from the
  rightmost digit and skipping every other digit with `/ 100`. A mistake in
  where the loop starts (e.g., forgetting to divide by 10 first in
  `sumOfDoubleEvenPlace()`) would shift every digit's "place," producing an
  incorrect Luhn sum even though the code compiles and runs without error.
* **Numbers shorter than the expected prefix.** `getPrefix()` includes a
  guard so that if `number` has fewer digits than `k`, it just returns
  `number` unchanged rather than crashing — but callers must remember this
  edge case exists, since it affects how `prefixMatched()` behaves on very
  short input.
* **Boundary length values.** Card numbers with exactly 13 or exactly 16
  digits are valid-length edge cases that should be tested explicitly, since
  off-by-one mistakes in the length check (`< 13` vs `<= 13`, `> 16` vs
  `>= 16`) are a common source of bugs.
* **Negative input.** The program does not check for negative numbers. If a
  user enters a negative value, `getSize()`, `getPrefix()`, and the Luhn
  functions may produce incorrect or undefined results, since none of the
  digit-extraction logic accounts for a sign.
