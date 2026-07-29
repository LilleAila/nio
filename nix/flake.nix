{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs =
    { nixpkgs, ... }@inputs:
    let
      inherit (nixpkgs) lib;
      systems = lib.systems.flakeExposed;
      pkgsFor = lib.genAttrs systems (system: import nixpkgs { inherit system; });
      forEachSystem = f: lib.genAttrs systems (system: f pkgsFor.${system});
    in
    {
      devShells = forEachSystem (pkgs: {
        default = pkgs.mkShell {
          packages = with pkgs; [
            nixfmt
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
        };
      });
    };
}
