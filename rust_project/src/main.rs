/*
 * @Author: Skye
 * @Date: 2024-09-04 19:46:26
 * @LastEditTime: 2025-01-05 14:30:24
 * @Description:
 * Skye:'Never stop!'
 */

struct MyCalendarTwo {
    books: Vec<(i32, i32)>,
    over_laps: Vec<(i32, i32)>,
}

impl MyCalendarTwo {
    pub fn new() -> Self {
        MyCalendarTwo {
            books: Vec::new(),
            over_laps: Vec::new(),
        }
    }

    pub fn book(&mut self, start_time: i32, end_time: i32) -> bool {
        for (s, e) in &self.over_laps {
            if start_time < *e && end_time > *s {
                return false;
            }
        }
        for (s, e) in &self.books {
            if start_time < *e && end_time > *s {
                self.over_laps.push((std::cmp::max(start_time, *s), std::cmp::min(end_time, *e)));
            }
        }
        self.books.push((start_time, end_time));
        true
    }
}

fn main() {
    println!("Hello, world!");
}
