use regex::Regex;
use std::collections::HashMap;


pub fn main() {
    let rules: HashMap<_, _> = include_str!("input.txt")
        .lines()
        .map(parse_bag)
        .collect();
    println!("The result of part2 is {}", bags("shiny gold", &rules) - 1);
}

/// Parse bag ruleset.
#[inline(always)]
fn parse_bag<'a>(rule: &'a str) -> (&'a str, Vec<(&str, usize)>) {
    let RE_RULE: Regex = Regex::new(r#"^([a-z ]+) bags contain (.*)$"#).unwrap();
    let RE_CONT: Regex = Regex::new(r#"(\d) ([a-z ]+) b"#).unwrap();

    let captures = RE_RULE.captures(rule).unwrap();
    (
        captures.get(1).unwrap().as_str(),
        RE_CONT
            .captures_iter(captures.get(2).unwrap().as_str())
            .map(|cond| (cond.get(2).unwrap().as_str(), cond[1].parse().unwrap()))
            .collect(),
    )
}

/// Count bags in bags.
fn bags(color: &str, rules: &HashMap<&str, Vec<(&str, usize)>>) -> usize {
    1 + rules[color]
        .iter()
        .map(|(color, count)| bags(color, rules) * count)
        .sum::<usize>()
}
