#[derive(Clone, Copy, Debug)]
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

    fn apply(&mut self, val: i32, len: i32) {
        self.sum += val * len;
        self.min += val;
        self.max += val;
    }
}

struct SegmentTree {
    n: usize,
    tree: Vec<Node>,
    lazy: Vec<i32>,
}

impl SegmentTree {
    fn new(xs: &[i32]) -> Self {
        let n = xs.len();
        let mut seg = Self {
            n,
            tree: vec![Node::identity(); 4 * n],
            lazy: vec![0; 4 * n],
        };

        seg.build(1, 0, n - 1, xs);
        seg
    }

    fn build(&mut self, v: usize, l: usize, r: usize, xs: &[i32]) {
        if l == r {
            self.tree[v] = Node::new(xs[l]);
            return;
        }

        let mid = (l + r) / 2;
        self.build(v * 2, l, mid, xs);
        self.build(v * 2 + 1, mid + 1, r, xs);

        self.tree[v] = Node::combine(self.tree[v * 2], self.tree[v * 2 + 1]);
    }

    fn push(&mut self, v: usize, l: usize, r: usize) {
        let lazy_val = self.lazy[v];
        if lazy_val == 0 {
            return;
        }

        let mid = (l + r) / 2;
        let left = v * 2;
        let right = v * 2 + 1;

        self.tree[left].apply(lazy_val, (mid - l + 1) as i32);
        self.tree[right].apply(lazy_val, (r - mid) as i32);

        self.lazy[left] += lazy_val;
        self.lazy[right] += lazy_val;

        self.lazy[v] = 0;
    }

    fn update_range(&mut self, v: usize, l: usize, r: usize, ql: usize, qr: usize, val: i32) {
        if ql > r || qr < l {
            return;
        }

        if ql <= l && r <= qr {
            self.tree[v].apply(val, (r - l + 1) as i32);
            self.lazy[v] += val;
            return;
        }

        self.push(v, l, r);

        let mid = (l + r) / 2;

        self.update_range(v * 2, l, mid, ql, qr, val);
        self.update_range(v * 2 + 1, mid + 1, r, ql, qr, val);

        self.tree[v] = Node::combine(self.tree[v * 2], self.tree[v * 2 + 1]);
    }

    fn query(&mut self, v: usize, l: usize, r: usize, ql: usize, qr: usize) -> Node {
        if ql > r || qr < l {
            return Node::identity();
        }

        if ql <= l && r <= qr {
            return self.tree[v];
        }

        self.push(v, l, r);

        let mid = (l + r) / 2;

        let left = self.query(v * 2, l, mid, ql, qr);
        let right = self.query(v * 2 + 1, mid + 1, r, ql, qr);

        Node::combine(left, right)
    }

    fn update(&mut self, l: usize, r: usize, val: i32) {
        self.update_range(1, 0, self.n - 1, l, r, val);
    }

    fn range_query(&mut self, l: usize, r: usize) -> Node {
        self.query(1, 0, self.n - 1, l, r)
    }
}

fn main() {
    let xs = vec![1, 3, 5, 7, 9, 11];
    let mut st = SegmentTree::new(&xs);
    st.update(1, 4, 10);
    let res = st.range_query(0, 5);
    println!("sum = {}", res.sum);
    println!("min = {}", res.min);
    println!("max = {}", res.max);
}
