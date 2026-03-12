// 2-SAT with SCCs
fn main() {
    // Initialize the graph
    let variables = 3;
    let n = variables * 2;
    let mut graph = vec![Vec::new(); n];

    let add_or = |graph: &mut Vec<Vec<usize>>, a: usize, b: usize| {
        graph[a ^ 1].push(b);
        graph[b ^ 1].push(a);
    };

    let x0 = 0;
    let nx0 = 1;
    let x1 = 2;
    let nx1 = 3;
    let x2 = 4;
    let nx2 = 5;

    add_or(&mut graph, x0, x1); // x0 V x1
    add_or(&mut graph, nx0, x2); // !x0 V x2
    add_or(&mut graph, nx1, nx2); // !x1 V !x2

    // --- Kosaraju SCC ---

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

    let mut ok = true;
    let mut assignment = vec![false; variables];
    for i in 0..variables {
        if component[2 * i] == component[2 * i + 1] {
            // x_i and !x_i were found in the same SCC
            ok = false;
            break;
        } else {
            // True if x_i's SCC comes after !x_i's SCC
            assignment[i] = component[2 * i] > component[2 * i + 1];
        }
    }

    if ok {
        println!("Satisfiable with assignment {:?}", assignment);
    } else {
        println!("Unsatisfiable :(");
    }
}
