# Lox ANSI C Virtual Machine

Virtual machine implementation for the Lox programming language, implemented in ANSI C.
Based on the language and design from [Crafting Interpreters](https://craftinginterpreters.com) by Robert Nystrom.

## Building

There are a few build flags available

| Flag | Description | Default value |
| ---- | ---- | ---- |
| `ENABLE_DEBUG` | Enables debug information: dissasembling op codes, printing runtime stack, logging garbage collector. | OFF |
| `ENABLE_NAN_TAGGING` | Enables NaN tagging for value types. | ON |

You can use these flags in succession with `cmake` to generate the project. See an example script below:

```bash
cmake . -B out -DENABLE_DEBUG=OFF
```

## Lox program

```lox
print "Hello, world!";

var x = 10;
for (var i = 0; i < x; i = i + 1) {
  print i;
}
```

>[!TIP]
> You can find more lox code snippets under [the test folder](./tests/res/).
