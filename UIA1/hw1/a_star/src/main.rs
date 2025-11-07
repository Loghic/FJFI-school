mod mazes;
use mazes::*;
use eframe::egui;


#[cfg(not(target_arch = "wasm32"))]
use rfd::FileDialog;

#[cfg(target_arch = "wasm32")]
mod web_imports {
    pub use wasm_bindgen::JsCast;
    pub use console_error_panic_hook;
    pub use web_sys;
    pub use wasm_bindgen_futures;
}

#[cfg(target_arch = "wasm32")]
fn main() {
    use web_imports::*;
    // Redirect panic messages to the browser console:
    console_error_panic_hook::set_once();

    wasm_bindgen_futures::spawn_local(async {
        // Grab the <canvas id="the_canvas_id"> element from the DOM:
        let window = web_sys::window().expect("no global `window` exists");
        let document = window.document().expect("should have a document on window");
        let canvas = document
            .get_element_by_id("the_canvas_id")
            .expect("canvas with id 'the_canvas_id' not found")
            .dyn_into::<web_sys::HtmlCanvasElement>()
            .expect("couldn't convert to HtmlCanvasElement");

        eframe::WebRunner::new()
            .start(
                canvas, // pass the actual canvas element
                eframe::WebOptions::default(),
                Box::new(|cc| {
                    egui_extras::install_image_loaders(&cc.egui_ctx);
                    Ok(Box::<MyApp>::default())
                }),
            )
            .await
            .expect("failed to start eframe web app");
    });
}


#[cfg(not(target_arch = "wasm32"))]
fn main() -> eframe::Result<()> {
    let options = eframe::NativeOptions {
        viewport: egui::ViewportBuilder::default().with_inner_size([800.0, 600.0]),
        ..Default::default()
    };
    eframe::run_native(
        "Maze Solver",
        options,
        Box::new(|cc| {
            egui_extras::install_image_loaders(&cc.egui_ctx);
            Ok(Box::<MyApp>::default())
        }),
    )
}

#[derive(PartialEq)]
enum PickMode {
    None,
    PickingStart,
    PickingEnd,
}

#[derive(PartialEq)]
enum Algorithm {
    AStar,
    BFS,
    DFS,
}

impl Default for Algorithm {
    fn default() -> Self {
        Algorithm::AStar
    }
}

struct MyApp {
    maze: Vec<Vec<Cell>>,
    selected_maze: String,
    rows: usize,
    cols: usize,
    cell_size: f32,
    last_canvas_size: egui::Vec2,

    // For opening files desktop
    #[cfg(not(target_arch = "wasm32"))]
    selected_file: Option<String>,
    #[cfg(not(target_arch = "wasm32"))]
    file_contents: Option<String>,

    // Right panel
    start_x: u32,
    start_y: u32,
    end_x: u32,
    end_y: u32,
    selected_algorithm: Algorithm,
    speed_ms: u32,
    solve_clicked: bool,
    step_clicked: bool,

    pick_mode: PickMode,
}

impl Default for MyApp {
    fn default() -> Self {
        let rows = 10;
        let cols = 10;

        Self {
            #[cfg(not(target_arch = "wasm32"))]
            selected_file: None,
            #[cfg(not(target_arch = "wasm32"))]
            file_contents: None,
            rows,
            cols,
            maze: maze_starting(),
            selected_maze: "Starting".to_owned(),
            cell_size: 30.0,
            last_canvas_size: egui::vec2(800.0, 600.0),
            start_x: 1,
            start_y: 1,
            end_x: 5,
            end_y: 5,
            selected_algorithm: Algorithm::AStar,
            speed_ms: 100,
            solve_clicked: false,
            step_clicked: false,

            pick_mode: PickMode::None,
        }
    }
}

impl MyApp {
    #[cfg(not(target_arch = "wasm32"))]
    fn open_file(&mut self) {
        if let Some(path) = FileDialog::new()
            .add_filter("Text", &["txt"])
            .add_filter("PBM image", &["pbm"])
            .add_filter("Images", &["png", "jpeg", "jpg"])
            .set_directory(".")
            .pick_file()
        {
            self.selected_file = Some(path.display().to_string());

            // Try reading file if it's text
            if let Ok(content) = std::fs::read_to_string(&path) {
                self.file_contents = Some(content);
            } else {
                self.file_contents = Some("<binary or unreadable file>".into());
            }
        }
    }
}

impl eframe::App for MyApp {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::TopBottomPanel::top("top_nale").show(ctx, |ui| {

            egui::MenuBar::new().ui(ui, |ui| {

                let is_web = cfg!(target_arch = "wasm32");
                ui.menu_button("File", |ui|{
                    if !is_web {
                        if ui.button("Quit").clicked() {
                            ctx.send_viewport_cmd(egui::ViewportCommand::Close);
                        }
                        ui.add_space(16.0);
                        if ui.button("Open File").clicked() {
                            #[cfg(not(target_arch = "wasm32"))]
                            self.open_file();
                        }
                    }
                });

                egui::widgets::global_theme_preference_buttons(ui);

            });
        });
        // Righ side panel
        egui::SidePanel::right("settings_panel").show(ctx, |ui| {
            ui.heading("Settings");

            ui.horizontal(|ui| {
                ui.label("Maze");

                let previous_maze = self.selected_maze.clone();

                egui::ComboBox::from_label("")
                    .selected_text(&self.selected_maze)
                    .show_ui(ui, |ui| {
                        ui.selectable_value(&mut self.selected_maze, "Starting".to_string(), "Starting");
                        ui.selectable_value(&mut self.selected_maze, "Open".to_string(), "Open");
                        ui.selectable_value(&mut self.selected_maze, "Wall Split".to_string(), "Wall Split");
                        ui.selectable_value(&mut self.selected_maze, "Boxed".to_string(), "Boxed");
                    });

                if self.selected_maze != previous_maze {
                    self.maze = match self.selected_maze.as_str() {
                        "Open" => mazes::maze_open(self.rows, self.cols),
                        "Wall Split" => mazes::maze_wall_split(self.rows, self.cols),
                        "Boxed" => mazes::maze_boxed(self.rows, self.cols),
                        "Starting" => mazes::maze_starting(),
                        _ => mazes::maze_open(self.rows, self.cols),
                    };
                    self.rows = self.maze.len();
                    self.cols = if self.rows > 0 { self.maze[0].len() } else { 0 };
                }
            });

            let active_color = ui.visuals().selection.bg_fill;
            let inactive_color = ui.visuals().widgets.inactive.bg_fill;

            ui.group(|ui| {
                ui.label("Start coordinates");
                ui.horizontal(|ui| {
                    ui.add(egui::DragValue::new(&mut self.start_x).range(0..=u32::MAX).speed(1));
                    ui.add(egui::DragValue::new(&mut self.start_y).range(0..=u32::MAX).speed(1));

                    let start_button_color = if self.pick_mode == PickMode::PickingStart {
                        active_color
                    } else {
                        inactive_color
                    };
                    if ui.add(egui::Button::new("Pick Start").fill(start_button_color)).clicked() {
                        self.pick_mode = PickMode::PickingStart;
                    }
                });
            });

            ui.group(|ui| {
                ui.label("End coordinates");
                ui.horizontal(|ui| {
                    ui.add(egui::DragValue::new(&mut self.end_x).range(0..=u32::MAX).speed(1));
                    ui.add(egui::DragValue::new(&mut self.end_y).range(0..=u32::MAX).speed(1));

                    let end_button_color = if self.pick_mode == PickMode::PickingEnd {
                        active_color
                    } else {
                        inactive_color
                    };

                    if ui.add(egui::Button::new("Pick End").fill(end_button_color)).clicked() {
                        self.pick_mode = PickMode::PickingEnd;
                    }
                });
            });

            ui.group(|ui| {
                ui.label("Cell size");
                ui.add(egui::Slider::new(&mut self.cell_size, 5.0..=100.0).text("px"));
            });

            if ui.button("Fit to window").clicked() {
                let new_size_x = self.last_canvas_size.x / self.cols as f32;
                let new_size_y = self.last_canvas_size.y / self.rows as f32;
                self.cell_size = new_size_x.min(new_size_y).clamp(5.0, 100.0);
            }

            // Algorithm dropdown
            egui::ComboBox::from_label("Algorithm")
                .selected_text(match self.selected_algorithm {
                    Algorithm::AStar => "A*",
                    Algorithm::BFS => "BFS",
                    Algorithm::DFS => "DFS",
                })
                .show_ui(ui, |ui| {
                    ui.selectable_value(&mut self.selected_algorithm, Algorithm::AStar, "A*");
                    ui.selectable_value(&mut self.selected_algorithm, Algorithm::BFS, "BFS");
                    ui.selectable_value(&mut self.selected_algorithm, Algorithm::DFS, "DFS");
                });

            // Speed dropdown
            egui::ComboBox::from_label("Speed (ms)")
                .selected_text(format!("{}", self.speed_ms))
                .show_ui(ui, |ui| {
                    for &speed in &[100, 200, 500, 1000] {
                        ui.selectable_value(&mut self.speed_ms, speed, format!("{}", speed));
                    }
                });

            ui.horizontal(|ui| {
                if ui.button("Solve").clicked() {
                    self.solve_clicked = true;
                    self.step_clicked = false;
                }
                if ui.button("Step").clicked() {
                    self.step_clicked = true;
                    self.solve_clicked = false;
                }
            });
        });

        egui::CentralPanel::default().show(ctx, |ui| {
            let available = ui.available_size();
            self.last_canvas_size = available;

            // Compute maze pixel size
            let maze_width = self.cols as f32 * self.cell_size;
            let maze_height = self.rows as f32 * self.cell_size;

            // Center the maze if there is extra space
            let offset_x = (available.x - maze_width).max(0.0) / 2.0;
            let offset_y = (available.y - maze_height).max(0.0) / 2.0;

            // Start drawing from the top-left corner of the available region
            let origin = ui.min_rect().min + egui::vec2(offset_x, offset_y);

            let maze_rect = egui::Rect::from_min_size(origin, egui::vec2(maze_width, maze_height));

            let response = ui.allocate_rect(maze_rect, egui::Sense::click());

            // Painter the canvas
            let painter = ui.painter_at(maze_rect);

            for row in 0..self.rows {
                for col in 0..self.cols {
                    let x = origin.x + col as f32 * self.cell_size;
                    let y = origin.y + row as f32 * self.cell_size;
                    let cell_rect = egui::Rect::from_min_size(
                        egui::pos2(x, y),
                        egui::vec2(self.cell_size, self.cell_size),
                    );

                    // Determine color based on coordinates
                    let color = if row as u32 == self.start_y && col as u32 == self.start_x {
                        egui::Color32::BLUE
                    } else if row as u32 == self.end_y && col as u32 == self.end_x {
                        egui::Color32::RED
                    } else {
                        match self.maze[row][col] {
                            Cell::Empty => egui::Color32::WHITE,
                            Cell::Wall => egui::Color32::BLACK,
                        }
                    };

                    painter.rect_filled(cell_rect, 0.0, color);

                    // Grid lines
                    painter.rect_stroke(cell_rect, 0.0, (1.0, egui::Color32::GRAY), egui::StrokeKind::Outside);
                }
            }

            // Hanlde picking start/end with mouse
            if let Some(pos) = response.interact_pointer_pos() {
                if response.clicked() && maze_rect.contains(pos) {
                    let col = ((pos.x - origin.x) / self.cell_size).floor() as u32;
                    let row = ((pos.y - origin.y) / self.cell_size).floor() as u32;

                    match self.pick_mode {
                        PickMode::PickingStart => {
                            self.start_x = col;
                            self.start_y = row;
                            self.pick_mode = PickMode::None;
                        }
                        PickMode::PickingEnd => {
                            self.end_x = col;
                            self.end_y = row;
                            self.pick_mode = PickMode::None;
                        }
                        PickMode::None => {}
                    }
                }
            }
        });
    }
}

