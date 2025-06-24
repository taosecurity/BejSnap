#!/bin/bash

# GitHub publish script for BejSnap

# Check if username is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <your-github-username>"
    exit 1
fi

USERNAME=$1
REPO_NAME="BejSnap"
REPO_URL="https://github.com/$USERNAME/$REPO_NAME.git"

echo "=== Initializing Git Repository ==="
git init

echo "=== Adding files to Git ==="
git add .

echo "=== Creating initial commit ==="
git commit -m "Initial commit: BejSnap square screen capture application"

echo "=== Setting up remote repository ==="
git remote add origin $REPO_URL

echo "=== Setting main branch ==="
git branch -M main

echo "=== Updating README with your repository URL ==="
sed -i "s|https://github.com/yourusername/BejSnap.git|$REPO_URL|g" README.md

echo "=== Adding README change ==="
git add README.md
git commit -m "Update README with correct repository URL"

echo ""
echo "Repository setup complete! To push to GitHub, run:"
echo "git push -u origin main"
echo ""
echo "Make sure you've created a repository at: $REPO_URL"
