import tkinter

key = ""

def key_down(e):
    global key
    key = e.keysym

def main_proc():
    label["text"] = key
    root.after(100, main_proc)

root = tkinter.Tk()
label = tkinter.Label(font = ("Times New Roman", 80))
label.pack()
root.title("키 코드 얻기")
root.bind("<KeyPress>", key_down)
main_proc()
root.mainloop()
