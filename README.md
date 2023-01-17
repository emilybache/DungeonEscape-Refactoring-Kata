Dungeon Escape Refactoring Kata
================================

Try your luck with this Dungeon Escape game. There are two ways to win. Either find your friend Freija who rescues you. Alternatively you can find the other escaped prisonor. Note you will need to run two instances of the game for this second scenario, so you have two escaped prisoners at once.

New Feature
-----------
You have been asked to add a new feature to this game. The hero should be able to pick up the torch and fight the screaming man with it. Add an option to the 'left corridor' - (p)ick up the torch. This should take you to a new list of options - the screaming man is infront of you. Your choices are to run or fight him with the torch. If you run, he kills you. If you fight, he is scared off and runs up the stairs, leaving you back at the same 'left corridor' options menu minus the option to pick up the torch.

The design of this code involves a little more duplication than we're comfortable with. Before you add the new feature you will probably want to refactor. Before you refactor it you will need tests. How can you design tests for a command-line program that needs user input like this one? 

