use std::fs;

fn main () {
    let contents = fs::read_to_string("input.txt").expect("AAAAAAAAAAAAAAAAAAA");

    let mut strings:Vec<&str> = contents.split("\n").collect();

    strings.pop();

    println!("{:?}", strings);
    let l = strings[0].len();

    let mut x1 = 1;
    let mut x2 = 3;
    let mut x3 = 5;
    let mut x4 = 7;
    let mut x5 = 1;

    let mut res1:u64 = 0;
    let mut res2:u64 = 0;
    let mut res3:u64 = 0;
    let mut res4:u64 = 0;
    let mut res5:u64 = 0;

    for n in 0..strings.len() - 1 {
        if strings[n + 1].chars().nth(x1).unwrap() == '#' {
            res1 += 1;
        }
        if strings[n + 1].chars().nth(x2).unwrap() == '#' {
            res2 += 1;
        }
        if strings[n + 1].chars().nth(x3).unwrap() == '#' {
            res3 += 1;
        }
        if strings[n + 1].chars().nth(x4).unwrap() == '#' {
            res4 += 1;
        }
        if n % 2 == 0 && strings[n + 2].chars().nth(x5).unwrap() == '#' {
            res5 += 1;
        }
        if n % 2 == 0 {
            x5 += 1;
            x5 %= l;
        }
        x1 += 1;
        x2 += 3;
        x3 += 5;
        x4 += 7;
        x1 %= l;
        x2 %= l;
        x3 %= l;
        x4 %= l;
    }
    println!("The result of part 1 is {}", res2);
    println!("The result of part 2 is {}", res1 * res2 * res3 * res4 * res5);
}
