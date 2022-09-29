import tkinter

root = tkinter.Tk()
root.title("첫번째 캔버스")

canvas = tkinter.Canvas(root, width = 400, height = 600, bg = "aqua")
canvas.pack()
root.mainloop
