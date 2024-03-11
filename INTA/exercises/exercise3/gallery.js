var root = document.body;
var data = [];

// komponenta pro zobrazení přehledu všech obrázků
var Gallery = {
    view: function() {
        console.log("Gallery.view");
        return m("main", {class: "gallery-view"},
            [
                m("h1", "Pet Gallery"),
                m("p", data.length + " images"),
                m("section", 
                {id: "gallery-container"}, 
                [
                    m("a", {href: "#!/image/0"},
                        m("img", {src: data[0]})
                    )
                ]),
            ]
        );
    }
}

// komponenta pro zobrazení jednoho obrázku
var Image = {
    view: function(index) {
        return m("p", "Image index " + index)
    }
}

m.route(root, "/gallery", {
    "/gallery": Gallery,
    "/image/:index": Image,
})

// obnovení UI po kompletním načtení dat
window.onload = (event) => {
    console.log("window.onload");
    m.redraw();
};