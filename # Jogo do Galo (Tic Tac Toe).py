# Jogo do Galo (Tic Tac Toe)
def print_board(board):
    for row in board:
        print("|".join(row))

def check_winner(board):
    # Verificar linhas, colunas e diagonais
    for row in board:
        if row[0] == row[1] == row[2] != " ":
            return row[0]
    for col in range(3):
        if board[0][col] == board[1][col] == board[2][col] != " ":
            return board[0][col]
    if board[0][0] == board[1][1] == board[2][2] != " " or board[0][2] == board[1][1] == board[2][0] != " ":
        return board[1][1]
    return None

def main():
    board = [[" " for _ in range(3)] for _ in range(3)]
    player = "X"
    for turn in range(9):
        print_board(board)
        print(f"Vez do jogador {player}.")
        row, col = map(int, input("Escolha linha e coluna (0-2): ").split())
        if board[row][col] == " ":
            board[row][col] = player
            winner = check_winner(board)
            if winner:
                print_board(board)
                print(f"O jogador {winner} ganhou!")
                return
            player = "O" if player == "X" else "X"
        else:
            print("Jogada inválida! Tente novamente.")
    print("Empate!")

if __name__ == "__main__":
    main()
