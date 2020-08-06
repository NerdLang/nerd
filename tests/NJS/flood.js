/*** From @HighCo on Discord ***/
// nectar --stack 10000000 flood.js
 
var size = 150;
var iterations = 1;

function to_index(x, y) {
    return y * size + x;
}
function flood_cell(grid, x, y, value) {
    var index = to_index(x, y);
    grid[index] = value;
    value++;
    console.log("flood_cell "+x+" "+y+" -> "+grid[index]);

    index = to_index(x - 1, y);
    if (x > 0 && grid[index] == 0)
        value = flood_cell(grid, x - 1, y, value);

    index = to_index(x + 1, y);
    if (x < size - 1 && grid[index] == 0)
        value = flood_cell(grid, x + 1, y, value);

    index = to_index(x, y - 1);
    if (y > 0 && grid[index] == 0)
        value = flood_cell(grid, x, y - 1, value);
    
    index = to_index(x, y + 1);
    if (y < size - 1 && grid[index] == 0)
        value = flood_cell(grid, x, y + 1, value);

    return value;
}
function flood_grid() {
    console.log("flood_grid");
    var grid = [];
    var i = 0;
    for (let y = 0; y < size; y++) {
        for (let x = 0; x < size; x++) {
            let value = x % 2 == 0 && y % 2 == 0 ? -1 : 0;
            grid[i] = value;
            i++;
        }
    }
    flood_cell(grid, size / 2, size / 2, 1);
    return grid;
}
function flood() {
    let sum = 0;
    for (let i = 0; i < iterations; i++) {
        let grid = flood_grid();
        let index = grid.length - 1;
        sum += grid[index];
    }
    console.log("sum: " + sum);
}
flood();