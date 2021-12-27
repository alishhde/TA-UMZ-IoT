import socket
import tkinter as tk


Host = "192.168.1.104"
Port = 8888
a = 0

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server = (Host, Port)

def On():
    client.sendall("0".encode())
    
    lable = tk.Label(win, text=" O P E N ")
    lable.place(x=70, y=60)
    lable.config(bg="#99CCFF", fg="#003300")

def Off():
    client.sendall("C".encode())
    
    lable = tk.Label(win, text=" C L O S E ")
    lable.place(x=70, y=60)
    lable.config(bg="#99CCFF", fg="#5C0000")
    
win = tk.Tk()
win.title("Lights")
win.geometry("200x300")
win.config(bg="#99CCFF")

openkey = tk.Button(win, text=" O P E N ", command=lambda: On())
openkey.place(x=70, y=110)
openkey.config(bg="#7DFF7D", fg="#003300")

closekey = tk.Button(win, text=" C L O S E ", command=lambda: Off())
closekey.place(x=70, y=140)
closekey.config(bg="#FF6969", fg="#5C0000")


client.connect(server)

tk.mainloop()