# Publishing BejSnap to GitHub

Follow these steps to publish your BejSnap project to GitHub:

## 1. Initialize Git Repository

You've already created a `.gitignore` file. Now initialize a Git repository in your project directory:

```bash
git init
```

## 2. Add and Commit Your Files

Add all project files to Git and create your initial commit:

```bash
git add .
git commit -m "Initial commit: BejSnap square screen capture application"
```

## 3. Create a GitHub Repository

1. Go to [GitHub](https://github.com/) and sign in to your account
2. Click on the "+" icon in the top-right corner and select "New repository"
3. Name your repository "BejSnap"
4. Add a short description: "A graphical Linux application for taking square screen captures"
5. Keep the repository public (or private if preferred)
6. Do NOT initialize with README, .gitignore, or license as we already have these files
7. Click "Create repository"

## 4. Connect Local Repository to GitHub

After creating the repository, GitHub will show instructions. Use the commands for "push an existing repository":

```bash
git remote add origin https://github.com/YOUR_USERNAME/BejSnap.git
git branch -M main
git push -u origin main
```

Replace `YOUR_USERNAME` with your actual GitHub username.

## 5. Verify Your Repository

After pushing, go to `https://github.com/YOUR_USERNAME/BejSnap` in your browser to see your published project.

## 6. Additional GitHub Features to Consider

Once your project is on GitHub, you might want to:

1. **Add Topics**: Add topics like "qt", "linux", "screenshot", "screen-capture" to make your project more discoverable
2. **Enable GitHub Pages**: To create a project website
3. **Set Up GitHub Actions**: For automated builds and testing
4. **Create Releases**: For versioned releases of your application

## 7. Update README Link

Update the clone URL in your README.md to point to your actual GitHub repository:

```
git clone https://github.com/YOUR_USERNAME/BejSnap.git
```

## 8. Share Your Repository

Share the URL with others so they can use, star, and potentially contribute to your BejSnap application!
