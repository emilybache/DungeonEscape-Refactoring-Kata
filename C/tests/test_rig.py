import sys, os, pathlib, subprocess

C_FOLDER = pathlib.Path(os.environ.get("TEXTTEST_ROOT", os.getcwd())).parent
DUNGEON_GAME = C_FOLDER / "cmake-build-debug" / "DungeonEscape.exe"
def main(args):
    if not DUNGEON_GAME.exists():
        print(f"could not find executable: {DUNGEON_GAME}")
        return

    single_player = not pathlib.Path("player1_stdin.txt").exists()
    if single_player:
        subprocess.run(DUNGEON_GAME)
    else:
        with open("player1_stdin.txt") as player1_stdin,\
                open("player1_stdout.dungeon", "w") as player1_stdout:
            player1 = subprocess.Popen(DUNGEON_GAME, stdin=player1_stdin, stdout=player1_stdout)

        with open("player2_stdin.txt") as player2_stdin, \
                open("player2_stdout.dungeon", "w") as player2_stdout:
            player2 = subprocess.Popen(DUNGEON_GAME, stdin=player2_stdin, stdout=player2_stdout)

        player1.wait(20)
        player2.wait(20)


if __name__ == "__main__":
    main(sys.argv[1:])