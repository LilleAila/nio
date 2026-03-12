// Meet in the middle - subset sums

use std::collections::HashMap;

fn subset_sums(xs: &[i32]) -> Vec<i32> {
    let n = xs.len();
    let mut sums = Vec::new();
    for mask in 0..(1 << n) {
        let mut sum = 0;
        for i in 0..n {
            if mask & (1 << i) != 0 {
                sum += xs[i];
            }
        }
        sums.push(sum);
    }
    sums
}

fn main() {
    let xs = vec![1, 2, 3, 4, 5];
    let target = 5;

    let n = xs.len();
    let left = &xs[0..n / 2];
    let right = &xs[n / 2..];

    let left_sums = subset_sums(left);
    let right_sums = subset_sums(right);

    let mut right_count = HashMap::new();
    for &sum in &right_sums {
        *right_count.entry(sum).or_insert(0) += 1;
    }

    let mut total = 0;
    for &sum in &left_sums {
        let complement = target - sum;
        if let Some(&count) = right_count.get(&complement) {
            total += count;
        }
    }

    println!("Subsets with sum {}: {}", target, total);
}
