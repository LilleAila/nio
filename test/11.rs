// Topological sort

use std::collections::VecDeque;

fn main() {
    let n = 6;
    let mut graph = vec![Vec::new(); n];
    graph[5].push(0);
    graph[5].push(2);
    graph[4].push(0);
    graph[4].push(1);
    graph[2].push(3);
    graph[3].push(1);

    let mut visited = vec![false; n];
    let mut order = VecDeque::new();

    for start in 0..n {
        if visited[start] {
            continue;
        }

        let mut stack = Vec::new();
        // node, children_visited?
        stack.push((start, false));

        while let Some((node, children_visited)) = stack.pop() {
            if children_visited {
                order.push_front(node);
                continue;
            }

            if visited[node] {
                continue;
            }

            visited[node] = true;
            stack.push((node, true));

            for &neighbor in graph[node].iter().rev() {
                if !visited[neighbor] {
                    stack.push((neighbor, false));
                }
            }
        }
    }

    dbg!(order);
}
