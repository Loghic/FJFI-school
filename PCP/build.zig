const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    // Optional parameter to select lesson/project
    const lesson = b.option([]const u8, "lesson", "Lesson number") orelse "hodina1";
    const source_dir = lesson;
    const project_name = lesson;

    // Create executable (Zig 0.15.x)
    const exe = b.addExecutable(.{
        .name = project_name,
        .root_module = b.addModule("root", .{
            .target = target,
            .optimize = optimize,
        }),
    });

    // Add all .c/.cpp files from directory
    const has_cpp = addSourceFiles(b, exe, source_dir) catch |err| {
        std.debug.print("Error adding files: {}\n", .{err});
        return;
    };

    // Link with appropriate libraries
    if (has_cpp) {
        exe.linkLibCpp(); // For C++ files
    } else {
        exe.linkLibC(); // For C files only
    }

    // Install the resulting binary
    b.installArtifact(exe);

    // Add "run" step for execution
    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the application");
    run_step.dependOn(&run_cmd.step);
}

// Function to recursively add all source files
// Returns true if any C++ files were found
fn addSourceFiles(
    b: *std.Build,
    exe: *std.Build.Step.Compile,
    dir_path: []const u8,
) !bool {
    var dir = try std.fs.cwd().openDir(dir_path, .{ .iterate = true });
    defer dir.close();

    var walker = try dir.walk(b.allocator);
    defer walker.deinit();

    // Zig 0.15.x: Use .{} initialization syntax
    var source_files: std.ArrayList([]const u8) = .{};
    defer source_files.deinit(b.allocator);

    var has_cpp_files = false;

    std.debug.print("Searching for files in: {s}\n", .{dir_path});

    while (try walker.next()) |entry| {
        if (entry.kind == .file) {
            const ext = std.fs.path.extension(entry.basename);

            // Check for supported extensions
            if (std.mem.eql(u8, ext, ".c") or
                std.mem.eql(u8, ext, ".cpp") or
                std.mem.eql(u8, ext, ".cc") or
                std.mem.eql(u8, ext, ".cxx"))
            {
                // Track if we have any C++ files
                if (std.mem.eql(u8, ext, ".cpp") or
                    std.mem.eql(u8, ext, ".cc") or
                    std.mem.eql(u8, ext, ".cxx"))
                {
                    has_cpp_files = true;
                }

                const full_path = try std.fs.path.join(
                    b.allocator,
                    &[_][]const u8{ dir_path, entry.path },
                );
                try source_files.append(b.allocator, full_path);
                std.debug.print("  Adding: {s}\n", .{full_path});
            }
        }
    }

    if (source_files.items.len == 0) {
        std.debug.print("WARNING: No source files found in {s}\n", .{dir_path});
        return error.NoSourceFiles;
    }

    // Add all found files
    for (source_files.items) |file| {
        const ext = std.fs.path.extension(file);

        // Determine if C or C++ based on extension
        const is_cpp = std.mem.eql(u8, ext, ".cpp") or
                       std.mem.eql(u8, ext, ".cc") or
                       std.mem.eql(u8, ext, ".cxx");

        const std_flag = if (is_cpp) "-std=c++17" else "-std=c11";

        exe.addCSourceFile(.{
            .file = b.path(file),
            .flags = &[_][]const u8{
                "-Wall",
                "-Wextra",
                std_flag,
            },
        });
    }

    std.debug.print("Total files to build: {}\n", .{source_files.items.len});

    return has_cpp_files;
}
