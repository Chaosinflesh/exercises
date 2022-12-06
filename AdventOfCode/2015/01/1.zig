const std = @import("std");

pub fn main() !void {
    // input/output
    const stdout = std.io.getStdOut().writer();
    const stdin = std.io.getStdIn().reader();

    // Vars. Direction 0 = north, +1 -> clockwise, -1 -> anti-clockwise.
    var x: i32 = 0;
    var y: i32 = 0;
    var direction: u2 = 0;

    // B: TODO: set this up correctly.
    //var map = std.StringHashMap(void).init();
    //var b: string = undefined;
    
    var buffer: [1024]u8 = undefined;
    while (try stdin.readUntilDelimiterOrEof(&buffer, ',')) |read| {
        var line = std.mem.trim(u8, read, " ");
        line = std.mem.trim(u8, line, "\n");
        //try stdout.print("Read: '{s}'\n", .{line});
        if (line[0] == 'R') {
            direction +%= 1;
        } else {
            direction -%= 1;
        }
        var offset: i32 = (try std.fmt.parseInt(i32, line[1..], 10));
        switch (direction) {
            0 => y -= offset,
            1 => x += offset,
            2 => y += offset,
            3 => x -= offset
        }

        // TODO: check for multiple visits here.
    }
    try stdout.print("{}N + {}E = {}\n", .{y, x, y + x});
}


fn readLine(reader) []u8 {

}