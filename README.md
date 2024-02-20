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

## Resources
- Resource hub: [Ocean's Notion](https://suspectedoceano.notion.site/Minishell-60fef4ece7634fe89086c5154f846c83)
- 42 Cadet's [Medium Article](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)
- Textbook: [Writing your own shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- [Shell syntax](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
- Code Inspiration on [GitHub](https://github.com/maiadegraaf/minishell)

## Project plan
1 - create lexer and basic main
2 - create parser
3 - manage signals (after creating execution)
utils, libraries, header(s) do during the coding

## Notes
### Signals
signal = "If this signal happens, do this instead of what you'd normally do."
				(SIGINT)		(handle_sigint)
SIGINT
signal that is typically sent to a program when the interrupt key (Ctrl + C) 
is pressed. By default, this signal terminates a program.

### Other notes