#!/bin/bash
set -e

if [ $TRAVIS_PULL_REQUEST ] || [ "$TRAVIS_BRANCH" != "master" ]; then
  exit 0
fi

if [ ! $TRAVIS_TAG ]; then
  echo "BUMP VERSION: "
  lerna publish --conventional-commits --yes --skip-npm
  git push --follow-tags origin master

  exit 0
fi

echo "DEPLOYING: "
lerna updated --loglevel=silent --json

lerna exec npm prune --production
lerna exec --loglevel=silent npm publish

