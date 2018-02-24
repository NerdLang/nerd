/* eslint-disable global-require, import/no-dynamic-require, no-param-reassign */

const path = require('path');
const fs = require('fs');
const webpack = require('webpack');

const NODE_ENV = (process.env.NODE_ENV || 'development').toLowerCase();
const NODE_ENV_PRODUCTION = NODE_ENV === 'production';
const ROOT = __dirname;
const LICENSE = fs.readFileSync(path.join(ROOT, 'LICENSE'), 'utf8');

const build = (config, { ENV, ENV_PRODUCTION }) => {
  const packageRoot = config.root;
  const pkg = require(path.join(config.root, 'package.json'));

  const banner = `/**!
 * @build-info ${config} - ${new Date()}

 * @name ${pkg.name}
 * @version ${pkg.version}
 * @author ${pkg.author}
 * @description ${pkg.description}

 * @homepage ${pkg.homepage}
 * @keywords [ ${[pkg.keywords || []].join(', ')} ]

 * @license ${LICENSE}
**/`;

  return {
    target: 'node',
    devtool: 'source-map',
    context: path.join(packageRoot, 'src'),
    entry: ['./index.js'],
    output: {
      libraryTarget: 'commonjs2',
      path: path.join(packageRoot, 'dist'),
      filename: `index.${ENV}.js`,
    },
    module: {
      rules: [
        // {
        //   enforce: 'pre',
        //   test: /\.js?$/,
        //   loader: 'eslint-loader',
        //   exclude: /node_modules/,
        //   options: {
        //     emitWarning: !ENV_PRODUCTION
        //   }
        // },
        {
          test: /\.js?$/,
          loader: 'babel-loader',
          exclude: /node_modules/,
        },
      ],
    },
    resolve: {
      extensions: ['.js'],
    },
    plugins: [
      new webpack.BannerPlugin({
        banner,
        raw: true,
      }),
      new webpack.DefinePlugin({
        VERSION: JSON.stringify(pkg.version),
        ENV: JSON.stringify(ENV),
        ENV_PRODUCTION: JSON.stringify(ENV_PRODUCTION),
        ENV_DEVELOPMENT: JSON.stringify(!ENV_PRODUCTION),
      }),
    ],
  };
};

module.exports = (env = {}) => {
  env.root = env.root || ROOT;

  const tasks = [
    build(env, { ENV: 'development', ENV_PRODUCTION: false }),
  ];

  if (NODE_ENV_PRODUCTION) {
    const UglifyEs = require('uglifyjs-webpack-plugin');
    const task = build(env, { ENV: 'production', ENV_PRODUCTION: true });

    if (NODE_ENV_PRODUCTION) {
      task.plugins.push(new UglifyEs({
        sourceMap: true,
        uglifyOptions: {
          output: {
            quote_style: 1,
            comments: 'some',
          },
        },
      }));
    }

    tasks.push(task);
  }

  return Promise.resolve(tasks);
};
