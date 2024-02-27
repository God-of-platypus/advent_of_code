use std::fs;
use regex::Regex;
use std::collections::HashMap;

fn parse_bag<'a>(rule: &'a str) -> (&'a str, Vec<&str>) {
    let RE_RULE  = Regex::new(r#"^([a-z ]+) bags contain (.*)$"#).unwrap();
    let RE_CONT  = Regex::new(r#"\d ([a-z ]+) b"#).unwrap(); 
    let captures = RE_RULE.captures(rule).unwrap();
    (
        captures.get(1).unwrap().as_str(),
        RE_CONT
            .captures_iter(captures.get(2).unwrap().as_str())
            .map(|cond| cond.get(1).unwrap().as_str())
            .collect(),
    )
}

fn main() {
    let content = fs::read_to_string("input.txt").expect(" ");

    let rules:Vec<_> = content.lines().map(parse_bag).collect();

    let (mut bags, mut cursor) = (vec!["shiny gold"], 0);

    while let Some(target) = bags.get(cursor) {
        let extra = rules
            .iter()
            .filter(|(color, cont)| cont.contains(target) && !bags.contains(color))
            .map(|(color, _)| *color)
            .collect::<Vec<_>>();
        bags.extend_from_slice(&extra);
        cursor += 1;
    }

    println!("The result of part 1 is {}", bags.len() - 1);
}
