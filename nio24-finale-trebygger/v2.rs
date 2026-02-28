// Basically the same thing as v1 but optimized a bit by avoiding a vec for the queue

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

    // This works for subtask 1 lol
    // We are given that all numbers are unique integers <N.
    // Because there are N unique integers this means that when
    // sorted ascending, it will be increasing by 1 for each A
    // for i in 0..n {
    //     println!("{}", i);
    // }

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
}
