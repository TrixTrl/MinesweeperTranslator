File Format
===========

1. The first line contains a single character denoting what cells should be revealed initially.
   * Any token following this token will not be hidden with spoiler tags in the final output

2. The next lines define the used tokens and their replacements.
   * Each token is a single character, this is followed by a `|` and a string of arbitrary length that this token should be replaced by in the final output
   * `TOKEN|TOKEN_DEFINITION`
   * `1|:one:` would result in the token `1` being replaced with the string `:one:` in the final output

3. An empty line signals the end of the definitions section.

4. The board is written out row by row, with each line of the file being one row of the puzzle.
   * Every line must have the same number of tokens, not counting the one for being initially revealed
   * Irregular board shapes can be created using dummy tokens defined to be blank spaces
