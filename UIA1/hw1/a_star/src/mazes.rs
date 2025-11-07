#[derive(Clone, Copy, PartialEq)]
pub enum Cell {
    Empty,
    Wall,
}

pub type MazeGrid = Vec<Vec<Cell>>;

// Empty maze
pub fn maze_open(rows: usize, cols: usize) -> MazeGrid {
    vec![vec![Cell::Empty; cols]; rows]
}

// Small maze with vertical wall and a passage
pub fn maze_wall_split(rows: usize, cols: usize) -> MazeGrid {
    let mut maze = vec![vec![Cell::Empty; cols]; rows];
    let mid = cols / 2;

    for row in 0..rows {
        if row != rows / 2 {
            maze[row][mid] = Cell::Wall;
        }
    }

    maze
}

// More complex "boxed" maze
pub fn maze_boxed(rows: usize, cols: usize) -> MazeGrid {
    let mut maze = vec![vec![Cell::Empty; cols]; rows];

    // Border walls
    for x in 0..cols {
        maze[0][x] = Cell::Wall;
        maze[rows-1][x] = Cell::Wall;
    }

    for y in 0..rows {
        maze[y][0] = Cell::Wall;
        maze[y][cols - 1] = Cell::Wall
    }

    // Inner obstacles
    for y in (2..rows -2).step_by(2) {
        for x in (2..cols -2).step_by(3) {
            maze[y][x] = Cell::Wall;
        }
    }

    maze
}

pub fn maze_starting() -> MazeGrid {
    let layout = [
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 1, 1, 1, 1, 1, 1, 1, 1, 0],
            [0, 1, 0, 0, 0, 0, 0, 0, 1, 0],
            [0, 1, 0, 1, 1, 1, 1, 0, 1, 0],
            [0, 1, 0, 1, 0, 0, 1, 0, 1, 0],
            [0, 1, 0, 1, 0, 1, 1, 0, 1, 0],
            [0, 1, 0, 1, 0, 1, 0, 0, 1, 0],
            [0, 1, 1, 1, 0, 1, 1, 1, 1, 0],
            [0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    ];

    layout
        .iter()
        .map(|row| {
            row.iter()
                .map(|&v| if v == 1 { Cell::Empty } else { Cell::Wall })
                .collect()
        })
        .collect()
}
