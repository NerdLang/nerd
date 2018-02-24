export const sum = (...nums) => nums.reduce((a, b) => a + b);

export function* fibonacci() {
  let [current, next] = [0, 1];

  while (true) {
    yield [current, next];

    [current, next] = [next, current + next];
  }
}
