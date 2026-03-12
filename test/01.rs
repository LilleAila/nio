// Fenwick Trees

struct FenwickTree {
    bit: Vec<i32>,
    n: usize,
}

impl FenwickTree {
    fn new(n: usize) -> Self {
        Self {
            bit: vec![0; n + 1],
            n,
        }
    }

    fn update(&mut self, mut i: usize, val: i32) {
        i += 1;
        while i <= self.n {
            self.bit[i] += val;
            i += i & (!i + 1).wrapping_neg();
        }
    }

    fn query(&self, mut i: usize) -> i32 {
        i += 1;
        let mut sum = 0;
        while i > 0 {
            sum += self.bit[i];
            i -= i & (!i + 1).wrapping_neg();
        }
        sum
    }
}

fn main() {
    let xs = vec![1, 2, 3, 4, 5];
    let mut ft = FenwickTree::new(xs.len());
    for (i, &val) in xs.iter().enumerate() {
        ft.update(i, val);
    }

    println!("{}", ft.query(2)); // first 3 elements: 1 + 2 + 3 = 6
    ft.update(1, 5); // Add 5 to xs[1]
    println!("{}", ft.query(2)); // first 3 elements: 1 + 7 + 3 = 11

    // Sum of range (1..=4)
    println!("{}", ft.query(4) - ft.query(0)); // 7 + 3 + 4 + 5
}
