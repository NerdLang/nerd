// Define
const size = 256
const matrices = [[], [], []]

// Generate
for (let y = 0; y < size; y++) {
  matrices[0].push([])
  matrices[1].push([])
  for (let x = 0; x < size; x++) {
    matrices[0][y].push(Math.random())
    matrices[1][y].push(Math.random())
  }
}

// Multiply
for (let y = 0; y < size; y++) {
  matrices[2].push([])
  for (let x = 0; x < size; x++) {
    matrices[2][y][x] = matrices[0][y][x] * matrices[1][y][x]
  }
}

/*
// Normalize
for (let y = 0; y < size; y++) {
  for (let x = 0; x < size; x++) {
	matrix[y][x] = (
		(y && matrix[y - 1][x]) +
		(x && matrix[y][x - 1]) +
		((size - y - 1) && matrix[y + 1][x]) +
		((size - x - 1) && matrix[y][x + 1]) +
		matrix[y][x]
	) / 5
  }
}

// Visualize (why not?)
const pattern = "█▓▒░ "
for (let y = 0; y < size; y++) {
  let line = '';
  for (let x = 0; x < size; x++) {
	line += pattern[Math.floor(matrix[y][x] * (pattern.length - 1))]
  }
  console.log(line)
}
 */
