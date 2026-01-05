# Git & GitHub: Complete Guide

A comprehensive guide to Git and GitHub commands, features, and best practices with detailed examples.

---

## Table of Contents

1. [Introduction](#introduction)
2. [Installation & Setup](#installation--setup)
3. [Basic Git Commands](#basic-git-commands)
4. [Branching](#branching)
5. [Merging & Rebasing](#merging--rebasing)
6. [Remote Repositories](#remote-repositories)
7. [GitHub Features](#github-features)
8. [Advanced Git Workflows](#advanced-git-workflows)
9. [Common Workflows](#common-workflows)
10. [Best Practices](#best-practices)

---

## Introduction

**Git** is a distributed version control system that helps track code changes and collaborate with others.

**GitHub** is a cloud-based hosting service for Git repositories with additional collaboration features.

### Key Benefits

- Track changes over time
- Collaborate with multiple developers
- Revert to previous versions easily
- Maintain code history
- Work on features independently using branches

---

## Installation & Setup

### Install Git

#### Windows
```bash
# Download from https://git-scm.com/download/win
# Or use package manager
choco install git
# Or using winget
winget install Git.Git
```

#### macOS
```bash
# Using Homebrew
brew install git
```

#### Linux
```bash
# Ubuntu/Debian
sudo apt-get install git

# Fedora
sudo dnf install git
```

### Initial Configuration

```bash
# Set your name (global)
git config --global user.name "Your Name"

# Set your email (global)
git config --global user.email "your.email@example.com"

# View all configuration
git config --list

# Set configuration for specific repository (local)
git config user.name "Your Name"
git config user.email "your.email@example.com"
```

---

## Basic Git Commands

### Initialize a Repository

```bash
# Create a new Git repository
git init

# Clone an existing repository
git clone https://github.com/username/repository.git

# Clone to a specific directory
git clone https://github.com/username/repository.git my-folder
```

**Example:**
```bash
git clone https://github.com/torvalds/linux.git
# Downloads the Linux repository to your machine
```

---

### Check Repository Status

```bash
# View status of working directory
git status

# View short status
git status -s
```

**Example Output:**
```
On branch main
Your branch is up to date with 'origin/main'.

Changes not staged for commit:
  (use "git add <file>..." to stage for commit)
        modified:   index.js

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        config.env
```

---

### Staging Changes

```bash
# Stage a specific file
git add filename.js

# Stage all changes
git add .

# Stage all changes in current directory
git add .

# Stage specific file type
git add *.js

# Stage with interactive prompt
git add -i

# Stage part of a file (hunk)
git add -p filename.js
```

**Example:**
```bash
# After modifying index.js and app.js
git add index.js       # Stage only index.js
git add .              # Stage both index.js and app.js
git add *.js           # Stage all JavaScript files
```

---

### Commit Changes

```bash
# Commit with message
git commit -m "Add new feature"

# Commit with detailed message
git commit -m "Add new feature" -m "This feature implements user authentication"

# Stage and commit in one command (tracked files only)
git commit -am "Fix bug in login"

# Amend last commit (add changes to previous commit)
git commit --amend --no-edit

# Amend last commit and change message
git commit --amend -m "New commit message"
```

**Example:**
```bash
git add .
git commit -m "Implement user registration"
# Creates a commit with all staged changes

git commit --amend -m "Implement user registration and email verification"
# Updates the message of the last commit
```

---

### View History

```bash
# View commit history
git log

# View last N commits
git log -n 5

# View one-line commit history
git log --oneline

# View commit history with graph
git log --oneline --graph --all

# View commits by specific author
git log --author="Author Name"

# View commits after specific date
git log --since="2024-01-01"

# View commits before specific date
git log --until="2024-12-31"

# View commits with file changes
git log --stat

# View commits with detailed changes
git log -p

# Search for commits by message
git log --grep="feature"
```

**Example:**
```bash
git log --oneline --graph --all -n 10
# Shows last 10 commits in one-line format with branch visualization

git log --author="John Doe" --since="2024-01-01"
# Shows commits by John Doe from January 2024 onwards
```

---

### View Differences

```bash
# Show changes in working directory
git diff

# Show changes between staging area and repository
git diff --staged

# Show differences between two commits
git diff commit1 commit2

# Show differences in specific file
git diff filename.js

# Show differences between branches
git diff branch1 branch2
```

**Example:**
```bash
git diff
# Shows all uncommitted changes

git diff --staged
# Shows what will be committed

git diff main feature-branch
# Shows differences between main and feature-branch
```

---

## Branching

### Create & Switch Branches

```bash
# Create a new branch
git branch branch-name

# Create and switch to new branch
git checkout -b branch-name

# Create and switch (modern syntax)
git switch -c branch-name

# Switch to existing branch
git checkout branch-name

# Switch branches (modern syntax)
git switch branch-name

# List all branches (local)
git branch

# List all branches (local and remote)
git branch -a

# List branches with last commit info
git branch -v

# Delete a branch
git branch -d branch-name

# Force delete a branch
git branch -D branch-name

# Rename a branch
git branch -m old-name new-name
```

**Example:**
```bash
# Create and work on a new feature
git checkout -b feature/user-authentication

# Make changes and commit
echo "login code" > auth.js
git add auth.js
git commit -m "Add authentication module"

# List all branches
git branch
# Output:
#   feature/user-authentication
# * main

# Switch back to main
git checkout main

# Delete the feature branch
git branch -d feature/user-authentication
```

---

### Branch Naming Conventions

```bash
# Feature branch
git checkout -b feature/user-login

# Bug fix branch
git checkout -b bugfix/navbar-alignment

# Release branch
git checkout -b release/v1.0.0

# Hotfix branch
git checkout -b hotfix/critical-security-patch

# Development branch
git checkout -b develop

# Experimentation branch
git checkout -b experiment/new-ui-design
```

---

## Merging & Rebasing

### Merging Branches

```bash
# Merge a branch into current branch
git merge branch-name

# Merge with commit message
git merge branch-name -m "Merge feature branch"

# Abort an ongoing merge
git merge --abort

# Squash commits before merging
git merge --squash branch-name

# Fast-forward merge only
git merge --ff-only branch-name

# No fast-forward merge
git merge --no-ff branch-name
```

**Example:**
```bash
# Create feature and make changes
git checkout -b feature/dark-mode
echo "dark mode styles" > styles.css
git add styles.css
git commit -m "Add dark mode"

# Merge back to main
git checkout main
git merge feature/dark-mode

# Output:
# Updating abc1234..def5678
# Fast-forward
#  styles.css | 1 +
#  1 file changed, 1 insertion(+)
```

---

### Rebasing

```bash
# Rebase current branch onto another branch
git rebase branch-name

# Interactive rebase (last N commits)
git rebase -i HEAD~3

# Continue after resolving conflicts
git rebase --continue

# Abort rebase
git rebase --abort

# Rebase and keep merge commits
git rebase --preserve-merges branch-name
```

**Example:**
```bash
# On feature branch
git rebase main
# Replays feature branch commits on top of main

# Interactive rebase of last 3 commits
git rebase -i HEAD~3
# Opens editor to reorder, squash, or edit commits
```

---

## Remote Repositories

### Adding & Removing Remotes

```bash
# View remote repositories
git remote

# View remote URLs
git remote -v

# Add a remote repository
git remote add origin https://github.com/username/repo.git

# Add a secondary remote
git remote add upstream https://github.com/original-owner/repo.git

# Remove a remote
git remote remove origin

# Rename a remote
git remote rename origin upstream

# Change remote URL
git remote set-url origin https://github.com/username/new-repo.git

# View remote information
git remote show origin
```

**Example:**
```bash
git remote add origin https://github.com/john/my-project.git
git remote add upstream https://github.com/original/my-project.git

git remote -v
# Output:
# origin    https://github.com/john/my-project.git (fetch)
# origin    https://github.com/john/my-project.git (push)
# upstream  https://github.com/original/my-project.git (fetch)
# upstream  https://github.com/original/my-project.git (push)
```

---

### Push & Pull

```bash
# Push commits to remote branch
git push origin branch-name

# Push all commits
git push

# Push to remote and set upstream
git push -u origin branch-name

# Push tags
git push origin --tags

# Push specific tag
git push origin tag-name

# Delete remote branch
git push origin --delete branch-name

# Pull changes from remote
git pull

# Pull from specific remote and branch
git pull origin main

# Fetch without merging
git fetch

# Fetch from all remotes
git fetch --all
```

**Example:**
```bash
# Create local feature branch
git checkout -b feature/notifications

# Make changes
echo "notification system" > notify.js
git add notify.js
git commit -m "Add notification system"

# Push to remote and set upstream
git push -u origin feature/notifications

# Later, pull updates from remote
git pull origin feature/notifications

# Delete remote branch after merging
git push origin --delete feature/notifications
```

---

## GitHub Features

### Pull Requests (PR)

Pull Requests allow code review and discussion before merging.

**Workflow:**
1. Create a feature branch
2. Push to GitHub
3. Create Pull Request
4. Request reviewers
5. Address feedback
6. Merge to main branch

**Example:**
```bash
# Create and push feature branch
git checkout -b feature/payment-gateway
echo "payment code" > payment.js
git add payment.js
git commit -m "Implement Stripe integration"
git push -u origin feature/payment-gateway

# Now create PR on GitHub website
# Go to: https://github.com/username/repo/pulls
# Click "New Pull Request"
# Select main branch as base
# Add title and description
# Request reviewers
# Submit PR
```

---

### Issues

Issues track bugs, feature requests, and tasks.

**Create Issue via GitHub UI:**
- Navigate to repository
- Click "Issues"
- Click "New Issue"
- Add title and description
- Assign labels, assignees, milestones
- Click "Submit new issue"

**Reference in Commits:**
```bash
# Reference issue in commit message
git commit -m "Fix login bug #123"

# Close issue automatically
git commit -m "Fix login bug - closes #123"

# Reference pull request
git commit -m "Implements feature #456"
```

---

### Labels

Organize issues and PRs with labels.

**Common Labels:**
- `bug` - Something isn't working
- `enhancement` - New feature or request
- `documentation` - Improvements or additions to documentation
- `good first issue` - Good for newcomers
- `help wanted` - Extra attention is needed
- `priority-high` - Urgent
- `priority-low` - Can wait
- `testing` - Needs testing

---

### Milestones

Group issues and PRs into release versions.

**Usage:**
- Create milestone on GitHub
- Add issues to milestone
- Track progress toward release
- Automate workflows based on milestones

---

### Projects

Organize work with kanban-style boards.

**Features:**
- Create custom columns
- Drag and drop cards
- Automate transitions
- Track multiple repositories

---

### Discussions

Community conversations separate from issues.

**Use Cases:**
- Q&A
- Announcements
- General discussions
- Polls and surveys

---

## Advanced Git Workflows

### Stashing Changes

Save work without committing.

```bash
# Stash current changes
git stash

# Stash with description
git stash save "description"

# List all stashes
git stash list

# Apply latest stash
git stash pop

# Apply specific stash
git stash apply stash@{0}

# Keep stash after applying
git stash apply stash@{0}

# Delete a stash
git stash drop stash@{0}

# Delete all stashes
git stash clear

# Show stash contents
git stash show stash@{0}
```

**Example:**
```bash
# Working on feature but need to switch branches
git stash
# Stash has been saved to stash@{0}

# Switch and work on another branch
git checkout hotfix/critical-bug

# After fixing, return to original work
git checkout feature/new-feature
git stash pop
```

---

### Cherry-Picking

Apply specific commits from one branch to another.

```bash
# Cherry-pick a commit
git cherry-pick commit-hash

# Cherry-pick multiple commits
git cherry-pick commit1 commit2 commit3

# Cherry-pick range of commits
git cherry-pick commit1..commit3

# Continue after resolving conflicts
git cherry-pick --continue

# Abort cherry-pick
git cherry-pick --abort
```

**Example:**
```bash
# Found a bug fix in develop that's needed in main
git log develop --oneline
# Output:
# abc1234 Fix critical security issue
# def5678 Add new feature

# Switch to main and cherry-pick fix
git checkout main
git cherry-pick abc1234

# The fix is now in main branch
```

---

### Tagging

Mark specific commits as important (usually for releases).

```bash
# Create lightweight tag
git tag v1.0.0

# Create annotated tag
git tag -a v1.0.0 -m "Version 1.0.0 release"

# Tag previous commit
git tag v1.0.0 commit-hash

# List all tags
git tag

# View tag details
git show v1.0.0

# Push tag to remote
git push origin v1.0.0

# Push all tags
git push origin --tags

# Delete local tag
git tag -d v1.0.0

# Delete remote tag
git push origin --delete v1.0.0
```

**Example:**
```bash
# Ready for release
git tag -a v1.5.0 -m "Release version 1.5.0 - Major stability improvements"

# Push to remote
git push origin v1.5.0

# Users can now download this specific version
```

---

### Reflog (Reference Logs)

Recover lost commits using reference logs.

```bash
# View all reference changes
git reflog

# Show reflog for specific branch
git reflog show branch-name

# Recover deleted branch
git checkout -b restored-branch abc1234

# View reflog for specific time
git reflog --date=short
```

**Example:**
```bash
# Accidentally deleted a branch
git reflog
# Output shows: abc1234 HEAD@{0}: checkout: moving from feature-x to main

# Recover the branch
git checkout -b feature-x abc1234
```

---

## Common Workflows

### Feature Branch Workflow

Standard workflow for feature development.

```bash
# 1. Create feature branch from main
git checkout main
git pull origin main
git checkout -b feature/login-page

# 2. Work on feature
echo "login form" > login.html
git add login.html
git commit -m "Add login form"

echo "login styles" > login.css
git add login.css
git commit -m "Add login page styles"

# 3. Push to remote
git push -u origin feature/login-page

# 4. Create Pull Request on GitHub
# (Request reviewers and address feedback)

# 5. Merge to main (on GitHub or locally)
git checkout main
git pull origin main
git merge feature/login-page

# 6. Delete branch
git branch -d feature/login-page
git push origin --delete feature/login-page
```

---

### Git Flow Workflow

Complex workflow with develop and main branches.

```bash
# Main branches: main (production), develop (development)

# Create release branch
git checkout -b release/v1.0.0 develop

# Make release commits
echo "v1.0.0" > version.txt
git add version.txt
git commit -m "Bump version to 1.0.0"

# Merge to main
git checkout main
git merge --no-ff release/v1.0.0
git tag -a v1.0.0 -m "Release version 1.0.0"

# Merge back to develop
git checkout develop
git merge --no-ff release/v1.0.0

# Delete release branch
git branch -d release/v1.0.0
```

---

### Forking & Contributing to Others' Projects

```bash
# 1. Fork repository on GitHub (click Fork button)

# 2. Clone your fork
git clone https://github.com/YOUR_USERNAME/project.git
cd project

# 3. Add upstream remote
git remote add upstream https://github.com/ORIGINAL_OWNER/project.git

# 4. Create feature branch
git checkout -b feature/improvement
echo "improvement" > feature.js
git add feature.js
git commit -m "Add improvement"

# 5. Push to your fork
git push origin feature/improvement

# 6. Create Pull Request to original repository

# 7. Sync with upstream if needed
git fetch upstream
git rebase upstream/main
```

---

### Handling Merge Conflicts

```bash
# Attempt merge that causes conflicts
git merge feature-branch

# View conflict status
git status

# Edit files to resolve conflicts
# (Files will have markers like <<<<<<<, =======, >>>>>>>)

# After resolving
git add resolved-file.js

# Complete merge
git commit -m "Resolve merge conflicts"

# Or abort if merge went wrong
git merge --abort
```

**Example Conflict Marker:**
```
<<<<<<< HEAD
function calculateTotal(items) {
  return items.reduce((sum, item) => sum + item.price, 0);
}
=======
function calculateTotal(items) {
  let total = 0;
  for (let item of items) {
    total += item.price;
  }
  return total;
}
>>>>>>> feature-branch
```

**Resolution:**
Keep the version you want or combine both. Remove conflict markers.

---

## Best Practices

### Commit Message Guidelines

```bash
# Good: Clear, descriptive, imperative mood
git commit -m "Add user authentication module"
git commit -m "Fix dropdown menu alignment on mobile"
git commit -m "Update API endpoints documentation"

# Bad: Vague or unclear
git commit -m "Fix stuff"
git commit -m "Changed things"
git commit -m "wip"

# Detailed commit message
git commit -m "Implement password reset feature

- Add email verification
- Add password strength validation
- Add token expiration after 24 hours
- Add recovery email template"
```

---

### .gitignore

Prevent unnecessary files from being tracked.

**Example .gitignore:**
```
# Dependencies
node_modules/
venv/
env/

# Environment variables
.env
.env.local
.env.*.local

# IDE
.vscode/
.idea/
*.swp
*.swo

# OS
.DS_Store
Thumbs.db

# Build output
dist/
build/
*.log

# Temporary files
*.tmp
~$*.xlsx
```

---

### Branching Best Practices

```bash
# ✓ Good: Descriptive names
git checkout -b feature/user-profile
git checkout -b bugfix/memory-leak
git checkout -b docs/api-endpoints

# ✗ Bad: Generic or unclear
git checkout -b feature1
git checkout -b fix
git checkout -b test
```

---

### Code Review Practices

1. **Create descriptive Pull Requests** with clear title and description
2. **Request specific reviewers** who understand the code
3. **Link related issues** in the PR description
4. **Keep PRs focused** on single features or fixes
5. **Respond to feedback** promptly and professionally
6. **Test thoroughly** before requesting review

---

### Keeping Repository Clean

```bash
# Delete local branches that no longer exist on remote
git fetch --prune

# Compress repository
git gc

# View large files in history
git rev-list --all --objects | sort -k 2 | tail -10

# Remove large file from history (careful!)
git filter-branch --tree-filter 'rm -f path/to/large/file' HEAD
```

---

### Common Mistakes & Recovery

**Mistake: Committed to wrong branch**
```bash
# Save the commit
git log --oneline -n 1
# Copy the commit hash

# Undo commit on current branch
git reset HEAD~1

# Switch to correct branch
git checkout correct-branch

# Reapply commit
git cherry-pick commit-hash
```

**Mistake: Uncommitted changes before switching branches**
```bash
# Save work
git stash

# Switch branches
git checkout other-branch

# Restore work when ready
git checkout original-branch
git stash pop
```

**Mistake: Pushed wrong commit**
```bash
# Option 1: Create a revert commit (safe for public branches)
git revert commit-hash
git push

# Option 2: Force push (only for private branches!)
git reset HEAD~1
git push --force-with-lease origin branch-name
```

---

### Performance Tips

```bash
# Shallow clone (faster for large repos)
git clone --depth 1 https://github.com/username/repo.git

# Sparse checkout (clone only certain directories)
git clone --sparse https://github.com/username/repo.git

# Clean up repository
git gc --aggressive

# Check repository size
git count-objects -v
```

---

## Useful Aliases

Add to `.gitconfig` for faster commands:

```bash
# Add aliases
git config --global alias.st status
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.unstage 'reset HEAD --'
git config --global alias.last 'log -1 HEAD'
git config --global alias.visual 'log --graph --oneline --all'

# Usage
git st              # Instead of git status
git co main         # Instead of git checkout main
git ci -m "msg"     # Instead of git commit -m "msg"
git visual          # Instead of git log --graph --oneline --all
```

---

## Resources

- [Git Official Documentation](https://git-scm.com/doc)
- [GitHub Docs](https://docs.github.com)
- [Pro Git Book](https://git-scm.com/book/en/v2)
- [GitHub Learning Lab](https://lab.github.com)
- [Atlassian Git Tutorials](https://www.atlassian.com/git/tutorials)

---

## Quick Reference

| Command | Purpose |
|---------|---------|
| `git init` | Initialize repository |
| `git clone <url>` | Clone repository |
| `git status` | Check status |
| `git add .` | Stage all changes |
| `git commit -m "msg"` | Commit changes |
| `git push` | Push to remote |
| `git pull` | Pull from remote |
| `git branch` | List branches |
| `git checkout -b name` | Create new branch |
| `git merge name` | Merge branch |
| `git log` | View history |
| `git diff` | Show changes |

---

**Last Updated:** January 5, 2026

**License:** MIT

---

*This guide covers Git and GitHub essentials. For additional topics, refer to the official documentation.*
