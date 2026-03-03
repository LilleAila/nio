use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    // Precompute the expected values for a given N where h and l are extracted
    // as in the equation i wrote on paper but i still don't understand it 100% lol
    const N_MAX: usize = 20;
    let mut dp: Vec<f32> = vec![0.0; N_MAX + 1];
    dp[0] = 0.0; // Always accept last offer
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
