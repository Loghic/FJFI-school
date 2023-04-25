#include <iostream>
#include <fstream>
#include <cassert>
// #include <assert.h>

#undef UNICODE
// #include <windows.h>
#include <sys/syslimits.h>

using namespace std;

struct Item
{
    int key = 0;
    int height = 1;
    Item* left = nullptr;
    Item* right = nullptr;
};

Item* find(Item* top, int value)
{
    Item* p = top;
    while (p != nullptr && p->key != value)
    {
        if (value < p->key)
            p = p->left;
        else
            p = p->right;
    }
    // p == nullptr || p->key == value;
    return p;
}

inline int h(Item* p)
{
    if (p == nullptr){
        return 0;
    }else{
        return p->height;
    }
}

void update (Item* p)
{
    int L = h(p->left);
    int R = h(p->right);
    if (L > R){
        p->height = L + 1;
    }else{
        p->height = R + 1;
    }
}

void insert (Item * & p, int value)
{
    if (p == nullptr)
    {
        p = new Item;
        p->key = value;
        // p->height = 1;
        p->left = nullptr;
        p->right = nullptr;
    }
    else if (p->key == value)
    {
        // jiz je ve stromu
    }
    else if (value < p->key)
    {
        insert(p->left, value);
    }
    else
    {
        insert(p->right, value);
    }

    
    Item * a = p;
    int L = h(a->left);
    int R = h(a->right);
    if (L > R + 1) {
        Item* b = a->left;
        if (h(b->left) > h(b->right)) {
            Item* c = b->left;
            Item* t = b->right;
            p = b;
            b->right = a;
            a->left = t;
            update(a);
        }
        else {
            Item* c = b->right;
            Item* s = c->left;
            Item* t = c->right;
            p = c;
            c->left = b;
            c->right = a;
            b->right = s;
            a->left = t;
            update(a);
            update(b);
        }
    }
    else if (L + 1 < R) {
        Item* b = a->right;
        if (h(b->right) > h(b->left)) {
            Item* c = b->right;
            Item* t = b->left;
            p = b;
            b->left = a;
            a->right = t;
            update(a);
        }
        else {
            Item* c = b->left;
            Item* s = c->right;
            Item* t = c->left;
            p = c;
            c->right = b;
            c->left = a;
            b->left = s;
            a->right = t;
            update(a);
            update(b);
        }
    }
    update (p);

}

/* ---------------------------------------------------------------------- */

void writeNode (ofstream& f, Item* p, int x, int y, int sx, int sy)
{
    if (p != nullptr)
    {
        f << "        var v" << p->key << " = graph.insertVertex (parent, null, '" << p->key << "', "
            << x << ", " << y << ", 80, 30);" << endl;

        if (p->left != nullptr)
        {
            writeNode(f, p->left, x - sx, y + sy, sx / 2, sy);
            f << "        graph.insertEdge (parent, null, '', v" << p->key << ", v" << p->left->key << ");" << endl;
        }
        if (p->right != nullptr)
        {
            writeNode(f, p->right, x + sx, y + sy, sx / 2, sy);
            f << "        graph.insertEdge (parent, null, '', v" << p->key << ", v" << p->right->key << ");" << endl;
        }
    }
}

void writeHtml (string fileName, Item* p)
{
    ofstream f (fileName);

    f << R"...(
    <html>
    <head>
    <title>Tree with mxGraph</title>
    <script type="text/javascript">
    mxBasePath = 'http://jgraph.github.io/mxgraph/javascript/src';
    </script>
    <script type="text/javascript" src="http://jgraph.github.io/mxgraph/javascript/src/js/mxClient.js"></script>
    <script type="text/javascript">

    function start (container)
    {
        var graph = new mxGraph(container);
        var parent = graph.getDefaultParent();
        graph.getModel().beginUpdate();
    )..." << endl;

    /*
    f << "    var v1 = graph.insertVertex (parent, null, 'a', 0, 0, 80, 30);" << endl;
    f << "    var v2 = graph.insertVertex (parent, null, 'b', 0, 0, 80, 30);" << endl;
    f << "    var e1 = graph.insertEdge (parent, null, '', v1, v2);" << endl;
    */

    if (p != nullptr)
    {
        writeNode(f, p, 400, 0, 200, 80);
    }

    f << R"...(
        graph.getModel().endUpdate();
    };
    </script>
    </head>
    <body onload="start(document.getElementById('graphContainer'))">
    <div id="graphContainer">
    </div>
    </body>
    </html>
    )...";

    f.close();


    /* toto je jen automaticky spusteni na internetu*/
    /*spousti se pres file:///neco neco atd/FJFI-school/ZALG/cv/cv10/output.html v mem pripade meni se jen absolutni cesta */ 
    /* pozn. staci napsat file:/Users a proklikat se k souboru, ktery chci pouzit napr: output.html*/

    // char path[PATH_MAX];
    // GetCurrentDirectory(PATH_MAX, path);
    // fileName = string("file:///") + path + "/" + fileName;

    // string cmd = "\"C:/Program Files/Mozilla Firefox/firefox\" " + fileName;
    // // string cmd = "\"C:/Program Files/Mozilla Firefox/firefox\" file:///C:/Users/culikzde/source/repos/zalg-ct-2023/avl/" + fileName;
    // system(cmd.c_str());
}

/* ---------------------------------------------------------------------- */

Item* root = nullptr;

int main()
{
    // insert(root, 7);
    // insert(root, 10);
    // insert(root, 4);
    // insert(root, 3);
    // insert(root, 2);
    // insert(root, 1);
    insert(root, 5);
    insert(root, 6);
    insert(root, 7);
    insert(root, 9);
    insert(root, 8);
    writeHtml("output.html", root);

    cout << "O.K." << endl;
}

