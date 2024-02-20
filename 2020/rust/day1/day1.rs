use std::fs;

fn main() {
    let contents = fs::read_to_string("input.txt").expect("AAAAAAAAAAAAAAAAAAAAAAAAAAAAA");

    let mut arr:Vec<&str> = contents
        .split("\n")
        .collect();

    arr.pop();

    let nums:Vec<u32> = arr.iter().filter_map(|x| x.parse().ok()).collect();

    println!("{:?}", nums);

    for i in 0..nums.len() {
        for j in i..nums.len() {
            if nums[i] + nums[j] == 2020 {
                println!("The result of part 1 is {}", nums[i] * nums[j]);
            }
            for k in j..nums.len() {
                if nums[i] + nums[j] + nums[k] == 2020 {
                    println!("The result of part 2 is {}",nums[i] * nums[j] * nums[k]);
                }
            }
        }
    }
}
