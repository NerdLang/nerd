const path = require('path')
const fs = require('fs')
const webpack = require('webpack')

const ROOT = __dirname
const pkg = require('./package')
const ENV = (process.env.NODE_ENV || 'development').toLowerCase()
const ENV_PRODUCTION = ENV === 'production'
const getBabelConfig = () => {
  const babelrc = JSON.parse(fs.readFileSync('./.babelrc', 'utf8'))

  // temporary:
  // only webpack needs for modules = false
  babelrc.presets.forEach((preset) => {
    if (Array.isArray(preset) && preset[0] === '@babel/preset-env') {
      preset[1].modules = false
    }
  })

  return babelrc
}

const banner = (buildDate => env => `/**!
 * @build-info ${env} - ${buildDate}

 * @name ${pkg.name}
 * @version ${pkg.version}
 * @author ${pkg.author}
 * @description ${pkg.description}

 * @homepage ${pkg.homepage}
 * @keywords [ ${pkg.keywords.join(', ')} ]

 * @license ${fs.readFileSync('./LICENSE', 'utf8')}
**/`)(new Date())

const config = ({ ENV, ENV_PRODUCTION }) => {
  return {
    target: 'node',
    devtool: 'source-map',
    context: path.join(ROOT, 'src'),
    entry: [`./${pkg.name}.js`],
    output: {
      libraryTarget: 'commonjs2',
      path: path.join(ROOT, 'build'),
      filename: `${pkg.name}.${ENV}.js`
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
        banner: banner(ENV),
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
  env.changes = (env.changes || '').split('\n')
  console.log(process.env.NODE_ENV, env);
  return process.exit(0);

  const tasks = [
    config({ ENV: 'development', ENV_PRODUCTION: false })
  ]

  if (ENV_PRODUCTION) {
    const UglifyEs = require('uglifyjs-webpack-plugin')
    const task = config({ ENV, ENV_PRODUCTION })

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
