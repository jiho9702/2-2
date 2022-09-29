import tkinter

root = tkinter.Tk()
root.title("첫번째 라벨")
root.geometry("400x300")

label = tkinter.Label(root, text = "Label String", font = ("Times new Roman", 24))
label.place(x=100, y=100)
root.mainloop()
