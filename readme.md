# NIO

## Running the code

This replicates excactly how it is run on the competition server, however LSP support is limited / non existant when working on standalone rust files outside of a cargo project.

```sh
rustc -O -o main main.rs && ./main < examples/1.txt
```

One could do this instead, which makes it easier to develop locally, with the limitation that if you are working on multiple versions of the code in different files, the LSP only works in the main file and is disabled in the others as this is not how cargo is really supposed to be used. Could be fixed with a wrapper or utility script or something maybe?

```sh
cargo run < examples/1.txt
```

Note that this will also require this in the `Cargo.toml` such that it complies with the same rules used by the version on the server:

```toml
[package]
edition = "2015"
```

Most notably, this applies to the `try_into`-function which has to be imported in the `2015`-version of rust.

## Oversikt over poeng på oppgavene

| Points (/100) | Name                              | Done in competition |
| ------------- | --------------------------------- | ------------------- |
| 0             | `nio16-finale-reven`              |                     |
| 0             | `nio18-finale-klassebilde`        |                     |
| 60            | `nio21-runde2-tetris`             |                     |
| 100           | `nio21-finale-togtur`             |                     |
| 100           | `nio22-finale-brusskap`           |                     |
| 100           | `nio23-runde2-lynnedslag`         |                     |
| 100           | `nio23-runde2-bananbonanza`       |                     |
| 27            | `nio23-runde2-personlighetstyper` |                     |
| 0             | `nio23-runde2-nettverkssikkerhet` |                     |
| 80            | `nio23-finale-ekornfare`          |                     |
| 100           | `nio24-finale-trebygger`          |                     |
| 100           | `nio25-runde2-byggeklosser`       |                     |
| 15            | `nio25-runde2-oyberedskap`        |                     |
| 16            | `nio25-runde2-tennis`             |                     |
| 0             | `nio25-runde2-utjevning`          |                     |
| 100           | `nio25-finale-papirfly`           |                     |
| 100           | `nio25-finale-runddans`           |                     |
| 0             | `nio25-finale-ormhull`            |                     |
| 100           | `nio25-finale-belysning`          |                     |
| 41            | `nio26-runde2-logistikkdroem`     | x                   |
| 85            | `nio26-runde2-romfart`            | x                   |
| 100           | `nio26-runde2-klatrevegger`       | x                   |
| 100           | `nio26-runde2-tradisjonsmat`      | x                   |
| 100           | `nio26-runde2-tannhelse`          | x                   |

## Deltakelser i rundene

### 2025/26

- Runde 1: 39/40 poeng, 5. plass
- Runde 2: 428/500 poeng, 13. plass

### 2024/25

- Runde 1: 39/44 poeng, 31. plass
- Runde 2: ¯\\_(ツ)_/¯

### 2022/23

- Runde 1: 28/40 poeng, 185. plass
- Runde 2: ¯\\_(ツ)_/¯
