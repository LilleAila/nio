use std::io;

fn main() {
    let mut lines = io::stdin().lines();
    let n: f64 = lines.next().unwrap().unwrap().parse().unwrap();
    let result = (n / 10.0).ceil() as usize;
    println!("{}", result);
}
