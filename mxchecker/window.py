from tkinter import *
from tkinter import ttk
from PIL import ImageTk, Image

class Window:
    def __init__(self):
        self.wndw = Tk()
        self.wndw.title("")
        self.wndw.attributes('-fullscreen', True)
        self.wndw.configure(bg="#D70040")
    def addLabel(self, text, font, bg, fg, x, y):
        label = Label(self.wndw, text=text, font=font, bg=bg, fg=fg)
        label.place(x=x, y=y)
    def addImage(self, path, x, y):
        img = ImageTk.PhotoImage(Image.open(path))
        label = Label(self.wndw, image=img)
        label.image = img
        label.place(x=x, y=y)
    def run(self):
        self.wndw.mainloop()