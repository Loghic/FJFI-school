const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const lesson = b.option([]const u8, "lesson", "Lesson directory")
        orelse "hodina1";

    const source_dir = lesson;

    // Replace "/" with "-" for executable name
    const project_name = std.mem.replaceOwned(
        u8,
        b.allocator,
        lesson,
        "/",
        "-",
    ) catch unreachable;
    defer b.allocator.free(project_name);

    // ✅ Zig 0.15.x style executable creation
    const exe = b.addExecutable(.{
        .name = project_name,
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
        }),
    });

    const has_cpp = addSourceFiles(b, exe, source_dir) catch |err| {
        std.debug.print("Error adding files: {}\n", .{err});
        return;
    };

    if (has_cpp) {
        exe.linkLibCpp();
    } else {
        exe.linkLibC();
    }

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the application");
    run_step.dependOn(&run_cmd.step);
}


// Recursively add all C/C++ files
fn addSourceFiles(
    b: *std.Build,
    exe: *std.Build.Step.Compile,
    dir_path: []const u8,
) !bool {
    var dir = try std.fs.cwd().openDir(dir_path, .{ .iterate = true });
    defer dir.close();

    var walker = try dir.walk(b.allocator);
    defer walker.deinit();

    var has_cpp_files = false;

    std.debug.print("Searching in: {s}\n", .{dir_path});

    while (try walker.next()) |entry| {
        if (entry.kind != .file) continue;

        const ext = std.fs.path.extension(entry.basename);

        const is_c =
            std.mem.eql(u8, ext, ".c");

        const is_cpp =
            std.mem.eql(u8, ext, ".cpp") or
            std.mem.eql(u8, ext, ".cc") or
            std.mem.eql(u8, ext, ".cxx");

        if (!is_c and !is_cpp) continue;

        if (is_cpp) has_cpp_files = true;

        const full_path = try std.fs.path.join(
            b.allocator,
            &[_][]const u8{ dir_path, entry.path },
        );

        const std_flag = if (is_cpp) "-std=c++23" else "-std=c11";

        exe.addCSourceFile(.{
            .file = b.path(full_path),
            .flags = &[_][]const u8{
                "-Wall",
                "-Wextra",
                std_flag,
            },
        });

        std.debug.print("  Adding: {s}\n", .{full_path});
    }

    return has_cpp_files;
}
