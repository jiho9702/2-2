import random

p1_pos = 1
com_pos = 1

def board():
    print("•" * (p1_pos - 1) + ":]" + "•" * (30-p1_pos) + "Goal")
    print("•" * (com_pos - 1) + "=]" + "•" * (30-com_pos) + "Goal")

board()
print("주사위 게임 Start!")

while True:
    #플레이어 턴
    input("Enter를 누르면 여러분의 말이 움직입니다.")
    p1_pos = p1_pos + random.randint(1,6)
    if p1_pos>30:
        p1_pos = 30
    board()
    if p1_pos == 30:
        print("여러분이 승리했습니다.")
        break


    #컴퓨터 턴
    input("Enter를 누르면 컴퓨터의 말이 움직입니다.")
    com_pos = com_pos + random.randint(1, 6)
    if com_pos >30:
        com_pos = 30
    board()
    if com_pos == 30:
        print("컴퓨터가 이겼습니다.")
        break;

print("Game Over")
