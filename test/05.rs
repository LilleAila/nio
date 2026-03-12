// Floyd-Warshall

fn main() {
    let graph: Vec<Vec<(i32, usize)>> = vec![
        vec![(3, 1), (8, 2)],
        vec![(2, 2)],
        vec![(1, 3)],
        vec![(4, 0)],
    ];

    let n = graph.len();
    let mut d = vec![vec![i32::MAX / 2; n]; n];

    for i in 0..n {
        d[i][i] = 0;
        for &(w, j) in &graph[i] {
            d[i][j] = w;
        }
    }

    for k in 0..n {
        for i in 0..n {
            for j in 0..n {
                d[i][j] = d[i][j].min(d[i][k] + d[k][j]);
            }
        }
    }

    dbg!(&d);
}
