function fibonacci(n)
{
  if (n < 2)  return n;
  return fibonacci(n - 2) + fibonacci(n - 1);
}
console.log(fibonacci(45));