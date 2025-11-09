#[derive(Clone, Copy, PartialEq)]
pub enum Cell {
    Empty,
    Wall,
}

pub type MazeGrid = Vec<Vec<Cell>>;

#[cfg(not(target_arch = "wasm32"))]
pub fn maze_from_pbm(path: &str) -> Result<MazeGrid, String> {
    use std::fs::File;
    use std::io::{BufRead, BufReader};
    let file = File::open(path).map_err(|e| format!("Failed to open file: {}", e))?;
    let reader = BufReader::new(file);

    let mut lines = reader
        .lines()
        .map_while(Result::ok)
        .filter(|l| !l.trim().is_empty())
        .collect::<Vec<_>>();

    // Hanlde PBM header
    if lines.is_empty() || !lines[0].starts_with("P1") {
        return Err("Invalid PBM file (missing P1 header)".to_string());
    }
    lines.remove(0);

    // Commented lines
    while !lines.is_empty() & lines[0].starts_with('#') {
        lines.remove(0);
    }

    // Read widht/height line
    if lines.is_empty() {
        return Err("PBM missing size info".to_string());
    }

    let dims: Vec<usize> = lines[0]
        .split_whitespace()
        .filter_map(|v| v.parse().ok())
        .collect();

    if dims.len() != 2 {
        return Err("Invalid PBM size line".to_string());
    }

    let (width, height) = (dims[0], dims[1]);
    lines.remove(0);

    // Collect pixel data
    let data: Vec<u8> = lines
        .iter()
        .flat_map(|line| line.split_whitespace())
        .filter_map(|s| s.parse::<u8>().ok())
        .collect();

    if data.len() != width * height {
        return Err(format!(
            "PBM data size mismatch: expected {} got {}",
            width * height,
            data.len()
        ));
    }

    let mut maze = vec![vec![Cell::Empty; width]; height];
    for y in 0..height {
        for x in 0..width {
            maze[y][x] = if data[y * width + x ] == 1 {
                Cell::Wall
            } else {
                Cell::Empty
            };
        }
    }

    Ok(maze)
}


#[cfg(target_arch = "wasm32")]
pub fn maze_from_pbm_str(contents: &str) -> Result<MazeGrid, String> {
    let mut lines = contents
        .lines()
        .map(str::trim)
        .filter(|l| !l.is_empty())
        .collect::<Vec<_>>();

    if lines.is_empty() || !lines[0].starts_with("P1") {
        return Err("Invalid PBM file (missing P1 header)".to_string());
    }
    lines.remove(0);

    while !lines.is_empty() && lines[0].starts_with('#') {
        lines.remove(0);
    }

    if lines.is_empty() {
        return Err("PBM missing size info".to_string());
    }

    let dims: Vec<usize> = lines[0]
        .split_whitespace()
        .filter_map(|v| v.parse().ok())
        .collect();

    if dims.len() != 2 {
        return Err("Invalid PBM size line".to_string());
    }

    let (width, height) = (dims[0], dims[1]);
    lines.remove(0);

    let data: Vec<u8> = lines
        .iter()
        .flat_map(|line| line.split_whitespace())
        .filter_map(|s| s.parse::<u8>().ok())
        .collect();

    if data.len() != width * height {
        return Err(format!(
            "PBM data size mismatch: expected {} got {}",
            width * height,
            data.len()
        ));
    }

    let mut maze = vec![vec![Cell::Empty; width]; height];
    for y in 0..height {
        for x in 0..width {
            maze[y][x] = if data[y * width + x] == 1 {
                Cell::Wall
            } else {
                Cell::Empty
            };
        }
    }

    Ok(maze)
}


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
