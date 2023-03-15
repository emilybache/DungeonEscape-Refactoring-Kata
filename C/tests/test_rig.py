import sys, os, pathlib, subprocess

C_FOLDER = pathlib.Path(os.environ.get("TEXTTEST_ROOT", os.getcwd())).parent
DUNGEON_GAME_WINDOWS = C_FOLDER / "cmake-build-debug" / "DungeonEscape.exe"
DUNGEON_GAME_POSIX = C_FOLDER / "cmake-build-debug" / "DungeonEscape"


def main(args):
    if os.name == "nt":
        dungeon_game = DUNGEON_GAME_WINDOWS
    else:
        dungeon_game = DUNGEON_GAME_POSIX

    if not dungeon_game.exists():
        print(f"could not find executable: {dungeon_game}")
        return

    single_player = not pathlib.Path("player1_stdin.txt").exists()
    if single_player:
        subprocess.run(dungeon_game)
    else:
        with open("player1_stdin.txt") as player1_stdin,\
                open("player1_stdout.dungeon", "w") as player1_stdout:
            player1 = subprocess.Popen(dungeon_game, stdin=player1_stdin, stdout=player1_stdout)

        with open("player2_stdin.txt") as player2_stdin, \
                open("player2_stdout.dungeon", "w") as player2_stdout:
            player2 = subprocess.Popen(dungeon_game, stdin=player2_stdin, stdout=player2_stdout)

        player1.wait(20)
        player2.wait(20)


if __name__ == "__main__":
    main(sys.argv[1:])