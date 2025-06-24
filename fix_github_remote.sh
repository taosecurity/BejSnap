#!/bin/bash

# Fix GitHub remote script for BejSnap

# Check if username is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <your-github-username>"
    exit 1
fi

USERNAME=$1
REPO_NAME="BejSnap"
REPO_URL="https://github.com/$USERNAME/$REPO_NAME.git"

echo "=== Current Git Remote Configuration ==="
git remote -v

echo "=== Updating Remote URL ==="
git remote set-url origin $REPO_URL
echo "Remote 'origin' updated to: $REPO_URL"

echo "=== Checking Repository Status ==="
git status

echo "=== Checking Commit History ==="
git log --oneline

# Check if we have any commits
if ! git log -1 &>/dev/null; then
    echo "=== No commits found, creating initial commit ==="
    git add .
    git commit -m "Initial commit: BejSnap square screen capture application"
else
    echo "=== Repository already has commits ==="
fi

echo "=== Updating README with your repository URL ==="
# Update the repository URL in the README.md file
sed -i "s|https://github.com/yourusername/BejSnap.git|$REPO_URL|g" README.md

# Check if README was changed
if git diff --quiet README.md; then
    echo "README already contains the correct URL"
else
    echo "README updated with your repository URL"
    git add README.md
    git commit -m "Update README with correct repository URL"
fi

echo ""
echo "Repository setup fixed! Now you can push to GitHub:"
echo "git push -u origin main"
echo ""
echo "Make sure you've created a repository at: $REPO_URL"
echo "Go to: https://github.com/new to create a new repository"
