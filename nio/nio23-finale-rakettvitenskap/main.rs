use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let n: usize = lines.next().unwrap().unwrap().parse().unwrap();

    let mut target = n;
    while target > 0 {
        let mut register = 7;
        for _ in 0..target {
            let next_register = if register == 7 { 0 } else { (register + 1) % 7 };
            println!("I {} {}", register, next_register);
            register = next_register;
        }

        for _ in 0..7.min(target) {
            println!("P {}", register);
            register = (register - 1 + 7) % 7;
            target -= 1;
        }
    }

    println!("P 7");
}
