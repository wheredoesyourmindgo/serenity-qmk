git switch wheredoesyourmindgo
git fetch upstream

# Try squash first
if git merge --squash upstream/master; then
  git commit -m "Squash merge from upstream/master"
else
  echo "Squash failed, falling back to real merge favoring upstream..."
  git reset --hard HEAD
  git merge -X theirs upstream/master || true

  # Now resolve any conflicts by favoring upstream when possible, else keep ours
  for file in $(git diff --name-only --diff-filter=U); do
    if git show ":3:$file" > /dev/null 2>&1; then
      echo "Favoring upstream (theirs) for $file"
      git checkout --theirs -- "$file"
    else
      echo "Keeping ours for $file"
      git checkout --ours -- "$file"
    fi
    git add "$file"
  done

  git commit -m "Merge upstream/master favoring upstream changes with fallback to ours"
fi

git push origin wheredoesyourmindgo
