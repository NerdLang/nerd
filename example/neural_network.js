/*
	Neural Network example by @wesley1989
	v1.3
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


    static transposeMatrix(matrix) {
      let result = new Matrix(matrix.cols, matrix.rows);
      for (let i = 0; i < matrix.rows; i++) {
        for (let j = 0; j < matrix.cols; j++) {
          result.data[j][i] = matrix.data[i][j];
        }
      }
      return result;
    }
  
    static dotProduct(matrix1, matrix2) {
      if (matrix1.cols !== matrix2.rows) {
        return 1;
      } 
      let result = new Matrix(matrix1.rows, matrix2.cols); 
      for (let i = 0; i < result.rows; i++) {
        for (let j = 0; j < result.cols; j++) {
          let sum = 0;
          for (let k = 0; k < matrix1.cols; k++) {
            sum += matrix1.data[i][k] * matrix2.data[k][j];
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
          result.data[i][j] = a.data[i][j] - b.data[i][j]
        }
      }
      return result;
    }
    
    static map(matrix, activation) {
      let result = new Matrix(matrix.rows, matrix.cols);
      for (let i = 0; i < matrix.rows; i++) {
        for (let j = 0; j < matrix.cols; j++) {
          result.data[i][j] = activation(matrix.data[i][j])
        }
      }
      return result;
    }
  
    toArray() {
      let arr = [];
      for (let i = 0; i < this.rows; i++) {
        for (let j = 0; j < this.cols; j++) {
          arr.push(Number((this.data[i][j]).toFixed(2)));
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
          this.data[i][j] = otherFunction(this.data[i][j])
        }
      }
    }
  }


class NeuralNetwork {

  // length of input
  // length of output
  constructor(input_length, output_length) {
    // weights = (input length + output length) times 2 
    // for a better nn training
    this.weights_1 = new Matrix((input_length + output_length) * 2, input_length);
    this.weights_2 = new Matrix(output_length, (input_length + output_length) * 2); 
    this.bias_1 = new Matrix((input_length + output_length) * 2, 1);
    this.bias_2 = new Matrix(output_length, 1);
    this.learning_rate = 0.9;  
  }



  feed_forward(inputs) {
    let inputs_from = Matrix.fromArray(inputs);
    let hidden = Matrix.dotProduct(this.weights_1, inputs_from);
    hidden.add(this.bias_1);
    hidden.map(sigmoid);
    let output = Matrix.dotProduct(this.weights_2, hidden);
    output.add(this.bias_2);
    output.map(sigmoid);
    return output.toArray();
  }

  // feedforward with backpropagation
  train(input_array, target_array) {  
    let inputs = Matrix.fromArray(input_array);

    let hidden = Matrix.dotProduct(this.weights_1, inputs);  
    hidden.add(this.bias_1);
    hidden.map(sigmoid);
    
    let outputs = Matrix.dotProduct(this.weights_2, hidden);
    outputs.add(this.bias_2);
    outputs.map(sigmoid); 

    
    let targets = Matrix.fromArray(target_array);
    let output_errors = Matrix.subtract(targets, outputs);

    let gradients = Matrix.map(outputs,derivativeOfSigmoid);
    gradients.multiply(output_errors);
    gradients.multiply(this.learning_rate);

    let hidden_transposed = Matrix.transposeMatrix(hidden);
  
    let weights_2_deltas = Matrix.dotProduct(gradients, hidden_transposed);



    this.weights_2.add(weights_2_deltas);
    this.bias_2.add(gradients);
    let who_t = Matrix.transposeMatrix(this.weights_2);
    let hidden_errors = Matrix.dotProduct(who_t, output_errors);
    
    let hidden_gradient = Matrix.map(hidden,derivativeOfSigmoid);
    hidden_gradient.multiply(hidden_errors);
    hidden_gradient.multiply(this.learning_rate);

    let inputs_transposed = Matrix.transposeMatrix(inputs);
    let weights_1_deltas = Matrix.dotProduct(hidden_gradient, inputs_transposed);
    this.weights_1.add(weights_1_deltas);
    this.bias_1.add(hidden_gradient);
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

for (let i = 0; i < 1000; i++) {
    var shuffled = shuffle(defined_data)
    for (let j = 0; j < shuffled.length; j++) {
      NN.train(shuffled[j].input,shuffled[j].output)
    }
} 


console.log("[0,1] =>", NN.feed_forward([0,1]));
console.log("[0,0] =>", NN.feed_forward([0,0]));
console.log("[1,0] =>", NN.feed_forward([1,0]));
console.log("[1,1] =>", NN.feed_forward([1,1]));