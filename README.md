# Minishell_42

it is our first team work in Git, so there is cheat sheet 4 us.
- git checkout -b "name-of-your-branch" = create new local branch and move in
- git push origin "name-of-your-branch" = push the branch on (GitHub)
  - edit the project
- git add . ; git commit -m "message"
  - go to main branch
- git merge "name-of-your-branch"
- git branch -d "name-of-your-branch" = delete local branch
- git push origin --delete "name-of-your-branch" = delete branch from (GitHub)
Im in outdated branch and I want to pull the main branch:
- git checkout "name-of-your-branch" = move to my branch
- git fetch origin = downloads changes from distance branches but does not apply into our local branches
- git reset --hard origin/main = reset our branch to main branch !!this deletes all our local changes
