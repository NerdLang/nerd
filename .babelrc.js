const ENV_TESTING = process.env.NODE_ENV === 'testing';

const config = {
  presets: [
    ["@babel/preset-env", {
      modules: ENV_TESTING && 'commonjs',
      targets: {
        node: "6"
      },
    }]
  ]
};

module.exports = config;
