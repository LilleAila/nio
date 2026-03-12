// LIS of tree with DP
use std::collections::VecDeque;

fn main() {
    let n = 5;
    let edges = vec![(0, 1), (0, 2), (1, 3), (1, 4)];
    // Representing the tree as a graph
    let mut tree = vec![Vec::new(); n];
    for (u, v) in edges {
        tree[u].push(v);
        tree[v].push(u);
    }

    // dp[node] = [exclude, include]
    let mut dp = vec![[0, 0]; n];
    let mut parent = vec![n; n];
    let mut order = Vec::new();

    let mut stack = VecDeque::new();
    stack.push_back(0);
    while let Some(u) = stack.pop_back() {
        order.push(u);
        for &v in &tree[u] {
            if v == parent[u] {
                // Skip parent nodes; only traverse downwards
                continue;
            }
            parent[v] = u;
            stack.push_back(v);
        }
    }

    for &u in order.iter().rev() {
        dp[u][1] = 1;
        for &v in &tree[u] {
            if v == parent[u] {
                continue;
            };
            // Exclude u
            dp[u][0] += dp[v][0].max(dp[v][1]);
            // Include u => exclude children
            dp[u][1] += dp[v][0];
        }
    }

    println!("{}", dp[0][0].max(dp[0][1]));
}
