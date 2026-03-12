// Bellman-Ford

fn main() {
    let n = 5;

    let edges = vec![
        (0, 1, 6),
        (0, 2, 7),
        (1, 2, 8),
        (1, 3, 5),
        (1, 4, -4),
        (2, 3, -3),
        (2, 4, 9),
        (3, 1, -2),
        (4, 3, 7),
    ];

    let inf = i32::MAX / 2;
    let mut dist = vec![inf; n];
    let source = 0;
    dist[source] = 0;

    for _ in 0..n - 1 {
        let mut changed = false;
        for &(u, v, w) in &edges {
            if dist[u] != inf && dist[u] + w < dist[v] {
                dist[v] = dist[u] + w;
                changed = true;
            }
        }
        if !changed {
            break;
        }
    }

    dbg!(&dist);

    for &(u, v, w) in &edges {
        if dist[u] != inf && dist[u] + w < dist[v] {
            println!("Negative cycle found!");
            break;
        }
    }
}
