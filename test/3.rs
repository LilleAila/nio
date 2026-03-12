// SCC -> DAG

fn main() {
    // Initialize the graph
    let n = 4;
    let mut graph = vec![Vec::new(); n];
    graph[0].push(1);
    graph[1].push(2);
    graph[2].push(0);
    graph[2].push(3);

    // Create a reversed graph
    let mut rg = vec![Vec::new(); n];
    for v in 0..n {
        for &to in &graph[v] {
            rg[to].push(v);
        }
    }

    // First DFS pass. This determines the order to process the nodes
    // so SCCs are discovered correctly in the second pass of DFS
    let mut visited = vec![false; n];
    let mut order = vec![];
    let mut stack = vec![];
    for i in 0..n {
        // For each unvisited node, do a DFS starting from `i`
        // This is used to build a "finishing order"-stack
        if visited[i] {
            continue;
        }
        stack.push((i, 0));
        while let Some((v, state)) = stack.pop() {
            if state == 0 {
                if visited[v] {
                    continue;
                }
                visited[v] = true;
                stack.push((v, 1));
                for &to in &graph[v] {
                    if !visited[to] {
                        stack.push((to, 0));
                    }
                }
            } else {
                order.push(v);
            }
        }
    }

    // The second DFS explores backward connections. This ensures that the
    // DFS starting from the last finished node in the first pass will
    // only stay inside of the SCC.
    let mut component = vec![usize::MAX; n];
    let mut id = 0;
    // As described, this iterates from the reverse finishing order.
    for &v in order.iter().rev() {
        if component[v] != usize::MAX {
            continue;
        }
        // Run a DFS for each node which is not a member of an SCC
        let mut stack = vec![v];
        component[v] = id;
        while let Some(x) = stack.pop() {
            for &to in &rg[x] {
                if component[to] == usize::MAX {
                    component[to] = id;
                    stack.push(to);
                }
            }
        }

        id += 1;
    }

    // Each node will now have a component ID
    dbg!(&id, &component);

    // Create the dag
    let mut dag = vec![Vec::new(); id];
    for u in 0..n {
        for &v in &graph[u] {
            let cu = component[u];
            let cv = component[v];
            if cu != cv {
                dag[cu].push(cv);
            }
        }
    }

    // Optional deduplication (often not necessary)
    for edges in dag.iter_mut() {
        edges.sort_unstable();
        edges.dedup();
    }

    dbg!(&dag);
}
