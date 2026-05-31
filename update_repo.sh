#!/bin/bash
set -e

git switch wheredoesyourmindgo
git fetch upstream

if git merge -X theirs upstream/master; then
  echo "Merged cleanly (upstream favored for conflicts)"
else
  echo "Merge had unresolvable conflicts, resolving manually..."
  for file in $(git diff --name-only --diff-filter=U); do
    if git show ":3:$file" > /dev/null 2>&1; then
      echo "Favoring upstream for $file"
      git checkout --theirs -- "$file"
    elif git show ":2:$file" > /dev/null 2>&1; then
      echo "Keeping ours for $file"
      git checkout --ours -- "$file"
    else
      echo "Removing $file (absent on both sides)"
      git rm "$file"
      continue
    fi
    git add "$file"
  done
  git commit -m "Merge upstream/master favoring upstream"
fi

git push origin wheredoesyourmindgo
