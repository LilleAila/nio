// Idk anything about trees yet lol i just tried some shit

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

    for i in 1..xs.len() {
        let a = xs[i];

        let mut queue: Vec<(usize, &mut Node<usize>)> = vec![(1, &mut root)];

        while let Some((h, b)) = queue.pop() {
            if a < b.value {
                match b.left {
                    Some(ref mut l) => {
                        queue.push((h + 1, l));
                    }
                    None => {
                        b.left = Some(Box::new(Node::new(a)));
                        println!("{}", h);
                        break;
                    }
                }
            } else {
                match b.right {
                    Some(ref mut r) => {
                        queue.push((h + 1, r));
                    }
                    None => {
                        b.right = Some(Box::new(Node::new(a)));
                        println!("{}", h);
                        break;
                    }
                }
            }
        }
    }
}
