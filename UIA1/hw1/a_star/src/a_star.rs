use crate::mazes::Cell;

#[derive(Default, Clone, PartialEq)]
pub enum Algorithm {
    #[default]
    AStar,
    BFS,
    DFS,
}

pub struct Solver {
    pub algorithm: Algorithm,
    pub start: (usize, usize),
    pub goal: (usize, usize),
    pub open: Vec<(usize, usize)>,
    pub closed: Vec<(usize, usize)>,
    pub came_from: std::collections::HashMap<(usize, usize), (usize, usize)>,
    pub finished: bool,
    pub path: Vec<(usize, usize)>,
}

impl Solver {
    pub fn new(algorithm: Algorithm, start: (usize, usize), goal: (usize, usize)) -> Self {
        Self {
            algorithm,
            start,
            goal,
            open: vec![start],
            closed: Vec::new(),
            came_from: std::collections::HashMap::new(),
            finished: false,
            path: Vec::new(),
        }
    }
}

impl Solver {
    pub fn step(&mut self, maze: &Vec<Vec<Cell>>) {
        if self.finished || self.open.is_empty() {
            return ;
        }

        let current = match self.algorithm {
            Algorithm::DFS => self.open.pop(),
            _ => self.open.remove(0).into(), // BFS or A*
        };

        let current = match current {
            Some(c) => c,
            None => return,
        };

        if current == self.goal {
            self.reconstruct_path(current);
            self.finished = true;
            return;
        }

        self.closed.push(current);

        for neighbor in self.neighbors(current, maze) {
            if self.closed.contains(&neighbor) || maze[neighbor.1][neighbor.0] == Cell::Wall {
                continue;
            }

            if !self.open.contains(&neighbor) {
                self.came_from.insert(neighbor, current);
                self.open.push(neighbor);
            }
        }

        // A* ordering (by heuristic)
        if let Algorithm::AStar = self.algorithm {
            let goal = self.goal;
            self.open.sort_by_key(|&(x, y)| Self::heuristic((x,y), goal));
        }
    }

    fn heuristic(a: (usize, usize), b: (usize, usize)) -> usize {
        let dx = a.0.abs_diff(b.0);
        let dy = a.0.abs_diff(b.1);
        dx + dy
    }

    fn neighbors(&self, (x, y): (usize, usize), maze: &Vec<Vec<Cell>>) -> Vec<(usize, usize)> {
        let mut result = Vec::new();
        let height = maze.len();
        let width = maze[0].len();

        let dirs = [(1,0),(-1,0),(0,1),(0,-1)];
        for (dx, dy) in dirs {
            let nx = x as isize + dx;
            let ny = y as isize + dy;
            if nx >= 0 && ny >= 0 && nx < width as isize && ny < height as isize {
                result.push((nx as usize, ny as usize));
            }
        }
        result
    }

    fn reconstruct_path(&mut self, mut current: (usize, usize)) {
        self.path = vec![current];
        while let Some(prev) = self.came_from.get(&current) {
            current = *prev;
            self.path.push(current);
        }
        self.path.reverse();
    }

    pub fn step_bfs_layer(&mut self, maze: &Vec<Vec<Cell>>) {
        if self.finished || self.open.is_empty() {
            return;
        }

        // Take a snapshot of the current layer
        let current_layer = self.open.clone();
        self.open.clear();

        for current in current_layer {
            if current == self.goal {
                self.reconstruct_path(current);
                self.finished = true;
                return;
            }

            self.closed.push(current);

            for neighbor in self.neighbors(current, maze) {
                if self.closed.contains(&neighbor) || maze[neighbor.1][neighbor.0] == Cell::Wall {
                    continue;
                }

                if !self.open.contains(&neighbor) && !self.came_from.contains_key(&neighbor) {
                    self.came_from.insert(neighbor, current);
                    self.open.push(neighbor);
                }
            }
        }
    }
}
