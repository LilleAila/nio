// Segment Trees

#[derive(Clone, Copy)]
struct Node {
    sum: i32,
    min: i32,
    max: i32,
}

impl Node {
    fn new(x: i32) -> Self {
        Self {
            sum: x,
            min: x,
            max: x,
        }
    }

    fn identity() -> Self {
        Self {
            sum: 0,
            min: i32::MAX,
            max: i32::MIN,
        }
    }

    fn combine(a: Self, b: Self) -> Self {
        Self {
            sum: a.sum + b.sum,
            min: a.min.min(b.min),
            max: a.max.max(b.max),
        }
    }
}

struct SegmentTree {
    n: usize,
    tree: Vec<Node>,
}

impl SegmentTree {
    fn new(xs: &[i32]) -> Self {
        let n = xs.len();
        let mut tree = vec![Node::identity(); 2 * n];

        for i in 0..n {
            tree[n + i] = Node::new(xs[i]);
        }
        for i in (1..n).rev() {
            tree[i] = Node::combine(tree[2 * i], tree[2 * i + 1]);
        }

        Self { n, tree }
    }

    fn update(&mut self, mut i: usize, val: i32) {
        i += self.n;
        self.tree[i] = Node::new(val);

        while i > 1 {
            i /= 2;
            self.tree[i] = Node::combine(self.tree[2 * i], self.tree[2 * i + 1]);
        }
    }

    fn query(&self, mut l: usize, mut r: usize) -> Node {
        l += self.n;
        r += self.n;

        let mut res_l = Node::identity();
        let mut res_r = Node::identity();

        while l <= r {
            if l % 2 == 1 {
                res_l = Node::combine(res_l, self.tree[l]);
                l += 1;
            }
            if r % 2 == 0 {
                res_r = Node::combine(self.tree[r], res_r);
                r -= 1;
            }
            l /= 2;
            r /= 2;
        }

        Node::combine(res_l, res_r)
    }
}

fn main() {
    let xs = vec![1, 2, 3, 4, 5];
    let mut st = SegmentTree::new(&xs);

    // Query range (1..=3)
    let res = st.query(1, 3);
    println!("sum = {}", res.sum);
    println!("min = {}", res.min);
    println!("max = {}", res.max);

    st.update(2, 10);

    let res = st.query(1, 3);
    println!("sum = {}", res.sum);
    println!("min = {}", res.min);
    println!("max = {}", res.max);
}
