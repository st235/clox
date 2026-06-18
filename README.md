# Lox ANSI C Virtual Machine

Virtual machine implementation for the Lox programming language, implemented in ANSI C.
Based on the language and design from [Crafting Interpreters](https://craftinginterpreters.com) by Robert Nystrom.

## Lox program

```lox
print "Hello, world!";

var x = 10;
for (var i = 0; i < x; i = i + 1) {
  print i;
}
```
