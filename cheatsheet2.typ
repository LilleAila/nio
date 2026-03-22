#import "@preview/colorful-boxes:1.4.2": colorbox

#set text(
  font: "DejaVu Sans",
  size: 8pt,
) // Uses fonts from system, requires to be installed

#set page(
  paper: "a4",
  margin: (top: 2cm, bottom: 2cm, left: 1cm, right: 1cm),
  header: {
    grid(
      columns: (1fr, auto),
      [NIO Cheatsheet 2 (c++)], align(right)[Olai Solsvik],
    )
    line(length: 100%)
  },
  footer: context {
    line(length: 100%)
    align(right)[#counter(page).display("1/1", both: true)]
  },
  columns: 2,
)
#set par(leading: 0.55em)

#show raw: set text(font: "JetBrainsMono NF")
#show raw.where(block: true): x => block(
  fill: luma(245),
  stroke: 1pt + luma(200),
  inset: 10pt,
  radius: 4pt,
  width: 100%,
  x,
)
#show raw.where(block: false): x => {
  h(1pt)
  box(
    fill: luma(240),
    stroke: 1pt + luma(200),
    inset: (x: 3pt),
    outset: (y: 3pt),
    radius: 2pt,
    x,
  )
  h(1pt)
}

#let note(body) = colorbox(title: "Note", color: "blue", body)

#outline(depth: 4)

= Introduction

This document contains commonly used code for competitive programming in c++ as preparation for the 2026 nordic-baltic olympiad of informatics.

= Basics

== Vim config

Here is a basic vim config for competitive programming in rust:

```vim
let mapleader = " "
nnoremap <leader>ff :%!rustfmt<cr>
nnoremap <leader>fm :Explore<cr>
tnoremap <Esc> <C-\><C-n>

syntax on
set clipboard=unnamedplus
set mouse=a
set hlsearch
set incsearch
set ignorecase
set smartcase

set number
set relativenumber
set cursorline
set nowrap

set tabstop=4
set shiftwidth=4
set expandtab
set autoindent
set smartindent

hi CursorLine cterm=NONE ctermbg=236
hi MatchParen ctermfg=0 ctermbg=188
```

Place this in `~/.vimrc` or `~/.config/nvim/init.vim` at the start of the competition.

== C++ Boilerplate

```cpp
#include <iostream>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
}
```

#note[
  Some environments provide `#include <bits/stdc++.h>`, but it is not always present. This non-standard header file imports all the standard libraries and avoids having to import many things in the same file.
]

== Reading input values

Reading a single value:

```cpp
int n;
cin >> n;
```

Reading multiple values on the same line. Types can also be mixed in the same line, for example

```cpp
int u, v;
Permission k;
cin >> u >> v >> k;
```

Reading values from multiple lines:

```cpp
vector<int> xs(n);
for (int i = 0; i < n; i++) {
  int x;
  cin >> x;
  xs[i] = x;
}
```

Reading $n$ values from the same line: TODO

== Binary

Parsing a binary value:

```cpp
#include <string>

string input;
cin >> input;
int x = stoi(input, nullptr, 2);
```

#note[
  The radix $2$ can also be replaced with any other integer.
]

Alternatively, a bitset can be used, as described in that section of this document.

== Useful Data Types

=== Defining Types

New types can be defined with `using` as follows

```cpp
using ll = long long;
```

=== Number Types

Signed integers:

#table(
  columns: 2,
  [*Type*], [*Bits*],
  [`char`], [$8$],
  [`short`], [$16$],
  [`int`], [$16$ / $32$],
  [`long`], [$32$],
  [`long long`], [$32$],
)

#note[
  These can be prefixed with `unsigned` to use the unsigned variants.
]

Floating-point numbers:

- `float` - $32$ bits, accurate to about 7 decimal digits.
- `double` - $64$ bits, accurate to about 15-17 decimal digits.
- `long double` - $80$ or $128$ bits.

For competitive programming, it is often better to use `<cstdint>` to provide the excact desired size.

#table(
  columns: 2,
  [*Type*], [*Bits*],
  [`int8_t`], [$8$],
  [`int16_t`], [$16$],
  [`int32_t`], [$32$],
  [`int64_t`], [$32$],
  [`uint8_t`], [$8$],
  [`uint16_t`], [$16$],
  [`uint32_t`], [$32$],
  [`uint64_t`], [$32$],
)

=== Bitsets

Bitsets are essentially boolean arrays but optimized to use only a single bit per value and allowing the use of boolean operators. It is for example useful when dealing with bitmasks. They provide the following operations

#table(
  columns: 2,
  [*Operator*], [*Operation*],
  [`&`], [AND],
  [`|`], [OR],
  [`^`], [XOR],
  [`~`], [NOT],
  [`<<`], [Left Shift],
  [`>>`], [Right Shift],
)

And here are some useful functions:

#table(
  columns: 2,
  [*Operator*], [*Operation*],
  [`b.count()`], [Return the number of `1` bits],
  [`b.any()`], [True if at least one bit is `1`],
  [`b.all()`], [True if all bits are `1`],
  [`b.none()`], [True if no bits are `1`],
  [`b.size()`], [Return the total number of bits],
  [`b.to_string()`], [Convert to a string of binary],
  [`b.to_ulong()`], [Convert to unsigned long],
  [`b.to_ullong()`], [Convert to unsigned long long],
  [`b.set(i)`], [Set the bit at `i` to `1`],
  [`b.reset(i)`], [Set the bit at `i` to `0`],
  [`b.flip(i)`], [Flip the bit at `i`],
  [`b.[i]`], [Access the bit at index `i`],
  [`b.test(i)`], [Access bit (with bounds check)],
)

```cpp
#include <bitset>

bitset<10> b; // 0000000000
b.set(2); // 0000000100
b[2]; // true
b[1]; // false
```

Here is an example from my solution to `nio23-finale-noekkelkort`.

```cpp
#include <bitset>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

using Permission = bitset<30>;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, k, t;
  cin >> n >> m >> k >> t;

  int j = 0;
  vector<tuple<int, int, Permission>> connections(t);
  vector<vector<pair<int, Permission>>> graph(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    Permission k;
    cin >> u >> v >> k;

    graph[u].push_back({v, k});
    graph[v].push_back({u, k});

    if (j < t) {
      connections[i] = {u, v, k};
    }
    j++;
  }

  // O(t (n + m))
  for (const auto &[u, v, k] : connections) {
    deque<int> queue;
    vector<bool> visited(n);
    Permission permission = ~k;
    queue.push_back(u);
    visited[u] = true;

    while (!queue.empty()) {
      int a = queue.front();
      queue.pop_front();

      if (a == v) {
        cout << "0" << endl;
        goto valid;
      }

      for (const auto &[b, k] : graph[a]) {
        if (!visited[b] && (permission & k).any()) {
          queue.push_back(b);
          visited[b] = true;
        }
      }
    }

    cout << "1" << endl;
  valid:;
  }
}
```
