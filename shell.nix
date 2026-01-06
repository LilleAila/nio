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
  ];
}
