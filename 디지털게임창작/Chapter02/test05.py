import tkinter

def click_btn():
    button["text"] = "clicked"
    
root = tkinter.Tk()
root.title("첫번째 버튼")
root.geometry("800x600")

button = tkinter.Button(root, text = "Button String", font = ("Times new Roman", 24), command = click_btn)
button.place(x=200, y=200)

#root.mainloop() // 위젯  widget
