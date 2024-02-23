use std::fs;
extern crate regex;
use regex::Regex;

fn byr_verif(string: &str) -> bool{
    let num:u32 = string.trim().parse().ok().unwrap();

    num >= 1920 && num <= 2002

}

fn iyr_verif(string : &str) -> bool {
    let num:u32 = string.trim().parse().ok().unwrap();
    
    num <= 2020 && num >= 2010
}

fn eyr_verif(string: &str) -> bool {
    let num:u32 = string.trim().parse().ok().unwrap();
    
    num >= 2020 && num <= 2030
}

fn hgt_verif(string : &str) -> bool {
    if string.len() < 2 {
        return false;
    }

    let (first, last) = string.split_at(string.len() - 2);

    match last {
        "cm" => {
                    let num:u32 = first.trim().parse().ok().unwrap();
                    return num >= 150 && num <= 193
                },
        "in" => {
                    let num:u32 = first.trim().parse().ok().unwrap();
                    return num >= 59 && num <= 76
                },
        _    => return false,
    }
}

fn hcl_verif(string : &str) -> bool {
    if string.len() != 7 {
        return false;
    }
    let reg = Regex::new(r"#[0-9a-f]{6}");
    reg.expect("Reason").is_match(string)
}

fn ecl_verif(string : &str) -> bool {
    match string {
        "amb" | "blu" | "brn" | "gry" | "grn" | "hzl" | "oth" => true,
        _ => false,
    }
}

fn pid_verif(string : &str) -> bool {
   return string.len() == 9
}

fn main() {
    let contents = fs::read_to_string("input.txt").expect("AAAAAAAAAAAAAAAAAAA");

    let mut strings:Vec<&str> = contents.split("\n").collect();

    strings.pop();

    
    let mut i = 0;

    let mut res = 0;

    while i < strings.len() {
        let mut byr = false;
        let mut iyr = false;
        let mut eyr = false;
        let mut hgt = false;
        let mut hcl = false;
        let mut ecl = false;
        let mut pid = false;
        let mut cid = false;
        while strings[i] != "" {
            let mini:Vec<&str> = strings[i].split(&[' ', ':'][..]).collect();
            i += 1; 
            for j in 0..mini.len() {
                if j % 2 == 0 {
                    match mini[j] {
                        "byr" => byr = byr_verif(mini[j + 1]),
                        "iyr" => iyr = iyr_verif(mini[j + 1]),
                        "eyr" => eyr = eyr_verif(mini[j + 1]),
                        "hgt" => hgt = hgt_verif(mini[j + 1]),
                        "hcl" => hcl = hcl_verif(mini[j + 1]),
                        "ecl" => ecl = ecl_verif(mini[j + 1]),
                        "pid" => pid = pid_verif(mini[j + 1]),
                        "cid" => cid = true,
                        _ => panic!("Fuckkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk"),
                    }
                }
            }
            if i == strings.len() {
                break;
            }
        }
        if byr && iyr && eyr && hgt && hcl && ecl && pid {
            res += 1;
        }
        i +=1;
    }
    println!("The result of part 1 is {}", res);
}
