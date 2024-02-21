use std::fs;

fn main() {
    let contents = fs::read_to_string("input.txt").expect("AAAAAAAAAAAAAAAAAAA");

    let mut strings:Vec<&str> = contents.split("\n").collect();

    strings.pop();

    let mut res1:u32 = 0;
    let mut res2:u32 = 0;

    for i in 0..strings.len() {
        let mut min:u32 = 0;
        let mut j:usize = 0;
        let mut max:u32 = 0;
        let chars:Vec<_> = strings[i].chars().collect();

        while chars[j].is_digit(10) {
            min = min * 10 + chars[j].to_digit(10).unwrap();
            j += 1;
        }

        j += 1;

        while chars[j].is_digit(10) {
            max = max * 10 + chars[j].to_digit(10).unwrap();
            j += 1;
        }
        j += 1;

        let c:char = chars[j];
        j += 3;

        let mut count1:u32 = 0;
        if chars[j - 1 + min as usize] == c && chars[j - 1 + max as usize] != c {
            res2 += 1;
        }
        if chars[j - 1 + min as usize] != c && chars[j - 1 + max as usize] == c {
            res2 += 1;
        }
        while j < chars.len() {
            if chars[j] == c {
                count1 +=1;
            }
            j += 1;
        }
        if count1 >= min && count1 <= max {
            res1 += 1;
        }
    }
    println!("The result of part 1 is {}", res1);
    println!("The result of part 2 is {}", res2);
}
