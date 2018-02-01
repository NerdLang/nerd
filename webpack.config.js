const path = require('path')
const fs = require('fs')
const webpack = require('webpack')


const ENV = (process.env.NODE_ENV || 'development').toLowerCase()
const ENV_PRODUCTION = ENV === 'production'
const ROOT = __dirname

const getBabelConfig = () => {
  const babelrc = JSON.parse(fs.readFileSync(path.join(ROOT, '.babelrc'), 'utf8'))

  // temporary:
  // only webpack needs for modules = false
  babelrc.presets.forEach((preset) => {
    if (Array.isArray(preset) && preset[0] === '@babel/preset-env') {
      preset[1].modules = false
    }
  })

  return babelrc
}

const banner = (buildDate => (env, pkg) => `/**!
 * @build-info ${env} - ${buildDate}

 * @name ${pkg.name}
 * @version ${pkg.version}
 * @author ${pkg.author}
 * @description ${pkg.description}

 * @homepage ${pkg.homepage}
 * @keywords [ ${[pkg.keywords || []].join(', ')} ]

 * @license ${fs.readFileSync(path.join(ROOT, 'LICENSE'), 'utf8')}
**/`)(new Date())

const config = (env, { ENV, ENV_PRODUCTION }) => {
  const packageRoot = env.root;
  const pkg = require(path.join(env.root, 'package.json'))

  return {
    target: 'node',
    devtool: 'source-map',
    context: path.join(packageRoot, 'src'),
    entry: [`./index.js`],
    output: {
      libraryTarget: 'commonjs2',
      path: path.join(packageRoot, 'dist'),
      filename: `index.${ENV}.js`
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
          options: getBabelConfig()
        }
      ]
    },
    resolve: {
      extensions: ['.js']
    },
    plugins: [
      new webpack.BannerPlugin({
        banner: banner(ENV, pkg),
        raw: true
      }),
      new webpack.DefinePlugin({
        VERSION: JSON.stringify(pkg.version),
        ENV: JSON.stringify(ENV),
        ENV_PRODUCTION: JSON.stringify(ENV_PRODUCTION),
        ENV_DEVELOPMENT: JSON.stringify(!ENV_PRODUCTION)
      })
    ]
  }
}

module.exports = (env = {}) => {
  env.root = env.root || ROOT

  const tasks = [
    config(env, { ENV: 'development', ENV_PRODUCTION: false })
  ]

  if (ENV_PRODUCTION) {
    const UglifyEs = require('uglifyjs-webpack-plugin')
    const task = config(env, { ENV, ENV_PRODUCTION })

    if (ENV_PRODUCTION) {
      task.plugins.push(
        new UglifyEs({
          sourceMap: true,
          uglifyOptions: {
            output: {
              quote_style: 1,
              comments: 'some'
            }
          }
        })
      )
    }

    tasks.push(task)
  }

  return Promise.resolve(tasks)
}
