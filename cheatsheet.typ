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
      [NIO Cheatsheet], align(right)[Olai Solsvik],
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

This document contains commonly used code for competitive programming, specifically in rust and written for the 2026 finale in the norwegian olympiad of informatics.

== Basics

=== Vim config

Here is a basic vim config for competitive programming in rust:

```vim
let mapleader = " "
nnoremap <leader>ff :%!rustfmt<cr>
nnoremap <leader>fm :Explore<cr>

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

Place this in `~/.vimrc` at the start of the competition.

=== Rust boilerplate

```rs
use std::convert::TryInto;
use std::io;

fn main() {
  let mut lines = io::stdin().lines();
}
```

The program can then be compiled and run with

```sh
rustc -O -o main main.rs && ./main < 1.txt
```

Additionally, the rust code can be formatted with

```sh
rustfmt main.rs
```

#note[
  This is slightly more efficient than the above:

  ```rs
  use std::io::{self, BufRead};

  fn main() {
    let stdin = io:.stdin();
    let mut lines = stdin.lock().lines();
  }
  ```
]

=== Capturing input

We will use the stdin lines iterator defined above to read the input:

```rs
let n: usize = lines.next().unwrap().unwrap().parse();
```

For reading multiple variables in a single line, one can do the following:

```rs
let [n, q]: [usize; 2] = lines
    .next()
    .unwrap()
    .unwrap()
    .trim()
    .split_whitespace()
    .map(|x| x.parse().unwrap())
    .collect::<Vec<_>>()
    .try_into()
    .unwrap();
```

, which is expandable to any number of values in the same line.

#note[
  This is unoptimal as it allocates a `Vec` when it is not necessary, but in my experience this was negligible. It can however be improved as such:
  ```rs
  let line = lines.next().unwrap().unwrap()
  let mut iter = line.trim().split_whitespace();
  let n: usize = iter.next().unwrap().parse().unwrap();
  let l: f32 = iter.next().unwrap().parse().unwrap();
  let h: f32 = iter.next().unwrap().parse().unwrap();
  ```
  This is useful for example when reading different types on the same line.
]

==== Reading a list of values

If the input is a single line split into values, it can be read as such:

```rs
let xs: Vec<usize> = lines.next().unwrap().unwrap()..split_whitespace().map(|x| x.parse().unwrap()).collect();
```

And if the input is given with each value on a separate line, it can be read with either of the following:

```rs
let xs: Vec<usize> = (0..n).map(|_| lines.next().unwrap().unwrap().parse().unwrap()).collect();
```

```rs
let mut xs: Vec<usize> = Vec::new();
for _ in 0..n {
  let x = lines.next().unwrap().unwrap().parse().unwrap();
  xs.push(x);
}
```

```rs
let mut xs: Vec<usize> = vec![usize::MAX; n];
for i in 0..n {
  xs[i] = lines.next().unwrap().unwrap().parse().unwrap();
}
```

I prefer the first of the three, but the others can be useful if the line contains more complex input.

==== Interactive programs

A general theme across interactive problems is to manipulate the mathematical equation used so that all the local variables are extracted, such that we can precompute the values to be used for each iteration of the program. Input and output are handled the same way as in programs with static input.

=== Strings and chars

Parsing a number in a string can be done like this:

```rs
let x: usize = s.parse().unwrap();
let x: i32 = s.parse().unwrap();
```

And with chars, as such:

```rs
let s: char = 'a';
let x: u32 = s.to_digit(10);
let x: u8 = s.to_digit(10) as u8;

let s: &str = "123";
let x: Vec<u32> = s.chars().map(|x| x.to_digit(10)).collect();
```

One can get an iterator of chars from a string by using `.chars()`. An alternative and more efficient way to get the value as a digit is by converting it to u8 to get its ascii value.

```rs
let c: char = '3';
let n: u8 = c as u8 - b'0';
let n: usize = (c as u8 - b'0') as usize;
```

Note that this only works when $x in [0, 9]$.

=== String and &str

`String` is an owned and heap-allocated string type. This means that it can grow and shrink.

```rs
let mut s: String = String::from("Hello");
s.push_back(", world!");

println("{}", s);
```

On the other hand, `&str` refers to a string slice. This is a borrowed reference, which is usually immutable.

```rs
let s: String = Strong::from("hello");
let slice: &str = s[0..2]; // "he"
```

It is possible to convert between them:

```rs
let s: String = String::from("hello");
let slice: &str = &s;
let slice: &str = s.as_str();

let slice: &str = "hello";
let s = slice.to_string();
let s = String::from(slice);
```

`io::stdin().lines().next().unwrap().unwrap()` returns a `String`.

=== Bitmasks and bitwise operations

#table(
  columns: 2,
  inset: 6pt,
  [*Operator*], [*Operation*],
  [`&`], [AND],
  [`|`], [OR],
  [`^`], [XOR],
  [`!`], [NOT],
  [`<<`], [Left shift],
  [`>>`], [Right shift],
)

Bitmasks are useful when one needs to store many related booleans in a way which makes it easier to run operations on multiple of them at the same time. It is usually easiest to use this if the number of booleans is less than 64, which means that it can fit into an `u64`. Here is an example usage of bitmasks to handle the door permissions in `nio23-finale-noekkelkort`:

```rs
use std::collections::{HashSet, VecDeque};
use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let [n, m, k, t]: [usize; 4];

    let all_permissions: u32 = (1 << k) - 1;

    // graph[from] = [(to, permissions)]
    let mut graph: Vec<Vec<(usize, u32)>> = vec![Vec::new(); n];
    // edges in the graph to check
    let mut pairs: Vec<(usize, usize, u32)> = Vec::new();

    for &(u, v, p) in &pairs {
        let mut queue: VecDeque<usize> = VecDeque::new();
        let mut visited: HashSet<usize> = HashSet::new();
        let permissions = !p & all_permissions;
        queue.push_back(u);

        let mut result = true;

        // Note that this is an inefficient implementation of BFS
        // It would be better to check if it is visited *before* pushing
        while let Some(a) = queue.pop_front() {
            if visited.contains(&a) {
                continue;
            }
            visited.insert(a);

            if a == v {
                result = false;
                break;
            }

            for &(n, ps) in &graph[a] {
                if permissions & ps != 0 {
                    queue.push_back(n);
                }
            }
        }

        println!("{}", result as u8);
    }
}
```

=== Match

Useful for pattern matching. Works similar to that of languages like haskell or python. It can contain expressions and also return values directly.

```rs
let bar = match foo {
    Some(x) = x,
    None = 0,
}
```

```rs
match foo {
    Some(0) = {
        println!("Value is zero :o");
    },
    Some(x) if x < 10 {
        println!("X is less than 10");
    },
    Some(x) {
        println!("Value: {}", x);
    },
    None = {
        println!("No value :(");
    }
}
```

#note[
  One can use the operator `@` to set a value while matching a pattern. For example, one can combine the pattern `x` and `1..=10` into a single expression with `x @ 1..=10`, which will keep the original value in `x` while matching it against the pattern.
]


=== Integer overflow

In problems where large numbers are required, for example finding the number of unique nonempty subsequences, the number grows exponentially and thus we need to clamp it to some number. Usually this number is defined as $M O D = 1 thin 000 thin 000 thin 007$ (because this is a prime number). In the aforementioned problem, we can then use the following to ensure the number stays within the bounds of a 64-bit integer.

```rs
const MOD: usize = 1_000_000_007;
let new_subsequences = (subsequences * 2 - last[x as usize] + MOD) % MOD;
```

=== Time complexity

Depending on the constraints in the problem, different algorithms should be chosen, approximately based on this:

#table(
  columns: 2,
  inset: 6pt,
  [*n*], [*Time complexity*],
  [1 000 000], [$O (n)$],
  [400 000], [$O (n log n)$],
  [1 000], [$O (n^2)$],
  [200], [$O (n^3)$],
  [20], [$O (2^n)$],
  [10], [$O (n!)$],
)

== Useful data types

=== Option

An option holds an optional value, similar to the `Maybe`-monad in haskell:

```rs
let x: Option<i32> = None;
let x: Option<i32> = Some(42);

match x {
  Some(n) => println!("value exists"),
  None => println!("no value"),
}

let x: i32 = x.unwrap(); // unsafe; panics if None
let x: i32 = x.unwrap_or(0); // safe; adds a fallback value
let x: Option<i32> = x.map(|v| v * 2);

if let Some(a) = x {
  println!("{}", a);
}

if let Some(v) = x {
  if v == 42 {
    println!("X is some and 42!")
  }
}

// Equivalent to above, but might not work in the version of rust used by NIO
if x.is_some_and(|v| v == 42) {}
if let Some(v) = x && v == 42 {}
```

Here is an example, taken from my solution to `nio24-finale-sokkeskuff`:

```rs
let mut prev: Option<usize> = None;
let mut pairs = 0;

for &s in &socks {
    if let Some(p) = prev {
        if s - p <= t {
            pairs += 1;
            prev = None;
            continue;
        }
    }
    prev = Some(s);
}
```

=== Enums

Can be defined with

```rs
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum Instruction {
    Build,
    Query,
}
```

=== Vectors

Vectors are lists of items with a dynamic length. Here are some examples:

```rs
let xs: Vec<i32> = vec![1, 2, 3, 4];
let xs: Vec<i32> = vec![0; 5]; // [0, 0, 0, 0, 0]
let mut xs: Vec<usize> = Vec::new(); // xs = vec![]
xs.push(42); // xs = vec![42]
xs.push(123); // xs = vec![42, 123]
```

==== VecDeque

// FIXME: should maybe be moved down to the data structures and algorithms section?

For algorithms such as 0-1 BFS, one can use a double-ended queue as follows:

```rs
use std::collections::VecDeque;

let mut queue: VecDeque<usize> = VecDeque::new();

while let Some(x) = queue.pop_front() {
  if weights[x] == 0 {
    for &n in &graph[x] {
      queue.push_front(n);
    }
  } else {
    for &n in &neighbors[x] {
      queue.push_back(n);
    }
  }
}
```

Note that this is just pseudocode.

=== Slices

A vector can be indexed with a slice as such:

```rs
let xs = vec![0, 1, 2, 3, 4];

let slice = &xs[1..4]; // [1, 2, 3]
let slice = &xs[1..=3]; // [1, 2, 3]
let slice = &xs[..3]; // [0, 1, 2]
let slice = &xs[2..]; // [2, 3, 4]
let slice = &xs[..]; // [0, 1, 2, 3, 4]
```

Slices can also be mutable:

```rs
let xs = vec![0, 1, 2, 3, 4];

for x in &mut xs[1..4] {
  *x *= 2;
}

println!("{:?}", xs); // [0, 2, 4, 6, 4]
```

#note[
  Slices borrow from the vector. `xs[1..4]` produces a slice of type `&[i32]`.
]

A slice can also be used as an iterator, in pattern matching, etc.

```rs
let xs = vec![0, 1, 2, 3, 4];

match &xs[..] {
    [first, .., last] => {
        println!("First: {}, Last: {}", first, last);
    }
}

// .iter() on a slice of type &[i32] creates an iterator of references (`&i32`)
let slice_sum = xs[1..4].iter().sum(); // 6
```

=== Sets and maps

==== HashSet

Note that most set operations use borrows, with the exception of `insert`.

```rs
use std::collections::HashSet;

let mut set: HashSet<usize> = HashSet::new();

set.insert(5); // true
set.insert(6); // true
set.insert(6); // false (already exists)

assert!(set.contains(&5));
assert!(!set.contains(&7));

set.remove(&6);
```

#note[
  When doing a lookup, one uses a reference to the value, not the value itself (`set.contains(&5)`). The same applies to HashMaps.
]

HashSets also have some useful in-place functions

```rs
let mut set: HashSet<usize> = HashSet::from([1, 2, 3, 4, 5, 6]);

set.retain(|x| x % 2 == 0);
dbg!(&set); // { 2, 4, 6 }

let set_b: HashSet<usize> = HashSet::from([7, 8, 9]);
set.extend(set_b);
dbg!(&set); // { 2, 4, 6, 7, 8, 9 }
```

=== HashMap

HashMaps store data in a map with hashed keys and have $O(1)$ operations.

```rs
use std::collections::HashMap;

let mut map: HashMap<usize, &str> = HashMap::new();
map.insert(1, "one");
map.insert(2, "two");

let x: Option<&str> = map.get(&1); // Some("one")
let x: Option<&str> = map.get(&3); // None

assert!(map.contains_key(&2));
map.remove(&2);
assert!(!map.contains_key(&2));

map.insert(1, "en");
```

There is also more complex funcionality present, such as:

```rs
let mut map: HashMap<usize, i32> = HashMap::new();
map.insert(1, 123);

let x: &i32 = map[&1]; // unsafe; panics if 1 does not exist
let x: Option<&i32> = map.get(&1); // safe

let mut x: &mut i32 = map.entry(1); // .entry() returns an &mut i32
let x: &i32 = map.entry(1).or_insert(456); // 123
let x: &i32 = map.entry(2).or_insert(456); // 456

*map.entry(3).or_insert(0) += 1; // map[&3] == 1
*map.entry(3).or_insert(0) += 1; // map[&3] == 2

map.entry(4).and_modify(|ref mut v| v += 1).or_insert(1); // map[&4] = 1
map.entry(4).and_modify(|v| *v += 1).or_insert(1); // map[&4] = 2
```

=== BTreeSet and BTreeMap

BTreeSet and BTreeMap work conceptually same as their Hash counterparts, with the addition that they are automatically sorted. The difference is that the Hash versions are (as the name suggests) hash-based with $O(1)$ operations, and the BTree versions have $O(log n)$ operations..

#note[
  These data types internally use a B-tree to sort the values, hence the name "B-Tree Set".
]

Here are some usage examples:

```rs
use std::collections::BTreeSet;

let mut set = BTreeSet::new();
set.insert(10);
set.insert(5);
set.insert(20);

let left: Option<&i32> = set.range(..10).next_back();
let right: Option<&i32> = set.range(10 + 1..).next();
```

If one needs to store data along with the sorted indexes, a BTreeMap is useful. It would also work to use a separate HashMap and BTreeSet, but combining it into a BTreeMap is more efficient and makes the code cleaner.

```rs
use std::collections::BTreeMap;

let mut map = BTreeMap::new();
map.insert(10, "root");
map.insert(5, "left child");
map.insert(20, "right child");

let left_depth: Option<&&str> = map.range(..10).next_back().map(|(_, v)| v);
// Optionally:
let left_depth: Option<&str> = map.range(..10).next_back().map(|(_, v)| *v);
```

== Data structures

=== Graphs

I like to define graphs as follows:

```rs
type Graph = Vec<Vec<(usize, usize)>>;
```

Which will be indexed like this:

```
graph[from_node] = [(neighbor1, cost), (neigbor2, cost), (neighbor3, cost)]
```

#note[
  Unweighted graphs can be simplified to
  ```rs
  type Graph = Vec<Vec<usize>>;
  ```
]

Here is an example of how a graph can be constructed in rust (taken from my solution to `nio21-finale-togtur`). In this case I am creating an undirected graph. For a directed graph, one would remove the line with `graph[b].push((a, k))`.

```rs
let mut graph: Vec<Vec<(usize, usize)>> = vec![Vec::new(); n];
for _ in 0..m {
    let [a, b, k]: [usize; 3] = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();
    graph[a].push((b, k));
    graph[b].push((a, k));
}
```

==== Dijkstra

Dijkstra's algorithm is an algorithm for finding the lowest total weight path between two nodes in a graph. It has a time complexity of $O ((V + E) log V)$. It requires the following imports:

```rs
use std::cmp::Reverse;
use std::collections::BinaryHeap;
```

#note[
  We use `Reverse` here because rust's `BinaryHeap` sorts the values descending, but for Dijkstra we want it to be ascending. `Reverse` is used to reverse the natural ordering of values.
]

And can be implemented as such:

```rs
let n: usize; // Number of nodes in the graph
let graph: Graph;
let start: usize;
let target: usize;

let mut heap = BinaryHeap::new();
heap.push(Reverse((0, start)));
let mut dist = vec![usize::MAX; n];
dist[start] = 0;

let mut result = None;

while let Some(Reverse((cost, node))) = heap.pop() {
    if cost > dist[node] {
        continue;
    }

    if node == target {
        result = Some(cost);
        break;
    }

    for &(neighbor, c) in &graph[node] {
        let new_cost = cost + c;
        if new_cost < dist[neighbor] {
            dist[neighbor] = new_cost;
            heap.push(Reverse((new_cost, neighbor)));
        }
    }
}

println!("{}", result.unwrap());
```

There are often problems which require a variation of Dijkstra, for example the aforementioned `nio21-finale-togtur` which adds another layer for each "free edge". This can easily be implemented by extending the dist DP table and adding another item to the tuple in the heap:

```rs
heap.push(Reverse((0, v, start))); // (cost, tickets, node)
let mut dist = vec![vec![usize::MAX; v + 1]; n];
dist[start][v] = 0;

// ---

for &(n, c) in &graph[node] {
    let new_cost = cost + c;
    if new_cost < dist[n][tickets] {
        dist[n][tickets] = new_cost;
        heap.push(Reverse((new_cost, tickets, n)));
    }

    if tickets > 0 && cost < dist[n][tickets - 1] {
        dist[n][tickets - 1] = cost;
        heap.push(Reverse((cost, tickets - 1, n)));
    }
}
```

==== BFS / DFS

BFS (breadth-first search) and DFS (depth-first search) are both algorithms used to traverse an unweighted graph. They both use a queue, with the difference being that BFS uses a FIFO-queue while DFS uses a LIFO-stack. They both have an asymptotic time complexity of $O (V + E)$. Here is a simple example implementation of BFS in rust which returns a boolean for whether or not a path exists:

```rs
use std::collections::{HashSet, VecDeque};

let graph: Vec<Vec<usize>>;
let start: usize;
let target: usize;

let mut queue: VecDeque<usize> = VecDeque::new();
let mut visited: HashSet<usize> = HashSet::new();
queue.push_back(start);
visited.insert(start);

let mut result = false;

while let Some(a) = queue.pop_front() {
  if a == target {
    result = true;
    break;
  }

  for &n in &graph[a] {
    if !visited.contains(&n) {
      queue.push_back(n);
      visited.insert(n);
    }
  }
}
```

This pushes to the back and pops from the front, thus making it a breadth-first search in which all neighbor nodes are searched before continuing to the next level. The only difference is changing this line:

```diff
- queue.push_back(n);
+ queue.push_front(n);
```

BFS is often the best when trying to find the shortest path between two nodes, while DFS is preferred if all we need is to know whether or not a path exists. Finding the path length with BFS can be done as such:

```rs
use std::collections::{HashSet, VecDeque};

let graph: Vec<Vec<usize>>;
let start: usize;
let target: usize;

let mut queue: VecDeque<(usize, usize)> = VecDeque::new();
let mut visited: HashSet<usize> = HashSet::new();
queue.push_back((start, 0));
visited.insert(start);

let mut result = None;

while let Some((a, c)) = queue.pop_front() {
  if a == target {
    result = Some(c);
    break;
  }

  for &n in &graph[a] {
    if !visited.contains(&n) {
      queue.push_back((n, c+1));
      visited.insert(n);
    }
  }
}
```

==== 0-1 BFS

0-1 BFS is an extension of BFS in which a double ended queue is used to determine which nodes to traverse first. This is used for a special case of weighted graphs where the weights are all either $0$ or $1$.

```rs
use std::collections::VecDeque;

let n: usize; // n of nodes
let graph: Vec<Vec<(usize, usize)>>; // (target, weight)
let start: usize;
let target: usize;

let mut queue: VecDeque<usize> = VecDeque::new();
let mut dist: Vec<usize> = vec![usize::MAX; n];
queue.push_back(start);

while let Some(a) = queue.pop_front() {
  for &(n, c) in &graph[a] {
    let new_dist = dist[a] + c;
    if new_dist < dist[n] {
      dist[n] = new_dist;
      if c == 0 {
        // Prioritize weight 0
        queue.push_front(n);
      } else {
        queue.push_back(n);
      }
    }
  }
}
```

==== Minimum Spanning Tree

A minimum spanning tree (MST) in a connected, weighted and undirected graph is a subset of the edges which

- Connects all vertices
- Has no cycles (and is thus a tree)
- Contains excactly $V - 1$ edges if there are $V$ vertices.

===== Kruskal's algorithm for MST

Kruskal's algorithm is an algorithm used to find the total weight of the minimum spanning tree. This uses the DSU-implementation also found in this document.

```rs
// Given a list of edges with (weight, from, to)
let edges: Vec<(i32, usize, usize)>;

edges.sort_by_key(|&(w, _, _)| w); // Sort by weight ascending
let mut dsu = DSU::new(n);
let mut mst_weight = 0;

for (w, u, v) in edges {
    if dsu.union(u, v) {
        mst_weight += w;
    }
}
```

=== DP (TODO)

=== Binary trees

A binary tree can be defined with

```rs
#[derive(Debug)]
struct Node<T> {
    value: T,
    left: Option<Box<Node<T>>>,
    right: Option<Box<Node<T>>>,
}

impl<T> Node<T> {
    fn new(value: T) -> Self {
        Node {
            value,
            left: None,
            right: None,
        }
    }
}
```

Which can then be used like

```rs
let mut root = Node::new(10);

root.left = Some(Box::new(Node::new(5)));
root.right = Some(Box::new(Node::new(20)));

dbg!(root);
```

Traversing it can be done either recursively or iteratively, as follows:

```rs
fn inorder<T: std::fmt::Display>(node: &Option<Box<Node<T>>>) {
    if let Some(n) = node {
        inorder(&n.left);
        print!("{} ", n.value);
        inorder(&n.right);
    }
}
```

Here is an example taken from my unoptimized solution to `nio24-finale-trebygger`:

```rs
let mut root: Node<usize> = Node::new(xs[0]);
println!("0");

for &a in &xs[1..] {
    let mut h = 1;
    let mut c = &mut root;

    loop {
        if a < c.value {
            match c.left {
                Some(ref mut l) => {
                    c = l;
                }
                None => {
                    c.left = Some(Box::new(Node::new(a)));
                    println!("{}", h);
                    break;
                }
            }
        } else {
            match c.right {
                Some(ref mut r) => {
                    c = r;
                }
                None => {
                    c.right = Some(Box::new(Node::new(a)));
                    println!("{}", h);
                    break;
                }
            }
        }

        h += 1;
    }
}
```

#note[
  One usually will not need to implement a tree in CP - most of the time it will suffice to use a `BTreeSet` or `BTreeMap`. The solution listed above exists as an example of how one _could_ use this data structure, but in this and most other cases it will be better to use one of the aforementioned data types. The above solution could be significantly optimized to this:

  ```rs
  let mut tree: BTreeMap<usize, usize> = BTreeMap::new();

  tree.insert(xs[0], 0);
  println!("0");

  for &x in &xs[1..] {
      let l = tree.range(..x).next_back().map(|(_, &d)| d);
      let r = tree.range(x + 1..).next().map(|(_, &d)| d);

      let d = l.unwrap_or(0).max(r.unwrap_or(0)) + 1;
      tree.insert(x, d);

      println!("{}", d);
  }
  ```
]

=== DSU / Union-Find

A Disjoint Set Union is a data structure that can keep track of multiple disjoint / non-overlapping sets, and can efficiently do the following operations:

- Find: Determine which set an element belongs to
- Union: Merge two sets into one

This is useful to track connectivity. An example implementation in rust is as follows:

```rs
struct DSU {
    parent: Vec<usize>,
    size: Vec<usize>,
}

impl DSU {
    fn new(n: usize) -> Self {
        DSU {
            parent: (0..n).collect(),
            size: vec![1; n],
        }
    }

    fn find(&mut self, x: usize) -> usize {
        if self.parent[x] != x {
            // Compress the path with recursion
            self.parent[x] = self.find(self.parent[x]);
        }
        self.parent[x]
    }

    // False if the sets are already the same
    fn union(&mut self, x: usize, y: usize) -> bool {
        let mut rx = self.find(x);
        let mut ry = self.find(y);
        if rx == ry {
            return false;
        }
        // Union the larger of the two sets
        if self.size[rx] < self.size[ry] {
            std::mem::swap(&mut rx, &mut ry);
        }
        self.parent[ry] = rx;
        self.size[rx] += self.size[ry];
        true
    }
}
```

#note[
  The time complexity of both the `find` and `union` methods in a `DSU` both have the time complexity $O(alpha (n))$ where $alpha$ is the inverse Ackermann function. In practice, $alpha (n) <= 5$ for all reasonable values of $n$, so it can be treated as constant.
]

This can be a bit confusing to think about, but here is an example:

```rs
let mut dsu = DSU::new(5);
// Has 5 sets: {0}, {1}, {2}, {3}, {4}

dsu.union(0, 1);
// Has 4 sets: {0, 1}, {2}, {3}, {4}
dsu.union(1, 2);
// Has 3 sets: {0, 1, 2}, {3}, {4}
dsu.union(3, 4);
// Has 2 sets: {0, 1, 2}, {3, 4}
dsu.union(1, 3)
// Has 1 set: {0, 1, 2, 3, 4}
```

I used this in my solution for `nio24-runde2-tognett`. Note that this solution is not optimal, and only gave `65/100` points, however this is still much more efficient than one which uses BFS for each iteration.

```rs
let mut dsu = DSU::new(n);

for &(a, b) in &trains {
    dsu.union(a, b);

    let mut removed = 0;
    for u in 0..n {
        let mut to_remove = Vec::new();
        for &v in &plane_graph[u] {
            if dsu.find(u) == dsu.find(v) {
                to_remove.push(v);
            }
        }
        removed += to_remove.len();
        for v in to_remove {
            plane_graph[u].remove(&v);
        }
    }

    println!("{}", removed / 2);
}
```

This is very useful in cases where one wants to find the connected components in a graph. Instead of running a BFS search from one node, one can use a DSU to store it. Using that in this task would be $O (k (n + m))$, while using a DSU has the same time complexity but is much faster in practice because the overhead of using a BFS and queue is avoided.

=== Difference arrays

Difference arrays provide a more efficient way to update all values within an interval. Instead of looping over all items in the interval $[a, b]$, one instead just sets the values at $a$ and $b$, then passes over the array afterwards. A boolean implementation could look like this (taken from my solution to `nio23-runde2-lynnedslag`):

```rs
let mut houses: Vec<bool> = vec![false; n];

for _ in k {
  let [a, b]: [usize; 2];
  houses[a] = !houses[a];
  houses[b+1] = !houses[b+1];
}

let mut flip = false;
let mut result = 0;

for h in houses {
  flip ^= h;

  if !flip {
    result += 1;
  }
}
```

#note[
  We use $b+1$ instead of $b$ because the interval is inclusive. The difference array marks where the effect starts and stops, and the prefix accumulation applies the effect from $a$ through $b$.
]

A more general implementation could look like this:

```rs
let mut xs: Vec<isize> = vec![0; 10 + 1];

// Add 3 to the interval [2, 5]
xs[2] += 3;
xs[5+1] -= 3;

// Subtract 9 in the interval [6, 9]
xs[6] -= 9;
xs[9+1] += 9;

let mut d = 0;
let mut result = 0;

for x in xs {
  d += x;
  result += d;
}
```

Note that the previous version is actually a special case of this, in which one would use `+= x % 2` (which I have simplified to using booleans).

== Various other algorithms

=== Binary search

Given a sorted list, one can find a value in $O (log n)$ using binary search. This also works for any monotonic function in which one wants to find the value in which it turns, and is thus useful in many problems. Here is an example of binary search implemented with a monotonic boolean function which starts at false and then becomes true, like `[false, false, false, true, true]`.

```rs
let mut a: usize = 0;
let mut b: usize = n; // n is the max value
let mut result: Option<usize> = None;

while a <= b {
  let mid = (a + b) / 2;
  if some_predicate(mid) {
    result = Some(mid);
    b = mid - 1;
  } else {
    a = mid + 1;
  }
}
```

=== Probability

One of the tasks usually contain some sort of probability, usually some sort of linear distribution in an interval. Here is my solution for `nio25-finale-jobbjakt`:

Vi er ikke gitt noen globale variabler, men dette er et sannsynlighetsproblem der vi vil fokusere på $N$. Her definerer jeg $N$ som antall jobbtilbud igjen (altså starter man for eksempel på $N=4$, så $N=3$, $N=2$ etc). Jeg inkluderer først de lokale variablene $l$ og $h$ for å løse likningen, men setter disse lik henholdsvis $0$ og $1$, slik at jeg kan sette inn igjen disse variablene etterpå.

Jeg ønsker å fine den forventede verdien for lønn med en gitt $N$. Hvis et gitt tilbud er høyere enn forventningsverdien, skal jeg velge å akseptere det. Jeg starter da ved å definere grunntilstanden $E_0=0$, da man er nødt til å akseptere enhver verdi hvis det ikke er noen tilbud igjen. Videre har jeg at den forventede verdien for $N=1$ er $E_1= (h+l)/2$. For å forenkle dette substituerer jeg $l$ og $h$ som beskrevet og får da at $E_1 = 0.5$.

Når $N=2$, bruker man $E_1$ som terskel på tilbudet. Hvis tilbudet er $<E_1$, takker man nei. Forventningsverdien hvis man takker nei blir da det samme som situasjonen der $N=1$, altså $E_1$. Hvis man takker ja derimot, har vi at tilbudet $>E_1$. Dden forventede verdien ligger da i intervallet $[E_1, h]$. Da dette er en uniform distribusjon har vi nå at den forventede verdien er $(E_1 + h)/2$, som da blir $(E_1 + 1)/2$. Sannsynligheten for at tilbudet ligger i intervallet blir da $1-P_"nei"$ ($1 - E_1$), slik at summen er 1. Hvis vi setter inn verdien for $E_1$ får vi da $0.75$. Den samlede forventningsverdien er gitt ved

$
  E_2 = underbrace(0.5, P_"nei") dot underbrace(0.5, E_"nei") + underbrace((1 - 0.5), P_"ja") dot underbrace((0.5 + 1) / 2, E_"ja") = 0.625
$

Jeg kan trekke den samme logikken videre for å beregne $E_3$:

$
  E_3 = underbrace(0.625, P_"nei") dot underbrace(0.625, E_"nei") + underbrace((1 - 0.625), P_"ja") dot underbrace((0.625 + 1)/2, E_"ja")
$

Bruker denne logikken til å skrive det generelle uttrykket:

$
  E_2 = underbrace(E_(n-1), P_"nei") dot underbrace(E_(n-1), E_"nei") + underbrace((1 - E_(n-1)), P_"ja") dot underbrace((E_(n-1) + 1)/2, E_"ja")
$

Og forenkler dette:

$
  E_n & = E_(n-1)^2 + 1/2 dot (1 - E_(n-1)) dot (E_(n-1) + 1) \
      & = E_(n-1)^2 + 1/2 dot (E_(n-1) + 1 - E_(n-1)^2 - E_(n-1)) \
      & = (2 E_(n-1)^2)/2 + (- E_(n-1)^2 + 1)/2 \
  E_n & = (1 + E_(n-1)^2)/2
$

Der $n$ er antall tilbud igjen etter dette tilbudet. Dette kan implementeres i rust ved hjelp av DP med tabulation som følger:

```rs
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    const N_MAX: usize = 20;
    let mut dp: Vec<f32> = vec![0.0; N_MAX + 1];
    dp[0] = 0.0;
    dp[1] = 0.5;
    for n in 2..=N_MAX {
        dp[n] = (1.0 + dp[n - 1] * dp[n - 1]) / 2.0;
    }

    let r: usize = lines.next().unwrap().unwrap().parse().unwrap();
    for _ in 0..r {
        let line = lines.next().unwrap().unwrap();
        let mut iter = line.trim().split_whitespace();
        let n: usize = iter.next().unwrap().parse().unwrap();
        let l: f32 = iter.next().unwrap().parse().unwrap();
        let h: f32 = iter.next().unwrap().parse().unwrap();

        for i in 0..n {
            let n_remaining = n - i - 1;
            let v: f32 = lines.next().unwrap().unwrap().parse().unwrap();

            if v >= l + (h - l) * dp[n_remaining] {
                println!("ja");
                break;
            } else {
                println!("nei");
            }
        }
    }
}
```
