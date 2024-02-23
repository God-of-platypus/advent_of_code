use std::fs;
use std::collections::btree_set::BTreeSet;

fn main() {
    let contents = fs::read_to_string("input.txt").expect("");

    let lines:Vec<&str> = contents.split("\n").collect();


    println!("{:?}", lines);
    
    let mut i = 0;

    let mut res = 0;
    let mut p2 = 0;

    while i < lines.len() {
        let mut set = BTreeSet::new();
        let mut vec:Vec<u32> = vec![0;26];
        let mut nb = 0;

        while lines[i] != "" {
            for c in lines[i].chars() {
                set.insert(c);
                vec[c as usize - 97] += 1;
            }
            i += 1;
            nb += 1;
        }
        for k in 0..26 {
            if nb == vec[k] {
                p2 += 1;
            }
        }
        res += set.len();
        i += 1;
    }

    println!("The result of part 1 is {}", res);
    println!("The result of part 2 is {}", p2);
}
