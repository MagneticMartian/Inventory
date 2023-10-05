const std = @import("std");
const ArrayList = std.ArrayList;
const expect = std.testing.expect;
const test_allocator = std.testing.allocator;
const eql = std.mem.eql;

const entity = struct {
    Name: []const u8,
    Date: []const u8,
};
const m5Data = struct {
    propNum: []const u8,
    decription: []const u8,
    serialNum: []const u8,
    sourceLoc: []const u8,
    destLoc: []const u8,
    sourceSign: entity,
    destSign: entity,
};

var alM5List = ArrayList(m5Data).init(
    test_allocator,
);

fn TrackNewLoc(m5d: m5Data) !void {
    try alM5List.append(m5d);
}

test "test-suit" {
    defer alM5List.deinit();
    var m5d: m5Data = undefined;
    m5d.sourceSign = .{
        .Name = "Tried",
        .Date = "Today",
    };
    try TrackNewLoc(m5d);
    const val = alM5List.pop();
    try expect(eql(u8, val.sourceSign.Name, "Tried"));
}
