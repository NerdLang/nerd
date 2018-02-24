#!/bin/bash
set -e

#if [ $TRAVIS_PULL_REQUEST ] || [ "$TRAVIS_BRANCH" != "master" ]; then
#  echo "SKIPPING DEPLOY."
#  exit 0
#fi

if [ ! $TRAVIS_TAG ]; then
  echo "BUMPING VERSION: "
  git config user.name "Continuous Integration"
  git config user.password ${GH_TOKEN}

  lerna publish --conventional-commits --yes --skip-npm
  git push --follow-tags origin master

  exit 0
fi

echo "DEPLOYING: "
lerna updated --loglevel=silent --json

lerna exec npm prune --production
lerna exec --loglevel=silent npm publish

