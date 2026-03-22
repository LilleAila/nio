// Optimized to use a BTreeSet and a HashMap
// A BTreeSet is basically a set but sorted so that one can in thie case
// get the item which is before and after a given value in the set.

use std::collections::{BTreeSet, HashMap};
use std::convert::TryInto;
use std::io;

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

fn main() {
    let mut lines = io::stdin().lines();

    let n: usize = lines.next().unwrap().unwrap().parse().unwrap();

    let xs: Vec<usize> = lines
        .next()
        .unwrap()
        .unwrap()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut depths = HashMap::new();
    let mut set = BTreeSet::new();

    depths.insert(xs[0], 0);
    set.insert(xs[0]);
    println!("0");

    for &x in &xs[1..] {
        let l = set.range(..x).next_back();
        let r = set.range(x..).next();

        let d = std::cmp::max(
            l.map(|v| depths[v]).unwrap_or(0),
            r.map(|v| depths[v]).unwrap_or(0),
        ) + 1;

        depths.insert(x, d);
        set.insert(x);

        println!("{}", d);
    }
}
