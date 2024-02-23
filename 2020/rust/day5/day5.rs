use std::fs;
use std::cmp;
use std::convert::TryInto;

fn main() {
    let contents = fs::read_to_string("input.txt").expect("");

    let mut strings:Vec<&str> = contents.split("\n").collect();

    strings.pop();

    let mut res:u32 = 0;

    let mut vec = Vec::new();

    for j in 0..strings.len() {
        let line = strings[j];
        let mut start = 0;
        let mut end = 127;
        for i in 0..line.len() - 3 {
            match line.chars().nth(i).unwrap() {
                'B' => start = (start + end + 1) / 2,
                'F' => end = (start + end - 1) / 2,
                _ => panic!("FUUUUUUUUUUU"),
            }
        }
        let mut s = 0;
        let mut e = 7;

        for i in line.len() - 3..line.len() {
            match line.chars().nth(i).unwrap() {
                'R' => s = (s + e + 1) / 2,
                'L' => e = (s + e - 1) / 2,
                _ => panic!("FUUUUFUFUUFUFUFUFU"),
            }
        }
        vec.push(start * 8 + s);
        res = cmp::max(start * 8 + s, res);
    };

    println!("The result of part 1 is {}", res);
    vec.sort();
    for i in 0..vec.len() {
        let u:u32 = (i + 40).try_into().unwrap();
        if vec[i] != u {
            println!("The result of part 2 is {}", i + 40);
            break;
        }
    }
}
