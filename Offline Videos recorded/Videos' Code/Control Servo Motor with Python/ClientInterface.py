import socket
import tkinter as tk


Host = "172.20.10.8"
Port = 8888
a = 0

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server = (Host, Port)

def On():
    client.sendall("F".encode())
    
    lable = tk.Label(win, text=" F O R W A R D ")
    lable.place(x=70, y=60)
    lable.config(bg="#99CCFF", fg="#003300")

def Off():
    client.send("B".encode())
    
    lable = tk.Label(win, text=" B A C K W A R D ")
    lable.place(x=70, y=60)
    lable.config(bg="#99CCFF", fg="#5C0000")
    
win = tk.Tk()
win.title("Lights")
win.geometry("250x300")
win.config(bg="#99CCFF")

openkey = tk.Button(win, text=" F O R W A R D ", command=lambda: On())
openkey.place(x=75, y=110)
openkey.config(bg="#7DFF7D", fg="#003300")

closekey = tk.Button(win, text=" B A C K W A R D ", command=lambda: Off())
closekey.place(x=70, y=140)
closekey.config(bg="#FF6969", fg="#5C0000")


client.connect(server)

tk.mainloop()