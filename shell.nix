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

    (writeShellApplication {
      name = "kattis";
      runtimeInputs = [
        (python3.withPackages (
          ps: with ps; [
            requests
            lxml
          ]
        ))
      ];
      text =
        let
          src = pkgs.fetchFromGitHub {
            owner = "Kattis";
            repo = "kattis-cli";
            rev = "58daa46da95d43793ac2112c0a7ecc9f7280e560";
            hash = "sha256-4THcYQy+UdH40V+MGmnoiNCSDd/1dxlO7cK1Ov1KmlM=";
          };
        in
        ''
          python3 ${src}/submit.py "$@"
        '';
    })

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
