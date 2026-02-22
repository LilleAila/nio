#import "@preview/colorful-boxes:1.4.2": colorbox

#set text(
  font: "DejaVu Sans",
  size: 10pt,
) // Uses fonts from system, requires to be installed

#set page(
  paper: "a4",
  margin: (top: 4cm, bottom: 4cm, left: 1.5cm, right: 1.5cm),
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
)

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

#outline()

= Introduction

This document contains commonly used code for competitive programming, specifically in rust and written for the 2026 finale in the norwegian olympiad of informatics.

== Basics

=== Rust boilerplate

```rs
use std::convert::TryInto;
use std::io;

fn main() {
  let mut lines = io::stdin().lines();
}
```

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

=== Enums

Can be defined with

```rs
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum Instruction {
    Build,
    Query,
}
```

=== Sets

Note that most set operations use borrows, with the exception of `insert`.

```rs
use std::collections::HashSet;

let mut set: HashSet<usize> = HashSet::new();

set.insert(5);
set.insert(6);

assert!(set.contains(&5));
assert!(!set.contains(&7));

set.remove(&6);
```

=== Hash Maps (TODO)

=== Time complexity

Depending on the constraints in the problem, different algorithms should be chosen, approximately based on this:

#table(
  columns: 2,
  inset: 6pt,
  [n], [Time complexity],
  [1 000 000], [$O (n)$],
  [400 000], [$O (n log n)$],
  [1 000], [$O (n^2)$],
  [200], [$O (n^3)$],
  [20], [$O (2^n)$],
  [10], [$O (n!)$],
)

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

==== BFS (TODO)

==== DFS (TODO)

=== DP (TODO)

=== Trees (TODO)

== Algorithms

=== Binary search (TODO)
