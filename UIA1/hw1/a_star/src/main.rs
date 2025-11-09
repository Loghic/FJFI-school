mod mazes;
use mazes::*;
use eframe::egui;

#[cfg(not(target_arch = "wasm32"))]
use std::fs::File;

#[cfg(not(target_arch = "wasm32"))]
use std::io::Write;


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

#[derive(Clone, Copy, Default)]
struct Point {
    x: u32,
    y: u32,
}

#[derive(Default, PartialEq)]
enum Algorithm {
    #[default]
    AStar,
    BFS,
    DFS,
}

#[derive(PartialEq)]
enum EditMode {
    None,
    DrawWall,
    EraseWall,
}

struct MyApp {
    maze: Vec<Vec<Cell>>,
    selected_maze: String,
    rows: usize,
    cols: usize,
    cell_size: f32,
    target_cell_size: f32,
    last_canvas_size: egui::Vec2,
    auto_fit: bool,

    edit_mode: EditMode,

    // For opening files desktop
    #[cfg(not(target_arch = "wasm32"))]
    selected_file: Option<String>,
    file_contents: Option<String>,

    // Right panel
    start: Point,
    end: Point,
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
            file_contents: None,

            rows,
            cols,
            maze: maze_starting(),
            selected_maze: "Starting".to_owned(),
            cell_size: 30.0,
            target_cell_size: 30.0,
            last_canvas_size: egui::vec2(800.0, 600.0),
            auto_fit: true,
            edit_mode: EditMode::None,

            start:Point { x: 1, y: 1},
            end: Point { x: 5, y: 5},
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
            //   .add_filter("Images", &["png", "jpeg", "jpg"])
            .set_directory("assets")
            .pick_file()
        {
            self.selected_file = Some(path.display().to_string());
            let ext = path.extension().and_then(|e| e.to_str()).unwrap_or("").to_lowercase();

            match ext.as_str() {
                "pbm" => match mazes::maze_from_pbm(&path.display().to_string()) {
                    Ok(maze) => {
                        self.rows = maze.len();
                        self.cols = maze[0].len();
                        self.maze = maze;
                        self.auto_fit_to_window(self.last_canvas_size);
                    }
                    Err(err) => {
                        eprintln!("Failed to load PBM: {}", err);
                        self.file_contents = Some(format!("Error loading PBM: {}", err));
                    }
                },
                "txt" => {
                    if let Ok(content) = std::fs::read_to_string(&path) {
                        self.file_contents = Some(content);
                    } else {
                        self.file_contents = Some("<undreadable text file>".into());
                    }
                }
                _ => {
                        self.file_contents = Some("<unsported format>".into());
                }
            }
        }
    }
}

impl MyApp {
    #[cfg(not(target_arch = "wasm32"))]
    fn save_as_pbm(&self, path: &std::path::Path) -> std::io::Result<()> {
        let mut file = File::create(path)?;

        // PBM header
        writeln!(file, "P1")?;
        writeln!(file, "{} {}", self.cols, self.rows)?;

        // Write each row
        for row in &self.maze {
            for cell in row {
                let bit = match *cell {
                    Cell::Wall => 1,
                    _ => 0,
                };
                write!(file, "{} ", bit)?;
            }
            writeln!(file)?;
        }

        Ok(())
    }
}

impl MyApp {
    #[cfg(target_arch = "wasm32")]
    fn open_file_web(&mut self) {
        use wasm_bindgen::JsCast;
        use web_sys::{FileReader, HtmlInputElement};
        use wasm_bindgen::closure::Closure;

        // Create a hidden file input
        let document = web_sys::window().unwrap().document().unwrap();
        let input: HtmlInputElement = document
            .create_element("input")
            .unwrap()
            .dyn_into()
            .unwrap();
        input.set_type("file");

        // Filter for pbm/txt
        input.set_accept(".pbm, .txt");

        let app_rc = std::rc::Rc::new(std::cell::RefCell::new(self));

        let closure = Closure::wrap(Box::new(move |event: web_sys::Event| {
            let input: HtmlInputElement = event.target().unwrap().dyn_into().unwrap();

            if let Some(file_list) = input.files() {
                if let Some(file) = file_list.get(0) {
                    let file_clone = file.clone();
                    let reader = FileReader::new().unwrap();
                    let reader_rc = std::rc::Rc::new(reader);

                    let app_rc2 = app_rc.clone();

                    // Clone file and reader to move into closure
                    // let reader_clone = reader.clone();

                    let value = reader_rc.clone();
                    let onload = Closure::wrap(Box::new(move |_: web_sys::Event| {
                        let result = value.result().unwrap();
                        let text = result.as_string().unwrap();

                        let mut app = app_rc2.borrow_mut();

                        // Parse PBM or text
                        if file_clone.name().ends_with(".pbm") {
                            match mazes::maze_from_pbm_str(&text) {
                                Ok(maze) => {
                                    app.rows = maze.len();
                                    app.cols = maze[0].len();
                                    app.maze = maze;
                                }
                                Err(err) => web_sys::console::error_1(&err.into()),
                            }
                        } else {
                            app.file_contents = Some(text.into());
                        }
                    }) as Box<dyn FnMut(_)>);

                    reader_rc.set_onload(Some(onload.as_ref().unchecked_ref()));
                    reader_rc.read_as_text(&file).unwrap();
                    onload.forget();
                }
            }
    }) as Box<dyn FnMut(_)>);

    input.set_onchange(Some(closure.as_ref().unchecked_ref()));
    document.body().unwrap().append_child(&input).unwrap();
    input.click();
    closure.forget();
    }
}

impl MyApp {
    #[cfg(target_arch = "wasm32")]
    fn save_as_pbm_web(&self) {
        use wasm_bindgen::JsCast;
        use web_sys::{Blob, Url, HtmlAnchorElement};

        // Convert maze to PBM string
        let mut pbm = format!("P1\n{} {}\n", self.cols, self.rows);
        for row in &self.maze {
            for cell in row {
                let bit = match *cell {
                    Cell::Wall => 1,
                    _ => 0,
                };
                pbm.push_str(&format!("{} ", bit));
            }
            pbm.push('\n');
        }

        let array = js_sys::Array::new();
        array.push(&wasm_bindgen::JsValue::from_str(&pbm));

        let blob = Blob::new_with_str_sequence(&array).unwrap();
        let url = Url::create_object_url_with_blob(&blob).unwrap();

        let document = web_sys::window().unwrap().document().unwrap();
        let a = document
            .create_element("a")
            .unwrap()
            .dyn_into::<HtmlAnchorElement>()
            .unwrap();
        a.set_href(&url);
        a.set_download("maze.pbm");
        a.click();

        Url::revoke_object_url(&url).unwrap();
    }
}


impl MyApp {
    fn auto_fit_to_window(& mut self, available: egui::Vec2) {
        if self.auto_fit {
            let new_size_x = available.x / self.cols as f32;
            let new_size_y = available.y / self.rows as f32;
            self.target_cell_size = new_size_x.min(new_size_y).clamp(5.0, 100.0);
        }
    }
}

impl MyApp {
    fn invert_maze(&mut self) {
        for row in &mut self.maze {
            for cell in row {
                *cell = match * cell {
                    Cell::Wall => Cell::Empty,
                    Cell::Empty => Cell::Wall,
                };
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
                        // Desktop only
                        #[cfg(not(target_arch = "wasm32"))]
                        {
                            if ui.button("Quit").clicked() {
                                ctx.send_viewport_cmd(egui::ViewportCommand::Close);
                            }
                            ui.add_space(16.0);
                            if ui.button("Open File").clicked() {
                                self.open_file();
                            }

                            if ui.button("Save File").clicked()
                               &&  let Some(path) = FileDialog::new()
                                    .set_directory("assets")
                                    .add_filter("PBM", &["pbm"])
                                    .save_file()
                                 && let Err(err) = self.save_as_pbm(&path) {
                                        eprintln!("Failed to save PBM: {}", err);
                            }
                        }
                    } else {
                        // Web only
                        #[cfg(target_arch = "wasm32")]
                        {
                            if ui.button("Open File").clicked() {
                                self.open_file_web();
                            }

                            if ui.button("Save File").clicked() {
                                self.save_as_pbm_web();
                            }
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
                    ui.add(egui::DragValue::new(&mut self.start.x).range(0..=u32::MAX).speed(1));
                    ui.add(egui::DragValue::new(&mut self.start.y).range(0..=u32::MAX).speed(1));

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
                    ui.add(egui::DragValue::new(&mut self.end.x).range(0..=u32::MAX).speed(1));
                    ui.add(egui::DragValue::new(&mut self.end.y).range(0..=u32::MAX).speed(1));

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

            ui.group(|ui| {
                ui.label("Window Fit");
                ui.horizontal(|ui| {
                    if ui.button("Fit to window").clicked() {
                        let new_size_x = self.last_canvas_size.x / self.cols as f32;
                        let new_size_y = self.last_canvas_size.y / self.rows as f32;
                        self.cell_size = new_size_x.min(new_size_y).clamp(5.0, 100.0);
                    }

                    ui.checkbox(&mut self.auto_fit, "Auto-fit to window");
                });
            });

            ui.group(|ui| {
                ui.label("Solving options");
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

            });

            ui.group(|ui| {
                ui.label("Solve");
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

            ui.separator();
            ui.heading("Editing");

            let draw_active = self.edit_mode == EditMode::DrawWall;
            let erase_active = self.edit_mode == EditMode::EraseWall;

            ui.horizontal(|ui| {
                let draw_color = if draw_active {
                    active_color
                } else {
                    inactive_color
                };
                if ui.add(egui::Button::new("Draw Wall").fill(draw_color)).clicked() {
                    self.edit_mode = if draw_active { EditMode::None } else { EditMode::DrawWall };
                }

                let erase_color = if erase_active {
                    active_color
                } else {
                    inactive_color
                };
                if ui.add(egui::Button::new("Erase Wall").fill(erase_color)).clicked() {
                    self.edit_mode = if erase_active { EditMode::None } else { EditMode::EraseWall } ;
                }
            });

            ui.separator();
            ui.horizontal(|ui| {
                if ui.button("Fill Walls").clicked(){
                    for row in 0..self.rows {
                        for col in 0..self.cols {
                            self.maze[row][col] = Cell::Wall;
                        }
                    }
                }

                if ui.button("Clear Maze").clicked() {
                    for row in 0..self.rows {
                        for col in 0..self.cols {
                            self.maze[row][col] = Cell::Empty;
                        }
                    }
                }
            });

            ui.separator();
            ui.horizontal(|ui| {
                if ui.button("Add Row Walls").clicked() {
                    self.rows += 1;
                    let new_row = vec![Cell::Wall; self.cols];
                    self.maze.push(new_row);
                    self.auto_fit_to_window(self.last_canvas_size);
                }

                if ui.button("Add Column Walls").clicked() {
                    self.cols += 1;
                    for row in &mut self.maze {
                        row.push(Cell::Wall);
                    }
                    self.auto_fit_to_window(self.last_canvas_size);
                }
            });
            ui.horizontal(|ui| {
                if ui.button("Add Empty Row").clicked() {
                    self.rows += 1;
                    let new_row = vec![Cell::Empty; self.cols];
                    self.maze.push(new_row);
                    self.auto_fit_to_window(self.last_canvas_size);
                }

                if ui.button("Add Empty Column").clicked() {
                    self.cols += 1;
                    for row in &mut self.maze {
                        row.push(Cell::Empty);
                    }
                    self.auto_fit_to_window(self.last_canvas_size);
                }
            });

            ui.horizontal(|ui| {
                if ui.button("Remove Row").clicked() && self.rows > 1 {
                    self.rows -= 1;
                    self.maze.pop();
                    self.auto_fit_to_window(self.last_canvas_size);
                }

                if ui.button("Remove Column").clicked() && self.cols > 1 {
                    self.cols -= 1;
                    for row in &mut self.maze {
                        row.pop();
                    }
                    self.auto_fit_to_window(self.last_canvas_size);
                }
            });

            ui.separator();
            if ui.button("Invert Maze").clicked() {
                self.invert_maze();
            }
        });

        egui::CentralPanel::default().show(ctx, |ui| {
            let available = ui.available_size();

            // Auto-fit logic
            if self.auto_fit && available != self.last_canvas_size {
                let new_size_x = available.x / self.cols as f32;
                let new_size_y = available.y / self.rows as f32;
                self.target_cell_size= new_size_x.min(new_size_y).clamp(5.0, 100.0);
            }
            self.last_canvas_size = available;

            // Smooth transition
            // Might delete later; todo so: change target_cell_size -> cell_size
            self.cell_size = egui::lerp(self.cell_size..=self.target_cell_size, 0.3);

            // Compute maze pixel size
            let maze_width = self.cols as f32 * self.cell_size;
            let maze_height = self.rows as f32 * self.cell_size;

            // Center the maze if there is extra space
            let offset_x = (available.x - maze_width).max(0.0) / 2.0;
            let offset_y = (available.y - maze_height).max(0.0) / 2.0;

            // Start drawing from the top-left corner of the available region
            let origin = ui.min_rect().min + egui::vec2(offset_x, offset_y);

            // Maze size
            let maze_rect = egui::Rect::from_min_size(origin, egui::vec2(maze_width, maze_height));

            // Handle maze clicks
            let response = ui.allocate_rect(maze_rect, egui::Sense::click_and_drag());

            // Painter the canvas
            let painter = ui.painter_at(maze_rect);

            // Handle mouse click for wall editing
            if let Some(pos) = response.interact_pointer_pos() && maze_rect.contains(pos) {
                let col = ((pos.x - origin.x) / self.cell_size).floor() as usize;
                let row = ((pos.y - origin.y) / self.cell_size).floor() as usize;

                if row < self.rows && col < self.cols {
                    match self.edit_mode {
                        EditMode::DrawWall => {
                            self.maze[row][col] = Cell::Wall;
                        }
                        EditMode::EraseWall => {
                            self.maze[row][col] = Cell::Empty;
                        }
                        _ => {}
                    }
                }
            }

            for row in 0..self.rows {
                for col in 0..self.cols {
                    let x = origin.x + col as f32 * self.cell_size;
                    let y = origin.y + row as f32 * self.cell_size;
                    let cell_rect = egui::Rect::from_min_size(
                        egui::pos2(x, y),
                        egui::vec2(self.cell_size, self.cell_size),
                    );

                    // Determine color based on coordinates
                    let color = if row as u32 == self.start.y && col as u32 == self.start.x {
                        egui::Color32::BLUE
                    } else if row as u32 == self.end.y && col as u32 == self.end.x {
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

            // Handle picking start/end with mouse
            if let Some(pos) = response.interact_pointer_pos()  && response.clicked()
                    && maze_rect.contains(pos) {

                let col = ((pos.x - origin.x) / self.cell_size).floor() as u32;
                let row = ((pos.y - origin.y) / self.cell_size).floor() as u32;

                match self.pick_mode {
                    PickMode::PickingStart => {
                        self.start.x = col;
                        self.start.y = row;
                        self.pick_mode = PickMode::None;
                    }
                    PickMode::PickingEnd => {
                        self.end.x = col;
                        self.end.y = row;
                        self.pick_mode = PickMode::None;
                    }
                    PickMode::None => {}
                }
            }
        });
    }
}

