
  var a = 1;
  var b = 0;
  var c = 0;
  var n = 45;
  while (n > 0) {
    c = a;
    a = b + a;
    b = c;
    n--;
  }
  console.log(b);

