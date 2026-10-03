# mysh

A tiny Unix shell written in C. Learning project: read a line, parse args, `fork`/`exec`, optional stdout redirect.

Inspired by / transcribed from [this video](https://youtube.com/watch?v=_pc7pVvAoCg).

## Features

- Interactive prompt (`$ `)
- Script mode: `./mysh script.sh`
- `#` line comments
- Stdout redirect: `echo hello > out.txt`
- Builtin: `exit`

## Build

```bash
make
```

Requires a C compiler (`clang` or `gcc`) and `make`.

## Run

```bash
./mysh              # interactive
./mysh examples/hello.sh
```

## Make targets

| Target     | Description                |
| ---------- | -------------------------- |
| `make` / `make all` | Build `mysh`        |
| `make clean`        | Remove build artifacts |
| `make test`         | Smoke-run example script |
| `make run`          | Rebuild and start interactive shell |

## Limitations

Not a full shell. Missing on purpose (for now):

- Pipes (`\|`)
- Input redirect (`<`)
- Quoting / escapes
- Builtins beyond `exit` (no `cd`, `pwd`, …)
- Job control / signal handling

## License

[MIT](LICENSE)
