// TSP with bitmask DP

fn main() {
    let n = 4;
    let dist = vec![
        vec![0, 10, 15, 20],
        vec![10, 0, 35, 25],
        vec![15, 35, 0, 30],
        vec![20, 25, 30, 0],
    ];

    let size = 1 << n;

    // This DP is defined by DP[mask][target city]
    // The mask is a bitmask of visited cities
    let mut dp = vec![vec![i32::MAX / 2; n]; size];
    // With 1 visited city and ending at 0, the total cost is 0
    // (not leaving the starting city)
    dp[1][0] = 0;

    for mask in 1..size {
        for u in 0..n {
            if (mask & (1 << u)) == 0 {
                continue; // Skip if this city is not in the mask
            }
            for v in 0..n {
                if (mask & (1 << v)) != 0 {
                    continue; // Skip v if it is already in the mask
                }
                let next_mask = mask | (1 << v);
                dp[next_mask][v] = dp[next_mask][v].min(dp[mask][u] + dist[u][v]);
            }
        }
    }

    let mut result = i32::MAX;
    for u in 1..n {
        // Return to start
        result = result.min(dp[size - 1][u] + dist[u][0]);
    }

    println!("{}", result);
}
