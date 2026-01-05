use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let n: i32 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    let teeth: Vec<bool> = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split(" ")
        .map(|x| x == "1")
        .collect();

    // println!("{} {:?}", n, teeth);

    let mut potential: i32 = 0;
    for (i, &t) in teeth.iter().enumerate() {
        if t || (i > 0 && teeth[i - 1]) || (i < (n as usize) - 1 && teeth[i + 1]) {
            potential += 1;
        }
    }

    // TODO: find minimum. DP?
    println!("{} {}", 0, potential);
}
