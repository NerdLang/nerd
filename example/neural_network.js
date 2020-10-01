/*
	Neural Network example by @wesley1989
*/

function sigmoid(x) {
  return 1 / (1 + Math.exp(-x));
}
function derivativeOfSigmoid(y){  

  return y * (1 - y); 
}

  class Matrix {
    constructor(rows, cols) {  
      this.rows = rows;
      this.cols = cols;
      this.data = [];
      for (let i = 0; i < this.rows; i++) {
          this.data[i] = [];
        for (let j = 0; j < this.cols; j++) {
          this.data[i][j] = (Math.random() * 2) - 1; 
        }
      }           
    }
    copy() {
      let m = new Matrix(this.rows, this.cols);
      for (let i = 0; i < this.rows; i++) {
        for (let j = 0; j < this.cols; j++) {
          m.data[i][j] = this.data[i][j];
        }
      }
      return m;
    }

    static transpose(matrix) {
      let result = new Matrix(matrix.cols, matrix.rows);
      for (let i = 0; i < matrix.rows; i++) {
        for (let j = 0; j < matrix.cols; j++) {
          result.data[j][i] = matrix.data[i][j];
        }
      }
      return result;
    }
  
    static multiply(a, b) {
      if (a.cols !== b.rows) {
        return undefined;
      } 
      let result = new Matrix(a.rows, b.cols); 
      for (let i = 0; i < result.rows; i++) {
        for (let j = 0; j < result.cols; j++) {
          let sum = 0;
          for (let k = 0; k < a.cols; k++) {
  
            sum += a.data[i][k] * b.data[k][j];
          }
            result.data[i][j] = sum;
        }
      }
       return result;
    }

    static fromArray(arr) {
      let m = new Matrix(arr.length, 1);
      for (let i = 0; i < arr.length; i++) {
        m.data[i][0] = arr[i];
      }
      return m;
    }
  
    static subtract(a, b) {
      let result = new Matrix(a.rows, a.cols);
      for (let i = 0; i < result.rows; i++) {
        for (let j = 0; j < result.cols; j++) {
          result.data[i][j] = a.data[i][j] - b.data[i][j];
        }
      }
      return result;
    }
    
    static map(matrix, activation) {
      let result = new Matrix(matrix.rows, matrix.cols);
      for (let i = 0; i < matrix.rows; i++) {
        for (let j = 0; j < matrix.cols; j++) {
          result.data[i][j] = activation(matrix.data[i][j]);
        }
      }
      return result;
    }
  
    toArray() {
      let arr = [];
      for (let i = 0; i < this.rows; i++) {
        for (let j = 0; j < this.cols; j++) {
          arr.push(this.data[i][j]);
        }
      }
      return arr;
    }
    
    add(n) {
      if (n instanceof Matrix) {
        for (let i = 0; i < this.rows; i++) {
          for (let j = 0; j < this.cols; j++) {
            this.data[i][j] += n.data[i][j];
          }
        }
      } else {
        for (let i = 0; i < this.rows; i++) {
          for (let j = 0; j < this.cols; j++) {
            this.data[i][j] += n;
          }
        }
      }
    }
  
  
    multiply(n) {  
      if (n instanceof Matrix) {
        for (let i = 0; i < this.rows; i++) {
          for (let j = 0; j < this.cols; j++) {
            this.data[i][j] *= n.data[i][j];
          }
        }
      } else {
        for (let i = 0; i < this.rows; i++) {
          for (let j = 0; j <  this.cols; j++) {
            this.data[i][j] *= n;
          }
        }
      }
    }

    map(otherFunction) {
      for (let i = 0; i < this.rows; i++) {
        for (let j = 0; j < this.cols; j++) {
          this.data[i][j] = otherFunction(this.data[i][j]);
        }
      }
    }
  }


class NeuralNetwork {

  //a length of input
  //b length of output
  constructor(a, b) {
    if (a instanceof NeuralNetwork) { 
      //copying neural network
      this.input_nodes = a.input_nodes;
      this.output_nodes = a.output_nodes;
      this.hidden_nodes = a.hidden_nodes;
      this.weights_1 = a.weights_1.copy();
      this.weights_2 = a.weights_2.copy();
      this.bias_1 = a.bias_1.copy();
      this.bias_2 = a.bias_2.copy();   
      this.learning_rate=a.learning_rate;
    } else {
      this.input_nodes = a;
      this.output_nodes = b;
      // weights = (input length + output length) times 2 
      // for a better nn training
      this.hidden_nodes = (a + b) * 2;
      this.weights_1 = new Matrix(this.hidden_nodes, this.input_nodes);
      this.weights_2 = new Matrix(this.output_nodes, this.hidden_nodes); 
      this.bias_1 = new Matrix(this.hidden_nodes, 1);
      this.bias_2 = new Matrix(this.output_nodes, 1);
      this.learning_rate = 0.9;  
    }  

  }



  feed_forward(inputs) {
    let inputs_from = Matrix.fromArray(inputs);
    let hidden = Matrix.multiply(this.weights_1, inputs_from);
    hidden.add(this.bias_1);
    hidden.map(sigmoid);
    let output = Matrix.multiply(this.weights_2, hidden);
    output.add(this.bias_2);
    output.map(sigmoid);
    return output.toArray();
  }

  // feedforward with backpropagation
  train(input_array, target_array) {  
    let inputs = Matrix.fromArray(input_array);

    let hidden = Matrix.multiply(this.weights_1, inputs);  
    hidden.add(this.bias_1);
    hidden.map(sigmoid);
    
    let outputs = Matrix.multiply(this.weights_2, hidden);
    outputs.add(this.bias_2);
    outputs.map(sigmoid); 

    
    let targets = Matrix.fromArray(target_array);
    let output_errors = Matrix.subtract(targets, outputs);

    let gradients = Matrix.map(outputs,derivativeOfSigmoid);
    gradients.multiply(output_errors);
    gradients.multiply(this.learning_rate);
  
    let hidden_T = Matrix.transpose(hidden);
    let weight_ho_deltas = Matrix.multiply(gradients, hidden_T);

    this.weights_2.add(weight_ho_deltas);
    this.bias_2.add(gradients);

  
    let who_t = Matrix.transpose(this.weights_2);
    let hidden_errors = Matrix.multiply(who_t, output_errors);
    
    
    let hidden_gradient = Matrix.map(hidden,derivativeOfSigmoid);
    hidden_gradient.multiply(hidden_errors);
    hidden_gradient.multiply(this.learning_rate);

    let inputs_T = Matrix.transpose(inputs);
    let weight_ih_deltas = Matrix.multiply(hidden_gradient, inputs_T);

    this.weights_1.add(weight_ih_deltas);
    this.bias_1.add(hidden_gradient);
      
  }

  copy() {
    return new NeuralNetwork(this);
  }
 
  mutate(func) {
    this.weights_1.map(func);
    this.weights_2.map(func);
    this.bias_1.map(func);
    this.bias_2.map(func);
  }

}



function shuffle(a) {
  var j, x, i;
  for (i = a.length - 1; i > 0; i--) {
      j = Math.floor(Math.random() * (i + 1));
      x = a[i];
      a[i] = a[j];
      a[j] = x;
  }
  return a;
  }

// XOR example
// NeuralNetwork takes as params 
// input and output length
// 2 inputs and 1 output

var NN = new NeuralNetwork(2, 1);

var defined_data = [
  {
  input:[0,0],
  output:[0]
  },
 {
  input:[0,1],
  output:[1]
},
{
  input:[1,0],
  output:[1]
},
{
  input:[1,1],
  output:[0]
},
]


for (let i = 0; i < 500; i++) {
	var shuffled = shuffle(defined_data)
    for (let j = 0; j < defined_data.length; j++) {
      NN.train(shuffled[j].input,shuffled[j].output)
    }
}

console.log("[1,0] => ", NN.feed_forward([1,0])) //[ 0.973527677207338 ]
console.log("[0,1] => ", NN.feed_forward([0,1])) //[ 0.9829688288812666 ]
console.log("[1,1] => ", NN.feed_forward([1,1])) //[ 0.025380822747380676 ]
console.log("[0,0] => ", NN.feed_forward([0,0])) //[ 0.01929245473990312 ]


