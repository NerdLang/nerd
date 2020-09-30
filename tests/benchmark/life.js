// Define
const size = 128
const generations = 1024
const grid = []

// Generate
for (let y = 0; y < size; y++) {
  grid.push([])
  for (let x = 0; x < size; x++) {
    grid[y].push(Math.round(Math.random()))
  }
}

// Iterate
for (let g = 0; g < generations; g++) {
  for (let y = 0; y < size; y++) {
    for (let x = 0; x < size; x++) {
      const n = ((x + 1 < size) ? grid[y][x + 1] : 0)
        + ((y + 1 < size) ? grid[y + 1][x] : 0)
        + (y ? grid[y - 1][x] : 0)
        + (x ? grid[y][x - 1] : 0)
        + ((y + 1 < size && x + 1 < size) ? grid[y + 1][x + 1] : 0)
        + ((y && x + 1 < size) ? grid[y - 1][x + 1] : 0)
        + ((y && x) ? grid[y - 1][x - 1] : 0)
        + ((x && y + 1 < size) ? grid[y + 1][x - 1] : 0)
      grid[y][x] = (((n & 2) >> 1) && (grid[y][x] || (n == 3))) | 0
    }
  }
}

// Display
const pattern = " █"
for (let y = 0; y < size; y++) {
  let line = '';
  for (let x = 0; x < size; x++) {
    line += pattern[grid[y][x]]
  }
  console.log(line)
}