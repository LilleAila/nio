with import <nixpkgs> { };
mkShell {
  packages = [
    nixfmt-rfc-style
    nixd
    statix

    rustc
    cargo
    rustfmt
    rust-analyzer

    black
    pyright
    ruff
    python3

    typst
    tinymist
    typstyle

    gcc
    clang-tools
    gdb
    lldb

    prettierd

    hyperfine
  ];
}
