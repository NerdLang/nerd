/*
	Vector proposed by @wesley1989 on Discord to test classes implementation
*/
class Vector {
  constructor(x,y){
    this.x = x | 0
    this.y = y | 0
  }

  add(n){
    this.x+=n
    this.y+=n
  }

  copy(vec){
    if(vec && (vec instanceof Vector)){
      this.x = vec.x
      this.y = vec.y
    }
  }
}
var vec = new Vector()
console.log(vec);
vec = new Vector(8,9)
console.log(vec);
vec.add(4)
console.log(vec);
var vec2 = new Vector()
vec.copy(vec2)
console.log(vec);