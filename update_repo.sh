#!/bin/bash
set -e

git switch wheredoesyourmindgo
git fetch upstream

if git rebase -X theirs upstream/master; then
  echo "Rebased cleanly (upstream favored for conflicts)"
else
  echo "Rebase has conflicts, resolving manually..."
  while git rebase --show-current-patch > /dev/null 2>&1; do
    for file in $(git diff --name-only --diff-filter=U); do
      if git show ":3:$file" > /dev/null 2>&1; then
        echo "Favoring upstream for $file"
        git checkout --theirs -- "$file"
      else
        echo "Keeping ours for $file"
        git checkout --ours -- "$file"
      fi
      git add "$file"
    done
    git rebase --continue || break
  done
fi

git push --force-with-lease origin wheredoesyourmindgo
