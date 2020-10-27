// Define
const size = 1e6
const list = []

// Fill
for (let i = 0; i < size; i++) {
  list.push((Math.random() * 2147483647) | 0)
}

// Sort
const sorted = list.sort(function (a, b) {
  return Math.clz32(b) - Math.clz32(a)
})

/*
// Visualize
console.log(list)
*/
