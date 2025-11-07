/* use web_sys::window;

fn main() {
    console_error_panic_hook::set_once();

    let document = window()
        .and_then(|win| win.document())
        .expect("Could not access the document");
    let body = document.body().expect("Could not access document.body");
    let text_node = document.create_text_node("Hello, world from Vanilla Rust!");
    body.append_child(text_node.as_ref())
        .expect("Failed to append text");
}
*/

use eframe::egui;
use wasm_bindgen::JsCast;
use console_error_panic_hook;
use web_sys;
use wasm_bindgen_futures;

#[cfg(target_arch = "wasm32")]
fn main() {
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
                canvas, // ✅ pass the actual canvas element
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
        viewport: egui::ViewportBuilder::default().with_inner_size([320.0, 240.0]),
        ..Default::default()
    };
    eframe::run_native(
        "My egui App",
        options,
        Box::new(|cc| {
            egui_extras::install_image_loaders(&cc.egui_ctx);
            Ok(Box::<MyApp>::default())
        }),
    )
}

struct MyApp {
    name: String,
    age: u32,
}

impl Default for MyApp {
    fn default() -> Self {
        Self {
            name: "Arthur".to_owned(),
            age: 42,
        }
    }
}

impl eframe::App for MyApp {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.heading("My egui Application");
            ui.horizontal(|ui| {
                let name_label = ui.label("Your name: ");
                ui.text_edit_singleline(&mut self.name)
                    .labelled_by(name_label.id);
            });
            ui.add(egui::Slider::new(&mut self.age, 0..=120).text("age"));
            if ui.button("Increment").clicked() {
                self.age += 1;
            }
            ui.label(format!("Hello '{}', age {}", self.name, self.age));
        });
    }
}

