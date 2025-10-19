import json
import sys


def preprocessing():
    try:
        json_path = sys.stdin.readline().strip()
    except EOFError:
        sys.exit(0)

    with open(json_path) as f:
        automata = json.load(f)

    transition_map = {}

    for t in automata["transitions"]:
        state_from = t["from"]
        letter = t["letter"]
        state_to = t["to"]

        if state_from not in transition_map:
            transition_map[state_from] = {}

        transition_map[state_from][letter] = state_to
    return (
        automata["initial"],
        set(automata["accepting"]),
        transition_map,
    )


def process_word(state, accepting):
    if state in accepting:
        print("yes")
    else:
        print("no")


def main():
    [initial, accepting, transition_map] = preprocessing()
    state = initial
    word_in_progress = False

    while True:
        c = sys.stdin.read(1)
        if not c:
            if word_in_progress:
                process_word(state, accepting)
                break
        if c == "\n":
            if word_in_progress:
                process_word(state, accepting)
            state = initial
            word_in_progress = False
            continue
        else:
            state = transition_map[state][c]
            word_in_progress = True


if __name__ == "__main__":
    main()
